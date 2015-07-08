#ifndef HS_OPCODE_H

#define __cplusplus
extern "C" {
#endif

enum hs_opcode
{
  HS_OP_NOP                       =   1, /* wait() */
  HS_OP_BREAKPOINT                =   2, /* breakpoint() */
  HS_OP_HALT                      =   3, /* halt( <reg> ) */
 
  HS_OP_LOAD_NULL                 =  10, /* <reg> <- null */
  HS_OP_LOAD_FALSE                =  11, /* <reg> <- false */
  HS_OP_LOAD_TRUE                 =  12, /* <reg> <- true */
  HS_OP_LOAD_ARG_INDIRECT         =  13, /* <reg> <- arguments [ <reg> ] */
  HS_OP_LOAD_ARG                  =  14, /* <reg> <- arguments [ <uint16> ] */
  HS_OP_LOAD_LOCAL                =  15, /* <reg> <- context [ <uint16> ] */
  HS_OP_LOAD_LOCAL_INDIRECT       =  16, /* <reg> <- context [ <reg> ] */
  HS_OP_LOAD_FIELD                =  17, /* <reg> <- this [ <uint16> ] */
  HS_OP_LOAD_FIELD_INDIRECT       =  18, /* <reg> <- <reg> [ <reg> ] */
  HS_OP_LOAD_LOCAL_CONST          =  19, /* <reg> <- module [ <uint16> ] */
  HS_OP_LOAD_LOCAL_CONST_INDIRECT =  20, /* <reg> <- module [ <reg> ] */
 
  HS_OP_STORE_LOCAL               =  30, /* context [ <uint16> ] <- <reg> */
  HS_OP_STORE_LOCAL_INDIRECT      =  31, /* context [ <reg> ] <- <reg> */
  HS_OP_STORE_FIELD               =  32, /* this [ <uint16> ] <- <reg> */
  HS_OP_STORE_FIELD_INDIRECT      =  33, /* <reg> [ <reg> ] <- <reg> */
 
  HS_OP_MOVE                      =  40, /* <reg> <- <reg> */
 
  HS_OP_STACK_POP                 =  50, /* <reg> <- stack.pop() */
  HS_OP_STACK_PUSH                =  51, /* stack.push( <reg> ) */
  HS_OP_STACK_PEEK                =  52, /* <reg> <- stack.peek() */
  HS_OP_STACK_DUP                 =  53, /* stack.dup(); */
 
  HS_OP_JUMP                      =  60, /* jump( <uint16> ) */
  HS_OP_JUMP_EQ_REG               =  61, /* if <reg> = <reg> then jump( <reg> ) */
  HS_OP_JUMP_NE_REG               =  62, /* if <reg> <> <reg> then jump( <reg> ) */
  HS_OP_JUMP_LT_REG               =  63, /* if <reg> < <reg> then jump( <reg> ) */
  HS_OP_JUMP_LE_REG               =  64, /* if <reg> <= <reg> then jump( <reg> ) */
  HS_OP_JUMP_GT_REG               =  65, /* if <reg> > <reg> then jump( <reg> ) */
  HS_OP_JUMP_GE_REG               =  66, /* if <reg> >= <reg> then jump( <reg> ) */
  HS_OP_JUMP_EQ_ZERO              =  67, /* if <reg> = 0 then jump( <uint16> ) */
  HS_OP_JUMP_NE_ZERO              =  68, /* if <reg> <> 0 then jump( <uint16> ) */
  HS_OP_JUMP_LT_ZERO              =  69, /* if <reg> < 0 then jump( <uint16> ) */
  HS_OP_JUMP_LE_ZERO              =  70, /* if <reg> <= 0 then jump( <uint16> ) */
  HS_OP_JUMP_GT_ZERO              =  71, /* if <reg> > 0 then jump( <uint16> ) */
  HS_OP_JUMP_GE_ZERO              =  72, /* if <reg> >= 0 then jump( <uint16> ) */
  HS_OP_JUMP_INDIRECT             =  73, /* jump( <reg> ) */
  HS_OP_JUMP_EQ_ZERO_INDIRECT     =  80, /* if <reg> = 0 then jump( <reg> ) */
  HS_OP_JUMP_NE_ZERO_INDIRECT     =  81, /* if <reg> <> 0 then jump( <reg> ) */
  HS_OP_JUMP_LT_ZERO_INDIRECT     =  82, /* if <reg> < 0 then jump( <reg> ) */
  HS_OP_JUMP_LE_ZERO_INDIRECT     =  83, /* if <reg> <= 0 then jump( <reg> ) */
  HS_OP_JUMP_GT_ZERO_INDIRECT     =  84, /* if <reg> > 0 then jump( <reg> ) */
  HS_OP_JUMP_GE_ZERO_INDIRECT     =  85, /* if <reg> >= 0 then jump( <reg> ) */
  
  HS_OP_RETURN                    =  90, /* return( <reg> ) */
  HS_OP_RETURN_NULL               =  91, /* return( null ) */
  HS_OP_RETURN_SELF               =  92, /* return( self ) */
  
  HS_OP_RESERVE_ARGS              = 100, /* arguments.push( <uint16> ) */
  HS_OP_RESERVE_ARGS_INDIRECT     = 101, /* arguments.push( <reg> ) */
  HS_OP_SET_ARG                   = 102, /* arguments[ <uint16> ] <- <reg> */
  HS_OP_SET_ARG_INDIRECT          = 103, /* arguments[ <reg> ] <- <reg> */
  HS_OP_CALL                      = 104, /* <reg> <- call( this, <reg> )  */
  HS_OP_LOCAL_CALL                = 105, /* <reg> <- call( module, <reg> )  */
  HS_OP_DYNAMIC_CALL              = 106, /* <reg> <- call( <reg>, <reg> )  */
  
  HS_OP_SET_THIS                  = 110, /* this   <- <reg> */
  HS_OP_SET_MODULE                = 111, /* module <- <reg> */
  
  HS_OP_GET_THIS                  = 120, /* <reg> <- this */
  HS_OP_GET_MODULE                = 121, /* <reg> <- module */
  
  HS_OP_BOOL_AND                  = 130, /* <reg> <- bool : <reg> & <reg> */
  HS_OP_BOOL_OR                   = 131, /* <reg> <- bool : <reg> | <reg> */
  HS_OP_BOOL_XOR                  = 132, /* <reg> <- bool : <reg> ^ <reg> */
  HS_OP_BOOL_CMP                  = 133, /* <reg> <- bool : <reg> <=> <reg> */
  HS_OP_BOOL_NOT                  = 134, /* <reg> <- bool : not <reg> */
  
  HS_OP_INT_ADD                   = 140, /* <reg> <- int : <reg> + <reg> */
  HS_OP_INT_SUB                   = 141, /* <reg> <- int : <reg> - <reg> */
  HS_OP_INT_MUL                   = 142, /* <reg> <- int : <reg> * <reg> */
  HS_OP_INT_DIV                   = 143, /* <reg> <- int : <reg> / <reg> */
  HS_OP_INT_MOD                   = 144, /* <reg> <- int : <reg> %% <reg> */
  HS_OP_INT_REM                   = 145, /* <reg> <- int : <reg> % <reg> */
  HS_OP_INT_SHL                   = 146, /* <reg> <- int : <reg> << <reg> */
  HS_OP_INT_SHR                   = 147, /* <reg> <- int : <reg> >> <reg> */
  HS_OP_INT_LSL                   = 148, /* <reg> <- int : <reg> <<< <reg> */
  HS_OP_INT_LSR                   = 149, /* <reg> <- int : <reg> >>> <reg> */
  HS_OP_INT_AND                   = 150, /* <reg> <- int : <reg> & <reg> */
  HS_OP_INT_OR                    = 151, /* <reg> <- int : <reg> | <reg> */
  HS_OP_INT_XOR                   = 152, /* <reg> <- int : <reg> ^ <reg> */
  HS_OP_INT_CMP                   = 153, /* <reg> <- int : <reg> <=> <reg> */
  HS_OP_INT_NEG                   = 154, /* <reg> <- int : -<reg> */
  HS_OP_INT_CPL                   = 155, /* <reg> <- int : ~<reg> */
  HS_OP_INT_POW                   = 142, /* <reg> <- int : <reg> ** <reg> */
  
  HS_OP_FLOAT_ADD                 = 160, /* <reg> <- float : <reg> + <reg> */
  HS_OP_FLOAT_SUB                 = 161, /* <reg> <- float : <reg> - <reg> */
  HS_OP_FLOAT_MUL                 = 162, /* <reg> <- float : <reg> * <reg> */
  HS_OP_FLOAT_DIV                 = 163, /* <reg> <- float : <reg> / <reg> */
  HS_OP_FLOAT_SQRT                = 164, /* <reg> <- sqrt( <reg> ) */
  HS_OP_FLOAT_EXP                 = 165, /* <reg> <- exp( <reg> ) */
  HS_OP_FLOAT_POW                 = 166, /* <reg> <- <reg> ** <reg> */
  HS_OP_FLOAT_LOG2                = 167, /* <reg> <- log2(<reg>) */
  HS_OP_FLOAT_LOG                 = 168, /* <reg> <- log(<reg>) */
  HS_OP_FLOAT_LN                  = 169, /* <reg> <- ln(<reg>) */
  HS_OP_FLOAT_SIN                 = 170, /* <reg> <- sin( <reg> ) */
  HS_OP_FLOAT_COS                 = 171, /* <reg> <- cos( <reg> ) */
  HS_OP_FLOAT_TAN                 = 172, /* <reg> <- tan( <reg> ) */
  HS_OP_FLOAT_ASIN                = 173, /* <reg> <- asin( <reg> ) */
  HS_OP_FLOAT_ACOS                = 174, /* <reg> <- acos( <reg> ) */
  HS_OP_FLOAT_ATAN                = 175, /* <reg> <- atan( <reg> ) */
  HS_OP_FLOAT_ATAN2               = 176, /* <reg> <- atan2( <reg>, <reg> ) */
  HS_OP_FLOAT_NEG                 = 177, /* <reg> <- float : -<reg> */
  HS_OP_FLOAT_CMP                 = 178, /* <reg> <- float : <reg>  <=> <reg> */
 
  HS_OP_BOOL2INT                  = 180, /* <reg> <- bool : int( <reg> ) */
  HS_OP_INT2BOOL                  = 181, /* <reg> <- int : bool( <reg> ) */
  HS_OP_INT2FLOAT                 = 182, /* <reg> <- int : float( <reg> ) */
  HS_OP_FLOAT2INT                 = 183, /* <reg> <- float : int( <reg> ) */
 
  HS_OP_NEW                       = 190, /* <reg> <- {} */
  HS_OP_EXTEND                    = 191, /* <reg> <- new <reg> */
 
  HS_OP_BOX_BOOL                  = 200, /* <reg> <- bool : &<reg> */
  HS_OP_BOX_INT                   = 201, /* <reg> <- int : &<reg> */
  HS_OP_BOX_FLOAT                 = 202, /* <reg> <- float : &<reg> */
  HS_OP_UNBOX                     = 203, /* <reg> <- *<reg> */
 
  HS_OP_LOCK                      = 210, /* lock( <reg> ) */
  HS_OP_UNLOCK                    = 211, /* unlock( <reg> ) */
  
  HS_OP_ARRAY_NEW                 = 220, /* <reg> <- [ <uint16> ] */
  HS_OP_ARRAY_NEW_INDIRECT        = 221, /* <reg> <- [ <reg> ] */
  HS_OP_ARRAY_GET                 = 222, /* <reg> <- <reg>[<reg>] */
  HS_OP_ARRAY_SET                 = 223, /* <reg> [<reg>] <- <reg> */
  HS_OP_ARRAY_DELETE              = 224, /* delete( <reg>[<reg>] ) */
  
  HS_OP_NEW_TRY_CONTEXT           = 230, /* try( <uint16> ) */
  HS_OP_NEW_TRY_CONTEXT_INDIRECT  = 231, /* try( <reg> ) */
  HS_OP_NEW_TRY_CONTEXT_NO_FINAL  = 232, /* try( ) */
  HS_OP_ADD_CATCH                 = 233, /* catch( <reg>, <uint16> ) */
  HS_OP_ADD_CATCH_INDIRECT        = 234, /* catch( <reg>, <reg> ) */
  HS_OP_THROW                     = 235, /* throw( <reg> ) */
  HS_OP_END_TRY_CONTEXT           = 236, /* end() */
  
  HS_OP_INT_INC                   = 240, /* inc( int : <reg> ) */
  HS_OP_INT_DEC                   = 241, /* dec( int : <reg> ) */
  HS_OP_FLOAT_INC                 = 242, /* inc( float : <reg> ) */
  HS_OP_FLOAT_DEC                 = 243, /* dec( float : <reg> ) */  
  
  HS_OP_DECLARE_FUNCTION          = 250, /* <reg> <- def( <uint16> ) */
  HS_OP_DECLARE_FUNCTION_INDIRECT = 251, /* <reg> <- def( <reg> ) */
  HS_OP_END_FUNCTION              = 252, /* end() */
  
};

union hs_opcode_params
{
  uint8_t  u8[3];
  struct { uint16_t u16; uint8_t u8; } set;
};

extern const char HS_OPCODE_PARAM_TYPE[];

#define HS_OPCODE_NO_PARAMS 0
#define HS_OPCODE_ONE_REG_PARAMS 1
#define HS_OPCODE_TWO_REG_PARAMS 2
#define HS_OPCODE_THREE_REG_PARAMS 3
#define HS_OPCODE_UINT_PARAMS 4
#define HS_OPCODE_UINT_AND_REG_PARAMS 5

#define HS_OP_DECODE(opcode, instruction, params)                              \
  do                                                                           \
  {                                                                            \
    uint32_t o_opcode_ = (opcode);                                             \
    uint16_t o_ta_, o_tb_;                                                     \
    instruction = (uint8_t)( ( o_opcode_ >> 24) && 255 );                      \
    switch (HS_OPCODE_PARAM_TYPE[instruction])                                 \
    {                                                                          \                                                               \
      case HS_OPCODE_THREE_REG_PARAMS:                                         \
        (params).u8[2] = (uint8_t)(  o_opcode_        & 255 );                 \
      case HS_OPCODE_TWO_REG_PARAMS:                                           \
        (params).u8[1] = (uint8_t)( (o_opcode_ >>  8) & 255);                  \
      case HS_OPCODE_ONE_REG_PARAMS:                                           \
        (params).u8[0] = (uint8_t)( (o_opcode_ >> 16) & 255);                  \
        break;                                                                 \
      case HS_OPCODE_UINT_AND_REG_PARAMS:                                      \
        (params).set.u8  = (uint8_t)( ( o_opcode_ >> 16 ) & 255 );             \
      case HS_OPCODE_UINT_PARAMS:                                              \
        o_ta_ = (uint16_t)( ( o_opcode_ >>  8 ) & 255 );                       \
        o_tb_ = (uint16_t)(   o_opcode_         & 255 );                       \
        (params).set.u16 = ( ( o_ta_ << 8)|o_tb_ ) ;                           \
        break;                                                                 \
      default:                                                                 \
        break;                                                                 \
    }                                                                          \
  } while (0)

#define HS_OP_ENCODE(instruction, params, opcode)                              \
  do                                                                           \
  {                                                                            \
    opcode = ( ((instruction) & 255) << 24 );                                  \
    switch (HS_OPCODE_PARAM_TYPE[instruction])                                 \
    {                                                                          \
      case HS_OPCODE_THREE_REG_PARAMS:                                         \
        opcode |= (params).u8[2];                                              \
      case HS_OPCODE_TWO_REG_PARAMS:                                           \
        opcode |= (params).u8[1] << 8;                                         \
      case HS_OPCODE_ONE_REG_PARAMS:                                           \
        opcode |= (params).u8[1] << 16;                                        \
        break;                                                                 \
      case HS_OPCODE_UINT_AND_REG_PARAMS:                                      \
        opcode |= (params).set.u8 << 16;                                       \
      case HS_OPCODE_UINT_PARAMS:                                              \
        opcode |= ( (params).set.u16 << 8 ) << 8;                              \
        opcode |= (params).set.u16 & 255;                                      \
        break;                                                                 \
      default:                                                                 \
        break;                                                                 \
    }                                                                          \
  }                                                                            \
  while (0)
    
#define __cplusplus
}
#endif

#endif /* HS_OPCODE_H */