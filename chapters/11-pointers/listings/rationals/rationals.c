#include "rationals.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

size_t get_gcd(size_t a, size_t b) {
  if (b == 0) {
    return a;
  } else {
    return get_gcd(b, a % b);
  }
}

rat rat_get(signed sign, size_t num, size_t denom) {
  rat ret = {.sign = (sign < 0), .num = num, .denom = denom};

  return ret;
}

rat rat_get_normal(rat x) {
  size_t gcd = get_gcd(x.num, x.denom);

  return (rat){.sign = x.sign, .num = x.num / gcd, .denom = x.denom / gcd};
}

rat rat_get_extended(rat x, size_t f) {
  return (rat){.sign = x.sign, .num = x.num * f, .denom = x.denom * f};
}

rat rat_get_prod(rat x, rat y) {
  rat ret = {
      .sign = (x.sign != y.sign),
      .num = x.num * y.num,
      .denom = x.denom * y.denom,
  };

  return rat_get_normal(ret);
}

rat rat_get_sum(rat x, rat y) {
  size_t c = get_gcd(x.denom, y.denom);
  size_t mult_x = y.denom / c;
  size_t mult_y = x.denom / c;

  x = rat_get_extended(x, mult_x);
  y = rat_get_extended(y, mult_y);
  assert(x.denom == y.denom);

  if (x.sign == y.sign) {
    x.num += y.num;
  } else if (x.num > y.num) {
    x.num -= y.num;
  } else {
    x.num = y.num - x.num;
    x.sign = !x.sign;
  }

  return rat_get_normal(x);
}

void rat_destory(rat *rp) {
  if (rp) {
    *rp = (rat){};
  }
}

rat *rat_init(rat *rp, signed sign, size_t num, size_t denom) {
  rp->sign = sign;
  rp->num = num;
  rp->denom = denom;

  return rp;
}

rat *rat_normalize(rat *rp) {
  if (rp) {
    *rp = rat_get_normal(*rp);
  }

  return rp;
}

rat *rat_extend(rat *rp, size_t f) {
  if (rp) {
    *rp = rat_get_extended(*rp, f);
  }

  return rp;
}

rat *rat_sumup(rat *rp, rat y) {
  if (rp) {
    *rp = rat_get_sum(*rp, y);
  }

  return rp;
}

rat *rat_rma(rat *rp, rat x, rat y) {
  return rat_sumup(rp, rat_get_prod(x, y));
}

char const *rat_print(size_t len, char tmp[len], rat const *x) {
  tmp[0] = x->sign ? '-' : '+';
  sprintf(tmp + 1, "%zu/", x->num);
  sprintf(tmp + strlen(tmp), "%zu", x->denom);

  return tmp;
}

char const *rat_normalize_print(size_t len, char tmp[len], rat const *x) {
  rat normalized = rat_get_normal(*x);
  return rat_print(len, tmp, &normalized);
}

int main(void) {
  rat input_rat = {};

  char input[100] = {};

  printf("Enter a rational [-](x/y): ");
  scanf("%s", input);

  if (input[0] == '-') {
    input_rat.sign = true;
    sscanf(input + 1, "%zd /%zd", &input_rat.num, &input_rat.denom);
  } else {
    sscanf(input, "%zd /%zd", &input_rat.num, &input_rat.denom);
  }

  rat simplified = rat_get_normal(input_rat);

  printf("simplified: %s\n",
         rat_print(50, malloc(sizeof(char) * 50), &simplified));

  printf("simplified: %s\n",
         rat_normalize_print(50, malloc(sizeof(char) * 50), &input_rat));
}
