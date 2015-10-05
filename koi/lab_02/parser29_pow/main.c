/* main.c */

#include "global.h"

int main(void)
{
  init();
  stack_init();
  parse();
  getchar();
  exit(0);    /*  successful termination  */
}
