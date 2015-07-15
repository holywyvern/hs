#ifndef HS_BIGINT_H
#define HS_BIGINT_H

#include <stdint.h>
#include <stdlib.h>


typedef struct 
{
  uint32_t *data;
  size_t    size;
  size_t    capa;
  int       negative;
} hs_bigint;

int 
hs_bigint_init(hs_bigint *bi, size_t capa);

void
hs_bigint_end(hs_bigint *bi);

int 
hs_bigint_copy(hs_bigint *src, hs_bigint *dst);

int
hs_bigint_compare(hs_bigint *a, hs_bigint *b);

int
hs_bigint_equals(hs_bigint *a, hs_bigint *b);

int
hs_bigint_add(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigint_sub(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigint_mul(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigint_div(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigint_shl(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigint_shr(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigint_and(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigint_or(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigint_xor(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigint_rem(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigint_mod(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigint_neg(hs_bigint *src, hs_bigint *dst);

int
hs_bigint_cpl(hs_bigint *src, hs_bigint *dst);

int
hs_bigint_abs(hs_bigint *src, hs_bigint *dst);

int
hs_bigint_inc(hs_bigint *bi);

int
hs_bigint_dec(hs_bigint *bi);

int
hs_bigint_self_add(hs_bigint *a, hs_bigint *b);

int
hs_bigint_self_sub(hs_bigint *a, hs_bigint *b);

int
hs_bigint_self_mul(hs_bigint *a, hs_bigint *b);

int
hs_bigint_self_div(hs_bigint *a, hs_bigint *b);

int
hs_bigint_self_shl(hs_bigint *a, hs_bigint *b);

int
hs_bigint_self_shr(hs_bigint *a, hs_bigint *b);

int
hs_bigint_self_and(hs_bigint *a, hs_bigint *b);

int
hs_bigint_self_rem(hs_bigint *a, hs_bigint *b);

int
hs_bigint_self_mod(hs_bigint *a, hs_bigint *b);

int
hs_bigint_self_or(hs_bigint *a, hs_bigint *b);

int
hs_bigint_self_xor(hs_bigint *a, hs_bigint *b);

int
hs_bigint_self_neg(hs_bigint *bi);

int
hs_bigint_self_abs(hs_bigint *bi);

int
hs_bigint_self_cpl(hs_bigint *bi);

#endif /* HS_BIGINT_H */
