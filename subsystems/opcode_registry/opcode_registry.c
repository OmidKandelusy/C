/** standard c header files */
#include <stdio.h>
#include <string.h>

/** library header file */
#include "opcode_registry.h"

/** registry defintion */
static opcode_t opcode_register[CONFIG_OPCODE_REGISTRY_SIZE];

// =============================================================
// helper functions

int get_hashed_index(char *opcode, int *index) {

  if (!index || !opcode)
    return -1;

  uint32_t c = 0;
  for (int i = 0; i < CONFIG_OPCODE_NAME_MAX_LENG; i++) {
    if (opcode[i] == '\0')
      break;
    c += opcode[i];
  }

  uint32_t hash = (c * 31) % CONFIG_OPCODE_REGISTRY_SIZE;

  *index = hash;

  return 0;
}

// ===============================================================
// main routines:

void opcode_registry_init(void) {

  for (int i = 0; i < CONFIG_OPCODE_REGISTRY_SIZE; i++) {
    opcode_register[i].flag = OPC_SLOT_FREE;
    opcode_register[i].cb = NULL;
    memset(&opcode_register[i].name[0], 0, CONFIG_OPCODE_NAME_MAX_LENG);
  }
}

int register_opcode(char *opcode, opcode_callback_t opc_cb) {
  int ret = 0;
  if (!opcode)
    return -1;

  // try the hashed index:
  int index = -1;
  ret = get_hashed_index(opcode, &index);
  if (ret != 0)
    return -2;
  if (index < 0)
    return -3;

  opcode_t current_slot = opcode_register[index];
  int counter = 0;
  int erased_index = -1;
  while (current_slot.flag == OPC_SLOT_TAKEN ||
         current_slot.flag == OPC_SLOT_ERASED) {
    // save the first potential erased index:
    if (current_slot.flag == OPC_SLOT_ERASED && erased_index == -1) {
      erased_index = index;
    }

    // check for duplicate:
    if (strcmp(current_slot.name, opcode) == 0)
      break;

    counter++;
    index = (index + 1) % CONFIG_OPCODE_REGISTRY_SIZE;
    current_slot = opcode_register[index];

    if (counter >= CONFIG_OPCODE_REGISTRY_SIZE) {
      return -4;
    }
  }
  // Althouhg we found a Free slot, improve fragmentation:
  if (erased_index != -1)
    index = erased_index;

  // slot found, updating:
  opcode_register[index].flag = OPC_SLOT_TAKEN;
  opcode_register[index].cb = opc_cb;
  memcpy(opcode_register[index].name, opcode, CONFIG_OPCODE_NAME_MAX_LENG - 1);
  opcode_register[index].name[CONFIG_OPCODE_NAME_MAX_LENG - 1] = '\0';

  return 0;
}

int remove_opcode(char *opcode) {
  if (!opcode)
    return -1;

  // try the hashed index:
  int index = -1;
  int ret = get_hashed_index(opcode, &index);
  if (ret != 0)
    return -2;
  if (index < 0)
    return -3;

  opcode_t current_slot = opcode_register[index];
  int counter = 0;
  while (current_slot.flag == OPC_SLOT_TAKEN) {

    if (strcmp(current_slot.name, opcode) == 0)
      break;

    counter++;
    index = (index + 1) % CONFIG_OPCODE_REGISTRY_SIZE;
    current_slot = opcode_register[index];

    if (counter >= CONFIG_OPCODE_REGISTRY_SIZE) {
      return -4;
    }
  }
  // extra safety check incase search stops where we did not thin about:
  if (opcode_register[index].flag != OPC_SLOT_TAKEN)
    return -5;

  // found, reset the fields:
  opcode_register[index].flag = OPC_SLOT_ERASED;
  opcode_register[index].cb = NULL;
  memset(&opcode_register[index].name[0], 0, CONFIG_OPCODE_NAME_MAX_LENG);

  return 0;
}

int trigger_opcode(char *opcode) {
  if (!opcode)
    return -1;

  // try the hashed index:
  int index = -1;
  int ret = get_hashed_index(opcode, &index);
  if (ret != 0)
    return -2;
  if (index < 0)
    return -3;

  opcode_t current_slot = opcode_register[index];
  int counter = 0;
  while (current_slot.flag != OPC_SLOT_FREE) {

    if (strcmp(current_slot.name, opcode) == 0)
      break;
    counter++;
    index = (index + 1) % CONFIG_OPCODE_REGISTRY_SIZE;
    current_slot = opcode_register[index];

    if (counter >= CONFIG_OPCODE_REGISTRY_SIZE) {
      return -4;
    }
  }
  // extra safety check incase search stops where we did not thin about:
  if (opcode_register[index].flag != OPC_SLOT_TAKEN)
    return -5;

  // trigger the opcode:
  if (opcode_register[index].cb) {
    opcode_register[index].cb();
  }

  return 0;
}