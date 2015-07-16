#ifndef HS_BIGINT_H
#define HS_BIGINT_H

#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Contains the structure information of bigint types.
 *
 * Bigintegers are on any platform an array 32 bits integers.
 * I try to write the code of this to be as endianness independent as it can.
 * While negative zero and positive zero can coexist because this works as 
 * a complement of one and not a complement of two. The functions are adapted
 * to simulate complement of two situations.
 */
typedef struct 
{
  /** The array of bits inside the structure*/
  uint32_t *data; 
  /** The position where the first non zero value starts */
  size_t    size;
  /** The amount of uint32 values the number can handle */
  size_t    capa;
  /** True if the number is negative */
  int       negative;
} hs_bigint;

/** @defgroup BigInt constructors and destructors

 */
/**@{ */
/**
 * @brief starts and integer, able to store up to capa uint32 values inside.
 *
 * @param bi a big int pointer to initialize.
 * @param capa The initial capacity of the integer.
 * @return 0 on success, a non zero value on failure.
 */
int 
hs_bigint_init(hs_bigint *bi, size_t capa);

/**
 * @brief starts and integer, from an uint32.
 *
 * @param bi a big int pointer to initialize.
 * @param value The number to convert.
 * @return 0 on success, a non zero value on failure.
 */
int
hs_bigint_from_i32(hs_bigint *bi, uint32_t value);

/**
 * @brief starts and integer, from an int32.
 *
 * @param bi a big int pointer to initialize.
 * @param value The number to convert.
 * @return 0 on success, a non zero value on failure.
 */
int
hs_bigint_from_i32(hs_bigint *bi, int32_t value);

/**
 * @brief starts and integer, from an uint64.
 *
 * @param bi a big int pointer to initialize.
 * @param value The number to convert.
 * @return 0 on success, a non zero value on failure.
 */
int
hs_bigint_from_u64(hs_bigint *bi, uint64_t value);

/**
 * @brief starts and integer, from an int64.
 *
 * @param bi a big int pointer to initialize.
 * @param value The number to convert.
 * @return 0 on success, a non zero value on failure.
 */
int
hs_bigint_from_i64(hs_bigint *bi, int64_t value);

/**
 * @brief copys a bigint into another bigint.
 *
 * @param src a big int pointer to copy from.
 * @param dst The destination where the source (src) will be copied.
 * @return 0 on success, a non zero value on failure.
 */
int 
hs_bigint_copy(hs_bigint *src, hs_bigint *dst);

/**
 * @brief release the resources used by the bigint.
 *
 * @param bi a big int pointer to end.
 */
void
hs_bigint_end(hs_bigint *bi);

/**@} */

/** @defgroup BigInt comparators
 * Bigints have the equals and the compare, using both for sorting and 
 * equality.
 * Negative zero is treated the same as positive zero here.
 */
/**@{ */
int
hs_bigint_compare(hs_bigint *a, hs_bigint *b);

int
hs_bigint_equals(hs_bigint *a, hs_bigint *b);
/**@} */

/** @defgroup BigInt non destructive operations
 * Operations in this group returns a new bigint instead of destroying one of
 * the parameters.
 * They have destructive alternatives with self before the operation names.
 * Non-destructive operations works by coping the left argument, then performing
 * a destructive on the copy, so they are a bit slower, but safer.
 */
/**@{ */

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
hs_bigint_ushr(hs_bigint *a, hs_bigint *b, hs_bigint *dst);

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
hs_bigint_divrem(hs_bigint *a, hs_bigint *b, hs_bigint *res, hs_bigint *rem );

/**@} */

/** @defgroup BigInt common simplifications
 *
 * This group is dedicated to do a quick operation to increment/decrement your
 * number in order to allow a fastest way to iterate.
 */
/**@{ */

int
hs_bigint_inc(hs_bigint *bi);

int
hs_bigint_dec(hs_bigint *bi);

/**@} */


/** @defgroup BigInt destructive operations
 * Operations in this group destroy the left parameter send into the 
 * operation, even on failure you can't assume the original number was not 
 * modified.
 * Because they don't copy the original left operand, they are a bit faster.
 * They all have self before the operation names.
 */
/**@{ */
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
hs_bigint_self_ushr(hs_bigint *a, hs_bigint *b);

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

/**@} */

#endif /* HS_BIGINT_H */
