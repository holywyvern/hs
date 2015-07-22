#ifndef HS_LEXER_H
#define HS_LEXER_H

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct hs_lexer_state
{
  size_t line;
  size_t column;
  size_t index;
};

typedef struct hs_lexer
{
  hs_file        *fp;
  hs_lexer_state *states;
  size_t          states_size;
  size_t          states_capa;
} hs_lexer;

typedef struct hs_token
{
  union
  {
    
  } value;
  enum
  {
    
  } type;
};



#ifdef __cplusplus
}
#endif 

#endif /* HS_LEXER_H */