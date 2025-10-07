#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "text-processing.h"

void print_bracket_expr(bracket_expr *expr);

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

bool test_match_class() {
  bool fail = false;

  match_class_test tests[] = {
    (match_class_test){ .text = "words 39378 more words", .class_start = '0', .class_end = '9', .expected = &(char){'3'}, },
    (match_class_test){ .text = "39378 words more words", .class_start = 'a', .class_end = 'z', .expected = &(char){'w'}, },
    (match_class_test){ .text = "39378 lowercase UPPER",  .class_start = 'A', .class_end = 'Z', .expected = &(char){'U'}, },
    (match_class_test){ .text = "39378",                  .class_start = 'A', .class_end = 'Z', .expected = nullptr,      },
  };

  for (size_t i = 0; i < (sizeof tests / sizeof tests[0]); ++i) {
    match_class_test test = tests[i];
    char const *result = match_class(test.text, test.class_start, test.class_end);

    printf("test_match_class %zu: match_class(\"%s\", '%c', '%c')\n", i + 1, test.text, test.class_start, test.class_end);

    if(!test.expected) {
      if(result) {
        printf("  FAIL: expected nullptr, got '%c'\n", *result);
        fail = true;
      } else {
        printf("  PASS\n");
      }
    } else {
      if(!result) {
        printf("  FAIL: expected '%c', got nullptr\n", *test.expected);
        fail = true;
      } else if(*test.expected != *result) {
        printf("  FAIL: expected '%c', got '%c'\n", *test.expected, *result);
        fail = true;
      } else {
        printf("  PASS\n");
      }
    }
  }

  return fail;
}

bool test_match_class_negated() {
  bool fail = false;

  match_class_test tests[] = {
    (match_class_test){ .text = "words 39378 more words", .class_start = 'a', .class_end = 'z', .expected = &(char){' '}, },
    (match_class_test){ .text = "39378_words more words", .class_start = '0', .class_end = '9', .expected = &(char){'_'}, },
    (match_class_test){ .text = "39378 lowercase UPPER",  .class_start = 'A', .class_end = 'Z', .expected = &(char){'3'}, },
    (match_class_test){ .text = "39378",                  .class_start = '0', .class_end = '9', .expected = nullptr,      },
  };

  for (size_t i = 0; i < (sizeof tests / sizeof tests[0]); ++i) {
    match_class_test test = tests[i];
    char const *result = match_class_negated(test.text, test.class_start, test.class_end);

    printf("test_match_class_negated %zu: match_class_negated(\"%s\", '%c', '%c')\n", i + 1, test.text, test.class_start, test.class_end);

    if(!test.expected) {
      if(result) {
        printf("  FAIL: expected nullptr, got '%c'\n", *result);
        fail = true;
      } else {
        printf("  PASS\n");
      }
    } else {
      if(!result) {
        printf("  FAIL: expected '%c', got nullptr\n", *test.expected);
        fail = true;
      } else if(*test.expected != *result) {
        printf("  FAIL: expected '%c', got '%c'\n", *test.expected, *result);
        fail = true;
      } else {
        printf("  PASS\n");
      }
    }
  }

  return fail;
}

bool test_read_bracket_expr() {
  bool fail = false;

  char const *exprs[] = {
    "[^0-9]",
    "[[:digit:]]",
    "hello"
  };

  for(size_t i = 0; i < (sizeof exprs / sizeof exprs[0]); ++i) {
    print_bracket_expr(read_bracket_expr(exprs[i]));
  }
  
  return fail;
}
