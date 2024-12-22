#pragma once

/// @brief Queue of ints
typedef struct StackQueue StackQueue;

/// @brief Creates queue
/// @param queue Pointer to store queue in
/// @return `true` if created successfully, `false` otherwise (allocation failed)
bool createQueue(StackQueue **queue);

/// @brief Tells if queue is empty
/// @param queue Queue to check
/// @return `true` if queue is empty, `false` otherwise
bool isEmpty(StackQueue *queue);

/// @brief Enqueues value to queue
/// @param queue Queue to enqueue value in
/// @param value Value to enqueue
/// @return `true` if enqueued successfully, `false` otherwise (allocation failed)
bool enqueue(StackQueue *queue, int value);

/// @brief Dequeues value from queue
/// @param queue Queue to dequeue value from
/// @param value Pointer to store dequeued value to
/// @return `true` if dequeued successfully, `false` otherwise (allocation failed or queue is empty)
bool dequeue(StackQueue *queue, int *value);

/// @brief Disposes queue
/// @param queue Queue to dispose
void disposeQueue(StackQueue *queue);
