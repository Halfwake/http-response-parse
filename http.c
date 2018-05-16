#include "http.h"

void http_generic(char * action, char * collection, char * body, int sequence_number) {
    char request_buffer [1024];
    char full_body_buffer [1024];
    snprintf(full_body_buffer, 1024,
            "{\"action\":\"%s\", \"body\":%s, \"sequence\":%d}",
            action, body, sequence_number);
    snprintf(request_buffer, 1024,
            "POST /api/0.0.1/%s/ HTTP/1.1\r\nContent-Length: %d\r\nHost: localhost:2000\r\nX-Checksum: %u\r\n\r\n%s\x09",
            collection, strlen(full_body_buffer) + 1, crc32_checksum(full_body_buffer), full_body_buffer);
    send_queue_send(request_buffer);
}

void http_update_generic(char * action, char * collection, char * body, char * query, int sequence_number) {
  char request_buffer [1024];
  char full_body_buffer [1024];
  snprintf(full_body_buffer, 1024,
	   "{\"action\":\"%s\", \"body\":%s, \"query\":%s, \"sequence\":%d}",
	   action, body, query, sequence_number);
  snprintf(request_buffer, 1024,
	   "POST /api/0.0.1/%s/ HTTP/1.1\r\nContent-Length: %d\r\nHost: localhost:2000\r\nX-Checksum: %u\r\n\r\n%s\x09",
	   collection, strlen(full_body_buffer) + 1, crc32_checksum(full_body_buffer), full_body_buffer);
  send_queue_send(request_buffer);
}

void http_post(char * collection, char * body, int sequence_number) {
    http_generic("post", collection, body, sequence_number);
}

void http_get(char * collection, char * body, int sequence_number) {
    http_generic("get", collection, body, sequence_number);
}

void http_delete(char * collection, char * body, int sequence_number) {
    http_generic("delete", collection, body, sequence_number);
}

void http_update(char * collection, char * body, char * query, int sequence_number){
    http_update_generic("update",collection, body,query,sequence_number);
}