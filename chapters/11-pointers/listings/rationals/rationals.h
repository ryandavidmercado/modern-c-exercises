#include <stdlib.h>

struct rat {
  bool sign;
  size_t num;
  size_t denom;
};
typedef struct rat rat;

rat rat_get(signed sign, size_t num, size_t denom);
rat rat_get_normal(rat x);
rat rat_get_extended(rat x, size_t f);
rat rat_get_prod(rat x, rat y);
rat rat_get_sum(rat x, rat y);

void rat_destroy(rat *rp);
rat *rat_init(rat *rp, signed sign, size_t num, size_t denom);
rat *rat_normalize(rat *rp);
rat *rat_extend(rat *rp, size_t f);
rat *rat_sumup(rat *rp, rat y);
rat *rat_rma(rat *rp, rat x, rat y);

char const *rat_print(size_t len, char tmp[len], rat const *x);
char const *rat_normalize_print(size_t len, char tmp[len], rat const *x);
rat *rat_dotproduct(rat rp[static 1], size_t n, rat const A[n], rat const B[n]);
