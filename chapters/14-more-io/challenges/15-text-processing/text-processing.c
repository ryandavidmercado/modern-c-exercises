#include <stddef.h>

int search_word(size_t haystack_len, size_t needle_len,
                char const haystack[static haystack_len],
                char const needle[static needle_len]) {

  for (size_t haystack_i; haystack_i < haystack_len; ++haystack_i) {
    for (size_t needle_i;
         needle_i < needle_len && ((haystack_i + needle_i) < haystack_len);
         ++needle_i) {
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
