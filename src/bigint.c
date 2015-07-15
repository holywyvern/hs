#include <stdint.h>
#include "hs/bigint.h"

static int
inc_bits(hs_bigint *bi)
{
  size_t i = 0;
  while ( i < bi->size ) {
    if ( bi->data[i] != UINT32_MAX ) {
      ++(bi->data[i]);
      return 0;
    }
    bi->data[i] = 0;
    ++i;
  }
  if ( check_size(bi, 1) ) 
  {
    while (i > 0) {
      bi->data[i - 1] = UINT32_MAX;
    }
    return 1;
  }
  bi->data[bi->size] = 1;
  bi->size += 1;
  return 0;
}

static int
dec_bits(hs_bigint *bi)
{
  size_t i = 0;
  while ( i < bi->size ) {
    if ( bi->data[i] != 0 ) {
      --(bi->data[i]);
      if (bi->data[i] == 0 && i > 0) bi->size -= 1;
      return 0;
    }
    bi->data[i] = UINT32_MAX;
    ++i;
  }
  return 0;
}

/* preventing overflow at all costs */
/* Given a value X + Y >= Z, I can get the part below z as:
 * Z - (Z - X) - (Z - Y) 
 * This formula is the result of simplification,
 * Z = UINT32_MAX + 1 (which I can't use this way, and I must avoid overflows) 
 */  
#define OVERFLOW_ROLLOUT(a, b)                                                 \
  ( UINT32_MAX - ( ( UINT32_MAX - (a) ) + 1 + ( UINT32_MAX - (b) ) ) )

  
int
add_bits(hs_bigint *a, hs_bigint *b)
{
  uint32_t carry = 0;
  uint32_t tmp;
  uint32_t t;
  size_t size = a->size > b->size ? b->size : a->size;
  if (a->size < b->size)
    if ( check_size(a, b->size - a->size) )
    {
     return 1;
    }    
    for (size_t j = a->size; j < b->size; ++j) {
      a->data[j] = b->data[j];
    }
    a->size = b->size;
  }    
  for (size_t i = 0; i < size; ++i) {
    if (UINT32_MAX - carry >= a->data[i]) {
      a->data[i] += carry;
      carry = 0;
    } else {
      a->data[i] = carry - 1;
      carry = 1;
    }
    tmp = b->data[i];
    if (UINT32_MAX - tmp >= a->data[i]) {
      a->data[i] += tmp;
    } else {
      carry += 1;
      a->data[i] = OVERFLOW_ROLLOUT(a->data[i], tmp);
    }
  }
  while (carry) {
    if (size < a->size) {
      if ( UINT32_MAX - carry >= a->data[size])
      {
        a->data[size] += carry;
        carry = 0;
      } else {
        tmp = a->data[size];
        a->data[size] = OVERFLOW_ROLLOUT(carry, tmp);
        carry = 1;
      }
      ++size;
    }
  }
}

int
sub_bits(hs_bigint *a, hs_bigint *b)
{
  
}

static int
is_zero(hs_bigint *bi)
{
  return (bi->size < 2) && (bi->data[0] == 0);
}

static int
check_size( hs_bigint *bi, size_t add )
{
  if (SIZE_MAX - add < bi->size) return 1;
  if (bi->size + add <= bi->capa) return 0;
  size_t new_capa = bi->capa * 2 + 1;
  uint32_t new_data = realloc(bi->data, new_capa * sizeof(*(bi->data)));
  if (!new_data) return 1;
  bi->data = new_data;
  bi->capa = new_capa;
  return 0;
}

int 
hs_bigint_init(hs_bigint *bi, size_t capa)
{
  if (capa == 0) return 1;
  bi->data = malloc(capa * sizeof(*(bi->data)));
  if (!bi->data) return 1;
  bi->size = 1;
  bi->data[0] = 0;
  bi->negative = 0;
  bi->capa = capa;
  return 0;
}

void
hs_bigint_end(hs_bigint *bi)
{
  if (bi->data)
    free(bi->data);
}

int 
hs_bigint_copy(hs_bigint *src, hs_bigint *dst)
{
  if (hs_bigint_init(dst, src->size)) return 1;
  dst->size = src->size;
  dst->negative = src->negative;
  memcpy(dst->data, src->data, src->size * sizeof(*(src->data)));
  return 0;
}

int
hs_bigint_compare(hs_bigint *a, hs_bigint *b)
{
  if (a->neg != b->neg) {
    if (a->neg) {
      return -1;
    }
    return 1;
  }
  if (a->negative) {
    if (a->size > b->size) return -1;
    if (a->size < b->size) return  1;
    for (size_t j = 0; j < a->size; ++j) {
      size_t k = a->size - j - 1;
      if (a->data[k] > b->data[k]) return -1;
      if (a->data[k] < b->data[k]) return  1;
    } 
    return 0;
  } 
  if (a->size > b->size) return  1;
  if (a->size < b->size) return -1;
  for (size_t j = 0; j < a->size; ++j) {
    size_t k = a->size - j - 1;
    if (a->data[k] > b->data[k]) return  1;
    if (a->data[k] < b->data[k]) return -1;
  } 
  return 0;  
}

int
hs_bigint_equals(hs_bigint *a, hs_bigint *b)
{
  if (a->neg != b->neg) return 0;
  if (a->size != b->size) return 0;
  for (size_t i = 0; i < a->size; ++i) {
    if (a->data[i] != b->data[i]) return 0;
  }
  return 1;
}

int
hs_bigint_add(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_add(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_sub(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_sub(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_mul(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_mul(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_div(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_div(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_shl(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_shl(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_shr(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_shr(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_and(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_and(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_or(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_or(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_xor(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_xor(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_rem(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_rem(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_mod(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_mod(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_neg(hs_bigint *src, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_neg(dst)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_cpl(hs_bigint *src, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_cpl(dst)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_abs(hs_bigint *src, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_abs(dst)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_inc(hs_bigint *bi)
{
  if ( bi->negative && !is_zero(bi) ) return dec_bits(bi);
  bi->negative = 0;
  return inc_bits(bi);
}

int
hs_bigint_dec(hs_bigint *bi)
{
  size_t i = 0;
  if ( bi->negative && !is_zero(bi) ) return inc_bits(bi);
  bi->negative = 1;
  return dec_bits(bi);
}

int
hs_bigint_self_add(hs_bigint *a, hs_bigint *b)
{
  if (a->negative == b->negative) return add_bits(a, b);
  return sub_bits(a, b);
}

int
hs_bigint_self_sub(hs_bigint *a, hs_bigint *b)
{
  if (a->negative == b->negative) return sub_bits(a, b);
  return add_bits(a, b);
}

int
hs_bigint_self_mul(hs_bigint *a, hs_bigint *b)
{
  
}

int
hs_bigint_self_div(hs_bigint *a, hs_bigint *b)
{
  
}

int
hs_bigint_self_shl(hs_bigint *a, hs_bigint *b)
{
  
}

int
hs_bigint_self_shr(hs_bigint *a, hs_bigint *b)
{

}

int
hs_bigint_self_and(hs_bigint *a, hs_bigint *b)
{
  size_t size = a->size < b->size ? a->size : b->size;
  a->size = size;
  for (size_t i = 0; i < size; ++i) {
    a->data[i] = a->data[i] & b->data[i];
  }
  a->size = size;
  return 0;
}

int
hs_bigint_self_rem(hs_bigint *a, hs_bigint *b)
{

}

int
hs_bigint_self_mod(hs_bigint *a, hs_bigint *b)
{
  
}

int
hs_bigint_self_or(hs_bigint *a, hs_bigint *b)
{
  size_t size = a->size < b->size ? a->size : b->size;
  if (a->size < b->size) {
    if (check_size(a, b->size - a->size) {
      return 1;
    }
  }
  for (size_t i = 0; i < size; ++i) {
    a->data[i] = a->data[i] | b->data[i];
  }
  for (size_t j = a->size; j < b->size; ++j) {
    a->data[j] = b->data[j];
  }  
  a->size = b->size;
  return 0;
}

int
hs_bigint_self_xor(hs_bigint *a, hs_bigint *b)
{
  size_t size = a->size < b->size ? a->size : b->size;
  if (a->size < b->size) {
    if (check_size(a, b->size - a->size) {
      return 1;
    }
  }
  for (size_t i = 0; i < size; ++i) {
    a->data[i] = a->data[i] ^ b->data[i];
  }
  for (size_t j = a->size; j < b->size; ++j) {
    a->data[j] = b->data[j];
  }  
  a->size = b->size;
  return 0;
}

int
hs_bigint_self_neg(hs_bigint *bi)
{
  bi->negative = !bi->negative;
  return 0;
}

int
hs_bigint_self_abs(hs_bigint *bi)
{
  bi->negative = 0;
  return 0;
}

int
hs_bigint_self_cpl(hs_bigint *bi)
{
  
}
