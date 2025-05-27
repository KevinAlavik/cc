/* cc 1.0 (c) Copyright 2025 Kevin Alavik */
#include <arena.h>
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
    while (*lex->current == ' ' || *lex->current == '\t' || *lex->current == '\n') {
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
    printf("Unknown token at: %d:%d\n", lex->line, lex->column);
    return NULL;
}
