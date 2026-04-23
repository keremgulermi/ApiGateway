#include "min_heap.h"
#include <stdio.h>
#include <stdlib.h>

PriorityQueue* create_queue(int capacity) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (!pq) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    pq->requests = (HttpRequest*)malloc(capacity * sizeof(HttpRequest));
    if (!pq->requests) {
        free(pq);
        printf("Memory allocation failed!\n");
        exit(1);
    }
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

void swap(HttpRequest *a, HttpRequest *b) {
    HttpRequest temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(PriorityQueue *pq, int index) {
    int parent = (index - 1) / 2;
    // Lower urgency value means higher priority in RFC 9213
    if (index > 0 && pq->requests[index].urgency < pq->requests[parent].urgency) {
        swap(&pq->requests[index], &pq->requests[parent]);
        heapify_up(pq, parent);
    }
}

void heapify_down(PriorityQueue *pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->requests[left].urgency < pq->requests[smallest].urgency)
        smallest = left;

    if (right < pq->size && pq->requests[right].urgency < pq->requests[smallest].urgency)
        smallest = right;

    if (smallest != index) {
        swap(&pq->requests[index], &pq->requests[smallest]);
        heapify_down(pq, smallest);
    }
}

void enqueue(PriorityQueue *pq, HttpRequest req) {
    if (pq->size == pq->capacity) {
        // Realloc implementation for dynamic resizing
        pq->capacity *= 2;
        pq->requests = (HttpRequest*)realloc(pq->requests, pq->capacity * sizeof(HttpRequest));
        printf("Queue capacity increased to %d\n", pq->capacity);
    }
    pq->requests[pq->size] = req;
    heapify_up(pq, pq->size);
    pq->size++;
}

HttpRequest dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        HttpRequest empty = {-1, -1, false};
        return empty;
    }
    HttpRequest root = pq->requests[0];
    pq->requests[0] = pq->requests[pq->size - 1];
    pq->size--;
    heapify_down(pq, 0);
    return root;
}

void free_queue(PriorityQueue *pq) {
    if (pq) {
        if (pq->requests) free(pq->requests);
        free(pq);
    }
}
