 #ifndef HS_MAP_H
 #define HS_MAP_H

#include <hs/array.h>
 
#define HS_DEFINE_MAP(K, V, N)                                                 \
                                                                               \
  typedef struct N##_pair { K key; V val; struct N##_pair *link[2]; } N##_pair;\
  typedef int ( *N##_cmp )( void*, K, K );                                     \
  typedef struct { size_t size; N##_pair *root; N##_cmp cmp; void *ctx; } N;   \
                                                                               \
  int                                                                          \
  N##_init( N *map N##_cmp cmp, void *ctx );                                   \
                                                                               \
  int                                                                          \
  N##_end( N *map );                                                           \
                                                                               \
  int                                                                          \
  N##_has_key( N *map, K key );                                                \
                                                                               \
  int                                                                          \
  N##_has_value( N *map, V value, void *ctx, int (*cmp)(void *, V, V) );       \
                                                                               \
  int                                                                          \
  N##_get( N *map, K key, V *dst );                                            \
                                                                               \
  int                                                                          \
  N##_set( N *map, K key, V value );
    
#define HS_DEFINE_MAP_COLLECTORS(K, V, N)                                      \
                                                                               \
  HS_DEFINE_ARRAY( K, N##_key_array   )                                        \
  HS_DEFINE_ARRAY( V, N##_value_array )                                        \
  HS_DEFINE_ARRAY( N##_pair*, N##_pair_array )                                 \
                                                                               \
  int                                                                          \
  N##_keys(  N *map, N##_key_array *dst );                                     \
                                                                               \
  int                                                                          \
  N##_values( N *map, N##_value_array *dst );                                  \
                                                                               \
  int                                                                          \
  N##_pairs( N *map, N##_pair_array *dst );
  
  
#define HS_DEFINE_MAP_ITERATORS(K, V, N)                                       \
                                                                               \
  void                                                                         \
  N##_each_pair( N *map, void *ctx, void (*fn)(void *, N##_pair *) );          \
                                                                               \
  void                                                                         \
  N##_each_key( N *map, void *ctx, void (*fn)( void *, K ) );                  \
                                                                               \
  void                                                                         \
  N##_each_value( N *map, void *ctx, void (*fn)( void *, K ) );                \
                                                                               \
  int                                                                          \
  N##_select( N *src, N *dst, void *ctx, int (*cmp)( void *, N##_pair * ) );   \
                                                                               \
  int                                                                          \
  N##_collect( N *src, N *dst, void *ctx, int (*cmp)( void *, N##_pair * ) );
 
#define HS_DEFINE_MAP_ARRAY_EXTENSIONS(K, V, N)                                \
                                                                               \
  HS_DEFINE_ARRAY_EXTENSIONS( K, N##_key_array )                               \
  HS_DEFINE_ARRAY_EXTENSIONS( V, N##_value_array )                             \
  HS_DEFINE_ARRAY_EXTENSIONS( N##_pair *, N##_pair_array )
  
#define HS_DEFINE_MAP_ARRAY_ITERATORS(K, V, N)                                 \
                                                                               \
  HS_DEFINE_ARRAY_ITERATORS( K, N##_key_array )                                \
  HS_DEFINE_ARRAY_ITERATORS( V, N##_value_array )                              \
  HS_DEFINE_ARRAY_ITERATORS( N##_pair *, N##_pair_array )
  
#define HS_IMPLEMENT_MAP(K, V, N)                                              \
                                                                               \
  int                                                                          \
  N##_init( N *map N##_cmp cmp, void *ctx )                                    \
  {                                                                            \
  }                                                                            \
                                                                               \
  int                                                                          \
  N##_end( N *map )                                                            \
  {                                                                            \
  }                                                                            \
                                                                               \
  int                                                                          \
  N##_has_key( N *map, K key )                                                 \
  {                                                                            \
  }                                                                            \
                                                                               \
  int                                                                          \
  N##_has_value( N *map, V value, void *ctx, int (*cmp)(void *, V, V) )        \
  {                                                                            \
  }                                                                            \
                                                                               \
  int                                                                          \
  N##_get( N *map, K key, V *dst )                                             \
  {                                                                            \
  }                                                                            \
                                                                               \
  int                                                                          \
  N##_set( N *map, K key, V value )                                            \
  {                                                                            \
  }
                                                                               
#define HS_IMPLEMENT_MAP_COLLECTORS(K, V, N)                                   \
                                                                               \
  HS_IMPLEMENT_ARRAY( K, N##_key_array   )                                     \
  HS_IMPLEMENT_ARRAY( V, N##_value_array )                                     \
  HS_IMPLEMENT_ARRAY( N##_pair*, N##_pair_array )                              \
                                                                               \
  int                                                                          \
  N##_keys(  N *map, N##_key_array *dst )                                      \
  {                                                                            \
  }                                                                            \
                                                                               \
  int                                                                          \
  N##_values( N *map, N##_value_array *dst )                                   \
  {                                                                            \
  }                                                                            \
                                                                               \
  int                                                                          \
  N##_pairs( N *map, N##_pair_array *dst )                                     \
  {                                                                            \
  }
  
#define HS_IMPLEMENT_MAP_ITERATORS(K, V, N)                                    \
                                                                               \
  void                                                                         \
  N##_each_pair( N *map, void *ctx, void (*fn)(void *, N##_pair *) )           \
  {                                                                            \
  }                                                                            \
                                                                               \
  void                                                                         \
  N##_each_key( N *map, void *ctx, void (*fn)( void *, K ) )                   \
  {                                                                            \
  }                                                                            \
                                                                               \
  void                                                                         \
  N##_each_value( N *map, void *ctx, void (*fn)( void *, K ) )                 \
  {                                                                            \
  }                                                                            \
                                                                               \
  int                                                                          \
  N##_select( N *src, N *dst, void *ctx, int (*cmp)( void *, N##_pair * ) )    \
  {                                                                            \
  }                                                                            \
                                                                               \
  int                                                                          \
  N##_collect( N *src, N *dst, void *ctx, int (*cmp)( void *, N##_pair * ) )   \
  {                                                                            \
  }
                                                                               
#define HS_IMPLEMENT_MAP_ARRAY_EXTENSIONS(K, V, N)                             \
                                                                               \
  HS_IMPLEMENT_ARRAY_EXTENSIONS( K, N##_key_array )                            \
  HS_IMPLEMENT_ARRAY_EXTENSIONS( V, N##_value_array )                          \
  HS_IMPLEMENT_ARRAY_EXTENSIONS( N##_pair *, N##_pair_array )
  
#define HS_DEFINE_MAP_ARRAY_ITERATORS(K, V, N)                                 \
                                                                               \
  HS_IMPLEMENT_ARRAY_ITERATORS( K, N##_key_array )                             \
  HS_IMPLEMENT_ARRAY_ITERATORS( V, N##_value_array )                           \
  HS_IMPLEMENT_ARRAY_ITERATORS( N##_pair *, N##_pair_array )  
  
 #endif /* HS_MAP_H */