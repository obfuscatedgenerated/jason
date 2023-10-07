#include "parser.h"

#include "subparsers/object.h"
#include "subparsers/array.h"
#include "subparsers/string.h"
#include "subparsers/boolean.h"
#include "subparsers/nullable.h"
#include "subparsers/number.h"

#include <stdlib.h>

jason_parser *jason_parser_new(char *json, size_t json_len) {
    jason_parser *parser = malloc(sizeof(jason_parser));

    if (parser == NULL) {
        return NULL;
    }

    parser->json = json;
    parser->json_len = json_len;
    parser->_pos = 0;
    parser->_tokens_head = NULL;
    parser->_tokens_current = NULL;

    return parser;
}

void jason_parser_free(jason_parser *parser) {
    if (parser == NULL) {
        return;
    }

    while (parser->_tokens_head != NULL) {
        jason_tokens_ll_node *node = parser->_tokens_head;
        parser->_tokens_head = parser->_tokens_head->next;

        //jason_token_free(node->token);
        free(node->token);
        free(node);
    }

    free(parser);
}

// TODO: need to recognise when key
jason_parse_result jason_parse_next(jason_parser *parser) {
    switch (parser->json[parser->_pos]) {
        case '{':
            //return jason_parse_object(parser);
        case '[':
            //return jason_parse_array(parser);
        case '"':
            //return jason_parse_string(parser);
        case 't':
        case 'f':
            return jason_parse_boolean(parser);
        case 'n':
            //return jason_parse_nullable(parser);
        case '-':
            //return jason_parse_number(parser);
        default:
            if (parser->json[parser->_pos] >= '0' && parser->json[parser->_pos] <= '9') {
                //return jason_parse_number(parser);
            }

            return JASON_PARSE_EXPECTED_TOKEN;
    }
}

jason_parse_result jason_parse(jason_parser *parser) {
    if (parser == NULL) {
        return JASON_PARSE_NULL_PARSER;
    }

    if (parser->json == NULL) {
        return JASON_PARSE_NULL_JSON;
    }

    if (parser->json_len == 0) {
        return JASON_PARSE_UNEXPECTED_END;
    }

    return jason_parse_next(parser);
}
