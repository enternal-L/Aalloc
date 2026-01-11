#include "arena.h"

int main() {
    mem_arena * perm_arena = arena_create(MiB(1));

    PRINT_ARENA_STATS(perm_arena);

    // placing a simple array into the arena
    int arr[4] = {1,2,3,4};

    int * arena_arr = PUSH_ARRAY(perm_arena, int, 4);

    // now fill the arena with our values
    for (int i = 0; i < 4; ++i){
        arena_arr[i] = arr[i];
    }

    // print what's inside of the arena
    for (int i = 0; i < 4; ++i){
        printf("Value at index %d is %d\n", i, arena_arr[i]);
    }

    // placing a struct into the arena
    typedef struct {
        char * name;
        float social_score;
        int id;
    } Person;

    Person * person_a = PUSH_STRUCT(perm_arena, Person);

    person_a->name = "Lowk";
    person_a->id = 0;
    person_a->social_score = 100.0;

    printf("%s with id %d and social score of %f\n", person_a->name, person_a->id, person_a->social_score);

    arena_destroy(perm_arena);
}