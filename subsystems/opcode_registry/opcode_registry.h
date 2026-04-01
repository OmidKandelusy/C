#ifndef OPCODE_REG_HEADER_G
#define OPCODE_REG_HEADER_G

/** standard c header files */
#include <stdint.h>

/** registry configuration params */
#define CONFIG_OPCODE_REGISTRY_SIZE 20
#define CONFIG_OPCODE_NAME_MAX_LENG 32

/** opcode slot flag type */
#define OPC_SLOT_TAKEN 0xA0
#define OPC_SLOT_FREE 0xB0
#define OPC_SLOT_ERASED 0xC0


/** opcode callback data type */
typedef int (*opcode_callback_t)(void);

/** a registry entry data type for an opcode */
typedef struct{
    uint8_t flag;
    char name[CONFIG_OPCODE_NAME_MAX_LENG];
    opcode_callback_t cb;
} opcode_t;


// =========================================================
// publicly exposed apis

/**
 * @brief initializes the opcode registry subsystem
*/
void opcode_registry_init(void);

/**
 * @brief registers an opcode to the subsystem
 * @param [in] opcode the opcode we want to register
 * @param [in] opc_cb the associated opcode handler 
 * @return 0 on success, negative value on error
*/
int register_opcode(char *opcode, opcode_callback_t opc_cb);

/**
 * @brief removes an opcode from the subsystem
 * @param [in] opcode the opcode we want to remove
 * @return 0 on success, negative value on error
*/
int remove_opcode(char *opcode);


/**
 * @brief tiggers the handler for the opcode
 * @param [in] opcode the opcode we want to remove
 * @return 0 on success, negative value on error
*/
int trigger_opcode(char *opcode);

#endif