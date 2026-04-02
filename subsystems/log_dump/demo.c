/** standard c header files */
#include "logdump.h"

int main(void) {

  log_dump_init();

  int counter = 0;
  for (int i = 0; i < 5; i++) {
    counter++;
    log_inf("this is the %d-th test message \n\r", counter);
  }

  log_dump();

  return 0;
}