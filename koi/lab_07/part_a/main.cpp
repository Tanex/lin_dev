/* main.c */

#include "global.h"

StackMachine sm;

int main(void)
{
  init();
  parse();
  exit(0);    /*  successful termination  */
}
