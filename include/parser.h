#ifndef JASON_PARSER_H
#define JASON_PARSER_H

#include "./hashtable/jason_object.h"
#include "./lib_def.h"

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
    JASON_TYPE_UNDEFINED, ///< in general, the whole token will be NULL. it is unlikely this type will be used, unless you manually set it upon a token.
    JASON_TYPE_NULL,
    JASON_TYPE_BOOLEAN,
    JASON_TYPE_NUMBER,
    JASON_TYPE_STRING,
    JASON_TYPE_ARRAY,
    JASON_TYPE_OBJECT,
} jason_type;

struct jason_token_s {
    jason_type type;
    union {
        int boolean;
        double number;
        char *string;
        struct jason_tokens_ll_node_s *array;
        struct jason_object_s *object;
    } value;
};
typedef struct jason_token_s jason_token;

struct jason_tokens_ll_node_s {
    struct jason_token_s *token;
    struct jason_tokens_ll_node_s *next;
};
typedef struct jason_tokens_ll_node_s jason_tokens_ll_node;


typedef struct {
    char *json;
    size_t json_len;

    size_t _pos;

    struct jason_tokens_ll_node_s *_tokens_head;
    struct jason_tokens_ll_node_s *_tokens_current;
} jason_parser;


PUBLIC jason_parser *jason_parser_new(char *json, size_t json_len);

PUBLIC void jason_parser_free(jason_parser *parser);

#ifdef JASON_SHOW_PRIVATES
PRIVATE jason_parse_result jason_parse_next(jason_parser *parser);
#endif

PUBLIC jason_parse_result jason_parser_run(jason_parser *parser);

#endif //JASON_PARSER_H
