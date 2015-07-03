#ifndef HS_THREAD_H
#define HS_THREAD_H

typedef int (*hs_thread_func)(void *);

#ifdef _WIN32
#include <windows.h>
#else
#include <pthreads.h>
#endif



typedef struct 
{ 
#ifdef _WIN32
  HANDLE handle; 
  HANDLE mutex; 
#else
  pthread_t handle; 
#endif  
  void *ctx; 
  int r; 
  hs_thread_func fn; 
} hs_thread;

typedef HANDLE hs_mutex;

typedef struct 
{ 
  void *ctx; 
  int r;  
  hs_thread_func fn;  
} hs_thread;

typedef pthread_mutex_t hs_mutex;



int
hs_thread_init( hs_thread *th, void *ctx, hs_thread_func fn );

int
hs_thread_run( hs_thread *th );

int
hs_thread_end( hs_thread *th );

int
hs_thread_join( hs_thread *th );

int
hs_mutex_init( hs_mutex *mx );

int
hs_mutex_end( hs_mutex *mx );

int
hs_mutex_lock( hs_mutex *mx );

int
hs_mutex_unlock( hs_mutex *mx );

#endif /* HS_THREAD_H */