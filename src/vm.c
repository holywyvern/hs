#define HS_MAX_REGISTERS  8
#define HS_MAX_ARGS       3
#define HS_HEAP_INIT_SIZE 4

int logicalRightShift(int x, int n) {
    return (unsigned)x >> n;
}
int arithmeticRightShift(int x, int n) {
    if (x < 0 && n > 0)
        return x >> n | ~(~0U >> n);
    else
        return x >> n;
}

typedef struct hs_code_stack hs_code_stack;
typedef union hs_opcode hs_opcode;

union hs_opcode
{
  uint8_t  i8[4];
  uint16_t i16[2];
  uint32_t i32;
};

union hs_opcode_arg
{
  hs_int    as_int;
  hs_float  as_float;
  uint8_t   as_chars[3];
  hs_object as_object;
};

struct hs_code_stack
{
  hs_module    *module;
  int           run;
  size_t        opcode;
  uint8_t       code;
  hs_object     temp;
  hs_object     registers[HS_MAX_REGISTERS];
  hs_opcode_arg args[HS_MAX_ARGS];
  struct 
  {
    hs_object *data;
    size_t     size;
    size_t     capa;
  } heap;
};

#define HS_OP_INVALID     0 
#define HS_OP_EXIT        1
#define HS_OP_NOP         2

#define HS_OP_JUMP       10
#define HS_OP_JUMP_LT    11
#define HS_OP_JUMP_GT    12
#define HS_OP_JUMP_LE    13
#define HS_OP_JUMP_GE    14
#define HS_OP_JUMP_EQ    15
#define HS_OP_JUMP_NE    16

#define HS_OP_IADD       20
#define HS_OP_ISUB       21
#define HS_OP_IMUL       22
#define HS_OP_IDIV       23
#define  HS_OP_IMOD      24
#define HS_OP_IREM       25
#define HS_OP_IPOW       26
#define HS_OP_ISHL       27
#define HS_OP_ISHR       28
#define HS_OP_IUSHR      29
#define HS_OP_IAND       30
#define HS_OP_IOR        31
#define HS_OP_IXOR       32
#define HS_OP_INOT       33
#define HS_OP_ICPL       34
#define HS_OP_ICMP       35
#define HS_OP_IINC       36
#define HS_OP_IDEC       37
#define HS_OP_INEG       38

#define HS_OP_FADD       40
#define HS_OP_FSUB       41
#define HS_OP_FMUL       42
#define HS_OP_FDIV       43
#define HS_OP_FPOW       44
#define HS_OP_FNEG       45
#define HS_OP_FCMP       46
#define HS_OP_FINC       47
#define HS_OP_FDEC       48
#define HS_OP_SIN        49
#define HS_OP_COS        50
#define HS_OP_TAN        51
#define HS_OP_ASIN       52
#define HS_OP_ACOS       53 
#define HS_OP_ATAN       54
#define HS_OP_ATAN2      55

#define HS_OP_GET_STACK     60
#define HS_OP_SET_STACK     61
#define HS_OP_GET_ARG       62
#define HS_OP_SET_FIELD     63     
#define HS_OP_GET_FIELD     64
#define HS_OP_STACK_RESERVE 65
#define HS_OP_MOVE          66
#define HS_OP_SWAP          67

#define HS_OP_PREPARE_ARGS  70
#define HS_OP_SET_ARG       71
#define HS_OP_CALL          72

#define HS_OA_ZERO   0
#define HS_OA_RONE   1
#define HS_OA_RTWO   2
#define HS_OA_RTHREE 3

static uint8_t IP_MODE[] = {
  
  /* 000 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 001 - HS_OP_EXIT    */ HS_OA_ZERO,
  /* 002 - HS_OP_NOP */     HS_OA_ZERO,
  
  /* 003 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 004 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 005 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 006 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 007 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 008 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 009 - <<UNDEFINED>> */ HS_OA_ZERO,
  
  /* 010 - HS_OP_JUMP */    HS_OA_RONE,
  /* 011 - HS_OP_JUMP_LT */ HS_OA_RTWO,
  /* 012 - HS_OP_JUMP_GT */ HS_OA_RTWO,
  /* 013 - HS_OP_JUMP_LE */ HS_OA_RTWO,
  /* 014 - HS_OP_JUMP_GE */ HS_OA_RTWO,
  /* 015 - HS_OP_JUMP_EQ */ HS_OA_RTWO,
  /* 016 - HS_OP_JUMP_NE */ HS_OA_RTWO,
  /* 017 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 018 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 019 - <<UNDEFINED>> */ HS_OA_ZERO,
  
  /* 020 - HS_OP_IADD    */ HS_OA_RTHREE,
  /* 021 - HS_OP_ISUB    */ HS_OA_RTHREE,
  /* 022 - HS_OP_IMUL    */ HS_OA_RTHREE,
  /* 023 - HS_OP_IDIV    */ HS_OA_RTHREE,
  /* 024 - HS_OP_IMOD    */ HS_OA_RTHREE,
  /* 025 - HS_OP_IREM    */ HS_OA_RTHREE,
  /* 026 - HS_OP_IPOW    */ HS_OA_RTHREE,
  /* 027 - HS_OP_ISHL    */ HS_OA_RTHREE,
  /* 028 - HS_OP_ISHR    */ HS_OA_RTHREE,
  /* 029 - HS_OP_IUSHR   */ HS_OA_RTHREE,
  /* 030 - HS_OP_IAND    */ HS_OA_RTHREE,
  /* 031 - HS_OP_IOR     */ HS_OA_RTHREE,
  /* 032 - HS_OP_IXOR    */ HS_OA_RTHREE,
  /* 033 - HS_OP_INOT    */ HS_OA_RTHREE,
  /* 034 - HS_OP_ICPL    */ HS_OA_RTHREE,
  /* 035 - HS_OP_ICMP    */ HS_OA_RTHREE,
  /* 036 - HS_OP_IINC    */ HS_OA_RONE,
  /* 037 - HS_OP_IDEC    */ HS_OA_RONE,
  /* 038 - HS_OP_INEG    */ HS_OA_RTWO,
  /* 039 - <<UNDEFINED>> */ HS_OA_ZERO,
  
  /* 040 - HS_OP_FADD    */ HS_OA_RTHREE,
  /* 041 - HS_OP_FSUB    */ HS_OA_RTHREE,
  /* 042 - HS_OP_FMUL    */ HS_OA_RTHREE,
  /* 043 - HS_OP_FDIV    */ HS_OA_RTHREE,
  /* 044 - HS_OP_FPOW    */ HS_OA_RTHREE,
  /* 045 - HS_OP_FNEG    */ HS_OA_RTWO,
  /* 046 - HS_OP_FCMP    */ HS_OA_RTHREE,
  /* 047 - HS_OP_FINC    */ HS_OA_RONE,
  /* 048 - HS_OP_FDEC    */ HS_OA_RONE,
  /* 049 - HS_OP_SIN     */ HS_OA_ZERO,
  
  /* 050 - HS_OP_COS     */ HS_OA_RTWO,
  /* 051 - HS_OP_TAN     */ HS_OA_RTWO,
  /* 052 - HS_OP_ASIN    */ HS_OA_RTWO,
  /* 053 - HS_OP_ACOS    */ HS_OA_RTWO,
  /* 054 - HS_OP_ATAN    */ HS_OA_RTWO,
  /* 055 - HS_OP_ATAN2   */ HS_OA_RTHREE,
  /* 056 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 057 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 058 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 059 - <<UNDEFINED>> */ HS_OA_ZERO, 
  
  /* 060 - HS_OP_GET_STACK     */ HS_OA_ZERO,
  /* 061 - HS_OP_SET_STACK     */ HS_OA_ZERO,
  /* 062 - HS_OP_GET_ARG       */ HS_OA_ZERO,
  /* 063 - HS_OP_SET_FIELD     */ HS_OA_ZERO,
  /* 064 - HS_OP_GET_FIELD     */ HS_OA_ZERO,
  /* 065 - HS_OP_STACK_RESERVE */ HS_OA_ZERO,
  /* 066 - HS_OP_MOVE          */ HS_OA_ZERO,
  /* 067 - HS_OP_SWAP          */ HS_OA_ZERO,
  /* 068 - <<UNDEFINED>>       */ HS_OA_ZERO,
  /* 069 - <<UNDEFINED>>       */ HS_OA_ZERO,
  
  /* 070 - HS_OP_PREPARE_ARGS  */ HS_OA_ZERO,
  /* 071 - HS_OP_SET_ARG       */ HS_OA_ZERO,
  /* 072 - HS_OP_CALL          */ HS_OA_ZERO,
  /* 073 - <<UNDEFINED>> */       HS_OA_ZERO,
  /* 074 - <<UNDEFINED>> */       HS_OA_ZERO,
  /* 075 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 076 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 077 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 078 - <<UNDEFINED>> */ HS_OA_ZERO,
  /* 079 - <<UNDEFINED>> */ HS_OA_ZERO, 
  
  /* 080 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 081 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 082 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 083 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 084 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 085 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 086 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 087 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 088 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 089 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 090 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 091 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 092 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 093 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 094 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 095 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 096 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 097 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 098 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 099 - HS_OP_INVALID */ HS_OA_ZERO, 
  
  /* 100 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 101 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 102 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 103 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 104 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 105 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 106 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 107 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 108 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 109 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 110 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 111 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 112 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 113 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 114 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 115 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 116 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 117 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 118 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 119 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 120 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 121 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 122 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 123 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 124 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 125 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 126 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 127 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 128 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 129 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 130 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 131 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 132 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 133 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 134 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 135 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 136 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 137 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 138 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 139 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 140 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 141 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 142 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 143 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 144 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 145 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 146 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 147 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 148 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 149 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 150 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 151 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 152 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 153 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 154 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 155 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 156 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 157 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 158 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 159 - HS_OP_INVALID */ HS_OA_ZERO, 
  
  /* 160 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 161 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 162 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 163 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 164 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 165 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 166 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 167 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 168 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 169 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 170 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 171 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 172 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 173 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 174 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 175 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 176 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 177 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 178 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 179 - HS_OP_INVALID */ HS_OA_ZERO, 
  
  /* 180 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 181 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 182 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 183 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 184 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 185 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 186 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 187 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 188 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 189 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 190 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 191 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 192 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 193 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 194 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 195 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 196 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 197 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 198 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 199 - HS_OP_INVALID */ HS_OA_ZERO, 
    
  /* 200 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 201 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 202 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 203 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 204 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 205 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 206 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 207 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 208 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 209 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 210 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 211 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 212 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 213 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 214 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 215 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 216 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 217 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 218 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 219 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 220 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 221 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 222 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 223 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 224 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 225 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 226 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 227 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 228 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 229 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 230 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 231 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 232 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 233 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 234 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 235 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 236 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 237 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 238 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 239 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 240 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 241 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 242 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 243 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 244 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 245 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 246 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 247 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 248 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 249 - HS_OP_INVALID */ HS_OA_ZERO,
  
  /* 250 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 251 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 252 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 253 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 254 - HS_OP_INVALID */ HS_OA_ZERO,
  /* 255 - HS_OP_INVALID */ HS_OA_ZERO,
  
}

static int
init_stack(hs_code_stack *stack, hs_module *module, size_t entry_point)
{
  stack->heap.data = malloc( HS_HEAP_INIT_SIZE * sizeof(hs_object) );
  if (!(stack->heap.data)) return 1;
  stack->heap.capa = HS_HEAP_INIT_SIZE;
  stack->heap.size = 0;
  stack->instruction = entry_point;
  stack->run = 1;
  stack->module = module;
  return 0;
}

static void
end_stack(hs_code_stack *stack)
{
  free(stack->heap.data);
}

static void 
decode(hs_context *HS, hs_code_stack *stack)
{
  if (module->opcode_size < stack->opcode) {
    stack->code = HS_OP_INVALID;
    return;
  } 
  hs_opcode i = stack->module->opcodes[stack->opcode];
  stack.code = i >> 24;
}

int
hs_run_code(hs_context *HS, hs_module *module, size_t entry_point)
{
  hs_code_stack stack;
  if (init_stack(HS, &stack, module, entry_point)) 
  {
    hs_panic( HS_ERROR_STACK_OVERFLOW );
    return 1;
  }
  while (stack.run) 
  {
    decode(HS, &stack);
    switch (stack.code)
    {
      default:
        hs_panic( HS, HS_ERROR_INVALID_OPCODE );
        break;
    }
  }
  end_stack(&stack);
  return hs_end_context(HS);
}