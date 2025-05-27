/* cc 1.0 (c) Copyright 2025 Kevin Alavik */
#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

#define DEFAULT_ARENA_SIZE 16384 /* 16KB */

struct arena {
    void* pool;
    size_t size;
    size_t offset;
};

int arena_init(struct arena* arena, size_t size);

void* arena_alloc(struct arena* arena, size_t size);
void* arena_realloc(struct arena* arena, void* ptr, size_t new_size);

void arena_reset(struct arena* arena);
void arena_destroy(struct arena* arena);

#endif /* ARENA_H */
