#include <ctype.h>
#include <stdio.h>
#include <string.h>

double my_strtod(char *str) {
  double res = 0.0;

  size_t sep_index = strcspn(str, ".");

  for (size_t i = 0; str[i] != 0; ++i) {
    if (i == sep_index) {
      continue;
    }

    if (!isdigit(str[i])) {
      return res;
    }

    double mult = 1;
    if (i < sep_index) {
      for (int j = i; j < sep_index - 1; ++j) {
        mult *= 10;
      }

    } else {
      for (int j = 0; j < i - sep_index; ++j) {
        mult /= 10;
      }
    }

    res += (str[i] - '0') * mult;
  }

  return res;
}

int main() {
  char str[100];
  printf("Enter a number: ");
  scanf("%s", str);

  printf("As a string: %s\n", str);
  printf("As a double: %lf\n", my_strtod(str));
}
