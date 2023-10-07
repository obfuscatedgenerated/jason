#include "subparsers/null.h"

#include <stdlib.h>


// TODO: unify push methods into a single push, taking args at specific points for certain types
static int push_null(jason_parser *parser) {
    jason_token *token = malloc(sizeof(jason_token));

    if (token == NULL) {
        return 1;
    }

    token->type = JASON_TYPE_NULL;

    jason_tokens_ll_node *node = malloc(sizeof(jason_tokens_ll_node));

    if (node == NULL) {
        free(token);
        return 1;
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

    return 0;
}

jason_parse_result jason_parse_null(jason_parser *parser) {
    if (parser->json_len - parser->_pos < 4) {
        return JASON_PARSE_UNEXPECTED_END;
    }

    if (parser->json[parser->_pos] == 'n') {
        // if it starts with n, expect the next 3 chars to be ull
        if (parser->json[parser->_pos + 1] != 'u' || parser->json[parser->_pos + 2] != 'l' || parser->json[parser->_pos + 3] != 'l') {
            return JASON_PARSE_INVALID_TOKEN;
        }

        parser->_pos += 4;

        if (push_null(parser)) {
            return JASON_PARSE_OUT_OF_MEMORY;
        }
    } else {
        return JASON_PARSE_INVALID_TOKEN;
    }

    return JASON_PARSE_OK;
}
