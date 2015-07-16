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
need_sub_inversion(hs_bigint *a, hs_bigint *b)
{
  if ( a->size > b->size ) return 0;
  if ( a->size < b->size ) return 1;
  size_t i = a->size - 1;
  if ( a->data[i] < b->data[i] ) return 1;
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

  
static int
add_bits(hs_bigint *a, hs_bigint *b)
{
  uint32_t carry = 0;
  uint64_t tmp;
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
    tmp = (uint64_t)a->data[i] + (uint64_t)b->data[i];
    carry = (uint32_t)(tmp >> 32);
    a->data[i] = (uint32_t)( tmp && (uint64_t)UINT32_MAX );
  }
  while (carry) {
    if (size < a->size) {
      tmp = (uint64_t)a->data[i] + (uint64_t)b->data[i];
      carry = (uint32_t)(tmp >> 32);
      a->data[i] = (uint32_t)( tmp && (uint64_t)UINT32_MAX );
      ++size;
    } else {
      if ( check_size(a, 1) ) return 1;
      ++(a->size);
    }
  }
  return 0;
}

static int
sub_bits(hs_bigint *a, hs_bigint *b)
{
  uint64_t tmp;
  uint32_t carry;
  size_t i, j, size;
  size = b->size;
  carry = 0;
  for (i = 0; i < size; ++i)
  {
    if ( a->data[i] < b->data[i] ) {
      for ( j = i + 1; j < a->size; ++j ) {
        if (a->data[j] != 0) {
          --(a->data[j]);
          j = a->size - 1;
        } else
          a->data[j] = UINT32_MAX;
      }
      tmp = (uint64_t)a->data[i] + (uint64_t)UINT32_MAX - (uint64_t)b->data[i];
      a->data[i] = (uint32_t)tmp;
    } else 
      a->data[i] -= b->data[i];
    
  }
}

static int
shift_right(hs_bigint *a, hs_bigint *b)
{
  int carry;
  int t;  
  if (b->negative || is_zero(b)) return 1;
  hs_bigint bi;
  if ( hs_bigint_from_i32(&bi, 0) ) return 1;
  while ( !hs_bigint_equals(&bi, b) )
  {
    carry = 0;
    for (size_t i = 0; i < a->size; ++i) {
      t = a->data[i] & 1;
      a->data[i] = a->data[i] >> 1;
      if (carry)
        a->data[i] |= 0x80000000;
      carry = t;
    }
    /* Passing down the sign, */
    if (a->negative) a->data[a->size - 1] |= 0x80000000;
    if ( (a->data[a->size - 1] == 0) && a->size > 1) --(a->size);
    if ( hs_bigint_inc(&bi) ) {
      hs_bigint_end(&bi);
      return 1;
    }
  }
  hs_bigint_end(&bi);
  return 0;  
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

int
hs_bigint_from_i32(hs_bigint *bi, uint32_t value)
{
  if (hs_bigint_init(bi, 1)) return 1;
  bi->data[0] = value;
  return 0;
}

int
hs_bigint_from_i32(hs_bigint *bi, int32_t value)
{
  if (hs_bigint_init(bi, 1)) return 1;
  bi->data[0] = (uint32_t)(value & (uint32_t)INT32_MAX);
  bi->negative = value < 0; 
  return 0;
}

int
hs_bigint_from_u64(hs_bigint *bi, uint64_t value)
{
  if (hs_bigint_init(bi, 2)) return 1;
  bi->data[0] = (uint32_t)(value & (uint64_t)UINT32_MAX);
  bi->data[1] = (uint32_t)(value >> UINT32_MAX);
  return 0;
}

int
hs_bigint_from_i64(hs_bigint *bi, int64_t value)
{
  if (hs_bigint_from_u64(bi, (value & (uint64_t)INT64_MAX) )) return 1;
  bi->negative = value < 0; 
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
  size_t j, k;
  if (is_zero(a) && is_zero(b)) return 0;
  if (a->negative != b->negative) {
    if (a->negative) {
      return -1;
    }
    return 1;
  }
  if (a->negative) {
    if (a->size > b->size) return -1;
    if (a->size < b->size) return  1;
    for (j = 0; j < a->size; ++j) {
      k = a->size - j - 1;
      if (a->data[k] > b->data[k]) return -1;
      if (a->data[k] < b->data[k]) return  1;
    } 
    return 0;
  } 
  if (a->size > b->size) return  1;
  if (a->size < b->size) return -1;
  for (j = 0; j < a->size; ++j) {
    k = a->size - j - 1;
    if (a->data[k] > b->data[k]) return  1;
    if (a->data[k] < b->data[k]) return -1;
  } 
  return 0;  
}

int
hs_bigint_equals(hs_bigint *a, hs_bigint *b)
{
  if (is_zero(a) && is_zero(b)) return 1;
  if (a->negative != b->negative) return 0;
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
hs_bigint_ushr(hs_bigint *a, hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_ushr(dst, b)) {
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
  if  (need_sub_inversion(a, b)) {
    a->negative = !a->negative;
    return sub_bits(b, a);
  }
  return sub_bits(a, b);
}

int
hs_bigint_self_sub(hs_bigint *a, hs_bigint *b)
{
  if (a->negative != b->negative) return add_bits(a, b);
  if  (need_sub_inversion(a, b)) {
    a->negative = !a->negative;
    return sub_bits(b, a);
  }
  return sub_bits(a, b);  
}

int
hs_bigint_self_mul(hs_bigint *a, hs_bigint *b)
{
  a->negative = a->negative ^ b->negative;
  /* TODO: implement */
  return 1;
}

int
hs_bigint_self_div(hs_bigint *a, hs_bigint *b)
{
  a->negative = a->negative ^ b->negative;
  /* TODO: implement */
  return 1;  
}

int
hs_bigint_self_shl(hs_bigint *a, hs_bigint *b)
{
  int carry, t;
  if (b->negative || is_zero(b)) return 1;
  hs_bigint bi;
  if ( hs_bigint_from_i32(&bi, 0) ) return 1;
  while ( !hs_bigint_equals(&bi, b) )
  {
    carry = 0;
    for (size_t i = 0; i < a->size; ++i) {
      t = a->data[i] & 0x80000000;
      a->data[i] = a->data[i] << 1;
      if (carry)
        a->data[i] |= 1;
      carry = t;
    }
    /* Passing down the sign, if there was some carry after the shift */
    a->negative = carry ? 1 : 0;
    if ( (a->data[a->size - 1] == 0) && a->size > 1) --(a->size);
    if ( hs_bigint_inc(&bi) ) {
      hs_bigint_end(&bi);
      return 1;
    }
  }
  hs_bigint_end(&bi);
  return 0;  
}

int
hs_bigint_self_shr(hs_bigint *a, hs_bigint *b)
{
  if (shift_right(a, b)) return 1;
  /* In signed (logical) right shift, the sign is preserved */
  return 0;
}

int
hs_bigint_self_ushr(hs_bigint *a, hs_bigint *b)
{
  if (shift_right(a, b)) return 1;
  /* In unsigned (arithmetic) right shift, the sign disappears */
  a->negative = 0;  
  return 0;
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
  /* TODO: implement */
  return 1;
}

int
hs_bigint_self_mod(hs_bigint *a, hs_bigint *b)
{
  /* TODO: implement */
  return 1;
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
  size_t i;
  for (size_t i = 0; i < bi->size; ++i) {
    bi->data[i] = ~bi->data[i];
  }
  if (inc_bits(bi)) return 1;
  if (bi->data[bi->size - 1] == 1) {
    --(bi->size);
    bi->data[bi->size] = 0;
    bi->negative = !bi->negative;
  }
  return 0;
}
