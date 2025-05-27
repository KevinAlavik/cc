/* cc 1.0 (c) Copyright 2025 Kevin Alavik */
#include <arena.h>
#include <ctype.h>
#include <global.h>
#include <lexer.h>
#include <stdio.h>
#include <token.h>

struct lexer* lexer_create(const char* input) {
    struct lexer* l = NULL;
    if (!input) {
        fprintf(stderr, "ERROR: Got NULL input to lexer_create, expected something\n");
        return NULL;
    }

    l = arena_alloc(&g_arena, sizeof(struct lexer));
    if (!l)
        return NULL;

    l->input = input;
    l->current = input;
    l->line = 1;
    l->column = 1;

    return l;
}

struct token* lexer_next_token(struct lexer* lex) {
    if (!lex || !lex->current || *lex->current == '\0') {
        return token_create(TOKEN_EOF, "", lex->line, lex->column);
    }

    /* Skip whitespace */
    while (isspace((unsigned char)*lex->current)) {
        if (*lex->current == '\n') {
            lex->line++;
            lex->column = 1;
        } else {
            lex->column++;
        }
        lex->current++;
    }

    if (*lex->current == '\0') {
        return token_create(TOKEN_EOF, "", lex->line, lex->column);
    }

    /* TODO: Actual token handling logic (keywords, identifiers, etc.) */
    fprintf(stderr, "ERROR: Unknown token at %d:%d: '%c' (0x%02X)\n", lex->line, lex->column, *lex->current,
            (unsigned char)*lex->current);

    return NULL;
}
