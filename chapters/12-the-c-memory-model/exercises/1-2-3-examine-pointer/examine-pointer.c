#include <stdio.h>
typedef union double_ptr_inspect double_ptr_inspect;
union double_ptr_inspect {
  double *dblptr;
  unsigned char bytes[sizeof(double *)];
};

int main(void) {
  double dbls[] = {
      0.0,
      0.0,
  };

  double_ptr_inspect inspected = {
      .dblptr = &dbls[0],
  };
  double_ptr_inspect inspected_2 = {
      .dblptr = &dbls[1],
  };

  printf("value one is %p\n", inspected.dblptr);
  printf("value two is %p\n", inspected_2.dblptr);
  for (size_t i = 0; i < sizeof(inspected.bytes); ++i) {
    printf("byte[%zu]: %.02X\n", i, inspected.bytes[i]);
  }
}
