#include <string.h>
#include "parser.h"

int main() {
    char *json = "true";
    size_t json_len = 4;

    jason_parser *parser = jason_parser_new(json, json_len);

    jason_parse_result result = jason_parser_run(parser);

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

    jason_parse_result result2 = jason_parser_run(parser2);

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

    jason_parse_result result3 = jason_parser_run(parser3);

    if (result3 != JASON_PARSE_INVALID_TOKEN) {
        return 11;
    }

    jason_parser_free(parser3);

    char *json4 = "null";
    size_t json_len4 = 4;

    jason_parser *parser4 = jason_parser_new(json4, json_len4);

    jason_parse_result result4 = jason_parser_run(parser4);

    if (result4 != JASON_PARSE_OK) {
        return 12;
    }

    jason_tokens_ll_node *node4 = parser4->_tokens_head;

    if (node4 == NULL) {
        return 13;
    }

    if (node4->token->type != JASON_TYPE_NULL) {
        return 14;
    }

    if (node4->next != NULL) {
        return 15;
    }

    jason_parser_free(parser4);

    char *json5 = "\"hello\"";
    size_t json_len5 = 7;

    jason_parser *parser5 = jason_parser_new(json5, json_len5);

    jason_parse_result result5 = jason_parser_run(parser5);

    if (result5 != JASON_PARSE_OK) {
        return 16;
    }

    jason_tokens_ll_node *node5 = parser5->_tokens_head;

    if (node5 == NULL) {
        return 17;
    }

    if (node5->token->type != JASON_TYPE_STRING) {
        return 18;
    }

    if (strcmp(node5->token->value.string, "hello") != 0) {
        return 19;
    }

    if (node5->next != NULL) {
        return 20;
    }

    jason_parser_free(parser5);

    return 0;
}

// TODO: split up!
