#include "circular.h"
#include <string.h>

circular *circular_new(size_t len);
void circular_delete(circular *c);

[[deprecated("implementation")]]
circular *circular_init(circular *c, size_t cap) {
  if (!c)
    return c;

  if (!cap) {
    *c = (circular){};
    return c;
  }

  *c = (circular){.cap = cap, .tab = malloc(sizeof(double) * cap)};
  if (!c->tab) {
    // Allocation failed.
    c->cap = 0;
  }

  return c;
}

[[deprecated("implementation")]]
void circular_destroy(circular *c) {
  if (!c)
    return;

  free(c->tab);
  circular_init(c, 0);
}

[[deprecated("implementation")]]
static size_t circular_getpos(circular const c[static 1], size_t pos) {
  if (!c->cap)
    return pos;

  return (pos + c->start) % c->cap;
}

[[deprecated("implementation")]]
double *circular_element(circular const *c, size_t pos) {
  if (!c || (pos >= c->cap) || (pos >= c->len))
    return nullptr;

  size_t pos_circular = circular_getpos(c, pos);
  return &c->tab[pos_circular];
}

[[deprecated("implementation")]]
circular *circular_append(circular *c, double value) {
  if (!c || c->len >= c->cap) {
    return nullptr;
  }

  // 0 0 1 0 0
  size_t next_pos = circular_getpos(c, c->start + c->len);
  c->tab[next_pos] = value;
  ++c->len;

  return c;
}

[[deprecated("implementation")]]
double circular_pop(circular *c) {
  if (!c || c->len == 0) {
    return 0.0;
  }

  double ret = c->tab[c->start];
  c->start = (c->start + 1) % c->cap;
  --c->len;

  return ret;
}

[[deprecated("implementation")]]
size_t circular_getlength(circular const *c) {
  return c->len;
}

[[deprecated("implementation")]] [[nodiscard(
    "returned pointer replaces function argument")]]
circular *circular_resize(circular *c, size_t nlen) {
  if (!c || c->len > nlen)
    return nullptr;

  size_t len = c->len;
  size_t olen = c->cap;
  if (olen == nlen)
    return c;

  size_t ostart = circular_getpos(c, 0);
  size_t nstart = ostart;

  double *otab = c->tab;
  double *ntab = realloc(c->tab, sizeof(double[nlen]));

  if (!ntab)
    return nullptr;

  if (ostart + len > olen) {
    size_t ulen = olen - ostart;
    size_t llen = len - ulen;
    if (llen <= (nlen - olen)) {
      memcpy(ntab + olen, ntab, llen * sizeof(double));
    } else {
      nstart = nlen - ulen;
      memmove(ntab + nstart, ntab + ostart, ulen * sizeof(double));
    }
  }

  *c = (circular){
      .cap = nlen,
      .start = nstart,
      .len = c->len,
      .tab = ntab,
  };

  return c;
}
