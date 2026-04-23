#include "rfc9213_parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

HttpRequest parse_priority_header(int id, const char* header_str) {
    HttpRequest req;
    req.request_id = id;
    req.urgency = 3; // RFC 9213 default urgency
    req.incremental = false; // RFC 9213 default incremental

    if (header_str == NULL) return req;

    // Basic parsing logic for "u=X" and "i"
    const char *u_ptr = strstr(header_str, "u=");
    if (u_ptr != NULL) {
        req.urgency = u_ptr[2] - '0';
        if (req.urgency < 0 || req.urgency > 7) {
            req.urgency = 3; // reset to default if out of bounds
        }
    }

    if (strstr(header_str, "i") != NULL && strstr(header_str, "u=i") == NULL) {
        req.incremental = true;
    }

    return req;
}
