#ifndef FNV1A_HASHTABLE_KV_DICT_H
#define FNV1A_HASHTABLE_KV_DICT_H

#include <stddef.h>
#include "lib_def.h"
#include "parser.h"

#define INIT_CAPACITY 8

struct kv_entry_s {
    char *key;
    struct jason_token_s *value;
};

typedef struct kv_entry_s kv_entry;

struct kv_dict_s {
    kv_entry *entries;
    size_t size;
    size_t capacity;
};

typedef struct kv_dict_s kv_dict;

// returns NULL on failure
PUBLIC kv_dict* new_dict(void);

PUBLIC void free_dict(kv_dict *dict);

// returns 1 on failure
PUBLIC int set_item(kv_dict *dict, char *key, size_t key_size, struct jason_token_s *value);

PUBLIC struct jason_token_s *get_item(kv_dict *dict, char *key, size_t key_size);

#endif //FNV1A_HASHTABLE_KV_DICT_H