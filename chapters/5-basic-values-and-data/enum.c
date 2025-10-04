#include <stddef.h>
#include <stdio.h>

enum corvid {
  magpie,
  raven,
  jay,
  corvid_num,
};

char const *const bird[corvid_num] = {
    [raven] = "raven",
    [magpie] = "magpie",
    [jay] = "jay",
};

int main() {
  for (size_t i = 0; i < corvid_num; i++) {
    printf("Corvid %zu is the %s\n", i, bird[i]);
  }
}
