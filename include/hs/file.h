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

  typedef HANDLE hs_file;

#else

  typedef int hs_file;

#endif

int
hs_file_open(hs_file *fd, const char *name, const char *mode );

int
hs_file_close(hs_file *fd);

#ifdef __cplusplus
}
#endif

#endif /* HS_FILE_H */