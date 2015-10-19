/* error.c */

#include "global.h"

void error(const char* m)  /* generates all error messages  */
{
  fprintf(stderr, "error: %s\n", m);
  exit(EXIT_FAILURE);  /*  unsuccessful termination  */
}
