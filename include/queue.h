#ifndef QUEUE_H
#define QUEUE_H

struct Queue;

extern struct Queue *newQueue(int capacity);

extern int enqueue(struct Queue *q, void *value);

extern void *dequeue(struct Queue *q);

extern void freeQueue(struct Queue *q);

extern int isQueueEmpty(struct Queue *q);

#endif
