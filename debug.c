#include "debug.h"
#include <stdio.h>

void dbgUARTVal(unsigned int input) {
  printf("UART: [%d]\n", input);
}

void dbgPanic(unsigned int input) {
  printf("PANIC: [%d]\n", input);
}

void dbgOutputVal(unsigned int outVal) {
  printf("OUTPUT: [%d]\n", outVal);
}
