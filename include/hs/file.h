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

#include <stdint.h>

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

/**
 * @brief Gets the current file handle for the standard input
 *
 * @param fp A pointer to store the file descriptor handle
 */
void
hs_get_stdin(hs_file *fp);

/**
 * @brief Gets the current file handle for the standard output
 *
 * @param fp A pointer to store the file descriptor handle
 */
void
hs_get_stdout(hs_file *fp);

/**
 * @brief Gets the current file handle for the standard error 
 *
 * @param fp A pointer to store the file descriptor handle
 */
void
hs_get_stderr(hs_file *fp);

/**
 * @brief Sets the current file handle for the standard input
 *
 * @param fp A pointer with the file descriptor handle
 * @return zero on success, a non zero value on failure
 */
int
hs_set_stdin(hs_file *fp);

/**
 * @brief Sets the current file handle for the standard output
 *
 * @param fp A pointer with the file descriptor handle
 * @return zero on success, a non zero value on failure
 */
int
hs_set_stdout(hs_file *fp);

/**
 * @brief Sets the current file handle for the standard error
 *
 * @param fp A pointer with the file descriptor handle
 * @return zero on success, a non zero value on failure
 */
int
hs_set_stderr(hs_file *fp);

int
hs_file_eof(hs_file *fp);

size_t
hs_file_read_bytes(hs_file *fp, char *data, const size_t size);

size_t
hs_file_write_bytes(hs_file *fp, const void *data, const size_t size);

int
hs_file_move(hs_file *fp, intmax_t distance, int relative_to);

size_t
hs_file_read_u8(hs_file *fp, uint8_t *dst, size_t const size);

size_t
hs_file_read_u16(hs_file *fp, uint16_t *dst, size_t const size);

size_t
hs_file_read_u32(hs_file *fp, uint32_t *dst, size_t const size);

size_t
hs_file_read_u64(hs_file *fp, uint64_t *dst, size_t const size);

size_t
hs_file_read_umax(hs_file *fp, uintmax_t *dst, size_t const size);

size_t
hs_file_read_i8(hs_file *fp, uint8_t *dst, size_t const size);

size_t
hs_file_read_i16(hs_file *fp, uint16_t *dst, size_t const size);

size_t
hs_file_read_i32(hs_file *fp, uint32_t *dst, size_t const size);

size_t
hs_file_read_i64(hs_file *fp, uint64_t *dst, size_t const size);

size_t
hs_file_read_imax(hs_file *fp, intmax_t *dst, size_t const size);

size_t
hs_file_read_float(hs_file *fp, float *dst, size_t const size);

size_t
hs_file_read_double(hs_file *fp, double *dst, size_t const size);

size_t
hs_file_read_ldouble(hs_file *fp, long double *dst, const size_t size);

size_t
hs_file_write_u8(hs_file *fp, const uint8_t *value, const size_t size);

size_t
hs_file_write_u16(hs_file *fp, const uint16_t *value, const size_t size);

size_t
hs_file_write_u32(hs_file *fp, const uint32_t *value, const size_t size);

size_t
hs_file_write_u64(hs_file *fp, const uint64_t *value, const size_t size);

size_t
hs_file_write_umax(hs_file *fp, const uintmax_t *value, const size_t size);

size_t
hs_file_write_i8(hs_file *fp, const uint8_t *value, const size_t size);

size_t
hs_file_write_i16(hs_file *fp, const uint16_t *value, const size_t size);

size_t
hs_file_write_i32(hs_file *fp, const uint32_t *value, const size_t size);

size_t
hs_file_write_i64(hs_file *fp, const uint64_t *value, const size_t size);

size_t
hs_file_write_imax(hs_file *fp, const intmax_t *value, const size_t size);

size_t
hs_file_write_float(hs_file *fp, const float *value, const size_t size);

size_t
hs_file_write_double(hs_file *fp, const double *value, const size_t size);

size_t
hs_file_write_ldouble(hs_file *fp, const long double *value, const size_t size);

#define HS_FILE_POS_CURRENT 0
#define HS_FILE_POS_START   1
#define HS_FILE_POS_END     2

#ifdef __cplusplus
}
#endif

#endif /* HS_FILE_H */