#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_word(char const needle[static 1], char const haystack[static 1]) {
  size_t haystack_len = strlen(haystack);
  size_t needle_len = strlen(needle);

  for (size_t haystack_i = 0; haystack_i < haystack_len; ++haystack_i) {
    for (size_t needle_i = 0; needle_i < needle_len && ((haystack_i + needle_i) < haystack_len); ++needle_i) {
      if (haystack[haystack_i + needle_i] != needle[needle_i]) {
        break;
      }

      if (needle_i == (needle_len - 1)) {
        return haystack_i;
      }
    }
  }

  return -1;
}

char *find_and_replace(char const *text, char const *find, char const *replace) {
  int found_idx = search_word(find, text);

  if (found_idx < 0) {
    char *new = malloc(strlen(text) + 1);
    if (!new) {
      return nullptr;
    }

    strcpy(new, text);
    return new;
  }

  int len_diff = strlen(replace) - strlen(find);
  char *new = malloc(strlen(text) + 1 + len_diff);
  if (!new) {
    return nullptr;
  }

  strncat(new, text, found_idx);
  strcat(new, replace);
  strcat(new, text + found_idx + strlen(find));

  return new;
}

bool test_search_word();
bool test_find_and_replace();

int main(void) {
  fputs("\033c", stdout);

  test_search_word();
  test_find_and_replace();

  putchar('\n');
}
