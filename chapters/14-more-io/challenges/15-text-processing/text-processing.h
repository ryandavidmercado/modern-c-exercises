#include <stdio.h>
bool test_search_word();
bool test_find_and_replace();
bool test_match_class();
bool test_match_class_negated();
bool test_read_bracket_expr();

enum bracket_type { CHARACTER_CLASS, ALPHA, DIGIT };
typedef enum bracket_type bracket_type;

struct bracket_expr {
  bracket_type type;
  char char_start;
  char char_end;
  char const *next_char;
  bool negated;
};
typedef struct bracket_expr bracket_expr;

inline void print_bracket_expr(bracket_expr *expr) {
  if(!expr) {
    printf("----\nNULL\n----\n");
    return;
  }

  char const *type_str;
  switch(expr->type) {
    case CHARACTER_CLASS:
      type_str = "CHARACTER_CLASS";
      break;
    case ALPHA:
      type_str = "ALPHA";
      break;
    case DIGIT:
      type_str = "DIGIT";
      break;
  }

  printf("----\n");
  printf("type: %s\n", type_str);
  printf("char_start: '%c'\n", expr->char_start);
  printf("char_end: '%c'\n", expr->char_end);
  printf("negated: %s\n", expr->negated ? "TRUE" : "FALSE");
  printf("----\n");
}

int search_word(char const needle[static 1], char const haystack[static 1]);
char *find_and_replace(char const *text, char const *find, char const *replace);
char const *match_class(char const *text, char const class_start, char const class_end); 
char const *match_class_negated(char const *text, char const class_start, char const class_end); 
bracket_expr *read_bracket_expr(char const *text);

struct search_test {
  char const *needle;
  char const *haystack;
  int expected;
};
typedef struct search_test search_test;

struct replace_test {
  char const *text;
  char const *find;
  char const *replace;
  char const *expected;
};
typedef struct replace_test replace_test;

struct match_class_test {
  char const *text;
  char const class_start;
  char const class_end;
  char const *expected;
};
typedef struct match_class_test match_class_test;
