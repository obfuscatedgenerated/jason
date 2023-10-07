#ifndef JASON_PARSER_H
#define JASON_PARSER_H

#include "hashtable/kv_dict.h"
#include "lib_def.h"

typedef enum {
    JASON_PARSE_OK,
    JASON_PARSE_OUT_OF_MEMORY,
    JASON_PARSE_NULL_PARSER,
    JASON_PARSE_NULL_JSON,
    JASON_PARSE_UNEXPECTED_END,
    JASON_PARSE_EXPECTED_TOKEN,
    JASON_PARSE_UNEXPECTED_TOKEN,
    JASON_PARSE_INVALID_TOKEN,
    JASON_PARSE_INVALID_NUMBER,
} jason_parse_result;


typedef enum {
    JASON_TYPE_UNDEFINED,
    JASON_TYPE_NULL,
    JASON_TYPE_BOOLEAN,
    JASON_TYPE_NUMBER,
    JASON_TYPE_STRING,
    JASON_TYPE_ARRAY,
    JASON_TYPE_OBJECT,
} jason_type;

struct jason_token {
    jason_type type;
    union {
        int boolean;
        double number;
        char *string;
        struct jason_tokens_ll_node *array;
        kv_dict *object;
    } value;
};

struct jason_tokens_ll_node {
    struct jason_token *token;
    struct jason_tokens_ll_node *next;
};


typedef struct {
    char *json;
    size_t json_len;

    size_t _pos;

    struct jason_tokens_ll_node *_tokens_head;
    struct jason_tokens_ll_node *_tokens_current;
} jason_parser;


PUBLIC jason_parser *jason_parser_new(char *json, size_t json_len);

PUBLIC void jason_parser_free(jason_parser *parser);

#ifdef JASON_SHOW_PRIVATES
PRIVATE jason_parse_result jason_parse_next(jason_parser *parser);
#endif

PUBLIC jason_parse_result jason_parser_run(jason_parser *parser);

#endif //JASON_PARSER_H
