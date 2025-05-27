/* cc 1.0 (c) Copyright 2025 Kevin Alavik */
#include <arena.h>
#include <lexer.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <token.h>

/* Globals */
struct arena g_arena = {0};

int main(int argc, char** argv) {
    FILE* file = NULL;
    void* buff = NULL;
    size_t bytes_read = 0;
    long file_size = 0;

    /* Check for correct usage */
    if (argc != 2) {
        fprintf(stderr, "ERROR: Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    /* Open the specified file */
    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("ERROR: Failed to open file");
        return 1;
    }

    /* Get the file size */
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    /* Initialize the arena for memory allocation */
    if (arena_init(&g_arena, DEFAULT_ARENA_SIZE) != 0) {
        fprintf(stderr, "ERROR: Failed to initialize global arena\n");
        fclose(file);
        return 1;
    }

    /* Allocate memory from the arena */
    buff = arena_alloc(&g_arena, file_size);
    if (buff == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory from arena\n");
        fclose(file);
        return 1;
    }

    /* Read file content into the buffer */
    bytes_read = fread(buff, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "ERROR: Failed to read the entire file\n");
        fclose(file);
        return 1;
    }

    /* Lex the source code */ {
        struct token* cur_tok;

        /* Lexer */
        struct lexer* lex = lexer_create(buff);
        if (!lex) {
            fclose(file);
            return 1;
        }

        /* Loop over tokens */
        while ((cur_tok = lexer_next_token(lex)) != NULL) {
            PRINT_TOK(cur_tok);

            /* Stop at end of file */
            if (cur_tok->type == TOKEN_EOF)
                break;

            /* Continue on with the next token*/
            cur_tok = lexer_next_token(lex);
        }
    }

    printf("done.\n");

    /* Cleanup */
    fclose(file);
    arena_destroy(&g_arena);
    return 0;
}
