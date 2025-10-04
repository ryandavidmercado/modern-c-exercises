#include <stdbit.h>
#if __STDC_ENDIAN_NATIVE__ == __STDC_ENDIAN_LITTLE__
typedef signed hello;
#endif

#include <stdio.h>

typedef union unsignedInspect unsignedInspect;
union unsignedInspect {
  unsigned val;
  unsigned char bytes[sizeof(unsigned)];
};

unsignedInspect twofold = {
    .val = 0xAABBCCDD,
};

int main(void) {
  printf("value is 0x%.08X\n", twofold.val);
  for (size_t i = 0; i < sizeof twofold.bytes; ++i) {
    printf("byte[%zu]: 0x%.02hhX\n", i, twofold.bytes[i]);
  }
}
