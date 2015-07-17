#ifndef HS_STRING_H
#define HS_STRING_H

#include <stdlib.h>

typedef struct hs_string hs_string;



struct hs_string
{
  size_t size;
  char  *data;
};

#endif /* HS_STRING_H */