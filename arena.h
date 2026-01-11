#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// helpers for declaring arena size
#define KiB(n) ((uint64_t)(n) << 10)
#define MiB(n) ((uint64_t)(n) << 20)
#define GiB(n) ((uint64_t)(n) << 30)

// helpers to get min and max
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// helpers for memory addresses
#define ALIGN_UP_POW2(n, p) (((uint64_t)(n) + ((uint64_t)(p) - 1)) & (~((uint64_t)(p) - 1))) // memory aligns to power of 2
#define ARENA_BASE_POS (sizeof(mem_arena)) // memory align so it starts after the struct size
#define ARENA_ALIGN (sizeof(void *)) // programs are more performant when memory aligned

typedef struct {
    uint64_t capacity;
    uint64_t position;
} mem_arena;

// define MACROS where T is the size of int
#define PUSH_STRUCT(arena,T)     (T*)arena_push((arena), sizeof(T), 0) // returns a ptr for a struct
#define PUSH_STRUCT_NZ(arena,T)  (T*)arena_push((arena), sizeof(T), 1) // returns a ptr for a struct, not zero'd
#define PUSH_ARRAY(arena,T,n)    (T*)arena_push((arena), sizeof(T)*(n), 0) // returns a ptr for an array
#define PUSH_ARRAY_NZ(arena,T,n) (T*)arena_push((arena), sizeof(T)*(n), 1) // returns a ptr for an array, not zero'd
#define PRINT_ARENA_STATS(arena) \
    printf("Stats: size (%llu), position (%llu)\n", \
           (unsigned long long)(arena)->capacity, \
           (unsigned long long)(arena)->position)


mem_arena* arena_create(uint64_t capacity); // create the arena
void arena_destroy(mem_arena* arena); // destroy entire arena
void* arena_push(mem_arena* arena, uint64_t size, int32_t non_zero); // push more space into the arena
void arena_pop(mem_arena* arena, uint64_t size); // pop space from the arena
void arena_pop_to(mem_arena* arena, uint64_t pos);
void arena_clear(mem_arena* arena);

#endif