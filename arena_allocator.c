#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

// Arena allocation allocates a block of memory for a group, rather the standard allocation for individual pieces. 

typedef struct Arena
{
    struct Arena *next;
    // capacity, size, data 
    size_t capacity;
    size_t size;
    uint8_t *data;
} Arena;

// Initialize arena allocater 
Arena arena_init(size_t capacity)
{
    void *data = malloc(sizeof(uint8_t) * capacity);
    Arena arena = {
        .capacity = capacity,
        .size = 0,
        .data = data,
        .next = NULL,
    };
    return arena;
}

// Allocate memory
void *arena_alloc(Arena *arena, size_t size)
{
    assert(arena->capacity >= size);
    printf("arena_alloc()...\n");

    // Rather than asserting that if an overflow happens, we simply will create a new memory block to allocate over.
    Arena *current = arena;
    while (!(current->size + size <= current->capacity))
    {
        // Create our new memory block
        if (current->next == NULL)
        {
            Arena next = arena_init(arena->capacity);
            current->next = &next;
        }
        current = current->next;
    }
    
    // return the result of our data 
    current->size += size;
    uint8_t *data = &current->data[arena->size];
    return data;

}

// Reset allocator size 
void *arena_reset(Arena *arena)
{
    printf("arena_reset()...\n");
    
    // Reset alloc size to 0 
    arena->size = 0;
}

// Free memory 
void *arena_free(Arena *arena)
{
    printf("arena_free()...\n");
   
    arena->capacity = 0;
    arena->size = 0;

    free(arena->data);
    arena->data = NULL;
}

void arena_print(const Arena *arena)
{
    printf("capacity: %zu, size: %zu, data: %p\n", arena->capacity, arena->size, arena->data);
}


int main()
{
    Arena arena = arena_init(1024);    
    
    void *ptr = arena_alloc(&arena, 1000);    
    printf("mem size: %zu\n", arena.size);
    void *ptr2 = arena_alloc(&arena, 10);    
    printf("mem size: %zu\n", arena.size);
    void *ptr3 = arena_alloc(&arena, 20);    
    printf("mem size: %zu\n", arena.size);
    
    arena_print(&arena);

    arena_free(&arena);
    printf("mem size: %zu\n", arena.size);

    return 0;
}
