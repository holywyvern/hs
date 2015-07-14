/**
 * For reference about the license terms, please refer to <https://www.github.com/holywyvern/hs>
 *
 */
#ifndef HS_ARRAY_H
#define HS_ARRAY_H

#define HS_DEFINE_ARRAY(type, name)                                            \
                                                                               \
  typedef struct { size_t size; size_t capa; type *data; } name;               \
                                                                               \
  int                                                                          \
  name##_init( name *array );                                                  \
                                                                               \
  void                                                                         \
  name##_end( name *array );                                                   \
                                                                               \
  size_t                                                                       \
  name##_size( array );                                                        \
                                                                               \
  int                                                                          \
  name##_insert( name *array, size_t at, type value );                         \
                                                                               \
  int                                                                          \
  name##_get( name *array, size_t at, type *value );                           \
                                                                               \
  int                                                                          \
  name##_remove( name *array, type value, void *ctx,                           \
                 int (*cmp)(void *, const type, const type) );                 \
                                                                               \
  int                                                                          \
  name##_remove_at( name *array, size_t index );                               \
                                                                               \
  int                                                                          \
  name##_index_of( name *array, type value, size_t *pos, void *ctx,            \
                 int (*cmp)(void *, const type, const type) );                 \
                                                                               \
  void                                                                         \
  name##_sort( name *array, void *ctx,                                         \
               int (*cmp)(void *, const type, const type) );
  
#define HS_DEFINE_ARRAY_EXTENSIONS(type, name)                                 \
                                                                               \
  int                                                                          \
  name##_copy(name *src, name *dst );                                          \
                                                                               \
  int                                                                          \
  name##_push( name *array,  type value );                                     \
                                                                               \
  int                                                                          \
  name##_pop( name *array,  type *value );                                     \
                                                                               \
  int                                                                          \
  name##_unshift( name *array,  type value );                                  \
                                                                               \
  int                                                                          \
  name##_shift( name *array,  type *value );                                   \
                                                                               \
  int                                                                          \
  name##_first( name *array,  type *value );                                   \
                                                                               \
  int                                                                          \
  name##_last( name *array,  type *value );                                    \
                                                                               \
  int                                                                          \
  name##_reserve( name *array,  size_t size );                                 \
                                                                               \
  int                                                                          \
  name##_insert_all( name *array, size_t at, name *from );
  
#define HS_DEFINE_ARRAY_ITERATORS(type, name)                                  \
                                                                               \
  void                                                                         \
  name##_each( name *array, void *ctx, void (*fn)(void *, size_t, type) );     \
                                                                               \
  int                                                                          \
  name##_select( name *src, name *dst, void *ctx,                              \
                 int (*fn)(void *, size_t, type) );                            \
                                                                               \
  int                                                                          \
  name##_map( name *src, name *dst, void *ctx,                                 \
              type (*fn)(void *, size_t, type) );               
  
  
#define HS_IMPLEMENT_ARRAY(type, name)                                         \
                                                                               \
  int                                                                          \
  name##_init( name *array )                                                   \
  {                                                                            \
    array->size = 0;                                                           \
    array->capa = 1;                                                           \
    array->data = malloc(sizeof(type) );                                       \
    return array->data ? 0 : 1;                                                \
  }                                                                            \
                                                                               \
  void                                                                         \
  name##_end( name *array )                                                    \
  {                                                                            \
    free( array->data );                                                       \
  }                                                                            \
                                                                               \
  size_t                                                                       \
  name##_size( array )                                                         \
  {                                                                            \
    return array->size;                                                        \
  }                                                                            \
                                                                               \
  static int                                                                   \
  name##_check_space(name *array, size_t size)                                 \
  {                                                                            \
    if ( array->size > SIZE_MAX - size) return 1;                              \
    size_t new_size = array->size + size;                                      \
    if ( new_size <= array->capa ) return 0;                                   \
    if ( new_size > SIZE_MAX - array->capa ) return 1;                         \
    void *ptr = realloc(array->data, new_size);                                \
    if (!ptr) return 1;                                                        \
    array->capa = new_size;                                                    \
    array->data = ptr;                                                         \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_insert( name *array, size_t at, type value )                          \
  {                                                                            \
    if (at > array->size) return 1;                                            \
    if ( name##_check_space(array, 1) ) return 1;                              \
    for (size_t i = array->size; i > at ; --i )                                \
    {                                                                          \
      array->data[i] = array->data[i - 1];                                     \
    }                                                                          \
    array->data[at] = value;                                                   \
    array->size += 1;                                                          \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_get( name *array, size_t at, type *value )                            \
  {                                                                            \
    if (at >= array->size) return 1;                                           \
    *value = array->data[at];                                                  \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_remove( name *array, type value, void *ctx,                           \
                 int (*cmp)(void *, const type, const type) )                  \
  {                                                                            \
    if (array->size == 0) return 1;                                            \
    int result = 1;                                                            \
    for (size_t i = array->size; i > 0; --i)                                   \
    {                                                                          \
      if ( cmp(ctx, value, array->data[i - 1]) == 0 )                          \
      {                                                                        \
        for (size_t j = i; j < array->size; ++j)                               \
        {                                                                      \
          array->data[j - 1] = array->data[j];                                 \
        }                                                                      \
        array->size -= 1;                                                      \
        result = 0;                                                            \
      }                                                                        \
    }                                                                          \
    return result;                                                             \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_remove_at( name *array, size_t index )                                \
  {                                                                            \
    if (array->size <= index) return 1;                                        \
    for (size_t i = index + 1; i < array->size; ++i)                           \
    {                                                                          \
      array->data[i - 1] = array->data[i];                                     \
    }                                                                          \
    array->size -= 1;                                                          \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_index_of( name *array, type value, size_t *pos, void *ctx,            \
                 int (*cmp)(void *, const type, const type) )                  \
  {                                                                            \
    for (size_t i = 0; i < array->size; ++i)                                   \
    {                                                                          \
      if (cmp(ctx, value, array->data[i]) == 0)                                \
      {                                                                        \
        *pos = i;                                                              \
        return 0;                                                              \
      }                                                                        \
    };                                                                         \
    return 1;                                                                  \
  }                                                                            \
                                                                               \
  static void                                                                  \
  name##_sort_r( type *array, size_t l, size_t r, void *ctx,                   \
               int (*cmp)(void *, const type, const type) )                    \
  {                                                                            \
    at_size i, last;                                                           \
    type t;                                                                    \
    if (l >= r) return;                                                        \
    t = array[l];                                                              \
    array[l] = array[(l + r) / 2];                                             \
    array[(l + r) / 2] = t;                                                    \
    last = l;                                                                  \
    for (i = l+1; i <= r; i++)                                                 \
    {                                                                          \
      if (cmp(ctx, array[i], array[l]) < 0)                                    \
      {                                                                        \
        ++last;                                                                \
        t = array[last];                                                       \
        array[last] = array[i];                                                \
        array[i] = t;                                                          \
      }                                                                        \
    }                                                                          \
    t = array[l];                                                             \
    array[l] = array[last];                                                    \
    array[last] = t;                                                           \
    name##_sort_r(array, l, last-1, ctx, cmp);                                 \
    name##_sort_r(array, last+1, r, ctx, cmp);                                 \
  }                                                                            \
                                                                               \
  void                                                                         \
  name##_sort( name *array, void *ctx,                                         \
               int (*cmp)(void *, const type, const type) )                    \
  {                                                                            \
    if (array->size < 2) return;                                               \
    name##_sort_r(array->data, 0, array->size; ctx, cmp);                      \
  }
  
#define HS_IMPLEMENT_ARRAY_EXTENSIONS(type, name)                              \
                                                                               \
  int                                                                          \
  name##_copy(name *src, name *dst )                                           \
  {                                                                            \
    size_t bsize = src->capa * sizeof(type);                                   \
    dst->size = src->size;                                                     \
    dst->capa = src->capa;                                                     \
    dst->data = malloc(bsize);                                                 \
    if (!dst->data) return 1;                                                  \
    memcpy(dst->data, src, bsize);                                             \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_push( name *array,  type value )                                      \
  {                                                                            \
    return name##_insert(array, array->size, value );                          \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_pop( name *array,  type *value )                                      \
  {                                                                            \
    if (array->size < 1) return 1;                                             \
    name##_get( array, array->size - 1, value );                               \
    name##_remove_at( array, array->size - 1 );                                \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_unshift( name *array,  type value )                                   \
  {                                                                            \
    return name##_insert(array, 0, value );                                    \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_shift( name *array,  type *value )                                    \
  {                                                                            \
    if (array->size < 1) return 1;                                             \
    name##_get( array, 0, value );                                             \
    name##_remove_at( array, 0 );                                              \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_first( name *array,  type *value )                                    \
  {                                                                            \
    return name##_get( array, 0, value );                                      \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_last( name *array,  type *value )                                     \
  {                                                                            \
    if (array->size < 1) return 1;                                             \
    return name##_get( array, array->size - 1, value );                        \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_reserve( name *array,  size_t size )                                  \
  {                                                                            \
    if (array->capa > SIZE_MAX - size) return 1;                               \
    size_t new_capa = size + array->capa;                                      \
    type *ptr = realloc(array->data, sizeof(type) * new_capa );                \
    if (!ptr) return 1;                                                        \
    array->data = ptr;                                                         \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_insert_all( name *array, size_t at, name *from )                      \
  {                                                                            \
    if (at > array->size) return 1;                                            \
    if ( name##_check_space(array, from->size) ) return 1;                     \
    for (size_t i = array->size + from->size - 1; i > at ; --i )               \
    {                                                                          \
      array->data[i] = array->data[i - from->size];                            \
    }                                                                          \
    for (size_t j = 0; j < from->size; ++j)                                    \
    {                                                                          \
      array->data[at + j] = from->[j];                                         \
    }                                                                          \
    array->size += from->size;                                                 \
    return 0;                                                                  \
  }
  
#define HS_IMPLEMENT_ARRAY_ITERATORS(type, name)                               \
                                                                               \
  void                                                                         \
  name##_each( name *array, void *ctx, void (*fn)(void *, size_t, type)        \
  {                                                                            \
    for (size_t i = 0; i < array->size; ++i)                                   \
    {                                                                          \
      fn(ctx, i, array->data[i]);                                              \
    }                                                                          \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_select( name *src, name *dst, void *ctx,                              \
                 int (*fn)(void *, size_t, type) )                             \
  {                                                                            \
    size_t i;                                                                  \
    if ( name##_init( dst ) ) return 1;                                        \
    for ( i = 0; i < src->size; ++i )                                          \
    {                                                                          \
      if ( fn( ctx, i, src->data[i] ) )                                        \
      {                                                                        \
        if ( name##_push( dst, src->data[i] ) )                                \
        {                                                                      \
          name##_end( dst );                                                   \
          return 1;                                                            \
        }                                                                      \
      }                                                                        \
    }                                                                          \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_map( name *src, name *dst, void *ctx,                                 \
              type (*fn)(void *, size_t, type) )                               \
  {                                                                            \
    size_t i;                                                                  \
    if ( name##_init( dst ) ) return 1;                                        \
    for ( i = 0; i < src->size; ++i )                                          \
    {                                                                          \
      type tmp = fn( ctx, i, src->data[i] );                                   \
      if ( name##_push( dst, tmp ) )                                           \
      {                                                                        \
        name##_end( dst );                                                     \
        return 1;                                                              \
      }                                                                        \
    }                                                                          \
    return 0;                                                                  \
  }
  
#endif /* HS_ARRAY_H */