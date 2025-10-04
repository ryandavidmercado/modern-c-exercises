#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  BUFFER_SIZE = 32,
};

int main(int argc, char *argv[argc + 1]) {
  int ret = EXIT_SUCCESS;

  bool show_lines = (argc >= 2) && (strcmp(argv[1], "-n") == 0);
  bool from_stdin = argc < 2 || (argc == 2 && show_lines);

  char buffer[BUFFER_SIZE] = {};
  unsigned long long line = 0;

  size_t iteration_start = (show_lines && !from_stdin) ? 2 : 1;
  size_t iteration_end = from_stdin ? SIZE_MAX : argc;

  for (size_t i = iteration_start; i < iteration_end; (from_stdin ? i : ++i)) {
    FILE *input_file = from_stdin ? stdin : fopen(argv[i], "r");
    char *stream_name = from_stdin ? "stdin" : argv[i];

    if (!input_file) {
      fprintf(stderr, "failed to open %s", stream_name);
      perror(0);
      ret = EXIT_FAILURE;
    }

    bool prev_had_newline = true;
    while (fgets(buffer, BUFFER_SIZE, input_file)) {
      if (prev_had_newline && show_lines) {
        ++line;
        printf("%6llu  ", line);
      }

      printf("%s", buffer);

      prev_had_newline = strchr(buffer, '\n');
    }

    if (!feof(input_file)) {
      fprintf(stderr, "error while reading %s", stream_name);
      perror(0);
      ret = EXIT_FAILURE;
    }

    if (!from_stdin) {
      fclose(input_file);
    }
  }

  return ret;
}
