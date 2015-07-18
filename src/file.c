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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hs/file.h"

#ifdef _WIN32

static LPTSTR
utf8_to_utf16(const char *str)
{
    LPTSTR result = NULL;
    int size = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    if (size > 0)
    {
        result = at_malloc(sizeof(TCHAR) * ( size + 1) );
        if (result)
        {
            result[size] = '\0';
            size = MultiByteToWideChar(CP_UTF8, 0, str, -1, 
                                        result, size);
            if (size > 0)
                return result;
        }
    };
    return NULL;
};


#else
  #include <unistd.h>
#endif

int
hs_file_open(hs_file *fd, const char *name, const char *mode )
{
  int has_b, has_r, has_w, has_a;
  
  has_b = strchr(mode, 'b') && (!strchr(mode, 't'));
  has_r = strchr(mode, 'r') || strchr(mode, 'a');
  has_w = strchr(mode, 'w') || strchr(mode, 'a');
  has_a = strchr(mode, '+') && 1;  
  if (!has_w) has_r = 1;
#ifdef _WIN32
  DWORD access = 0;
  DWORD disposition = 0;
  LPTSTR filename = utf8_to_utf16(name);
  if (has_r) access |= GENERIC_READ; 
  if (has_w) access |= GENERIC_WRITE; 
  
  if (has_a) 
  {
    if (has_w)
      disposition = OPEN_ALWAYS;
    else
      disposition = OPEN_EXISTING;
  }
  else if (has_w)
    disposition = CREATE_ALWAYS;
  else
    disposition = OPEN_EXISTING;
  
  *fd = CreateFile(filename, access, 0, NULL, disposition, 
                   FILE_ATTRIBUTE_NORMAL, NULL);
  free(filename);
  if (*fd == INVALID_HANDLE_VALUE) return 1;
);
  
#else
  int flags;
  if (has_r && has_w) 
    flags = O_RDWR;
  else if (has_w)
    flags = O_WRONLY;
  else
    flags = O_RDONLY;

  if (has_a) 
    flags |= O_APPEND|O_CREAT;
  else if (has_w)
    flags |= O_CREAT|O_TRUNC;
  
  *fd = open(name, flags);

  if (*fd == -1) return 1;
  
#endif  
  return 0;
}

int
hs_file_close(hs_file *fd)
{
#ifdef _WIN32  
  return !CloseHandle(*fd);
#else
  return close(*fd);
#end
}

void
hs_get_stdin(hs_file *fp)
{
#ifdef _WIN32  
  *fp = GetStdHandle(STD_INPUT_HANDLE);
#else
   return fileno(stdin);
#end
}

void
hs_get_stdout(hs_file *fp)
{
#ifdef _WIN32  
  *fp = GetStdHandle(STD_OUTPUT_HANDLE);
#else
  return fileno(stdout);
#end
}

void
hs_get_stderr(hs_file *fp)
{
#ifdef _WIN32  
  *fp = GetStdHandle(STD_ERROR_HANDLE);
#else
  return fileno(stderr);
#end
}

int
hs_set_stdin(hs_file *fp)
{
#ifdef _WIN32  
  return !SetStdHandle(STD_INPUT_HANDLE, *fp);
#else
  FILE *f = fdopen(*fp, "rb+");
  if (!f) return 1;
  stdin = f;
  return 0;  
#end
}

int
hs_set_stdout(hs_file *fp)
{
#ifdef _WIN32  
  return !SetStdHandle(STD_OUTPUT_HANDLE, *fp);
#else
  FILE *f = fdopen(*fp, "wb+");
  if (!f) return 1;
  stdout = f;
  return 0;  
#end
}

int
hs_set_stderr(hs_file *fp)
{
#ifdef _WIN32  
  return !SetStdHandle(STD_ERROR_HANDLE, *fp);
#else
  FILE *f = fdopen(*fp, "ab+");
  if (!f) return 1;
  stderr = f;
  return 0;
#end
}

size_t
hs_file_read_bytes(hs_file *fp, void *data, const size_t size)
{
  
}

size_t
hs_file_write_bytes(hs_file *fp, const void *data, const size_t size)
{
  
}

int
hs_file_seek(hs_file *fp, intmax_t distance, int relative_to)
{
  
}

size_t
hs_file_read_u8(hs_file *fp, uint8_t *dst, const size_t size)
{
  
}

size_t
hs_file_read_u16(hs_file *fp, uint16_t *dst, const size_t size)
{
  
}

size_t
hs_file_read_u32(hs_file *fp, uint32_t *dst, const size_t size)
{
  
}

size_t
hs_file_read_u64(hs_file *fp, uint64_t *dst, const size_t size)
{
  
}

size_t
hs_file_read_umax(hs_file *fp, uintmax_t *dst, const size_t size)
{
  
}

size_t
hs_file_read_i8(hs_file *fp, uint8_t *dst, const size_t size)
{
  
}

size_t
hs_file_read_i16(hs_file *fp, uint16_t *dst, const size_t size)
{
  
}

size_t
hs_file_read_i32(hs_file *fp, uint32_t *dst, const size_t size)
{
  
}

size_t
hs_file_read_i64(hs_file *fp, uint64_t *dst, const size_t size)
{
  
}

size_t
hs_file_read_imax(hs_file *fp, intmax_t *dst, const size_t size)
{
  
}

size_t
hs_file_read_float(hs_file *fp, float *dst, const size_t size)
{
  
}

size_t
hs_file_read_double(hs_file *fp, double *dst, const size_t size)
{
  
}

size_t
hs_file_read_ldouble(hs_file *fp, long double *dst, const size_t size)
{
  
}

size_t
hs_file_write_u8(hs_file *fp, const uint8_t *value, const size_t size)
{
  
}

size_t
hs_file_write_u16(hs_file *fp, const uint16_t *value, const size_t size)
{
  
}

size_t
hs_file_write_u32(hs_file *fp, const uint32_t *value, const size_t size)
{
  
}

size_t
hs_file_write_u64(hs_file *fp, const uint64_t *value, const size_t size)
{
  
}

size_t
hs_file_write_umax(hs_file *fp, const uintmax_t *value, const size_t size)
{
  
}

size_t
hs_file_write_i8(hs_file *fp, const uint8_t *value, const size_t size)
{
  
}

size_t
hs_file_write_i16(hs_file *fp, const uint16_t *value, const size_t size)
{
  
}

size_t
hs_file_write_i32(hs_file *fp, const uint32_t *value, const size_t size)
{
  
}

size_t
hs_file_write_i64(hs_file *fp, const uint64_t *value, const size_t size)
{
  
}

size_t
hs_file_write_imax(hs_file *fp, const intmax_t *value, const size_t size)
{
  
}

size_t
hs_file_write_float(hs_file *fp, const float *value, const size_t size)
{
  
}

size_t
hs_file_write_double(hs_file *fp, const double *value, const size_t size)
{
  
}

size_t
hs_file_write_ldouble(hs_file *fp, const long double *value, const size_t size)
{
  
}