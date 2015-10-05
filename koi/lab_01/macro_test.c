#include <stdio.h>

#define FACT(x) ((x) < 1 ? 1 : (x) * FACT((x) - 1))

#define PLUS(x, y) ((x) + (y))

int factorial(int n) {
  if (n == 0)
    return 1;
  else
    return n * factorial(n - 1);
}


int plus(int x, int y) {
  return x + y;
}

int main()
{
	printf("%d \n", FACT(5) );
	return 0;
}