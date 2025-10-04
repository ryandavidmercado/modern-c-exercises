#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define CLOCK_BUFFER 500

int main(void) {
  char clock_display[CLOCK_BUFFER] = {};

  for (;;) {
    fputs("\033c", stdout);

    time_t current_s = time(0);
    auto current = localtime(&current_s);

    strftime(clock_display, CLOCK_BUFFER, "%B %e %Y | %r", current);
    printf("%s\n", clock_display);

    sleep(1);
  }
}
