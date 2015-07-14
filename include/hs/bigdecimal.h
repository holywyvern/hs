#ifndef HS_BIGDECIMAL_H
#define HS_BIGDECIMAL_H

#include <stdint.h>
#include <stdlib.h>

int 
hs_bigdecimal_init(hs_bigint *bi, size_t capa);

void
hs_bigdecimal_end(hs_bigint *bi);

int 
hs_bigdecimal_copy(hs_bigint *src, hs_bigint *dst);

int
hs_bigdecimal_compare(hs_bigint *a, hs_bigint *b);

int
hs_bigdecimal_equals(hs_bigint *a, hs_bigint *b);

int
hs_bigdecimal_add(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigdecimal_sub(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigdecimal_mul(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigdecimal_div(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigdecimal_neg(hs_bigint *src, hs_bigint *dst);

int
hs_bigdecimal_abs(hs_bigint *src, hs_bigint *dst);

int
hs_bigdecimal_inc(hs_bigint *bi);

int
hs_bigdecimal_dec(hs_bigint *bi);

int
hs_bigdecimal_self_add(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigdecimal_self_sub(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigdecimal_self_mul(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

int
hs_bigdecimal_self_div(hs_bigint *a, hs_bigint *b, hs_bigint *dst);


int
hs_bigdecimal_self_neg(hs_bigint *bi);

int
hs_bigdecimal_abs(hs_bigint *bi);



#endif /* HS_BIGINT_H */