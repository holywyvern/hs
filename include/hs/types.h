#ifndef HS_TYPES_H
#define HS_TYPES_H

#include <stdint.h>
#include <stdlib.h>

#include "hs/bigint.h"
#include "hs/array.h"
#include "hs/list.h"
#include "hs/set.h"
#include "hs/map.h"

typedef int32_t hs_int;
typedef float   hs_float;
struct hs_box;
struct hs_state;

typedef struct hs_object hs_object;
typedef struct hs_state hs_state;

HS_DEFINE_ARRAY(hs_object, hs_array)
HS_DEFINE_LIST(hs_object, hs_array)
HS_DEFINE_SET(hs_object, hs_array)
HS_DEFINE_MAP(hs_object, hs_object, hs_array)

typedef int (*hs_native_fn)(hs_state *, hs_object *);



struct hs_object
{
  union
  {
    hs_int         as_int;
    hs_float       as_float;
    hs_native_fn   as_native_fn;
    struct hs_box *as_box;
  } value;
  enum
  {
    
    HS_OBJECT_
    
    HS_OBJECT_FIXINT,
    HS_OBJECT_BIGINT,
    
    HS_OBJECT_FLOAT,
    HS_OBJECT_BIGDECIMAL,
    
    HS_OBJECT_STRING,
    
    HS_OBJECT_ARRAY,
    HS_OBJECT_LIST,
    HS_OBJECT_SET,
    HS_OBJECT_MAP,
    
    HS_OBJECT_NATIVE_FUNCTION,
    HS_OBJECT_CODE_FUNCTION,
    
    HS_OBJECT_BOXED,
    
    HS_OBJECT_CUSTOM,
    
  } tag;

};

struct hs_box
{
  hs_object_area *area;
  hs_box         *links[2]; 
  union
  {
    hs_bigint as_bigint;
    hs_array  as_array;
    hs_list   as_list;
    hs_set    as_set;
    hs_map    as_map;
  } value;
};

#endif /* HS_TYPES_H */