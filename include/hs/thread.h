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
#ifndef HS_THREAD_H
#define HS_THREAD_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*hs_thread_func)(void *);

#ifdef _WIN32
#include <windows.h>

/** The type used for mutex objects on windows. */
typedef HANDLE hs_mutex;

#else
#include <pthreads.h>

/** The type used for mutex objects on POSIX-like systems. */
typedef pthread_mutex_t hs_mutex;

#endif


/**
 * @brief the type used to store data as a thread.
 *
 * This object is a wrapper to generic type threads for a system.
 *
 */
typedef struct 
{ 
#ifdef _WIN32
  /** 
   * On windows, we may prefer a mutex for control, also almost everything
   * is a HANDLE
   */
  HANDLE handle; 
  HANDLE mutex; 
#else
  /** On POSIX-like system, its a lot easier  */
  pthread_t handle; 
#endif  
  /** A context used to pass data */
  void *ctx; 
  /** The result of the function as a promise */
  int r; 
  /** The function to call when the thread starts */
  hs_thread_func fn; 
} hs_thread;


/**
 * @brief Starts a thread with defaut values.
 *
 * The thread does NOT run after creation.
 * To run it, use hs_thread_run().
 *
 * @param th a hs_thread record to initialize.
 * @param ctx The context to pass inside the thread.
 * @param fn A callback used when the thread runs.
 *
 * @return zero on success, or a non zero value on failure
 */
int
hs_thread_init( hs_thread *th, void *ctx, hs_thread_func fn );

/**
 * @brief Runs a previously created thread.
 *
 * Runs a thread already initialized with hs_thread_init().
 * Finished threads with this method is called again has undefined behaviour.
 * You may want to reuse a variable, calling hs_thread_end() and then 
 * hs_thread_init() on the same variable.
 *
 * @param th a thread already initialized.
 *
 * @return zero on success, or a non zero value on failure
 */
int
hs_thread_run( hs_thread *th );

/**
 * @brief Cleans an used thread after it's usage.
 *
 * Closing an already cleaned thread, or a running thread is undefined 
 * behaviour.
 *
 * @param th a thread already initialized.
 *
 * @return zero on success, or a non zero value on failure
 */
int
hs_thread_end( hs_thread *th );

/**
 * @brief Stops execution of current thread until the thread stops.
 *
 * If the thread already finishes, this function does nothing.
 *
 * @param th a thread to ait for.
 * @param result A pointer to put the result of the thread. Can be NULL.
 *
 * @return zero on success, or a non zero value on failure
 */
int
hs_thread_join( hs_thread *th, int *result );

/**
 * @brief Creates a mutex for future use.
 *
 * @param mx a mutex to initialize.
 *
 * @return zero on success, or a non zero value on failure
 */
int
hs_mutex_init( hs_mutex *mx );

/**
 * @brief Ends a mutex, cleaning resources.
 *
 * @param mx a mutex to close.
 *
 * @return zero on success, or a non zero value on failure
 */
int
hs_mutex_end( hs_mutex *mx );

/**
 * @brief Stops execution, until the mutex is released, then locks it.
 *
 * If the same thread already locked the mutex, it is undefined behaviour.
 * On window it usually counts the number of locks of the thread, while on
 * POSIX systems may produce a deadlock.
 *
 * @param mx a mutex to lock.
 *
 * @return zero on success, or a non zero value on failure
 */
int
hs_mutex_lock( hs_mutex *mx );

/**
 * @brief Releases a mutex, allowing other threads to continue execution.
 *
 * Released an already unlocked mutex by the thread has undefined behaviour.
 *
 * @param mx a mutex to unlock.
 *
 * @return zero on success, or a non zero value on failure
 */
int
hs_mutex_unlock( hs_mutex *mx );

#ifdef __cplusplus
}
#endif

#endif /* HS_THREAD_H */