#include "ndsi/panic.h"

void OS_Panic() {

  iprintf("AHHHHHHHHHH!\n");

  while (1) {

    OS_DisableInterrupts();

    OS_Halt();

  }

}
