#ifndef CQUEUE_CREATOR_H
#define CQUEUE_CREATOR_H

#include <assert.h>
#include <stdlib.h>

#define CQUEUE_CREATE_DECLARATION_STRUCT(name, type)                                               \
    typedef struct {                                                                               \
        size_t cap;                                                                                \
        size_t size;                                                                               \
        type  *data;                                                                               \
        size_t head;                                                                               \
        size_t tail;                                                                               \
    } name;

#define CQUEUE_CREATE_DECLARATION_FUNCTION(name, type)                                             \
    void name##_alloc(name *queue, size_t cap);                                                    \
    void name##_free(name *queue);                                                                 \
    void name##_push(name *queue, type element);                                                   \
    type name##_peek(name *queue);                                                                 \
    type name##_pop(name *queue);

#define CQUEUE_CREATE_DECLARATION(name, type)                                                      \
    CQUEUE_CREATE_DECLARATION_STRUCT(name, type)                                                   \
    CQUEUE_CREATE_DECLARATION_FUNCTION(name, type)

#define CQUEUE_CREATE_DEFINITION(name, type)                                                       \
    void name##_alloc(name *queue, size_t cap) {                                                   \
        assert(cap > 0);                                                                           \
        queue->data = malloc(cap * sizeof(type));                                                  \
        queue->cap  = cap;                                                                         \
        queue->size = 0;                                                                           \
        queue->head = 0;                                                                           \
        queue->tail = 0;                                                                           \
    }                                                                                              \
    void name##_free(name *queue) { free(queue->data); }                                           \
    void name##_push(name *queue, type element) {                                                  \
        if (queue->size + 1 > queue->cap) {                                                        \
            name new_queue;                                                                        \
            name##_alloc(&new_queue, queue->cap * 2);                                              \
                                                                                                   \
            for (size_t i = 0; i < queue->cap; i++) {                                              \
                name##_push(&new_queue, queue->data[queue->tail]);                                 \
                queue->tail = (queue->tail + 1) % queue->cap;                                      \
            }                                                                                      \
            name##_free(queue);                                                                    \
            *queue = new_queue;                                                                    \
        }                                                                                          \
                                                                                                   \
        queue->data[queue->tail] = element;                                                        \
        queue->tail              = (queue->tail + 1) % queue->cap;                                 \
        ++queue->size;                                                                             \
    }                                                                                              \
    type name##_peek(name *queue) {                                                                \
        assert(queue->size != 0);                                                                  \
        return queue->data[queue->head];                                                           \
    }                                                                                              \
    type name##_pop(name *queue) {                                                                 \
        assert(queue->size != 0);                                                                  \
        type res = name##_peek(queue);                                                             \
                                                                                                   \
        queue->head = (queue->head + 1) % queue->cap;                                              \
        --queue->size;                                                                             \
        return res;                                                                                \
    }

#endif // CQUEUE_CREATOR_H
