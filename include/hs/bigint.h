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
hs_bigint_init(hs_bigint *bi, const size_t capa);

/**
 * @brief starts and integer, from an uint32.
 *
 * @param bi a big int pointer to initialize.
 * @param value The number to convert.
 * @return 0 on success, a non zero value on failure.
 */
int
hs_bigint_from_i32(hs_bigint *bi, const uint32_t value);

/**
 * @brief starts and integer, from an int32.
 *
 * @param bi a big int pointer to initialize.
 * @param value The number to convert.
 * @return 0 on success, a non zero value on failure.
 */
int
hs_bigint_from_i32(hs_bigint *bi, const int32_t value);

/**
 * @brief starts and integer, from an uint64.
 *
 * @param bi a big int pointer to initialize.
 * @param value The number to convert.
 * @return 0 on success, a non zero value on failure.
 */
int
hs_bigint_from_u64(hs_bigint *bi, const uint64_t value);

/**
 * @brief starts and integer, from an int64.
 *
 * @param bi a big int pointer to initialize.
 * @param value The number to convert.
 * @return 0 on success, a non zero value on failure.
 */
int
hs_bigint_from_i64(hs_bigint *bi, const int64_t value);

/**
 * @brief copys a bigint into another bigint.
 *
 * @param src a big int pointer to copy from.
 * @param dst The destination where the source (src) will be copied.
 * @return 0 on success, a non zero value on failure.
 */
int 
hs_bigint_copy(const hs_bigint *src, hs_bigint *dst);

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

/**
 * @brief compares the value of two bigints.
 *
 * If a is bigger than b, then it returns 1.
 * If a is less than b, then it returns -1.
 * If a is equal to b, then it returns 0.
 * -0 and +0 are considered the same.
 *
 * @param a a bigint pointer to compare.
 * @param b a bigint pointer to compare.
 * @return a value in  [-1, 0, 1]
 */
int
hs_bigint_compare(const hs_bigint *a, const hs_bigint *b);

/**
 * @brief compares the value of two bigints.
 *
 * @param a a bigint pointer to compare.
 * @param b a bigint pointer to compare.
 * @return a non zero value if a and b are equal, 0 if not.
 * @note -0 and +0 are considered the same.
 *
 */
int
hs_bigint_equals(const hs_bigint *a, const hs_bigint *b);
/**@} */

/** @defgroup BigInt non destructive operations
 * Operations in this group returns a new bigint instead of destroying one of
 * the parameters.
 * They have destructive alternatives with self before the operation names.
 * Non-destructive operations works by coping the left argument, then performing
 * a destructive on the copy, so they are a bit slower, but safer.
 */
/**@{ */

/**
 * @brief adds two big integers, storing the result in dst. ( dst = a + b )
 *
 * @param a The left number to add.
 * @param b The right value to add.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_add
 */
int
hs_bigint_add(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief subtracts two big integers, storing the result in dst. ( dst = a - b )
 *
 * @param a The left number to subtract.
 * @param b The right value to subtract.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_sub
 */
int
hs_bigint_sub(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief multiplies two big integers, storing the result in dst.( dst = a * b )
 *
 * @param a The left number to multiply.
 * @param b The right value to multiply.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_mul
 */
int
hs_bigint_mul(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief divides two big integers, storing the result in dst. (dst = a / b)
 *
 * @param a The left number to divide.
 * @param b The right value to divide.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_div
 */
int
hs_bigint_div(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief performs a left shift, storing the result in dst. (dst = a << b)
 *
 * @param a The left number to shift.
 * @param b The number of times to shift a, b must be bigger than 0.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_shl
 */
int
hs_bigint_shl(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief performs a arithmetic right shift, storing the result in dst. (dst = a >> b)
 *
 * @param a The left number to shift.
 * @param b The number of times to shift a, b must be bigger than 0.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_shr
 */
int
hs_bigint_shr(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief performs a logical right shift, storing the result in dst. (dst = a >>> b)
 *
 * @param a The left number to shift.
 * @param b The number of times to shift a, b must be bigger than 0.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_ushr
 */
int
hs_bigint_ushr(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief performs a  bitwise and between a and b, storing the result in dst (dst = a & b)
 *
 * @param a The left number to bitwise.
 * @param b The right number to bitwise.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_and
 */
int
hs_bigint_and(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief performs a  bitwise or between a and b, storing the result in dst (dst = a | b)
 *
 * @param a The left number to bitwise.
 * @param b The right number to bitwise.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_or
 */
int
hs_bigint_or(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief performs a  bitwise exclusive or between a and b, storing the result in dst (dst = a ^ b)
 *
 * @param a The left number to bitwise.
 * @param b The right number to bitwise.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_xor
 */
int
hs_bigint_xor(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief performs a remainder between a and b, storing the result in dst (dst = a % b)
 *
 * The remained must always satisfy than (a / b) * b + a % b = a
 *
 * @param a The left operand.
 * @param b The right operand.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_rem
 */
int
hs_bigint_rem(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief performs the modulo between a and b, storing the result in dst (dst = a %% b)
 *
 * The module is calculated with the definition of the remained as:
 * a %% b = (a % b + b) % b
 *
 * @param a The left operand.
 * @param b The right operand.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_mod
 */
int
hs_bigint_mod(const hs_bigint *a, const hs_bigint *b, hs_bigint *dst);

/**
 * @brief negates a number, storing its value in dst (dst = -src)
 *
 * @param src The number to negate.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_neg
 */
int
hs_bigint_neg(const hs_bigint *src, hs_bigint *dst);

/**
 * @brief does a two's complement of a number, storing it in dst (dst = ~src)
 *
 * @param src The number to complement.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_cpl
 */
int
hs_bigint_cpl(const hs_bigint *src, hs_bigint *dst);

/**
 * @brief Gets the absolute value, storing it in dst (dst = abs(src))
 *
 * An absolute value is defined as the distance of the number to zero.
 * So the result is always positive.
 * For example, the absolute value of both -3 and 3 is 3, because both are 3 
 * numbers apart from zero.
 *
 * @param src The number to get the absolute value of.
 * @param dst a destination where the result is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with dst if the functions succeeds.
 * @see hs_bigint_self_abs
 */
int
hs_bigint_abs(const hs_bigint *src, hs_bigint *dst);

/**
 * @brief Gets both the remainder and the result of a division between two bigints.
 *
 * This method takes the approach to get both a / b and a % b in one go, a bit
 * faster than each operation aside.
 *
 * @param a The left operand.
 * @param b The right operand.
 * @param res a destination where the result of (a / b) is stored.
 * @param rem a destination where the result of (a % b) is stored.
 * @return A non zero value on error, zero if the function succeeds
 * @warning remember to call hs_bigint_end() with both res and rem if the functions succeeds.
 */
int
hs_bigint_divrem(const hs_bigint *a, const hs_bigint *b, 
                  hs_bigint *res, hs_bigint *rem );

/**@} */

/** @defgroup BigInt common simplifications
 *
 * This group is dedicated to do a quick operation to increment/decrement your
 * number in order to allow a fastest way to iterate.
 */
/**@{ */
/**
 * @brief increments the value of bi in one. (++bi)
 *
 * This function is faster than a normal addition.
 *
 * @param bi The number to increment
 * @return A non zero value on error, zero if the function succeeds
 */
int
hs_bigint_inc(hs_bigint *bi);

/**
 * @brief decrements the value of bi in one. (--bi)
 *
 * This function is faster than a normal subtraction.
 *
 * @param bi The number to increment
 * @return A non zero value on error, zero if the function succeeds
 */
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
/**
 * @brief performs an addition between a and b, storing the result in a (a += b)
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_add
 */
int
hs_bigint_self_add(hs_bigint *a, const hs_bigint *b);

/**
 * @brief performs a subtraction between a and b, storing the result in a (a -= b)
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_sub
 */
int
hs_bigint_self_sub(hs_bigint *a, const hs_bigint *b);

/**
 * @brief performs a multiplication between a and b, storing the result in a (a *-= b)
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_mul
 */
int
hs_bigint_self_mul(hs_bigint *a, const hs_bigint *b);

/**
 * @brief performs a division between a and b, storing the result in a (a /= b)
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_div
 */
int
hs_bigint_self_div(hs_bigint *a, const hs_bigint *b);

/**
 * @brief performs a left shift between a and b, storing the result in a (a <<= b)
 *
 * @param a The left operand
 * @param b The right operand, must be bigger than zero.
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_shl
 */
int
hs_bigint_self_shl(hs_bigint *a, const hs_bigint *b);

/**
 * @brief performs a right arithmetic shift between a and b, storing the result in a (a >>= b)
 *
 * @param a The left operand
 * @param b The right operand, must be bigger than zero.
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_shr
 */
int
hs_bigint_self_shr(hs_bigint *a, const hs_bigint *b);

/**
 * @brief performs a  left logical shift between a and b, storing the result in a (a <<<= b)
 *
 * @param a The left operand
 * @param b The right operand, must be bigger than zero.
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_ushr
 */
int
hs_bigint_self_ushr(hs_bigint *a, const hs_bigint *b);

/**
 * @brief performs a bitwise and between a and b storing the result in a (a &= b)
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_and
 */
int
hs_bigint_self_and(hs_bigint *a, const hs_bigint *b);

/**
 * @brief Gets the remainder of the division between a and b, storing the result in a (a %= b )
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_rem
 */
int
hs_bigint_self_rem(hs_bigint *a, const hs_bigint *b);

/**
 * @brief Gets the modulo of the division between a and b, storing the result in a (a %%= b )
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_mod
 */
int
hs_bigint_self_mod(hs_bigint *a, const hs_bigint *b);

/**
 * @brief performs a bitwise or between a and b storing the result in a (a |= b)
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_or
 */
int
hs_bigint_self_or(hs_bigint *a, const hs_bigint *b);

/**
 * @brief performs a bitwise exclusive or between a and b storing the result in a (a ^= b)
 *
 * @param a The left operand
 * @param b The right operand
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_xor
 */
int
hs_bigint_self_xor(hs_bigint *a, const hs_bigint *b);

/**
 * @brief negates the value of a number on itself (bi = -bi)
 *
 * @param bi The value to negate 
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_neg
 */
int
hs_bigint_self_neg(hs_bigint *bi);

/**
 * @brief Gets the absolute value of a number on itself ( bi = abs(bi) )
 *
 * @param bi The value to make absolute 
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_neg
 */
int
hs_bigint_self_abs(hs_bigint *bi);

/**
 * @brief gets the complement of a number and stores on itself (bi = ~bi)
 *
 * @param bi The value to complement 
 * @return A non zero value on error, zero if the function succeeds
 * @warning Please be aware than even if the function fails, the value in a may be altered
 * @see hs_bigint_neg
 */
int
hs_bigint_self_cpl(hs_bigint *bi);

/**@} */

#endif /* HS_BIGINT_H */
