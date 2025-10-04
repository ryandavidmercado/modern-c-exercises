#include <stdio.h>
static_assert('z' - 'a' == 25, "lowercase alphabetic characters not contigous");
static_assert('Z' - 'A' == 25, "uppercase alphabetic characters not contigous");

#include <ctype.h>

/* Converts an alphanumeric digit to an unsigned */
/* '0' ... '9'  =>  0 ..  9u */
/* 'A' ... 'Z'  => 10 .. 35u */
/* 'a' ... 'z'  => 10 .. 35u */
/* Other values => Greater */

unsigned hexatridecimal(int a) {
  if (isdigit(a)) {
    /* This is guaranteed to work: decimal digits are consecutive,
     * and isdigit is not locale-dependent. */
    return a - '0';
  } else {
    a = toupper(a);

    /* Returns value >= 36 if not Latin uppercase */
    return (isupper(a)) ? 10 + (a - 'A') : -1;
  }
}

int main(void) {
  for (;;) {
    printf("Enter a character: ");
    char n = getchar();
    printf("value: %d\n", hexatridecimal(n));
    getchar();
  }
}
