/* Humming Script - Collection of libraries to build a scripting language
 * Written in 2015 by Ramiro Rojo <ramiro.rojo.cretta@gmail.com>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright 
 * and related and neighboring rights to this software to the public domain 
 * worldwide. This software is distributed without any warranty.
 * You should have received a copy of the CC0 Public Domain Dedication along 
 * with this software. If not, see 
 * <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
#ifndef HS_LIST_H
#define HS_LIST_H

#define HS_DEFINE_LIST(type, name)                                             \
                                                                               \
  typedef struct { type value; struct name##_node *links[2]; } name_##node;    \
  typedef struct { size_t size; name##_node *first; name##_node *last; } name; \
                                                                               \
  int                                                                          \
  name##_init( name *list );                                                   \
                                                                               \
  void                                                                         \
  name##_end( name *list );                                                    \
                                                                               \
  size_t                                                                       \
  name##_size( list );                                                         \
                                                                               \
  int                                                                          \
  name##_insert( name *list, size_t at, type value );                          \
                                                                               \
  int                                                                          \
  name##_get( name *list, size_t at, type *value );                            \
                                                                               \
  int                                                                          \
  name##_remove( name *list, type value, void *ctx,                            \
                 int (*cmp)(void *, const type, const type) );                 \
                                                                               \
  int                                                                          \
  name##_remove_at( name *list, size_t index );                                \
                                                                               \
  int                                                                          \
  name##_index_of( name *list, type value, size_t *pos, void *ctx,             \
                 int (*cmp)(void *, const type, const type) );                 \
                                                                               \
  void                                                                         \
  name##_sort( name *list, void *ctx,                                          \
               int (*cmp)(void *, const type, const type) );
  
#define HS_DEFINE_LIST_EXTENSIONS(type, name)                                  \
                                                                               \
  int                                                                          \
  name##_copy(name *src, name *dst );                                          \
                                                                               \
  int                                                                          \
  name##_push( name *list,  type value );                                      \
                                                                               \
  int                                                                          \
  name##_pop( name *list,  type *value );                                      \
                                                                               \
  int                                                                          \
  name##_unshift( name *list,  type value );                                   \
                                                                               \
  int                                                                          \
  name##_shift( name *list,  type *value );                                    \
                                                                               \
  int                                                                          \
  name##_first( name *list,  type *value );                                    \
                                                                               \
  int                                                                          \
  name##_last( name *list,  type *value );                                     \
                                                                               \
  int                                                                          \
  name##_insert_all( name *list, size_t at, name *from );
  
#define HS_DEFINE_LIST_ITERATORS(type, name)                                   \
                                                                               \
  void                                                                         \
  name##_each( name *list, void *ctx, void (*fn)(void *, size_t, type) );      \
                                                                               \
  int                                                                          \
  name##_select( name *src, name *dst, void *ctx,                              \
                 int (*fn)(void *, size_t, type) );                            \
                                                                               \
  int                                                                          \
  name##_map( name *src, name *dst, void *ctx,                                 \
              type (*fn)(void *, size_t, type) );               
  
  
#define HS_IMPLEMENT_LIST(type, name)                                          \
                                                                               \
  int                                                                          \
  name##_init( name *list )                                                    \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  void                                                                         \
  name##_end( name *list )                                                     \
  {                                                                            \
  }                                                                            \
                                                                               \
  size_t                                                                       \
  name##_size( list )                                                          \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_insert( name *list, size_t at, type value )                           \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_get( name *list, size_t at, type *value )                             \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_remove( name *list, type value, void *ctx,                            \
                 int (*cmp)(void *, const type, const type) )                  \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_remove_at( name *list, size_t index )                                 \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_index_of( name *list, type value, size_t *pos, void *ctx,             \
                 int (*cmp)(void *, const type, const type) )                  \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  void                                                                         \
  name##_sort( name *list, void *ctx,                                          \
               int (*cmp)(void *, const type, const type) )                    \
  {                                                                            \
  }
  
#define HS_IMPLEMENT_LIST_EXTENSIONS(type, name)                               \
                                                                               \
  int                                                                          \
  name##_copy(name *src, name *dst )                                           \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_push( name *list,  type value )                                       \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_pop( name *list,  type *value )                                       \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_unshift( name *list,  type value )                                    \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_shift( name *list,  type *value )                                     \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_first( name *list,  type *value )                                     \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_last( name *list,  type *value )                                      \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_insert_all( name *list, size_t at, name *from )                       \
  {                                                                            \
    return 0;                                                                  \
  }
                                                                               
#define HS_IMPLEMENT_LIST_ITERATORS(type, name)                                \
                                                                               \
  void                                                                         \
  name##_each( name *list, void *ctx, void (*fn)(void *, size_t, type) )       \
  {                                                                            \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_select( name *src, name *dst, void *ctx,                              \
                 int (*fn)(void *, size_t, type) )                             \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
                                                                               \
  int                                                                          \
  name##_map( name *src, name *dst, void *ctx,                                 \
              type (*fn)(void *, size_t, type) )                               \
  {                                                                            \
    return 0;                                                                  \
  }
#endif /* HS_LIST_H */