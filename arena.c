#include "arena.h"
#include <string.h>
#include <stdlib.h>

// creates the arena through reservation of "capacity"
mem_arena* arena_create(uint64_t capacity){
    // malloc that chunk, then return the ptr of capacity back to the user

    mem_arena * arena = (mem_arena *) malloc(capacity);
    arena->capacity = capacity;
    arena->position = ARENA_BASE_POS;

    return arena;
}

void arena_destroy(mem_arena* arena){
    free(arena);
}

// returns original "aligned" pointer, space is allocated
void* arena_push(mem_arena* arena, uint64_t size, int32_t non_zero){

    // align the ptr
    uint64_t pos_aligned = ALIGN_UP_POW2(arena->position, ARENA_ALIGN);

    // increment to the next position
    uint64_t new_position = pos_aligned + size;

    // error handling
    if (new_position > arena->capacity) return NULL;

    // set arena struct position to the new position
    arena->position = new_position;

    // the arena is the start of the arena + new position
    uint8_t * out = (uint8_t * )arena + pos_aligned;

    // zero out memory
    if (!non_zero) {
        memset(out, 0, size); // memset starting from memory address "out" up to "size", setting everything to 0
    }

    return out;
}

// pops "size" space out of the arena
void arena_pop(mem_arena* arena, uint64_t size){
    // correct the size decrement
    uint64_t decr_size = MIN(size, arena->position - ARENA_BASE_POS);
    
    // decrement the position by this much
    arena->position -= decr_size;
}

// pops to "pos" position in the arena
void arena_pop_to(mem_arena* arena, uint64_t pos){
    
    // check if size exists
    uint64_t decr_size = arena->position > pos ? arena->position - pos : 0;

    // borrow helper function
    arena_pop(arena, decr_size);
}

// clears the entire arena
void arena_clear(mem_arena* arena){

    // pop to base position
    arena_pop_to(arena, ARENA_BASE_POS);
}
