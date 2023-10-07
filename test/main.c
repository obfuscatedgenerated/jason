#include "parser.h"
#include "subparsers/boolean.h"

int main() {
    char *json = "true";
    size_t json_len = 4;

    jason_parser *parser = jason_parser_new(json, json_len);

    jason_parse_result result = jason_parse(parser);

    if (result != JASON_PARSE_OK) {
        return 1;
    }

    jason_tokens_ll_node *node = parser->_tokens_head;

    if (node == NULL) {
        return 2;
    }

    if (node->token->type != JASON_TYPE_BOOLEAN) {
        return 3;
    }

    if (node->token->value.boolean != 1) {
        return 4;
    }

    if (node->next != NULL) {
        return 5;
    }

    jason_parser_free(parser);

    char *json2 = "false";
    size_t json_len2 = 5;

    jason_parser *parser2 = jason_parser_new(json2, json_len2);

    jason_parse_result result2 = jason_parse(parser2);

    if (result2 != JASON_PARSE_OK) {
        return 6;
    }

    jason_tokens_ll_node *node2 = parser2->_tokens_head;

    if (node2 == NULL) {
        return 7;
    }

    if (node2->token->type != JASON_TYPE_BOOLEAN) {
        return 8;
    }

    if (node2->token->value.boolean != 0) {
        return 9;
    }

    if (node2->next != NULL) {
        return 10;
    }

    jason_parser_free(parser2);

    char *json3 = "nope";
    size_t json_len3 = 4;

    jason_parser *parser3 = jason_parser_new(json3, json_len3);

    jason_parse_result result3 = jason_parse_boolean(parser3);

    if (result3 != JASON_PARSE_INVALID_TOKEN) {
        return 11;
    }

    jason_parser_free(parser3);

    return 0;
}
