/* error.c */

#include "global.h"

void error(char* m)  /* generates all error messages  */
{
  fprintf(stderr, "error: %s\n", m);
  exit(EXIT_FAILURE);  /*  unsuccessful termination  */
}
