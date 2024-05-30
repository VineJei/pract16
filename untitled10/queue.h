#ifndef QUEUE_H
#define QUEUE_H

#include "student.h"

typedef struct QueueNode {
    struct Student* student;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* create_queue();
void enqueue(Queue* queue, struct Student* student);
struct Student* dequeue(Queue* queue);
void print_queue(const Queue* queue);
void free_queue(Queue* queue);

#endif
