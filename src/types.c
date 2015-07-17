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
#include <hs/types.h>

HS_IMPLEMENT_ARRAY(hs_object, hs_array)
HS_IMPLEMENT_LIST(hs_object, hs_array)
HS_IMPLEMENT_SET(hs_object, hs_array)
HS_IMPLEMENT_MAP(hs_object, hs_object, hs_array)