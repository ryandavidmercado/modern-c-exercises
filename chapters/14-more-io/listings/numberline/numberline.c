#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t *numberline(size_t size, char const text[restrict static size],
                   size_t *restrict nums_len_p, int base);

char *fgetline(size_t size, char s[restrict size], FILE *restrict stream);

int fprintnumbers(FILE *stream, char *const fmt, char *const seperator,
                  size_t len, size_t const *nums);

int main(void) {
  char lbuf[256];

  for (;;) {
    char *line = fgetline(sizeof lbuf, lbuf, stdin);
    if (!line) {
      if (!lbuf[0]) {
        break;
      }

      if (memchr(lbuf, '\n', sizeof lbuf)) {
        fprintf(stderr, "line too long: %s\n", lbuf);
        break;
      } else if (memchr(lbuf, EOF, sizeof lbuf)) {
        return EXIT_FAILURE;
      }

      continue;
    }

    size_t nums_length;
    size_t *nums = numberline(strlen(lbuf) + 1, lbuf, &nums_length, 0);

    if (!nums)
      continue;

    bool err = fprintnumbers(stdout, "%#zX", ",\t", nums_length, nums) < 0;
    if (err)
      return EXIT_FAILURE;

    free(nums);
  }
}

size_t numberline_inner(char const *text, size_t nums[restrict static 1],
                        int base) {
  size_t n = 0;
  for (char *next = nullptr; text[0]; text = next, ++n) {
    nums[n] = strtoul(text, &next, base);
    if (next == text) // no number found; end scanning
      break;
  }

  return n;
}

size_t *numberline(size_t size, char const text[restrict static size],
                   size_t *restrict nums_len_p, int base) {
  size_t n;
  if (!nums_len_p) {
    nums_len_p = &n; /* will be thrown away, but allows our other paths to
                function correctly */
  }

  if (!memchr(text, 0, size)) {
    *nums_len_p = 0;
    return nullptr;
  }

  size_t *nums = malloc(sizeof(size_t[1 + (2 * size) / 3]));
  if (!nums) {
    *nums_len_p = 0;
    return nullptr;
  }

  *nums_len_p = numberline_inner(text, nums, base);
  size_t nums_len_adj = *nums_len_p ? *nums_len_p : 1;

  size_t *nums_adj = realloc(nums, sizeof(size_t[nums_len_adj]));
  if (!nums_adj) {
    return nums;
  }

  return nums_adj;
}

char *fgetline(size_t size, char s[restrict size], FILE *restrict stream) {
  s[0] = 0;

  char *line = fgets(s, size, stream);
  if (!line) {
    return nullptr;
  }

  char *end = strchr(s, '\n');
  if (!end) {
    return nullptr;
  }

  *end = 0;
  return line;
}

int fprintnumbers(FILE *stream, char *const fmt, char *const seperator,
                  size_t len, size_t const *nums) {
  size_t len_printed;

  for (size_t i = 0; i < len; ++i) {
    int len_printed_sub = fprintf(stream, fmt, nums[i]);
    if (len_printed_sub < 1)
      return len_printed_sub;

    len_printed += len_printed_sub;

    if (i != (len - 1)) {
      len_printed_sub = fputs(seperator, stream);
      if (len_printed_sub < 1)
        return len_printed_sub;

      len_printed += len_printed_sub;
    }
  }

  if (fputc('\n', stream) == EOF) {
    return EOF;
  }

  ++len_printed;
  return len_printed;
}
