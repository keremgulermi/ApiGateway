#include <stdio.h>
#include "min_heap.h"
#include "rfc9213_parser.h"

int main() {
    /* Tüm deðiþken tanýmlamalarý eski C standartlarýna uyum için en üste alýndý */
    PriorityQueue *pq;
    int num_requests = 5;
    int i; 
    HttpRequest req;
    HttpRequest processed;
    
    const char* headers[] = {
        "u=5",       
        "u=1, i",    
        "u=3",       
        "u=0",       
        "u=7"        
    };

    printf("========================================\n");
    printf(" KLU YAZILIM MUH - API Gateway Scheduler\n");
    printf("========================================\n\n");

    pq = create_queue(2);

    printf("[*] Receiving and Parsing Requests...\n");
    
    /* int i tanimi yukarida yapildigi icin sadece i = 0 yaziyoruz */
    for (i = 0; i < num_requests; i++) {
        req = parse_priority_header(i + 1, headers[i]);
        printf(" -> Parsed Req ID: %d | Urgency: %d | Incremental: %d\n", 
               req.request_id, req.urgency, req.incremental);
        enqueue(pq, req);
    }

    printf("\n[*] Processing Requests via Min-Heap...\n");
    while (pq->size > 0) {
        processed = dequeue(pq);
        printf(" -> Processing Req ID: %d (Urgency: %d)\n", processed.request_id, processed.urgency);
    }

    free_queue(pq);
    printf("\n[*] Memory freed successfully. Exiting.\n");

    return 0;
}
