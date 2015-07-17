#include <stdint.h>
#include "hs/bigint.h"

/**
 * @brief increments the value of a number by 1
 *
 * This is used internally by hs_bigint_inc() and hs_bigint_dec()
 * This function does not check if the numbers themselves are positive nor 
 * negative
 *
 * @param bi A number to increment
 * @return A non zero value on error, zero if the function succeeds
 * @see hs_bigint_inc
 * @see hs_bigint_dec
 */
static int
inc_bits(hs_bigint *bi)
{
  size_t i = 0;
  
  while ( i < bi->size ) {
    /* If the number is less than the minimun, 
       then we can just increment it by 1 */
    if ( bi->data[i] != UINT32_MAX ) {
      ++(bi->data[i]);
      return 0;
    }
    bi->data[i] = 0;
    ++i;
  }
  /* if we still need to increment, we just check if we can upgrade our number*/
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

/**
 * @brief checks if the numbers are meant to be swapped in substraction
 *
 * This is used internally by hs_bigint_sub() and hs_bigint_add()
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @see hs_bigint_add
 * @see hs_bigint_sub
 */
static int
need_sub_inversion(const hs_bigint *a, const hs_bigint *b)
{
  /* we always want the bigger value to be on our left side */
  if ( a->size > b->size ) return 0;
  if ( a->size < b->size ) return 1;
  size_t i = a->size - 1;
  if ( a->data[i] < b->data[i] ) return 1;
  return 0;
}

/**
 * @brief decrements the value of a number by 1
 *
 * This is used internally by hs_bigint_inc() and hs_bigint_dec()
 * This function does not check if the numbers themselves are positive nor 
 * negative
 *
 * @param bi A number to decrement
 * @return A non zero value on error, zero if the function succeeds
 * @see hs_bigint_inc
 * @see hs_bigint_dec
 */
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

/**
 * @brief adds bits between two bigints
 *
 * This is used internally by hs_bigint_add() and hs_bigint_sub()
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @see hs_bigint_add
 * @see hs_bigint_sub
 */
static int
add_bits(hs_bigint *a, const hs_bigint *b)
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

/**
 * @brief subtracts bits between two bigints
 *
 * This is used internally by hs_bigint_add() and hs_bigint_sub()
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @see hs_bigint_add
 * @see hs_bigint_sub
 */
static int
sub_bits(hs_bigint *a, const hs_bigint *b)
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

/**
 * @brief shifts to the right a bigint
 *
 * This is an arithmetic shift and does not check the sign after it finishes
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @see hs_bigint_shr
 * @see hs_bigint_ushr
 */
static int
shift_right(hs_bigint *a, const hs_bigint *b)
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

/**
 * @brief divides two numbers, returning both remainder and the result
 *
 * I don't really know how to do a faster division algorithm, so I take
 * the approach of how the division is defined, by subtracting "b" to "a" until 
 * "a" is less than "b", then return the number of times "b" was 
 * subtracted from "a".
 * The advantage of this is that the division and remainder functions are
 * basically the same. 
 *
 * @param a The left operand
 * @param b The right operand
 *
 * @param accum The variable to store the result
 * @param rem The variable to store ther remainder
 * @return A non zero value on error, zero if the function succeeds
 * @see hs_bigint_div
 * @see hs_bigint_rem
 * @see hs_bigint_divrem
 */
static int
divrem(const hs_bigint *a, const hs_bigint *b, hs_bigint *accum, hs_bigint *rem)
{
  hs_bigint abs_b;
  int accum_negative = a->negative ^ b->negative;
  int rem_negative   = a->negative;
  if (is_zero(b)) return 1;
  if (is_zero(a)) {
    if (hs_bigint_from_u32(accum, 0)) return 1;
    if (hs_bigint_from_u32(rem, 0)) { hs_bigint_end(accum); return 1; }
    return 0;
  };
  if (hs_bigint_from_i32(accum, 0)) return 1;
  if (hs_bigint_copy(b, abs_b)) { hs_bigint_end(&accum); return 1; }
  abs_b->negative = 0;
  if (hs_bigint_copy(a, rem)) { 
    hs_bigint_end(accum); 
    hs_bigint_end(&abs_b); 
    return 1; 
  }
  rem->negative = 0;
  while ( hs_bigint_compare(rem, abs_b) >= 0 )
  {
    if (sub_bits(rem, b)) {  
      hs_bigint_end(accum); 
      hs_bigint_end(rem);
      hs_bigint_end(&abs_b);
      return 1;
    };
    if (hs_bigint_inc(accum)) {
      hs_bigint_end(accum);
      hs_bigint_end(rem);
      hs_bigint_end(&abs_b);
      return 1;
    }
  }
  hs_bigint_end(&abs_b);
  accum->negative = accum_negative;
  rem->negative = rem_negative;
  return 0;
} 

/**
 * @brief checks if a number is zero
 *
 * Both negative (-0) and positive zero (+0) returns as true
 *
 * @param bi A number to check
 * @return A non zero value if bi is zero, zero if not
 */
static int
is_zero(const hs_bigint *bi)
{
  return (bi->size < 2) && (bi->data[0] == 0);
}

/**
 * @brief checks if a number can increase the size of its buffer
 *
 * This is used in order to prevent things like segmentation faults and
 * overflows.
 *
 * @param bi A number to check
 * @return A non zero value on error, zero if the function succeeds
 */
static int
check_size( hs_bigint *bi, const size_t add )
{
  /* If this happens, sorry, there will be an overflow and I can't afford that */
  if (SIZE_MAX - add < bi->size) return 1;
  /* If the number has already reserved the bits, then its okay */
  if (bi->size + add <= bi->capa) return 0;
  /* Let's add those bits */
  size_t new_capa = bi->capa + add;
  uint32_t new_data = realloc(bi->data, new_capa * sizeof(*(bi->data)));
  if (!new_data) return 1;
  bi->data = new_data;
  bi->capa = new_capa;
  return 0;
}

int 
hs_bigint_init(hs_bigint *bi, const size_t capa)
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
hs_bigint_from_i32(hs_bigint *bi, const uint32_t value)
{
  if (hs_bigint_init(bi, 1)) return 1;
  bi->data[0] = value;
  return 0;
}

int
hs_bigint_from_i32(hs_bigint *bi, const int32_t value)
{
  if (hs_bigint_init(bi, 1)) return 1;
  bi->data[0] = (uint32_t)(value & (uint32_t)INT32_MAX);
  bi->negative = value < 0; 
  return 0;
}

int
hs_bigint_from_u64(hs_bigint *bi, const uint64_t value)
{
  if (hs_bigint_init(bi, 2)) return 1;
  bi->data[0] = (uint32_t)(value & (uint64_t)UINT32_MAX);
  bi->data[1] = (uint32_t)(value >> UINT32_MAX);
  return 0;
}

int
hs_bigint_from_i64(hs_bigint *bi, const int64_t value)
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
hs_bigint_copy(const hs_bigint *src, hs_bigint *dst)
{
  if (hs_bigint_init(dst, src->size)) return 1;
  dst->size = src->size;
  dst->negative = src->negative;
  memcpy(dst->data, src->data, src->size * sizeof(*(src->data)));
  return 0;
}

int
hs_bigint_compare(const hs_bigint *a, const hs_bigint *b)
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
hs_bigint_equals(const hs_bigint *a, const hs_bigint *b)
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
hs_bigint_add(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_add(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_sub(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_sub(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_mul(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_mul(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_div(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_div(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_shl(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_shl(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_shr(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_shr(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_ushr(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_ushr(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_and(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_and(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_or(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_or(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_xor(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_xor(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_rem(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_rem(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_mod(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_mod(dst, b)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_neg(const hs_bigint *src, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_neg(dst)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_cpl(const hs_bigint *src, hs_bigint *dst)
{
  if (hs_bigint_copy(a, dst)) return 1;
  if (hs_bigint_self_cpl(dst)) {
    hs_bigint_end(dst);
    return 1;
  };
  return 0;
}

int
hs_bigint_abs(const hs_bigint *src, hs_bigint *dst)
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
hs_bigint_self_add(hs_bigint *a, const hs_bigint *b)
{
  if (a->negative == b->negative) return add_bits(a, b);
  if  (need_sub_inversion(a, b)) {
    a->negative = !a->negative;
    return sub_bits(b, a);
  }
  return sub_bits(a, b);
}

int
hs_bigint_self_sub(hs_bigint *a, const hs_bigint *b)
{
  if (a->negative != b->negative) return add_bits(a, b);
  if  (need_sub_inversion(a, b)) {
    a->negative = !a->negative;
    return sub_bits(b, a);
  }
  return sub_bits(a, b);  
}

/**
 * I don't really know how to do a faster multiplication algorithm, so I take
 * the approach of how the multiplication is defined, by adding "a" a number of 
 * "b" times. 
 * Also, the rule of symbols ( symbol(a) ^ symbol(b) )is applied apart for the 
 * rest of algorithm.
 */
int
hs_bigint_self_mul(hs_bigint *a, const hs_bigint *b)
{
  hs_bigint count, accum, abs_b;
  int negative = a->negative ^ b->negative;
  if (is_zero(a)) return 0;
  if (is_zero(b)) { a->size = 1; a->data[0] = 0; a->negative = negative; return 0; }
  if (hs_bigint_from_u32(&count, 0)) return 1;
  if (hs_bigint_from_u32(&accum, 0)) { hs_bigint_end(&count); return 1; }
  if ( hs_bigint_copy(b, &abs_b) ) {
    hs_bigint_end(&count);
    hs_bigint_end(&accum);
    return 1;
  };
  abs_b->negative = 0;
  while (!hs_bigint_equals(&count, abs_b))
  {
    if (add_bits(&accum, a)) {  
      hs_bigint_end(&count); 
      hs_bigint_end(&accum);
      hs_bigint_end(&abs_b); 
      return 1;
    };
    if (hs_bigint_inc(&count)) {
      hs_bigint_end(&count);
      hs_bigint_end(&accum);
      hs_bigint_end(&abs_b); 
      return 1;
    }
  }
  hs_bigint_end(&count);
  hs_bigint_end(&a);
  hs_bigint_end(&abs_b); 
  a->data = accum->data;
  a->size = accum->size;
  a->negative = negative;
  return 0;
}




 
int
hs_bigint_self_div(hs_bigint *a, const hs_bigint *b)
{
  hs_bigint accum, rem;
  if (divrem(a, b, &accum, &rem) return 1;
  hs_bigint_end(a);
  hs_bigint_end(&rem);
  a->size = accum->size;
  a->data = accum->data;
  a->negative = acumm->negative;
  return 0;
}

/**
 * Shifting left is multiplying by 2 n times,
 * so X << Y is the same as doing X * (2 ^ Y) in this library, the sign is 
 * always preserved to ensure this.
 */
int
hs_bigint_self_shl(hs_bigint *a, const hs_bigint *b)
{
  int carry, t;
  if (b->negative || is_zero(b)) return 1;
  hs_bigint bi;
  if ( hs_bigint_from_u32(&bi, 0) ) return 1;
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
hs_bigint_self_shr(hs_bigint *a, const hs_bigint *b)
{
  if (shift_right(a, b)) return 1;
  /* In signed (logical) right shift, the sign is preserved */
  return 0;
}

int
hs_bigint_self_ushr(hs_bigint *a, const hs_bigint *b)
{
  if (shift_right(a, b)) return 1;
  /* In unsigned (arithmetic) right shift, the sign disappears */
  a->negative = 0;  
  return 0;
}

int
hs_bigint_self_and(hs_bigint *a, const hs_bigint *b)
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
hs_bigint_self_rem(hs_bigint *a, const hs_bigint *b)
{
  hs_bigint accum, rem;
  if (divrem(a, b, &accum, &rem) return 1;
  hs_bigint_end(a);
  hs_bigint_end(&accum);
  a->size = rem->size;
  a->data = rem->data;
  a->negative = rem->negative;
  return 0;
}

int
hs_bigint_self_mod(hs_bigint *a, const hs_bigint *b)
{
  /* TODO: implement (a % b + b) % b  */
  if ( hs_bigint_self_rem(a, b) ) return 1;
  if ( hs_bigint_self_add(a, b) ) return 1;
  if ( hs_bigint_self_rem(a, b) ) return 1;
  return 0;
}

int
hs_bigint_self_or(hs_bigint *a, const hs_bigint *b)
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
hs_bigint_self_xor(hs_bigint *a, const hs_bigint *b)
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

int
hs_bigint_divrem(const hs_bigint *a, const hs_bigint *b, 
                  hs_bigint *res, hs_bigint *rem )
{
  return divrem(a, b, res, rem);
}