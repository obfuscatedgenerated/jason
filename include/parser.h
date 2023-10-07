#ifndef JASON_PARSER_H
#define JASON_PARSER_H

#include "hashtable/kv_dict.h"

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

typedef struct {
    jason_type type;
    union {
        int boolean;
        double number;
        char *string;
        struct {
            size_t size;
            struct jason_token **values;
        } array;
        kv_dict *object;
    } value;
} jason_token;

typedef struct jason_tokens_ll_node jason_tokens_ll_node;
struct jason_tokens_ll_node {
    jason_token *token;
    jason_tokens_ll_node *next;
};


typedef struct {
    char *json;
    size_t json_len;

    size_t _pos;

    jason_tokens_ll_node *_tokens_head;
    jason_tokens_ll_node *_tokens_current;
} jason_parser;


jason_parser *jason_parser_new(char *json, size_t json_len);

void jason_parser_free(jason_parser *parser);

jason_parse_result jason_parser_run(jason_parser *parser);

#endif //JASON_PARSER_H
