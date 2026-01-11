# Arena Allocator
This is a simple implementation of an arena allocator, and alternative to manual memory management (individual malloc/free)

---

## How it works?
- Think of it like creating a vector and calling .reserve()
- As you want to use more of the arena's space, you call push (much like a vector)
- However like a reserved vector, the arena has a capacity that you set earlier at declaration
- Most of it is pointer arithmetic tbh

---

## Functions
```c
mem_arena* arena_create(uint64_t capacity)                                 // creates the arena
void arena_destroy(mem_arena* arena)                                       // destroys entire arena
void* arena_push(mem_arena* arena, uint64_t size, int32_t non_zero)        // pushes more space into the arena
void arena_pop(mem_arena* arena, uint64_t size)                            // pops space from the arena of set size
void arena_pop_to(mem_arena* arena, uint64_t pos)                          // pops space from the arena until a set position
void arena_clear(mem_arena* arena)                                         // clears out the entire arena (doesn't zero out)
```

---

## Macros
```c
PUSH_STRUCT(arena,T)              // returns a ptr for a struct
PUSH_STRUCT_NZ(arena,T)           // returns a ptr for a struct, not zero'd
PUSH_ARRAY(arena,T,n)             // returns a ptr for an array
PUSH_ARRAY_NZ(arena,T,n)          // returns a ptr for an array, not zero'd
PRINT_ARENA_STATS(arena)          // prints the stats (size and pos) of an arena
```
---

```bash
gcc main.c arena.c -o main
./main
