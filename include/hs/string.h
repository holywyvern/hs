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
#ifndef HS_STRING_H
#define HS_STRING_H

#include <stdlib.h>

typedef struct hs_string hs_string;



struct hs_string
{
  size_t size;
  char  *data;
};

int
hs_string_init(hs_string *str, const char *data);

void
hs_string_end(hs_string *str);

#endif /* HS_STRING_H */