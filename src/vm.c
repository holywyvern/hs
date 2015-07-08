#define HS_MAX_REGISTERS  8
#define HS_MAX_ARGS       3
#define HS_HEAP_INIT_SIZE 4

/*
int logicalRightShift(int x, int n) {
    return (unsigned)x >> n;
}
int arithmeticRightShift(int x, int n) {
    if (x < 0 && n > 0)
        return x >> n | ~(~0U >> n);
    else
        return x >> n;
}
*/

#define HS_OPCODE_NO_PARAMS 0
#define HS_OPCODE_ONE_REG_PARAMS 1
#define HS_OPCODE_TWO_REG_PARAMS 2
#define HS_OPCODE_THREE_REG_PARAMS 3
#define HS_OPCODE_UINT_PARAMS 4
#define HS_OPCODE_UINT_AND_REG_PARAMS 5

const char HS_OPCODE_PARAM_TYPE[] = {
  
  HS_OPCODE_NO_PARAMS,           /* 001 - HS_OP_NOP */
  HS_OPCODE_NO_PARAMS,           /* 002 - HS_OP_BREAKPOINT */
  HS_OPCODE_NO_PARAMS,           /* 003 - HS_OP_HALT  */
 
  HS_OPCODE_NO_PARAMS,           /* 004 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 005 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 006 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 007 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 008 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 009 - <<undefined>> */
  
  HS_OPCODE_ONE_REG_PARAMS,      /* 010 - HS_OP_LOAD_NULL */
  HS_OPCODE_ONE_REG_PARAMS,      /* 011 - HS_OP_LOAD_FALSE */
  HS_OPCODE_ONE_REG_PARAMS,      /* 012 - HS_OP_LOAD_TRUE */
  HS_OPCODE_TWO_REG_PARAMS,      /* 013 - HS_OP_LOAD_ARG_INDIRECT */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 014 - HS_OP_LOAD_ARG */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 015 - HS_OP_LOAD_LOCAL */
  HS_OPCODE_TWO_REG_PARAMS,      /* 016 - HS_OP_LOAD_LOCAL_INDIRECT */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 017 - HS_OP_LOAD_FIELD */
  HS_OPCODE_THREE_REG_PARAMS,    /* 018 - HS_OP_LOAD_FIELD_INDIRECT */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 019 - HS_OP_LOAD_LOCAL_CONST */
  HS_OPCODE_TWO_REG_PARAMS,      /* 020 - HS_OP_LOAD_LOCAL_CONST_INDIRECT */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 021 - HS_OP_LOAD_INT_CONST */
  
  
  HS_OPCODE_NO_PARAMS,           /* 022 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 023 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 024 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 025 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 026 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 027 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 028 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 029 - <<undefined>> */
 
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 030 - HS_OP_STORE_LOCAL */
  HS_OPCODE_TWO_REG_PARAMS,      /* 031 - HS_OP_STORE_LOCAL_INDIRECT */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 032 - HS_OP_STORE_FIELD */
  HS_OPCODE_THREE_REG_PARAMS,    /* 033 - HS_OP_STORE_FIELD_INDIRECT */
 
  HS_OPCODE_NO_PARAMS,           /* 034 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 035 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 036 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 037 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 038 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 039 - <<undefined>> */
 
  HS_OPCODE_TWO_REG_PARAMS,      /* 040 - HS_OP_MOVE */
 
  HS_OPCODE_NO_PARAMS,           /* 041 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 042 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 043 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 044 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 045 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 046 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 047 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 048 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 049 - <<undefined>> */
 
  HS_OPCODE_ONE_REG_PARAMS,      /* 050 - HS_OP_STACK_POP */
  HS_OPCODE_ONE_REG_PARAMS,      /* 051 - HS_OP_STACK_PUSH */
  HS_OPCODE_ONE_REG_PARAMS,      /* 052 - HS_OP_STACK_PEEK */
  HS_OPCODE_NO_PARAMS,           /* 053 - HS_OP_STACK_DUP */
 
  HS_OPCODE_NO_PARAMS,           /* 054 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 055 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 056 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 057 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 058 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 059 - <<undefined>> */ 
 
  HS_OPCODE_UINT_PARAMS,         /* 060 - HS_OP_JUMP */
  HS_OPCODE_THREE_REG_PARAMS,    /* 061 - HS_OP_JUMP_EQ_REG */
  HS_OPCODE_THREE_REG_PARAMS,    /* 062 - HS_OP_JUMP_NE_REG */
  HS_OPCODE_THREE_REG_PARAMS,    /* 063 - HS_OP_JUMP_LT_REG  */
  HS_OPCODE_THREE_REG_PARAMS,    /* 064 - HS_OP_JUMP_LE_REG */
  HS_OPCODE_THREE_REG_PARAMS,    /* 065 - HS_OP_JUMP_GT_REG */
  HS_OPCODE_THREE_REG_PARAMS,    /* 066 - HS_OP_JUMP_GE_REG */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 067 - HS_OP_JUMP_EQ_ZERO */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 068 - HS_OP_JUMP_NE_ZERO */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 069 - HS_OP_JUMP_LT_ZERO */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 070 - HS_OP_JUMP_LE_ZERO */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 071 - HS_OP_JUMP_GT_ZERO */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 072 - HS_OP_JUMP_GE_ZERO */
  HS_OPCODE_ONE_REG_PARAMS,      /* 073 - HS_OP_JUMP_INDIRECT */
  
  HS_OPCODE_NO_PARAMS,           /* 074 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 075 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 076 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 077 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 078 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 079 - <<undefined>> */ 
  
  HS_OPCODE_TWO_REG_PARAMS,      /* 080 - HS_OP_JUMP_EQ_ZERO_INDIRECT */
  HS_OPCODE_TWO_REG_PARAMS,      /* 081 - HS_OP_JUMP_NE_ZERO_INDIRECT */
  HS_OPCODE_TWO_REG_PARAMS,      /* 082 - HS_OP_JUMP_LT_ZERO_INDIRECT */
  HS_OPCODE_TWO_REG_PARAMS,      /* 083 - HS_OP_JUMP_LE_ZERO_INDIRECT */
  HS_OPCODE_TWO_REG_PARAMS,      /* 084 - HS_OP_JUMP_GT_ZERO_INDIRECT */
  HS_OPCODE_TWO_REG_PARAMS,      /* 085 - HS_OP_JUMP_GE_ZERO_INDIRECT */
  
  HS_OPCODE_NO_PARAMS,           /* 086 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 087 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 088 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 089 - <<undefined>> */     
  
  HS_OPCODE_ONE_REG_PARAMS,      /* 090 - HS_OP_RETURN */
  HS_OPCODE_NO_PARAMS,           /* 091 - HS_OP_RETURN_NULL */
  HS_OPCODE_NO_PARAMS,           /* 092 - HS_OP_RETURN_SELF */
  
  HS_OPCODE_NO_PARAMS,           /* 093 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 094 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 095 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 096 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 097 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 098 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 099 - <<undefined>> */   
  
  HS_OPCODE_UINT_PARAMS,         /* 100 - HS_OP_RESERVE_ARGS */
  HS_OPCODE_ONE_REG_PARAMS,      /* 101 - HS_OP_RESERVE_ARGS_INDIRECT */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 102 - HS_OP_SET_ARG */
  HS_OPCODE_TWO_REG_PARAMS,      /* 103 - HS_OP_SET_ARG_INDIRECT */
  HS_OPCODE_TWO_REG_PARAMS,      /* 104 - HS_OP_CALL */
  HS_OPCODE_TWO_REG_PARAMS,      /* 105 - HS_OP_LOCAL_CALL */
  HS_OPCODE_THREE_REG_PARAMS,    /* 106 - HS_OP_DYNAMIC_CAL */
  
  HS_OPCODE_NO_PARAMS,           /* 107 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 108 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 109 - <<undefined>> */    
  
  HS_OPCODE_ONE_REG_PARAMS,      /* 110 - HS_OP_SET_THIS */
  HS_OPCODE_ONE_REG_PARAMS,      /* 111 - HS_OP_SET_MODULE */
  
  HS_OPCODE_NO_PARAMS,           /* 112 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 113 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 114 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 115 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 116 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 117 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 118 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 119 - <<undefined>> */    
  
  HS_OPCODE_ONE_REG_PARAMS,      /* 120 - HS_OP_GET_THIS    */
  HS_OPCODE_ONE_REG_PARAMS,      /* 121 - HS_OP_GET_MODULE  */
  
  HS_OPCODE_NO_PARAMS,           /* 122 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 123 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 124 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 125 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 126 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 127 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 128 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 129 - <<undefined>> */    
  
  HS_OPCODE_THREE_REG_PARAMS,    /* 130 - HS_OP_BOOL_AND */
  HS_OPCODE_THREE_REG_PARAMS,    /* 131 - HS_OP_BOOL_OR  */
  HS_OPCODE_THREE_REG_PARAMS,    /* 132 - HS_OP_BOOL_XOR */
  HS_OPCODE_THREE_REG_PARAMS,    /* 133 - HS_OP_BOOL_CMP */
  HS_OPCODE_TWO_REG_PARAMS,      /* 134 - HS_OP_BOOL_NOT */
  
  HS_OPCODE_NO_PARAMS,           /* 135 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 136 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 137 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 138 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 139 - <<undefined>> */   
  
  HS_OPCODE_THREE_REG_PARAMS,    /* 140 - HS_OP_INT_ADD */
  HS_OPCODE_THREE_REG_PARAMS,    /* 141 - HS_OP_INT_SUB */
  HS_OPCODE_THREE_REG_PARAMS,    /* 142 - HS_OP_INT_MUL */
  HS_OPCODE_THREE_REG_PARAMS,    /* 143 - HS_OP_INT_DIV */
  HS_OPCODE_THREE_REG_PARAMS,    /* 144 - HS_OP_INT_MOD */
  HS_OPCODE_THREE_REG_PARAMS,    /* 145 - HS_OP_INT_REM */
  HS_OPCODE_THREE_REG_PARAMS,    /* 146 - HS_OP_INT_SHL */
  HS_OPCODE_THREE_REG_PARAMS,    /* 147 - HS_OP_INT_SHR */
  HS_OPCODE_THREE_REG_PARAMS,    /* 148 - HS_OP_INT_LSL */
  HS_OPCODE_THREE_REG_PARAMS,    /* 149 - HS_OP_INT_LSR */
  HS_OPCODE_THREE_REG_PARAMS,    /* 150 - HS_OP_INT_AND */
  HS_OPCODE_THREE_REG_PARAMS,    /* 151 - HS_OP_INT_OR */
  HS_OPCODE_THREE_REG_PARAMS,    /* 152 - HS_OP_INT_XOR */
  HS_OPCODE_THREE_REG_PARAMS,    /* 153 - HS_OP_INT_CMP */
  HS_OPCODE_TWO_REG_PARAMS,      /* 154 - HS_OP_INT_NEG */
  HS_OPCODE_TWO_REG_PARAMS,      /* 155 - HS_OP_INT_CPL */
  HS_OPCODE_THREE_REG_PARAMS,    /* 156 - HS_OP_INT_POW */
  
  HS_OPCODE_NO_PARAMS,           /* 157 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 158 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 159 - <<undefined>> */
  
  HS_OPCODE_THREE_REG_PARAMS,    /* 160 - HS_OP_FLOAT_ADD */
  HS_OPCODE_THREE_REG_PARAMS,    /* 161 - HS_OP_FLOAT_SUB */
  HS_OPCODE_THREE_REG_PARAMS,    /* 162 - HS_OP_FLOAT_MUL */
  HS_OPCODE_THREE_REG_PARAMS,    /* 163 - HS_OP_FLOAT_DIV */
  HS_OPCODE_TWO_REG_PARAMS,      /* 164 - HS_OP_FLOAT_SQRT */
  HS_OPCODE_TWO_REG_PARAMS,      /* 165 - HS_OP_FLOAT_EXP */
  HS_OPCODE_THREE_REG_PARAMS,    /* 166 - HS_OP_FLOAT_POW */
  HS_OPCODE_TWO_REG_PARAMS,      /* 167 - HS_OP_FLOAT_LOG2 */
  HS_OPCODE_TWO_REG_PARAMS,      /* 168 - HS_OP_FLOAT_LOG */
  HS_OPCODE_TWO_REG_PARAMS,      /* 169 - HS_OP_FLOAT_LN */
  HS_OPCODE_TWO_REG_PARAMS,      /* 170 - HS_OP_FLOAT_SIN */
  HS_OPCODE_TWO_REG_PARAMS,      /* 171 - HS_OP_FLOAT_COS */
  HS_OPCODE_TWO_REG_PARAMS,      /* 172 - HS_OP_FLOAT_TAN */
  HS_OPCODE_TWO_REG_PARAMS,      /* 173 - HS_OP_FLOAT_ASIN */
  HS_OPCODE_TWO_REG_PARAMS,      /* 174 - HS_OP_FLOAT_ACOS */
  HS_OPCODE_TWO_REG_PARAMS,      /* 175 - HS_OP_FLOAT_ATAN */
  HS_OPCODE_THREE_REG_PARAMS,    /* 176 - HS_OP_FLOAT_ATAN2 */
  HS_OPCODE_TWO_REG_PARAMS,      /* 177 - HS_OP_FLOAT_NEG */
  HS_OPCODE_THREE_REG_PARAMS,    /* 178 - HS_OP_FLOAT_CMP */
 
  HS_OPCODE_NO_PARAMS,           /* 179 - <<undefined>> */
 
  HS_OPCODE_TWO_REG_PARAMS,      /* 180 - HS_OP_BOOL2INT */
  HS_OPCODE_TWO_REG_PARAMS,      /* 181 - HS_OP_INT2BOOL */
  HS_OPCODE_TWO_REG_PARAMS,      /* 182 - HS_OP_INT2FLOAT */
  HS_OPCODE_TWO_REG_PARAMS,      /* 183 - HS_OP_FLOAT2INT */
 
  HS_OPCODE_NO_PARAMS,           /* 184 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 185 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 186 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 187 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 188 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 189 - <<undefined>> */
 
  HS_OPCODE_ONE_REG_PARAMS,      /* 190 - HS_OP_NEW */
  HS_OPCODE_TWO_REG_PARAMS,      /* 191 - HS_OP_EXTEND */
 
  HS_OPCODE_NO_PARAMS,           /* 192 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 193 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 194 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 195 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 196 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 197 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 198 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 199 - <<undefined>> */ 
 
  HS_OPCODE_TWO_REG_PARAMS,      /* 200 - HS_OP_BOX_BOOL */
  HS_OPCODE_TWO_REG_PARAMS,      /* 201 - S_OP_BOX_INT */
  HS_OPCODE_TWO_REG_PARAMS,      /* 202 - HS_OP_BOX_FLOAT */
  HS_OPCODE_TWO_REG_PARAMS,      /* 203 - HS_OP_UNBOX */
 
  HS_OPCODE_NO_PARAMS,           /* 204 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 205 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 206 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 207 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 208 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 209 - <<undefined>> */  
 
  HS_OPCODE_ONE_REG_PARAMS,      /* 210 - HS_OP_LOCK */
  HS_OPCODE_ONE_REG_PARAMS,      /* 211 - HS_OP_UNLOCK */
  
  HS_OPCODE_NO_PARAMS,           /* 212 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 213 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 214 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 215 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 216 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 217 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 218 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 219 - <<undefined>> */    
  
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 220 - HS_OP_ARRAY_NEW */
  HS_OPCODE_TWO_REG_PARAMS,      /* 221 - HS_OP_ARRAY_NEW_INDIRECT */
  HS_OPCODE_THREE_REG_PARAMS,    /* 222 - HS_OP_ARRAY_GET */
  HS_OPCODE_THREE_REG_PARAMS,    /* 223 - HS_OP_ARRAY_SET */
  HS_OPCODE_TWO_REG_PARAMS,      /* 224 - HS_OP_ARRAY_DELETE */  
  
  HS_OPCODE_UINT_PARAMS,         /* 231 - HS_OP_NEW_TRY_CONTEXT */
  HS_OPCODE_ONE_REG_PARAMS,      /* 232 - HS_OP_NEW_TRY_CONTEXT_INDIRECT */
  HS_OPCODE_NO_PARAMS,           /* 233 - HS_OP_NEW_TRY_CONTEXT_NO_FINAL */
  HS_OPCODE_UINT_AND_REG_PARAMS, /* 234 - HS_OP_ADD_CATCH */
  HS_OPCODE_TWO_REG_PARAMS,      /* 235 - HS_OP_ADD_CATCH_INDIRECT */
  HS_OPCODE_ONE_REG_PARAMS,      /* 236 - HS_OP_THROW */
  HS_OPCODE_NO_PARAMS,           /* 237 - HS_OP_END_TRY_CONTEXT */
  
  HS_OPCODE_NO_PARAMS,           /* 238 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 239 - <<undefined>> */

  HS_OPCODE_ONE_REG_PARAMS,      /* 240 - HS_OP_INT_INC */
  HS_OPCODE_ONE_REG_PARAMS,      /* 241 - HS_OP_INT_DEC */
  HS_OPCODE_ONE_REG_PARAMS,      /* 242 - HS_OP_FLOAT_INC */
  HS_OPCODE_ONE_REG_PARAMS,      /* 243 - HS_OP_FLOAT_DEC */    
  
  HS_OPCODE_NO_PARAMS,           /* 244 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 245 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 246 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 247 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 248 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 249 - <<undefined>> */

  HS_OPCODE_UINT_AND_REG_PARAMS, /* 250 - HS_OP_DECLARE_FUNCTION */
  HS_OPCODE_TWO_REG_PARAMS,      /* 251 - HS_OP_DECLARE_FUNCTION_INDIRECT */
  
  HS_OPCODE_NO_PARAMS,           /* 252 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 253 - <<undefined>> */
  HS_OPCODE_NO_PARAMS,           /* 254 - <<undefined>> */   
  
  HS_OPCODE_NO_PARAMS,           /* 255 - HS_OP_END_BYTECODE */ 
  
}


