#include "subparsers/string.h"

#include <stdlib.h>

static int push_string(jason_parser *parser, char *value) {
    jason_token *token = malloc(sizeof(jason_token));

    if (token == NULL) {
        return 1;
    }

    token->type = JASON_TYPE_STRING;
    token->value.string = value;

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

// TODO: ensure security. we're not using strcpy, so it's quite safe, but we should still check.
jason_parse_result jason_parse_string(jason_parser *parser) {
    if (parser->json[parser->_pos] != '"') {
        return JASON_PARSE_EXPECTED_TOKEN;
    }

    parser->_pos++;

    size_t start = parser->_pos;

    // increment index until we find the end of the string (or EOF)
    // TODO: ignore escaped quotes
    while (parser->_pos < parser->json_len && parser->json[parser->_pos] != '"') {
        parser->_pos++;
    }

    if (parser->_pos >= parser->json_len) {
        return JASON_PARSE_UNEXPECTED_END;
    }

    size_t end = parser->_pos;

    char *value = malloc(end - start + 1);

    if (value == NULL) {
        return JASON_PARSE_OUT_OF_MEMORY;
    }

    // copy character values from the buffer
    for (size_t i = start; i < end; i++) {
        value[i - start] = parser->json[i];
    }

    // enforce null-termination
    value[end - start] = '\0';

    // we already know it ends with "
    parser->_pos++;

    if (push_string(parser, value)) {
        free(value);
        return JASON_PARSE_OUT_OF_MEMORY;
    }

    return JASON_PARSE_OK;
}
