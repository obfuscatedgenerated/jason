#ifndef FNV1A_HASHTABLE_FNV1A_H
#define FNV1A_HASHTABLE_FNV1A_H

#include <stdint.h>
#include <stddef.h>
#include "../lib_def.h"

#define FNV1A_BASIS 0xcbf29ce484222325
#define FNV1A_PRIME 0x100000001b3

#ifdef JASON_SHOW_PRIVATES
PRIVATE uint64_t fnv1a(const void *payload, size_t len);
#endif

#endif //FNV1A_HASHTABLE_FNV1A_H
