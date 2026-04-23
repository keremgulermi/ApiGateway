#ifndef RFC9213_PARSER_H
#define RFC9213_PARSER_H

#include <stdbool.h>

// RFC 9213 Request Structure
typedef struct {
    int request_id;
    int urgency;       // 0 (Highest) to 7 (Lowest). Default is 3.
    bool incremental;  // Default is false.
} HttpRequest;

// Parses priority header string (e.g., "u=2, i")
HttpRequest parse_priority_header(int id, const char* header_str);

#endif
