/* cc 1.0 (c) Copyright 2025 Kevin Alavik */
#include <arena.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void* _arena_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed: %s", strerror(errno));
    }
    return ptr;
}

static void* _arena_realloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        fprintf(stderr, "ERROR: Memory reallocation failed: %s",
                strerror(errno));
    }
    return new_ptr;
}

static int _arena_grow(struct arena* arena, size_t size_needed) {
    size_t old_size = arena->size;
    size_t new_size = old_size;
    void* new_pool;

    while (new_size < arena->offset + size_needed) {
        new_size += DEFAULT_ARENA_SIZE;
    }

    new_pool = _arena_realloc(arena->pool, new_size);
    if (new_pool == NULL) {
        return -1;
    }

    arena->pool = new_pool;
    arena->size = new_size;
    return 0;
}

int arena_init(struct arena* arena, size_t size) {
    if (size == 0) {
        fprintf(stderr,
                "ERROR: Arena initialization failed: Size must be greater "
                "than 0\n");
        return -1;
    }

    arena->pool = _arena_malloc(size);
    if (arena->pool == NULL) {
        return -1;
    }

    arena->size = size;
    arena->offset = 0;
    return 0;
}

void* arena_alloc(struct arena* arena, size_t size) {
    void* ptr = NULL;

    if (arena == NULL || arena->pool == NULL) {
        fprintf(stderr, "ERROR: Arena not initialized properly\n");
        return NULL;
    }

    if (arena->offset + size > arena->size) {
        if (_arena_grow(arena, size) != 0) {
            fprintf(stderr,
                    "ERROR: Arena memory allocation failed: Unable to grow "
                    "arena\n");
            return NULL;
        }
    }

    ptr = (void*)((char*)arena->pool + arena->offset);
    arena->offset += size;
    return ptr;
}

void* arena_realloc(struct arena* arena, void* ptr, size_t new_size) {
    size_t current_offset = 0;
    void* new_ptr = NULL;

    if (arena == NULL || arena->pool == NULL || ptr == NULL) {
        fprintf(stderr, "ERROR: Invalid parameters for arena_realloc\n");
        return NULL;
    }

    current_offset = (char*)ptr - (char*)arena->pool;
    if (current_offset + new_size <= arena->size) {
        arena->offset = current_offset + new_size;
        return ptr;
    } else {
        if (_arena_grow(arena, new_size) != 0) {
            return NULL;
        }

        new_ptr = (char*)arena->pool + current_offset;
        arena->offset = current_offset + new_size;
        return new_ptr;
    }
}

void arena_reset(struct arena* arena) {
    if (arena != NULL) {
        arena->offset = 0;
    }
}

void arena_destroy(struct arena* arena) {
    if (arena != NULL) {
        if (arena->pool != NULL) {
            free(arena->pool);
        }
        arena->pool = NULL;
        arena->size = 0;
        arena->offset = 0;
    }
}
