#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *log = fopen("log.txt", "a");
  if (!log) {
    perror("failed to open log.txt");
    return EXIT_FAILURE;
  }

  if (remove("test.txt")) {
    perror("failed to remove test.txt");
    return EXIT_FAILURE;
  }

  puts("Removed test.txt!");
  fputs("[INFO] ~~~test.txt~~~\n", log);

  if (rename("foo.txt", "bar.txt")) {
    perror("failed to rename foo.txt");
    return EXIT_FAILURE;
  }

  puts("Renamed foo.txt to bar.txt!");
  fputs("[INFO] foo.txt -> bar.txt\n", log);

  return EXIT_SUCCESS;
}
