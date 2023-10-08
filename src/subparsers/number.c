#include "subparsers/number.h"

#include <stdlib.h>

static int push_number(jason_parser *parser, double value) {
    jason_token *token = malloc(sizeof(jason_token));

    if (token == NULL) {
        return 1;
    }

    token->type = JASON_TYPE_NUMBER;
    token->value.number = value;

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


jason_parse_result jason_parse_number(jason_parser *parser) {
    // considerations:
    // might start with -
    // might be a decimal
    // might be an exponent (1e3 / 1e+3 = 1000)
    // might be a negative exponent (1e-3 = 0.001)
    // might be outside range of double
    // only decimal is legal, not hex, oct etc
    // check the spec at https://www.json.org/json-en.html
    // have at look at some of these methods https://www.gnu.org/software/libc/manual/html_node/Parsing-of-Floats.html
    // can adjust them to fit standard + safety
}
