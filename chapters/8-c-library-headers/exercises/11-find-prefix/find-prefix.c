#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

size_t find_prefix(char *str, size_t start, char *prefix) {
  size_t ret = 0;
  for (size_t i = 0; str[i + start] != 0 && prefix[i] != 0; ++i) {
    if (tolower(str[i + start]) != tolower(prefix[i])) {
      return ret;
    }

    ++ret;
  }

  return ret;
}

void test_find_prefix() {
  size_t ans = find_prefix("  0Bdkd", 2, "0b");
  if (ans != 2) {
    printf("[FAIL] find_prefix(\"  0Bdkd\", 2, \"0b\") = %zu, expected 2\n",
           ans);
  } else {
    puts("[PASS] find_prefix(\"  0Bdkd\", 2, \"0b\") = 2");
  }

  ans = find_prefix("04123", 0, "0x");
  if (ans != 1) {
    printf("[FAIL] find_prefix(\"04123\", 0, \"0x\") = %zu, expected 1\n", ans);
  } else {
    puts("[PASS] find_prefix(\"04123\", 0, \"0x\") = 1");
  }

  ans = find_prefix("  dkd", 1, "0b");
  if (ans != 0) {
    printf("[FAIL] find_prefix(\"  dkd\", 1, \"0b\") = %zu, expected 0\n", ans);
  } else {
    puts("[PASS] find_prefix(\"  dkd\", 1, \"0b\") = 0");
  }
}

int main(void) { test_find_prefix(); }
