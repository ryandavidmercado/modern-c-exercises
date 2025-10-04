#include <limits.h>

enum wide {
  minimal = LONG_MIN,
  maximal = LONG_MAX,
};

// either long or int, depending on whether INT_WIDTH == LONG_WIDTH
// on the target platform
typedef enum wide wide;

int main() { wide t = {}; }
