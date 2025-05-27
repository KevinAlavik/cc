/* cc 1.0 (c) Copyright 2025 Kevin Alavik */
#include <arena.h>
#include <global.h>
#include <token.h>

struct token* token_create(enum token_type type, const char* lexeme, int line, int column) {
    struct token* t = arena_alloc(&g_arena, sizeof(struct token));
    if (!t)
        return NULL;
    t->type = type;
    t->lexeme = lexeme;
    t->line = line;
    t->column = column;
    return t;
}
