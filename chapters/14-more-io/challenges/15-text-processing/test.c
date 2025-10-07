#include <stddef.h>
#include <stdio.h>
#include <string.h>

int search_word(char const needle[static 1], char const haystack[static 1]);
char *find_and_replace(char const *text, char const *find, char const *replace);

struct search_test {
  char const *needle;
  char const *haystack;
  int expected;
};
typedef struct search_test search_test;

bool test_search_word() {
  bool fail = false;

  char const *haystack_main = "try to find the needle in this haystack";
  search_test tests[] = {
      (search_test){ .haystack = haystack_main, .needle = "needle", .expected = 16 },
      (search_test){ .haystack = haystack_main, .needle = "nope", .expected = -1 },
      (search_test){ .haystack = "", .needle = "larger", .expected = -1 }
  };

  for (size_t i = 0; i < (sizeof tests / sizeof tests[0]); ++i) {
    char const *needle = tests[i].needle;
    char const *haystack = tests[i].haystack;
    int expected = tests[i].expected;

    printf("test_search_word %zu: search_word(\"%s\", \"%s\")\n", i + 1, needle, haystack);
    int result = search_word(needle, haystack);

    if (result != expected) {
      printf("  FAIL: expected %d, got %d\n", expected, result);
      fail = true;
    } else {
      printf("  PASS\n");
    }
  }

  return fail;
}

struct replace_test {
  char const *text;
  char const *find;
  char const *replace;
  char const *expected;
};
typedef struct replace_test replace_test;

bool test_find_and_replace() {
  bool fail = false;
  replace_test tests[] = {
      (replace_test){ .text = "the old text", .find = "old", .replace = "new", .expected = "the new text" },            // test for same-length replacement
      (replace_test){ .text = "the old text", .find = "old", .replace = "newer", .expected = "the newer text" },        // test for longer replacement
      (replace_test){ .text = "the oldest text", .find = "oldest", .replace = "new", .expected = "the new text" },      // test for shorter replacement
      (replace_test){ .text = "nothing to replace", .find = "foo", .replace = "bar", .expected = "nothing to replace"}, // test for no replacement
  };

  for (size_t i = 0; i < (sizeof tests / sizeof tests[0]); ++i) {
    replace_test test = tests[i];
    char const *result = find_and_replace(test.text, test.find, test.replace);

    printf("test_find_and_replace %zu: find_and_replace(\"%s\", \"%s\", \"%s\")\n", i + 1, test.text, test.find, test.replace);

    if (strcmp(test.expected, result) != 0) {
      fail = true;
      printf("  FAIL: expected \"%s\", got \"%s\"\n", test.expected, result);
    } else {
      printf("  PASS\n");
    }
  }

  return fail;
}
