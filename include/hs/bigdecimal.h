/* Humming Script - Collection of libraries to build a scripting language
 * Written in 2015 by Ramiro Rojo <ramiro.rojo.cretta@gmail.com>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright 
 * and related and neighboring rights to this software to the public domain 
 * worldwide. This software is distributed without any warranty.
 * You should have received a copy of the CC0 Public Domain Dedication along 
 * with this software. If not, see 
 * <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
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