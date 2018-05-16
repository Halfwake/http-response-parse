#include "http_parse.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>

void assert(int check, char * description) {
  printf("[%s] - %s\n", check ? "T" : "F", description);
}

void test_basic() {
  struct http_parse_state state;
  char headers[512];
  size_t max_head_size = 64;
  size_t max_header_count = 8;
  char body[256];
  size_t max_body_length;
  _Bool failure;

  printf("Test Basic");
  
  state = init_http_state();
  assert(state.state == HTTP_STATE_STATUS_LINE, "Valid initial state.");
  assert(state.header_byte_position == 0, "Valid initial header byte position");
  assert(state.header_line_position == 0, "Valid initial header line position");
  assert(state.body_position == 0, "Valid initial body position.");
  
  state = update_http_state(state, 'H', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'P', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '/', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '.', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '2', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'O', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'K', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_OR_BLANK_LINE, "On header_or_blank line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, 'A', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, 'B', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'C', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ':', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '6', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '5', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_OR_BLANK_LINE, "On header_or_blank line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_BLANK_LINE, "On blank line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_DONE, "On done.");
  assert(!failure, "Did not fail.");

  assert(state.header_line_position == 1, "Correct line position.");
  assert(strcmp(headers + (0 * max_head_size), "ABC: 65\r\n") == 0, "Correct header ABC: 65");
}

void test_multiple_headers() {
  struct http_parse_state state;
  char headers[512];
  size_t max_head_size = 64;
  size_t max_header_count = 8;
  char body[256];
  size_t max_body_length;
  _Bool failure;  

  printf("Test Basic");
  
  state = init_http_state();
  assert(state.state == HTTP_STATE_STATUS_LINE, "Valid initial state.");
  assert(state.header_byte_position == 0, "Valid initial header byte position");
  assert(state.header_line_position == 0, "Valid initial header line position");
  assert(state.body_position == 0, "Valid initial body position.");
  
  state = update_http_state(state, 'H', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'P', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '/', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '.', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '2', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'O', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'K', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_OR_BLANK_LINE, "On header_or_blank line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, 'A', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, 'B', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'C', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ':', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '6', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '5', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_OR_BLANK_LINE, "On header_or_blank line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, 'X', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, 'Y', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'Z', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ':', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '6', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '5', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_OR_BLANK_LINE, "On header_or_blank line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_BLANK_LINE, "On blank line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_DONE, "On done.");
  assert(!failure, "Did not fail.");

  assert(state.header_line_position == 2, "Correct line position.");
  assert(strcmp(headers + (0 * max_head_size), "ABC: 65\r\n") == 0, "Correct header ABC: 65");
  assert(strcmp(headers + (1 * max_head_size), "XYZ: 65\r\n") == 0, "Correct header XYZ: 65");
}

void test_find_header_first() {
  char headers[512];
  size_t max_head_size = 64;
  size_t max_header_count = 8;
  char header_value[64];
  strcpy(headers + (0 * max_head_size), "Content-Length: 65\r\n");
  strcpy(headers + (1 * max_head_size), "XYZ: 44\r\n");
  strcpy(headers + (2 * max_head_size), "ABC: 23\r\n");  
  find_header("Content-Length", header_value, headers, 64, 3);
  assert(strcmp("65", header_value) == 0, "Header First Pass");
}

void test_find_header_middle() {
  char headers[512];
  size_t max_head_size = 64;
  size_t max_header_count = 8;
  char header_value[64];
  strcpy(headers + (0 * max_head_size), "Content-Length: 65\r\n");
  strcpy(headers + (1 * max_head_size), "XYZ: 44\r\n");
  strcpy(headers + (2 * max_head_size), "ABC: 23\r\n");  
  find_header("XYZ", header_value, headers, 64, 3);
  assert(strcmp("44", header_value) == 0, "Header Middle Pass");
}

void test_find_header_last() {
  char headers[512];
  size_t max_head_size = 64;
  size_t max_header_count = 8;
  char header_value[64];
  strcpy(headers + (0 * max_head_size), "Content-Length: 65\r\n");
  strcpy(headers + (1 * max_head_size), "XYZ: 44\r\n");
  strcpy(headers + (2 * max_head_size), "ABC: 23\r\n");
  find_header("ABC", header_value, headers, 64, 3);
  assert(strcmp("23", header_value) == 0, "Header Final Pass");
}

void test_find_header_missing() {
  char headers[512];
  size_t max_head_size = 64;
  size_t max_header_count = 8;
  char header_value[64];
  assert(!find_header("ABC", header_value, headers, 64, 3), "Nothing Found");
}

void test_body() {
  struct http_parse_state state;
  char headers[512];
  size_t max_head_size = 64;
  size_t max_header_count = 8;
  char body[256];
  size_t max_body_length;
  _Bool failure;  

  printf("Test Body");
  
  state = init_http_state();
  assert(state.state == HTTP_STATE_STATUS_LINE, "Valid initial state.");
  assert(state.header_byte_position == 0, "Valid initial header byte position");
  assert(state.header_line_position == 0, "Valid initial header line position");
  assert(state.body_position == 0, "Valid initial body position.");
  
  state = update_http_state(state, 'H', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'P', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '/', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '.', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '2', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'O', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'K', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_OR_BLANK_LINE, "On header_or_blank line");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, 'C', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'o', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 't', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'e', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 't', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '-', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'L', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'e', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'g', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 't', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'h', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ':', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '9', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_OR_BLANK_LINE, "On header_or_blank line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_BLANK_LINE, "On blank line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_BODY, "On body");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, '{', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_BODY, "On Body.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '"', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_BODY, "On Body.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'a', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_BODY, "On Body.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '"', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_BODY, "On Body.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ':', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_BODY, "On Body.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '"', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_BODY, "On Body.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'b', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_BODY, "On Body.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '"', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_BODY, "On Body.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '}', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_DONE, "On Done.");
  assert(!failure, "Did not fail.");

  assert(state.header_line_position == 1, "Correct line position.");
  assert(strcmp("Content-Length: 9\r\n", headers + (0 * max_head_size)) == 0, "Correct header Content-Length: 9");
  assert(strcmp("{\"a\":\"b\"}", body) == 0, "Correct body, {a:b}");
}

void test_multiple_requests() {
  struct http_parse_state state;
  char headers[512];
  size_t max_head_size = 64;
  size_t max_header_count = 8;
  char body[256];
  size_t max_body_length;
  _Bool failure;

  printf("Test Multiple Requests");
  state = init_http_state();
  assert(state.state == HTTP_STATE_STATUS_LINE, "Valid initial state.");
  assert(state.header_byte_position == 0, "Valid initial header byte position");
  assert(state.header_line_position == 0, "Valid initial header line position");
  assert(state.body_position == 0, "Valid initial body position.");
  
  state = update_http_state(state, 'H', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'P', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '/', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '.', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '2', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'O', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'K', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_OR_BLANK_LINE, "On header_or_blank line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, 'A', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, 'B', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'C', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ':', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '6', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '5', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_OR_BLANK_LINE, "On header_or_blank line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_BLANK_LINE, "On blank line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_DONE, "On done.");
  assert(!failure, "Did not fail.");

  assert(state.header_line_position == 1, "Correct line position.");
  assert(strcmp(headers + (0 * max_head_size), "ABC: 65\r\n") == 0, "Correct header ABC: 65");

  state = init_http_state();
  assert(state.state == HTTP_STATE_STATUS_LINE, "Valid initial state.");
  assert(state.header_byte_position == 0, "Valid initial header byte position");
  assert(state.header_line_position == 0, "Valid initial header line position");
  assert(state.body_position == 0, "Valid initial body position.");
  
  state = update_http_state(state, 'H', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'P', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '/', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '.', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '2', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'O', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'K', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_STATUS_LINE, "On status line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_OR_BLANK_LINE, "On header_or_blank line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, 'A', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, 'B', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, 'C', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ':', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '6', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '5', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_LINE, "On header line.");
  assert(!failure, "Did not fail.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(state.state == HTTP_STATE_HEADER_OR_BLANK_LINE, "On header_or_blank line.");
  assert(!failure, "Did not fail.");

  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(!failure, "Did not fail.");
  assert(state.state == HTTP_STATE_BLANK_LINE, "On blank line.");
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(!failure, "Did not fail.");
  assert(state.state == HTTP_STATE_DONE, "On done.");

  assert(state.header_line_position == 1, "Correct line position.");
  assert(strcmp(headers + (0 * max_head_size), "ABC: 65\r\n") == 0, "Correct header ABC: 65");
}

void test_failure() {
  struct http_parse_state state;
  char headers[512];
  size_t max_head_size = 64;
  size_t max_header_count = 8;
  char body[256];
  size_t max_body_length;
  _Bool failure;

  printf("Test Failure");
  
  state = init_http_state();  
  state = update_http_state(state, 'H', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, 'P', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '/', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '.', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '2', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '0', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, 'O', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, 'K', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, 'A', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, 'B', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, 'C', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, ':', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '6', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '5', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '\n', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '\r', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '#', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(failure, "Fail.");
  assert(state.state == HTTP_STATE_STATUS_LINE, "Fail on \n.");
  assert(state.header_byte_position == 0, "Fail on \n");
  assert(state.header_line_position == 0, "Fail on \n");
  assert(state.body_position == 0, "Fail on \n.");

  state = init_http_state();  
  state = update_http_state(state, 'H', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, 'T', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, 'P', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '/', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '.', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '1', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, ' ', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '2', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  state = update_http_state(state, '#', headers, max_head_size, max_header_count, body, max_body_length, &failure);
  assert(failure, "Fail.");
  assert(state.state == HTTP_STATE_STATUS_LINE, "Fail on \n.");
  assert(state.header_byte_position == 0, "Fail on \n");
  assert(state.header_line_position == 0, "Fail on \n");
  assert(state.body_position == 0, "Fail on \n.");
}

void test_hard() {
  struct http_parse_state state;
  char headers[512];
  size_t max_head_size = 64;
  size_t max_header_count = 8;
  char body[256];
  size_t max_body_length;
  _Bool failure;
  printf("Test Hard\n");

  FILE * request_f = fopen("response1.txt", "rb");
  state = init_http_state();
  for (;;) {
    char input = fgetc(request_f);
    if (feof(request_f)) {
      break;
    }
    state = update_http_state(state, input, headers, max_head_size, max_header_count, body, max_body_length, &failure);
  }
  fclose(request_f);
  assert(state.state == HTTP_STATE_DONE, "On Done");
  assert(state.header_line_position == 4, "Correct amount of headers.");
  assert(strcmp("Content-Type: text/html; charset=utf-8\r\n",  headers + (0 * max_head_size)) == 0, "Correct header: Content-Type: text/html; charset=utf-8");
  assert(strcmp("Content-Length: 105\r\n",  headers + (1 * max_head_size)) == 0, "Correct header: Content-Length: 105");
  assert(strcmp("Server: Werkzeug/0.14.1 Python/2.7.13\r\n",  headers + (2 * max_head_size)) == 0, "Correct header: Server: Werkzeug/0.14.1 Python/2.7.13");
  assert(strcmp("Date: Tue, 27 Feb 2018 22:19:18 GMT\r\n",  headers + (3 * max_head_size)) == 0, "Correct header: Date: Date: Tue, 27 Feb 2018 22:19:18 GMT");
  assert(strcmp("{\"message\": \"Bad checksum, expected [0], but got [<function checksum at 0x03DC19B0>].\", \"result\": \"fail\"}", body) == 0, "Body passed.");

  request_f = fopen("response2.txt", "rb");
  for (;;) {
    char input = fgetc(request_f);
    if (feof(request_f)) {
      break;
    }
    state = update_http_state(state, input, headers, max_head_size, max_header_count, body, max_body_length, &failure);
  }
  fclose(request_f);
  assert(state.state == HTTP_STATE_DONE, "On Done");
  assert(state.header_line_position == 4, "Correct amount of headers.");
  assert(strcmp("Content-Type: text/html; charset=utf-8\r\n",  headers + (0 * max_head_size)) == 0, "Correct header: Content-Type: text/html; charset=utf-8");
  assert(strcmp("Content-Length: 63\r\n",  headers + (1 * max_head_size)) == 0, "Correct header: Content-Length: 63");
  assert(strcmp("Server: Werkzeug/0.14.1 Python/2.7.13\r\n",  headers + (2 * max_head_size)) == 0, "Correct header: Server: Werkzeug/0.14.1 Python/2.7.13");
  assert(strcmp("Date: Tue, 27 Feb 2018 22:20:25 GMT\r\n",  headers + (3 * max_head_size)) == 0, "Correct header: Date: Tue, 27 Feb 2018 22:20:25 GMT");
  assert(strcmp("{\"body\": {\"_id\": \"5a95d9a9ef4a162c28985b70\"}, \"result\": \"okay\"}", body) == 0, "Body passed.");


  request_f = fopen("response3.txt", "rb");
  for (;;) {
    char input = fgetc(request_f);
    if (feof(request_f)) {
      break;
    }
    state = update_http_state(state, input, headers, max_head_size, max_header_count, body, max_body_length, &failure);
  }
  fclose(request_f);
  assert(state.state == HTTP_STATE_DONE, "On Done");
  assert(state.header_line_position == 4, "Correct amount of headers.");
  assert(strcmp("Content-Type: text/html; charset=utf-8\r\n",  headers + (0 * max_head_size)) == 0, "Correct header: Content-Type: text/html; charset=utf-8");
  assert(strcmp("Content-Length: 52\r\n",  headers + (1 * max_head_size)) == 0, "Correct header: Content-Length: 52");
  assert(strcmp("Server: Werkzeug/0.14.1 Python/2.7.13\r\n",  headers + (2 * max_head_size)) == 0, "Correct header: Date: Tue, 27 Feb 2018 22:20:25 GMT");
  assert(strcmp("Date: Tue, 27 Feb 2018 22:20:33 GMT\r\n",  headers + (3 * max_head_size)) == 0, "Correct header: Date: Tue, 27 Feb 2018 22:20:33 GMT");
  assert(strcmp("{\"message\": \"No checksum header.\", \"result\": \"fail\"}", body) == 0, "Body passed.");

  request_f = fopen("response4.txt", "rb");
  for (;;) {
    char input = fgetc(request_f);
    if (feof(request_f)) {
      break;
    }
    state = update_http_state(state, input, headers, max_head_size, max_header_count, body, max_body_length, &failure);
  }
  fclose(request_f);
  assert(state.state == HTTP_STATE_DONE, "On Done");
  assert(state.header_line_position == 4, "Correct amount of headers.");
  assert(strcmp("Content-Type: text/html; charset=utf-8\r\n",  headers + (0 * max_head_size)) == 0, "Correct header: Content-Type: text/html; charset=utf-8");
  assert(strcmp("Content-Length: 52\r\n",  headers + (1 * max_head_size)) == 0, "Correct header: Content-Length: 52");
  assert(strcmp("Server: Werkzeug/0.14.1 Python/2.7.13\r\n",  headers + (2 * max_head_size)) == 0, "Correct header: Server: Werkzeug/0.14.1 Python/2.7.13");
  assert(strcmp("Date: Tue, 27 Feb 2018 22:20:40 GMT\r\n",  headers + (3 * max_head_size)) == 0, "Correct header: Date: Tue, 27 Feb 2018 22:20:40 GMT");
  assert(strcmp("{\"message\": \"No checksum header.\", \"result\": \"fail\"}", body) == 0, "Body passed.");

  request_f = fopen("response5.txt", "rb");
  for (;;) {
    char input = fgetc(request_f);
    if (feof(request_f)) {
      break;
    }
    state = update_http_state(state, input, headers, max_head_size, max_header_count, body, max_body_length, &failure);
  }
  fclose(request_f);
  assert(state.state == HTTP_STATE_DONE, "On Done");
  assert(state.header_line_position == 4, "Correct amount of headers.");
  assert(strcmp("Content-Type: text/html; charset=utf-8\r\n",  headers + (0 * max_head_size)) == 0, "Correct header: Content-Type: text/html; charset=utf-8");
  assert(strcmp("Content-Length: 105\r\n",  headers + (1 * max_head_size)) == 0, "Correct header: Content-Length: 105");
  assert(strcmp("Server: Werkzeug/0.14.1 Python/2.7.13\r\n",  headers + (2 * max_head_size)) == 0, "Correct header: Server: Werkzeug/0.14.1 Python/2.7.13");
  assert(strcmp("Date: Thu, 01 Mar 2018 05:43:59 GMT\r\n",  headers + (3 * max_head_size)) == 0, "Correct header: Date: Thu, 01 Mar 2018 05:43:59 GMT");
  assert(strcmp("{\"message\": \"Bad checksum, expected [0], but got [<function checksum at 0x03FC29B0>].\", \"result\": \"fail\"}", body) == 0, "Body passed.");

  request_f = fopen("response6.txt", "rb");
  for (;;) {
    char input = fgetc(request_f);
    if (feof(request_f)) {
      break;
    }
    state = update_http_state(state, input, headers, max_head_size, max_header_count, body, max_body_length, &failure);
  }
  fclose(request_f);
  assert(state.state == HTTP_STATE_DONE, "On Done");
  assert(state.header_line_position == 4, "Correct amount of headers.");
  assert(strcmp("Content-Type: text/html; charset=utf-8\r\n",  headers + (0 * max_head_size)) == 0, "Correct header: Content-Type: text/html; charset=utf-8");
  assert(strcmp("Content-Length: 63\r\n",  headers + (1 * max_head_size)) == 0, "Correct header: Content-Length: 63");
  assert(strcmp("Server: Werkzeug/0.14.1 Python/2.7.13\r\n",  headers + (2 * max_head_size)) == 0, "Correct header: Server: Werkzeug/0.14.1 Python/2.7.13");
  assert(strcmp("Date: Thu, 01 Mar 2018 05:44:07 GMT\r\n",  headers + (3 * max_head_size)) == 0, "Correct header: Date: Thu, 01 Mar 2018 05:44:07 GMT");
  assert(strcmp("{\"body\": {\"_id\": \"5a979327ef4a161d2c1ded55\"}, \"result\": \"okay\"}", body) == 0, "Body passed.");
}

void test_ngnx() {
  struct http_parse_state state;
  char headers[512];
  size_t max_head_size = 64;
  size_t max_header_count = 8;
  char body[256];
  size_t max_body_length;
  _Bool failure;
  printf("Test Ngnx\n");

  FILE * request_f = fopen("ngnx1.txt", "rb");
  state = init_http_state();
  for (;;) {
    char input = fgetc(request_f);
    if (feof(request_f)) {
      break;
    }
    state = update_http_state(state, input, headers, max_head_size, max_header_count, body, max_body_length, &failure);
  }
  fclose(request_f);
  assert(state.state == HTTP_STATE_DONE, "On Done");
  assert(state.header_line_position == 6, "Correct amount of headers.");
  assert(strcmp("Server: nginx/1.13.9\r\n",  headers + (0 * max_head_size)) == 0, "Correct header: Server: nginx/1.13.9\r\n");
  assert(strcmp("Date: Sat, 17 Mar 2018 04:46:35 GMT\r\n",  headers + (1 * max_head_size)) == 0, "Correct header: Date: Sat, 17 Mar 2018 04:46:35 GMT");
  assert(strcmp("Content-Type: text/html; charset=utf-8\r\n",  headers + (2 * max_head_size)) == 0, "Correct header: Content-Type: text/html; charset=utf-8");
  assert(strcmp("Content-Length: 136\r\n",  headers + (3 * max_head_size)) == 0, "Correct header: Content-Length: 136");
  assert(strcmp("Connection: keep-alive\r\n",  headers + (4 * max_head_size)) == 0, "Correct header: Connection: keep-alive");
  assert(strcmp("X-Checksum: 2970207055\r\n",  headers + (5 * max_head_size)) == 0, "Correct header: X-Checksum: 2970207055");  
  assert(strcmp("{\"body\": {\"motor_speed\": \"1\", \"_id\": \"5a98ff20eb21d23504ea61ab\", \"speed\": \"1000\"}, \"found\": \"okay\", \"result\": \"okay\", \"sequence\": \"593\"}", body) == 0, "Body passed.");
}

int main() {
  printf("Test HTTP Parse\n");
  test_basic();
  test_multiple_headers();
  test_find_header_first();
  test_find_header_middle();
  test_find_header_last();
  test_body();
  test_multiple_requests();
  test_hard();
  test_find_header_missing();
  test_failure();
  test_ngnx();
  return 0;
}
