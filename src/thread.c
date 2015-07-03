#include <stdlib.h>

#include "hs/thread.h"

#ifdef _WIN32

static DWORD 
ThreadProc ( LPVOID lpdwThreadParam )
{
  hs_thread *s = lpdwThreadParam;
  switch (WaitForSingleObject(s->mutex, INFINITE))
  {
    case WAIT_OBJECT_0:
      s->r = s->fn(s->ctx);
      ReleaseMutex(th->mutex);
      return (DWORD)0;
    default:
      return 1;
  };
}

#else
  
static void *
pthread_init_call(void *arg)
{
  hs_thread *s = arg;
  s->r = s->fn(s->ctx);
  return arg;
}

#endif  

int
hs_thread_init( hs_thread *th, void *ctx, hs_thread_func fn )
{
#ifdef _WIN32
  SECURITY_ATTRIBUTES  sa;
  sa.nLength = sizeof *sa;
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle = TRUE;
  th->mutex = CreateMutex(&sa, TRUE, NULL );
  if (th->mutex == NULL) return 1;
#endif
  th->fn  = fn;
  th->ctx = ctx;
  return 0;
}

int
hs_thread_run( hs_thread *th )
{
#ifdef _WIN32
  th->handle = CreateThread(NULL, 0, ThreadProc, th, 0, NULL);
  if (th->handle == NULL) 
  {
    CloseHandle(th->mutex); 
    return 1;
  }
  ReleaseMutex(th->mutex);
  return 0;
#else
  return pthread_create(&(th->handle), NULL, pthread_init_call, th );
#endif  
}

int
hs_thread_end( hs_thread *th )
{
#ifdef _WIN32
  CloseHandle(th->handle); 
  CloseHandle(th->mutex);
#endif  
  return 0;
}

int
hs_thread_join( hs_thread *th, int *result  )
{
#ifdef _WIN32
  switch (WaitForSingleObject(th->mutex, INFINITE))
  {
    case WAIT_OBJECT_0:
      switch (WaitForSingleObject(th->handle, INFINITE))
      {
        case WAIT_OBJECT_0:
          if (result) *result = th->r;
          return 0;
        default: break;
      }
    default: break;
  };
  return 1;
#else
  void *result;
  int p = pthread_join(th->handle, &result);
  if (result) *result = th->r;
  return p;
#endif  
}

int
hs_mutex_init( hs_mutex *mx )
{
#ifdef _WIN32
  SECURITY_ATTRIBUTES  sa;
  sa.nLength = sizeof *sa;
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle = TRUE;
  *mx = CreateMutex(&sa, FALSE, NULL );
  return *mx == NULL ? 1 : 0;
#else
  return pthread_mutex_init( mx, NULL );
#endif  
}

int
hs_mutex_end( hs_mutex *mx )
{
#ifdef _WIN32
  return !CloseHandle(*mx);
#else
  return pthread_mutex_destroy( mx );
#endif  
}

int
hs_mutex_lock( hs_mutex *mx )
{
#ifdef _WIN32
  switch (WaitForSingleObject(*mx, INFINITE))
  {
    WAIT_OBJECT_0:
      return 0;
    default:
      break;
  };
  return 1;
#else
  return pthread_mutex_lock( mx );
#endif  
}

int
hs_mutex_unlock( hs_mutex *mx )
{
#ifdef _WIN32
  return !ReleaseMutex(*mx);
#else
  return pthread_mutex_unlock( mx );
#endif  
}