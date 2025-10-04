#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#if UINT128_WIDTH
constexpr char msg[] = "Up to 128";
#elif UINT64_WIDTH
constexpr char msg[] = "Up to 64";
#else
constexpr char msg[] = "No large unsigned ints";
#endif

int main() {
  printf("%s\n", msg);

  int8_t num = UINT8_C(27);
  printf("%" PRIu8 "\n", num);
}
