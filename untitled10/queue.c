#include "queue.h"

Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, struct Student* student) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    new_node->student = student;
    new_node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = new_node;
        return;
    }
    queue->rear->next = new_node;
    queue->rear = new_node;
}

struct Student* dequeue(Queue* queue) {
    if (queue->front == NULL)
        return NULL;
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)
        queue->rear = NULL;
    struct Student* student = temp->student;
    free(temp);
    return student;
}

void print_queue(const Queue* queue) {
    QueueNode* current = queue->front;
    while (current != NULL) {
        print_student(current->student);
        current = current->next;
    }
}

void free_queue(Queue* queue) {
    QueueNode* current = queue->front;
    while (current != NULL) {
        QueueNode* next = current->next;
        free(current->student);
        free(current);
        current = next;
    }
    free(queue);
}
