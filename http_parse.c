#include "http_parse.h"
#include "debug.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

struct http_parse_state init_http_state() {
  struct http_parse_state state;
  state.state = HTTP_STATE_STATUS_LINE;
  state.header_byte_position = 0;
  state.header_line_position = 0;
  state.body_length = 0;
  state.body_position = 0;
  state.status_line_state = init_status_line_state();
  state.header_line_state = init_header_line_state();
  state.blank_line_state = init_blank_line_state();
  return state;
}

struct http_parse_state update_http_state(struct http_parse_state state, char input, char * headers, size_t max_header_size, size_t max_header_count, char * body, size_t max_body_length, _Bool * failure) {
  *failure = 0;
  switch (state.state) {
  case HTTP_STATE_STATUS_LINE:
    state.status_line_state = update_status_line_state(state.status_line_state, input);
    if (state.status_line_state == STATUS_STATE_N_2) {
      state.state = HTTP_STATE_HEADER_OR_BLANK_LINE;
    }
    if (state.status_line_state == STATUS_STATE_START) {
      *failure = 1;
      return init_http_state();
    }
    break;
  case HTTP_STATE_HEADER_OR_BLANK_LINE:
    if (input == '\r') {
      state.state = HTTP_STATE_BLANK_LINE;
      state.blank_line_state = update_blank_line_state(state.blank_line_state, input);
      char header_value[256]; //TODO! This exposes a buffer overflow vuln for header_values longer than 256 bytes.
      if (find_header("Content-Length", header_value, headers, max_header_size, state.header_line_position)) {
	if (sscanf(header_value, "%d", &state.body_length) != 1) {
	  *failure = 1;
	  return init_http_state();
	}
      }
    } else {
      state.state = HTTP_STATE_HEADER_LINE;
      headers[(state.header_line_position * max_header_size) + state.header_byte_position++] = input;
      state.header_line_state = update_header_line_state(HEADER_STATE_START, input);
      if (state.header_line_state == HEADER_STATE_START) {
	*failure = 1;
	return init_http_state();
      }
    }
    break;
  case HTTP_STATE_HEADER_LINE:
    if (state.header_line_position >= (max_header_count - 1)) {
      *failure = 1;
      return init_http_state();
    }
    if (state.header_byte_position >= (max_header_size - 1)) {
      *failure = 1;
      return init_http_state();
    }
    headers[(state.header_line_position * max_header_size) + state.header_byte_position++] = input;
    state.header_line_state = update_header_line_state(state.header_line_state, input);
    if (state.header_line_state == HEADER_STATE_N_2) {
      state.state = HTTP_STATE_HEADER_OR_BLANK_LINE;
      headers[(state.header_line_position * max_header_size) + state.header_byte_position] = '\0';
      state.header_line_position++;
      state.header_byte_position = 0;
    } else if (state.header_line_state == HEADER_STATE_START) {
      *failure = 1;
      return init_http_state();
    }    
    break;
  case HTTP_STATE_BLANK_LINE:
    state.blank_line_state = update_blank_line_state(state.blank_line_state, input);
    if (state.blank_line_state == BLANK_STATE_START) {
      *failure = 1;
      return init_http_state();
    } else if (state.blank_line_state == BLANK_STATE_N_2) {
      if (state.body_length == 0) {
	state.state = HTTP_STATE_DONE;
      } else {
	state.state = HTTP_BODY;
      }
    }
    break;
  case HTTP_BODY:
    if (state.body_position >= (max_body_length - 1)) {
      *failure = 1;
      return init_http_state();
    }
    body[state.body_position++] = input;
    if (state.body_position == state.body_length) {
      body[state.body_position] = '\0';
      state.state = HTTP_STATE_DONE;
    }
    break;
  case HTTP_STATE_DONE:
    state = init_http_state();
    state.status_line_state = update_status_line_state(state.status_line_state, input);
    if (state.status_line_state == STATUS_STATE_START) {
      *failure = 1;
      return init_http_state();
    }
    break;
  default:
    dbgPanic(0x00);
  }
  return state;
}

_Bool find_header(char * key, char * header_value, char * headers, size_t header_line_size, size_t header_line_count) {
  size_t line_n;
  int success = 0;
  char format_buffer[256];
  snprintf(format_buffer, 256, "%s: %%%ds\r\n", key, header_line_size - 1);
   for (line_n = 0; line_n < header_line_count; line_n++) {
    success = sscanf(headers + (line_n * header_line_size), format_buffer, header_value);
    if (success == 1) { // Do not change this! Success is not a boolean.
      return true;
    }
  }
  return false;
}
