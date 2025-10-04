#include <float.h>
#include <stddef.h>
#include <stdio.h>

enum corvid { chough, raven, magpie, jay, corvid_num };

#define CORVID_NAME                                                            \
  (char const *const[corvid_num]) {                                            \
    [chough] = "chough", [raven] = "raven", [magpie] = "mapgie",               \
    [jay] = "jay",                                                             \
  }

int main() {
  for (size_t i = 0; i < corvid_num; i++) {
    printf("Corvid %zu is the %s\n", i, CORVID_NAME[i]);
  }

  printf("Arbitrary access: a beautiful %s\n", CORVID_NAME[raven]);
}
