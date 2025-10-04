#include "text-processor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

blob *blob_split(blob *base, size_t split_point) {
  if (!base) {
    return base;
  }

  size_t len = strlen(base->text);

  if (split_point >= len) {
    return base;
  }

  size_t len_a = split_point;
  size_t len_b = len - split_point;

  char *text_a = malloc(sizeof(char) * len_a);
  char *text_b = malloc(sizeof(char) * len_b);

  strncpy(text_a, base->text, len_a);
  strncpy(text_b, base->text + split_point, len_b);

  blob *b = malloc(sizeof(blob));
  blob *old_next = base->next;

  base->next = b;
  b->prev = base;

  base->text = text_a;
  b->text = text_b;

  b->next = old_next;
  if (old_next) {
    old_next->prev = b;
  }

  return base;
}

blob *blob_join(blob *base) {
  if (!base || !(base->next)) {
    return base;
  }

  size_t text_new_len = strlen(base->text) + strlen(base->next->text) + 1;
  char *text_new = malloc(sizeof(char) * text_new_len);

  strcat(text_new, base->text);
  strcat(text_new, base->next->text);

  base->text = text_new;
  base->next = base->next->next;
  if (base->next) {
    base->next->prev = base;
  }

  return base;
}

blob *blob_create(const char *text) {
  blob *root = nullptr;
  blob *current = root;

  for (size_t i = 0, j = 0; j == 0 || text[j - 1]; ++j) {
    if ((text[j] == '\n' || !text[j]) && (j > i)) {
      if (!current) {
        root = malloc(sizeof(blob));
        current = root;
      } else {
        current->next = malloc(sizeof(blob));
        current->next->prev = current;
        current = current->next;
      }

      /* Container for text[i] to text[j] (inclusive, unless !text[j]).
       * Consider i = 2, j = 4 --
       * We want to include text[2], text[3], text[4]: 3 elements,
       * or 4 - 2 (j - i) + 1.
       *
       * We add an extra 1 for including the null terminator.
       */
      size_t len = j - i + (text[j] ? 1 : 0);
      current->text = malloc(sizeof(char) * (len + 1));

      strncpy(current->text, text + i, len);

      i = j + 1;
    }
  }

  return root;
}

void blob_print(blob *root) {
  blob *current = root;

  while (current) {
    printf("%s", current->text);
    current = current->next;
  }
}

void blob_print_debug(blob *root) {
  blob *current = root;

  size_t i = 0;
  while (current) {
    printf("BLOB %4zu: \"%s\"\n", i, current->text);
    current = current->next;
    ++i;
  }
}

int main() {
  blob *new_blob =
      blob_create("this is some text that I would\n like to split at index 8.");

  blob_print_debug(blob_join(blob_join(blob_split(new_blob, 20))));
}
