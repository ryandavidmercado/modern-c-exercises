#include <limits.h>
#include <stdint.h>
#define FLOCK_MAGPIE 1U
#define FLOCK_RAVEN 2U
#define FLOCK_JAY 4U
#define FLOCK_CHOUGH 8U
#define FLOCK_EMPTY 0U
#define FLOCK_FULL 15U

int main(void) {
  unsigned flock = FLOCK_EMPTY;

  bool something = true;

  if (something) {
    flock |= FLOCK_JAY; // add JAY to flock
  }

  // check flock for COUGH
  if (flock & FLOCK_CHOUGH) {
    // do something chough specific
  }
}
