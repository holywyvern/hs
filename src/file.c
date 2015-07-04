
#include <stdlib.h>
#include <string.h>

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
