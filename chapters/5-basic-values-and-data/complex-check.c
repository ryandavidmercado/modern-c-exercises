#include <stdio.h>
#include <tgmath.h>

int main(void) {
  complex int test = CMPLX(5, 3);
  int real = creal(test);

  printf("%d\n", real);
}
