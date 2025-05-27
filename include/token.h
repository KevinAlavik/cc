/* cc 1.0 (c) Copyright 2025 Kevin Alavik */
#ifndef TOKEN_H
#define TOKEN_H

enum token_type {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_CONST,
    TOKEN_CHAR_CONST,
    TOKEN_SLIT,
    TOKEN_PUNC,
    TOKEN_PP_HEADER_NAME,
    TOKEN_PP_IDENTIFIER,
    TOKEN_PP_NUMBER,
    TOKEN_PP_CHAR_CONST,
    TOKEN_PP_SLIT,
    TOKEN_PP_PUNC,
    TOKEN_EOF
};

struct token {
    enum token_type type;
    const char *lexeme;
    int line;
    int column;
};

#define PRINT_TOK(tok) do { \
    const char *type_str = ""; \
    switch ((tok)->type) { \
        case TOKEN_KEYWORD: type_str = "KEYWORD"; break; \
        case TOKEN_IDENTIFIER: type_str = "IDENTIFIER"; break; \
        case TOKEN_CONST: type_str = "CONST"; break; \
        case TOKEN_CHAR_CONST: type_str = "CHAR_CONST"; break; \
        case TOKEN_SLIT: type_str = "SLIT"; break; \
        case TOKEN_PUNC: type_str = "PUNC"; break; \
        case TOKEN_PP_HEADER_NAME: type_str = "PP_HEADER_NAME"; break; \
        case TOKEN_PP_IDENTIFIER: type_str = "PP_IDENTIFIER"; break; \
        case TOKEN_PP_NUMBER: type_str = "PP_NUMBER"; break; \
        case TOKEN_PP_CHAR_CONST: type_str = "PP_CHAR_CONST"; break; \
        case TOKEN_PP_SLIT: type_str = "PP_SLIT"; break; \
        case TOKEN_PP_PUNC: type_str = "PP_PUNC"; break; \
        case TOKEN_EOF: type_str = "EOF"; break; \
        default: type_str = "UNKNOWN"; break; \
    } \
    printf("Token: { Type: %s, Lexeme: \"%s\", Line: %d, Column: %d }\n", \
           type_str, (tok)->lexeme, (tok)->line, (tok)->column); \
} while (0)

struct token *token_create(enum token_type type, const char *lexeme, int line, int column);

#endif /* TOKEN_H */
