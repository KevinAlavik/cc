/* cc 1.0 (c) Copyright 2025 Kevin Alavik */
#ifndef LEXER_H
#define LEXER_H

struct lexer {
    const char *input;      /* Input source */
    const char *current;    /* Current position in the input */
    int line;               /* Current line number */
    int column;             /* Current column number */
};

struct lexer *lexer_create(const char *input);
struct token *lexer_next_token(struct lexer *lex);
struct token *lexer_peek(struct lexer *lex);

#endif /* LEXER_H */
