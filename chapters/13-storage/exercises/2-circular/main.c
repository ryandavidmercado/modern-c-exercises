#include "circular.h"
#include <stdio.h>

/**
 * @returns bool - true if the test passed, otherwise false
 */
bool test_circular_append() {
  circular *c = circular_new(3);

  // we should be able to append N elements (where N is circular's cap)
  if (circular_append(c, 1.0) == nullptr) {
    return false;
  } else if (circular_append(c, 2.0) == nullptr) {
    return false;
  } else if (circular_append(c, 3.0) == nullptr) {
    return false;
  }

  // each element should be stored (grabbable at its respective position)
  if (*circular_element(c, 0) != 1.0) {
    return false;
  } else if (*circular_element(c, 1) != 2.0) {
    return false;
  } else if (*circular_element(c, 2) != 3.0) {
    return false;
  }

  // appending to a full buffer should fail
  if (circular_append(c, 4.0) != nullptr) {
    return false;
  }

  return true;
}

bool test_circular_pop() {
  circular *c = circular_new(3);

  circular_append(c, 1.0);
  circular_append(c, 2.0);
  circular_append(c, 3.0);

  if (circular_pop(c) != 1.0 || *circular_element(c, 0) != 2.0) {
    return false;
  } else if (circular_pop(c) != 2.0 || *circular_element(c, 0) != 3.0) {
    return false;
  } else if (circular_pop(c) != 3.0 || circular_element(c, 0) != nullptr) {
    printf("at second\n");
    return false;
  } else if (circular_pop(c) != 0.0) {
    return false;
  }

  return true;
}

bool test_circular_getlength() {
  circular *c = circular_new(3);

  if (circular_getlength(c) != 0) {
    return false;
  }

  circular_append(c, 1.0);
  if (circular_getlength(c) != 1) {
    return false;
  }

  circular_append(c, 2.0);
  if (circular_getlength(c) != 2) {
    return false;
  }

  circular_append(c, 3.0);
  if (circular_getlength(c) != 3) {
    return false;
  }

  // can't append past capacity
  circular_append(c, 4.0);
  if (circular_getlength(c) != 3) {
    return false;
  }

  return true;
}

int main() {
  printf("circular_append\t\t: %s\n", test_circular_append() ? "PASS" : "FAIL");
  printf("circular_pop\t\t: %s\n", test_circular_pop() ? "PASS" : "FAIL");
  printf("circular_getlength\t: %s\n",
         test_circular_getlength() ? "PASS" : "FAIL");
}
