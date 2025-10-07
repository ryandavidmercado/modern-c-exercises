#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text-processing.h"

int search_word(char const needle[static 1], char const haystack[static 1]) {
  size_t haystack_len = strlen(haystack);
  size_t needle_len = strlen(needle);

  for (size_t haystack_i = 0; haystack[haystack_i]; ++haystack_i) {
    for (size_t needle_i = 0; needle[needle_i] && haystack[haystack_i + needle_i]; ++needle_i) {
      if (haystack[haystack_i + needle_i] != needle[needle_i]) {
        break;
      }

      if(!needle[needle_i + 1]) {
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

char const *match_class(char const *text, char const class_start, char const class_end) {
  if(class_start >= class_end) {
    return nullptr;
  }

  for(size_t i = 0; text[i]; ++i) {
    if(text[i] >= class_start && text[i] <= class_end) {
      return text + i; 
    }
  }

  return nullptr;
}

char const *match_class_negated(char const *text, char const class_start, char const class_end) {
  if(class_start >= class_end) {
    return nullptr;
  }

  for(size_t i = 0; text[i]; ++i) {
    if(text[i] < class_start || text[i] > class_end) {
      return text + i; 
    }
  }

  return nullptr;
}

/**
  * Returns a pointer to the next character after the expression,
  * otherwise nullptr.
  *
  * Modifies *bracket_type with the type of the read expression.
  */
char const *read_posix_expr(char const *text, bracket_type *bracket_type_p) {
  char const *alpha = ":alpha:]]";
  char const *digit = ":digit:]]";

  if(strncmp(text, alpha, strlen(alpha)) == 0) {
    *bracket_type_p = ALPHA;
    return text + strlen(alpha);
  } else if(strncmp(text, digit, strlen(digit)) == 0) {
    *bracket_type_p = DIGIT;
    return text + strlen(digit);
  }

  return nullptr;
}

bracket_expr *read_bracket_expr(char const *text) {
  bracket_expr *expr = malloc(sizeof(bracket_expr));
  *expr = (bracket_expr){ .type = CHARACTER_CLASS };

  char const *current = text;
  
  // [
  if(!current || *current != '[') {
    free(expr);
    return nullptr;
  }

  ++current;
  if(!*current) {
    free(expr);
    return nullptr;
  }

  switch(*current) {
    case '^': { // [^
      expr->negated = true; 
      ++current;
      break;
    }
    case '[': { // [[
      char const *next_char = read_posix_expr(current + 1, &expr->type);
      if(!next_char) {
        free(expr);
        return nullptr;
      }
      expr->next_char = next_char;
      return expr;
    }
  }

  // [CHAR_START
  expr->char_start = *current;
  ++current;

  // [CHAR_START-
  if(!*current || *current != '-') {
    free(expr);
    return nullptr;
  }
  ++current;

  // [CHAR_START-CHART_END
  if(!*current) {
    free(expr);
    return nullptr;
  }
  expr->char_end = *current;
  ++current;

  // [CHAR_START-CHART_END]
  if(!*current || *current != ']') {
    free(expr);
    return nullptr;
  }

  ++current;
  expr->next_char = current;

  return expr;
}

int main(void) {
  fputs("\033c", stdout);

  bool fail = test_search_word() 
    || test_find_and_replace() 
    || test_match_class() 
    || test_match_class_negated()
    || test_read_bracket_expr();

  putchar('\n');

  return fail ? EXIT_FAILURE : EXIT_SUCCESS;
}
