#include "hashtable/kv_dict.h"
#include "hashtable/fnv1a.h"

#include <stdlib.h>
#include <string.h>

kv_dict *new_dict(void) {
    kv_dict *dict = malloc(sizeof(kv_dict));

    if (dict == NULL) {
        return NULL;
    }

    dict->size = 0;
    dict->capacity = INIT_CAPACITY;

    // allocate entry space and zero it out (so values are clearly NULL when unset)
    dict->entries = calloc(dict->capacity, sizeof(kv_entry));

    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }

    return dict;
}

void free_dict(kv_dict *dict) {
    // TODO: free each entry
    // iterating each entry and freeing it causes a corruption error
    free(dict->entries);
    free(dict);
}

static int raw_set(kv_entry *entries, size_t capacity, char *key, size_t key_size, void *value) {
    kv_entry *entry = malloc(sizeof(kv_entry));

    if (entry == NULL) {
        return 1;
    }

    entry->key = key;
    entry->value = value;

    uint64_t hash = fnv1a(key, key_size);

    // use AND to encode hash in terms of our array's indices (guess at index)
    size_t index = hash & (capacity - 1);

    while (entries[index].key != NULL) {
        // check if the key is the one we're setting
        if (strcmp(entries[index].key, key) == 0) {
            entries[index].value = value;
            return 0;
        }

        index++;

        // wrap around if need be
        if (index >= capacity) {
            index = 0;
        }
    }

    // insert the item
    entries[index] = *entry;
    return 0;
}


static int expand(kv_dict *dict) {
    size_t new_capacity = dict->capacity * 2;

    // realloc?
    kv_entry *new_entries = calloc(dict->capacity, sizeof(kv_entry));

    if (new_entries == NULL) {
        return 1;
    }

    // migrate old non-null entries
    for (size_t i = 0; i < dict->capacity; i++) {
        kv_entry entry = dict->entries[i];

        if (entry.key != NULL) {
            int set_err = raw_set(new_entries, new_capacity, entry.key, strlen(entry.key), entry.value);

            if (set_err) {
                free(new_entries);
                return 1;
            }
        }
    }

    // free old entries
    free(dict->entries);

    dict->entries = new_entries;
    dict->capacity = new_capacity;

    return 0;
}


int set_item(kv_dict *dict, char *key, size_t key_size, void *value) {
    if (value == NULL) {
        return 1;
    }

    // expand capacity if needed
    if (dict->size == dict->capacity) {
        int expand_err = expand(dict);

        if (expand_err) {
            return 1;
        }
    }

    int set_err = raw_set(dict->entries, dict->capacity, key, key_size, value);

    if (set_err) {
        return 1;
    }

    dict->size++;

    return 0;
}

void *get_item(kv_dict *dict, char *key, size_t key_size) {
    uint64_t hash = fnv1a(key, key_size);

    // use AND to encode hash in terms of our array's indices (guess at index)
    size_t index = hash & (dict->capacity - 1);

    while (dict->entries[index].key != NULL) {
        // check if the key is the one we're getting
        if (strcmp(dict->entries[index].key, key) == 0) {
            return dict->entries[index].value;
        }

        index++;

        // wrap around if need be
        if (index >= dict->capacity) {
            index = 0;
        }
    }

    // wasn't found!
    return NULL;
}

// TODO: add marker if keys and/or value needs to be freed for free_dict, or perhaps use special struct for each key/value instead of void*
