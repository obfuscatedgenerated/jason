#include "subparsers/boolean.h"

#include <stdlib.h>

jason_parse_result jason_parse_boolean(jason_parser *parser) {
    if (parser->json_len - parser->_pos < 4) {
        return JASON_PARSE_UNEXPECTED_END;
    }

    if (parser->json[parser->_pos] == 't') {
        if (parser->json[parser->_pos + 1] != 'r' || parser->json[parser->_pos + 2] != 'u' || parser->json[parser->_pos + 3] != 'e') {
            return JASON_PARSE_INVALID_TOKEN;
        }

        parser->_pos += 4;

        jason_token *token = malloc(sizeof(jason_token));

        if (token == NULL) {
            return JASON_PARSE_OUT_OF_MEMORY;
        }

        token->type = JASON_TYPE_BOOLEAN;
        token->value.boolean = 1;

        jason_tokens_ll_node *node = malloc(sizeof(jason_tokens_ll_node));

        if (node == NULL) {
            free(token);
            return JASON_PARSE_OUT_OF_MEMORY;
        }

        node->token = token;
        node->next = NULL;

        if (parser->_tokens_head == NULL) {
            parser->_tokens_head = node;
            parser->_tokens_current = node;
        } else {
            parser->_tokens_current->next = node;
            parser->_tokens_current = node;
        }
    } else if (parser->json[parser->_pos] == 'f') {
        if (parser->json[parser->_pos + 1] != 'a' || parser->json[parser->_pos + 2] != 'l' || parser->json[parser->_pos + 3] != 's' || parser->json[parser->_pos + 4] != 'e') {
            return JASON_PARSE_INVALID_TOKEN;
        }

        parser->_pos += 5;

        jason_token *token = malloc(sizeof(jason_token));

        if (token == NULL) {
            return JASON_PARSE_OUT_OF_MEMORY;
        }

        token->type = JASON_TYPE_BOOLEAN;
        token->value.boolean = 0;

        jason_tokens_ll_node *node = malloc(sizeof(jason_tokens_ll_node));

        if (node == NULL) {
            free(token);
            return JASON_PARSE_OUT_OF_MEMORY;
        }

        node->token = token;
        node->next = NULL;

        if (parser->_tokens_head == NULL) {
            parser->_tokens_head = node;
            parser->_tokens_current = node;
        } else {
            parser->_tokens_current->next = node;
            parser->_tokens_current = node;
        }
    } else {
        return JASON_PARSE_INVALID_TOKEN;
    }

    return JASON_PARSE_OK;
}
