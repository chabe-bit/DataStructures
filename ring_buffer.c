#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// FIFO
// 
// add elements
// remove elements - removing the oldest values
// when the buffer is full, it begins overwriting as it loops back from the start

#define ARR_SIZE 10

// https://stackoverflow.com/questions/827691/how-do-you-implement-a-circular-buffer-in-c

typedef struct 
{
    void *buffer; // entire data buffer 
    void *buffer_end; // end of data buffer
    size_t capacity; //
    size_t count;
    size_t size;
    void *head;
    void *tail;
} RingBuffer;

void ring_buffer_init(RingBuffer *ring_buffer, size_t capacity, size_t size)
{
	ring_buffer->buffer = malloc(capacity * size);
    assert(ring_buffer->buffer != NULL);

    ring_buffer->buffer_end = (char *)ring_buffer->buffer + capacity + size;
    ring_buffer->capacity = capacity;
    ring_buffer->size = size;
    ring_buffer->count = 0;
    ring_buffer->head = ring_buffer->buffer;
    ring_buffer->tail = ring_buffer->buffer;
}


void ring_buffer_free(RingBuffer *ring_buffer)
{
    assert(ring_buffer != NULL);

    free(ring_buffer->buffer);
    ring_buffer->buffer = NULL;
}

void ring_buffer_push_back(RingBuffer *ring_buffer, void *item)
{
    if (ring_buffer->count == ring_buffer->capacity)
    {
        // Start back from the start to overwrite
        
        return;
    }

    memcpy(ring_buffer->buffer, item, ring_buffer->size);
    ring_buffer->head = (char *)ring_buffer->head + ring_buffer->size;
    if (ring_buffer->head == ring_buffer->buffer_end)
        ring_buffer->head = ring_buffer->buffer;
    ring_buffer->count++;
}

void ring_buffer_pop_front(RingBuffer *ring_buffer, void *item)
{
    if (ring_buffer->count == 0)
        return;

    memcpy(item, ring_buffer->head, ring_buffer->size);
    ring_buffer->tail = (char *)ring_buffer->tail + ring_buffer->size;
    if (ring_buffer->tail == ring_buffer->buffer_end)
        ring_buffer->tail = ring_buffer->buffer;
    ring_buffer->count--;
}

void ring_buffer_print(RingBuffer *ring_buffer)
{
    if (ring_buffer->count == 0)
        return;

    void *current = ring_buffer->tail;
    printf("Ring buffer elements: ");
    for (size_t i = 0; i < ring_buffer->count; i++)
    {
        printf("%d ", *(int *)current);
        current = (char *)current + ring_buffer->size;
        if (current == ring_buffer->buffer_end)
            current = ring_buffer->buffer;
    }
    printf("\n");
}


int main()
{
    RingBuffer ring_buffer = {0};
    int item = 1;

    ring_buffer_init(&ring_buffer, 10, sizeof(int));
   
    ring_buffer_push_back(&ring_buffer, &item);
    ring_buffer_push_back(&ring_buffer, &item);

    ring_buffer_print(&ring_buffer);

    ring_buffer_free(&ring_buffer);


    return 0;
}
