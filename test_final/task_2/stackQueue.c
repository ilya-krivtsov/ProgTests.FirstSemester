#include "stackQueue.h"

#include <stdlib.h>

typedef struct {
    int count;
    int capacity;
    int *elements;
} Stack;

typedef struct StackQueue {
    Stack back;
    Stack front;
} StackQueue;

static bool createStack(Stack *stack) {
    stack->count = 0;
    stack->capacity = 16;
    stack->elements = calloc(stack->capacity, sizeof(int));
    if (stack->elements == NULL) {
        return false;
    }

    return true;
}

static bool push(Stack *stack, int value) {
    if (stack->count == stack->capacity) {
        stack->capacity *= 4;
        stack->elements = realloc(stack->elements, stack->capacity * sizeof(int));
        if (stack->elements == NULL) {
            return false;
        }
    }

    stack->elements[stack->count] = value;
    ++stack->count;

    return true;
}

static int pop(Stack *stack) {
    --stack->count;
    return stack->elements[stack->count];
}

static void disposeStack(Stack stack) {
    free(stack.elements);
}

bool createQueue(StackQueue **queue) {
    *queue = malloc(sizeof(StackQueue));

    if (!createStack(&(*queue)->back)) {
        free(*queue);
        return false;
    }

    if (!createStack(&(*queue)->front)) {
        disposeStack((*queue)->back);
        free(*queue);
        return false;
    }

    return true;
}

bool isEmpty(StackQueue *queue) {
    return queue->back.count == 0 && queue->front.count == 0;
}

bool enqueue(StackQueue *queue, int value) {
    return push(&queue->back, value);
}

bool dequeue(StackQueue *queue, int *value) {
    if (isEmpty(queue)) {
        return false;
    }

    if (queue->front.count != 0) {
        *value = pop(&queue->front);
        return true;
    }

    while (queue->back.count > 1) {
        if (!push(&queue->front, pop(&queue->back))) {
            return false;
        }
    }

    *value = pop(&queue->back);

    return true;
}

void disposeQueue(StackQueue *queue) {
    disposeStack(queue->back);
    disposeStack(queue->front);
    free(queue);
}
