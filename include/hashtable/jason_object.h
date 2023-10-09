#ifndef JASON_OBJECT_H
#define JASON_OBJECT_H

#include <stddef.h>
#include "../lib_def.h"
#include "../parser.h"

#define INIT_CAPACITY 8

struct jason_object_entry_s {
    char *key;
    struct jason_token_s *value;
};

typedef struct jason_object_entry_s jason_object_entry;

struct jason_object_s {
    jason_object_entry *entries;
    size_t size;
    size_t capacity;
};

typedef struct jason_object_s jason_object;

// returns NULL on failure
PRIVATE jason_object* jason_object_new(void);

PUBLIC void jason_object_free(jason_object *dict);

PUBLIC struct jason_token_s *jason_object_get(jason_object *dict, char *key, size_t key_size);

// returns 1 on failure         assuming read-only for now, so this is private
PRIVATE int jason_object_set(jason_object *dict, char *key, size_t key_size, struct jason_token_s *value);

#endif //JASON_OBJECT_H