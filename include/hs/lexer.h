#ifndef HS_LEXER_H
#define HS_LEXER_H

#include "hs/file.h"

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct hs_lexer_state
{
  size_t line;
  size_t column;
  size_t index;
} hs_lexer_state;

typedef struct hs_lexer
{
  int                                   mode;
  union { hs_file *fp, const char *str} data;
  hs_lexer_state                        state;
} hs_lexer;

typedef struct hs_token
{
  union
  {
    char *as_string;
  } value;
  enum
  {
    HS_TOKEN_INTEGER,
    HS_TOKEN_FLOAT,
    HS_TOKEN_STRING,
    HS_TOKEN_REGEXP,
    HS_TOKEN_SYMBOL,
  } type;
} hs_token;

/**
 * @brief Creates a lexer from a file descriptor
 *
 * @param lx The lexer to initialize
 * @param fp A file descriptor
 * @return zero on success, a non zero value on error.
 */
int
hs_lexer_from_file(hs_lexer *lx, hs_file *fp);

/**
 * @brief Creates a lexer from a null terminated string
 *
 * @param lx The lexer to initialize
 * @param str a pointer to the first character on a string
 * @return zero on success, a non zero value on error.
 */
int
hs_lexer_from_str(hs_lexer *lx, const char *str);

/**
 * @brief Release resources associated with the lexer
 *
 * @param lx The lexer 
 */
void
hs_lexer_end( hs_lexer *lx );

/**
 * @brief Gets the next token in the lexer
 *
 * @param lx The lexer
 * @param tk A pointer to store the token result
 * @return zero on success, a non zero value on error.
 */
int
hs_lexer_next( hs_lexer *lx, hs_token *tk );

/**
 * @brief Saves the current state of the lexer, for future use
 *
 * @param lx The lexer
 * @param st A pointer to store the state of the lexer
 * @return zero on success, a non zero value on error.
 */
int
hs_lexer_save( hs_lexer *lx, hs_lexer_state *st );

/**
 * @brief Loads a previously stored state of a lexer
 *
 * @param lx The lexer
 * @param st A state to load into the lexer
 * @return zero on success, a non zero value on error.
 */
int
hs_lexer_load( hs_lexer *lx, hs_lexer_state *st );

/**
 * @brief Release resources used by a token
 * This function should be called every time you get a new token on it
 * @param tk The token to end
 */
void
hs_token_end( hs_token *tk );

#ifdef __cplusplus
}
#endif 

#endif /* HS_LEXER_H */