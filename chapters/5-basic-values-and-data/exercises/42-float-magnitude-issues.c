#include <stdio.h>
#include <stdlib.h>
int main(void) {
  // algebraically, these should be equal.
  double first = 1.0e-13 + 1.0e-13;
  double second = (1.0e-13 + (1.0e-13 + 1.0)) - 1.0;

  printf("first:\t%e\n", first);
  printf("second:\t%e\n", second);

  return EXIT_SUCCESS;
}
