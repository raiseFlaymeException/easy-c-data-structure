#include <stdio.h>
#include <sys/time.h>

#include "easy_c_data_structure/queue/cqueue_creator.h"

#define USE_ARRAY_QUEUE 0
// the array one is better than a linked list:

// letters from a to z pushed than poped (time in seconds)

// 1000 -> 0.000200 VS 0.000800
// 10000 -> 0.001985 VS 0.009020
// 100000 -> 0.020074 VS 0.095530
// 1000000 -> 0.194608 VS 0.907024
// 10000000 -> 2.049669 VS 9.058137

// letters from a to z but pushed 1000 time than poped (time in seconds)

// 1000 -> 0.021748 VS 0.110199
// 10000 -> 0.218014 VS 1.043168
// 100000 -> 2.206364 VS 9.915313
// 1000000 -> 22.019626 VS 98.961895
// 10000000 -> TOO LONG VS TOO LONG

#if USE_ARRAY_QUEUE
CQUEUE_CREATE_DECLARATION(Queue, char)
CQUEUE_CREATE_DEFINITION(Queue, char)
#else
struct Node {
    char         el;
    struct Node *next; // struct is needed
};

typedef struct Node Node;

typedef struct {
    Node  *head;
    Node  *tail;
    size_t size;
} Queue;

void Queue_init(Queue *queue) { // NOLINT
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

void Queue_push(Queue *queue, char el) { // NOLINT
    if (queue->size == 0) {
        queue->tail = malloc(sizeof(*queue->tail));

        queue->tail->el   = el;
        queue->tail->next = NULL;

        queue->head = queue->tail;

        ++queue->size;
        return;
    }
    queue->tail->next = malloc(sizeof(*queue->tail));

    queue->tail = queue->tail->next;

    queue->tail->el   = el;
    queue->tail->next = NULL;

    ++queue->size;
}

char Queue_peek(Queue *queue) { // NOLINT
    assert(queue->size != 0);

    return queue->head->el;
}

char Queue_pop(Queue *queue) { // NOLINT
    char result = Queue_peek(queue);

    Node *next = queue->head->next;
    free(queue->head);
    queue->head = next;

    --queue->size;

    return result;
}

void Queue_free(Queue *queue) { // NOLINT
    for (; queue->size != 0;) { Queue_pop(queue); }
}
#endif

int main() {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    Queue queue;
#if USE_ARRAY_QUEUE
    Queue_alloc(&queue, 1);                // NOLINT
#else
    Queue_init(&queue);
#endif
    for (size_t i = 0; i < 1000; i++) {    // NOLINT
        for (size_t i = 0; i < 100; i++) { // NOLINT
            for (char chr = 'a'; chr <= 'z'; chr++) { Queue_push(&queue, chr); }
        }
        for (; queue.size != 0;) { Queue_pop(&queue); }
    }

    Queue_free(&queue);

    struct timespec stop;
    clock_gettime(CLOCK_MONOTONIC, &stop);
    printf("took %lf s\n",
           stop.tv_sec - start.tv_sec + (stop.tv_nsec - start.tv_nsec) * 1e-9); // NOLINT
    return 0;
}
