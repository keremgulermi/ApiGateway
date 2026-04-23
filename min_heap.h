#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "rfc9213_parser.h"

typedef struct {
    HttpRequest *requests;
    int capacity;
    int size;
} PriorityQueue;

PriorityQueue* create_queue(int capacity);
void swap(HttpRequest *a, HttpRequest *b);
void heapify_up(PriorityQueue *pq, int index);
void heapify_down(PriorityQueue *pq, int index);
void enqueue(PriorityQueue *pq, HttpRequest req);
HttpRequest dequeue(PriorityQueue *pq);
void free_queue(PriorityQueue *pq);

#endif
