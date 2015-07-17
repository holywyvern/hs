#ifndef HS_FILE_H
#define HS_FILE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32

#include <windows.h>

#else

#include <fcntl.h>

#endif

#ifdef _WIN32

  /** Windows uses files as a HANDLE */
  typedef HANDLE hs_file;

#else
  /** POSIX-like system uses of course, integers as file descriptors */
  typedef int hs_file;

#endif

/**
 * @brienf opens a file, in a mode indicated
 *
 * All files are opened as both byte and text mode.
 * The parameters work just like the <stdio.h> library:
 *
 * "r" opens the file for reading, if the file doesn't exists, it returns an 
 * error.
 * "w" opens the file for writing, if the file doesn't exists the system will
 * try to create it, if it failed, then it should return an error.
 * If you want to read-write you can write "wr" or "a"
 * Adding "+" into the mode, puts the file in append mode, so if you write
 * a file with "+" it will not be truncated before use.
 *
 * @param fd a file descriptor to store the file 
 * @param name A valued name for a file in UTF-8
 * @param mode The opening mode
 * @return zero on success, a non-zero value on failure
 */
int
hs_file_open(hs_file *fd, const char *name, const char *mode );

/**
 * @brief Closes a previously opened file
 * 
 * @param fd A file to close
 * @return zero on success, a non-zero value on failure
 */
int
hs_file_close(hs_file *fd);

#ifdef __cplusplus
}
#endif

#endif /* HS_FILE_H */