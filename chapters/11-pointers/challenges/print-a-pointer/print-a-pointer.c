#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  for (size_t i = 0; i < 100; ++i) {
    int *ptr_some_value = malloc(sizeof(int));
    *ptr_some_value = 100;

    printf("The address of some_value %d is %p\n", *ptr_some_value,
           (void *)ptr_some_value);

    free((void *)ptr_some_value);
  }
}
