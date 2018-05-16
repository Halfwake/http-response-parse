#include "debug.h"
#include "http_header_parse.h"
#include <stdio.h>

void assert(int check, char * description) {
  printf("[%s] - %s\n", check ? "T" : "F", description);
}

int test_basic() {
  printf("Basic Test:\n");
  
  enum HEADER_LINE_STATE state = init_header_line_state();
  assert(state == HEADER_STATE_START, "Start");
  
  state = update_header_line_state(state, 'C');
  assert(state == HEADER_STATE_NAME, "C");

  state = update_header_line_state(state, 'o');
  assert(state == HEADER_STATE_NAME, "o");

  state = update_header_line_state(state, 'n');
  assert(state == HEADER_STATE_NAME, "n");

  state = update_header_line_state(state, 't');
  assert(state == HEADER_STATE_NAME, "t");

  state = update_header_line_state(state, 'e');
  assert(state == HEADER_STATE_NAME, "e");

  state = update_header_line_state(state, 'n');
  assert(state == HEADER_STATE_NAME, "n");

  state = update_header_line_state(state, 't');
  assert(state == HEADER_STATE_NAME, "t");

  state = update_header_line_state(state, '-');
  assert(state == HEADER_STATE_NAME, "-");

  state = update_header_line_state(state, 'L');
  assert(state == HEADER_STATE_NAME, "L");

  state = update_header_line_state(state, 'e');
  assert(state == HEADER_STATE_NAME, "e");

  state = update_header_line_state(state, 'n');
  assert(state == HEADER_STATE_NAME, "n");

  state = update_header_line_state(state, 'g');
  assert(state == HEADER_STATE_NAME, "g");

  state = update_header_line_state(state, 't');
  assert(state == HEADER_STATE_NAME, "t");

  state = update_header_line_state(state, 'h');
  assert(state == HEADER_STATE_NAME, "g");

  state = update_header_line_state(state, ':');
  assert(state == HEADER_STATE_SEP, ":");

  state = update_header_line_state(state, ' ');
  assert(state == HEADER_STATE_SPACE, " ");

  state = update_header_line_state(state, '3');
  assert(state == HEADER_STATE_VAL, "3");

  state = update_header_line_state(state, '2');
  assert(state == HEADER_STATE_VAL, "2");

  state = update_header_line_state(state, '2');
  assert(state == HEADER_STATE_VAL, "2");

  state = update_header_line_state(state, '1');
  assert(state == HEADER_STATE_VAL, "1");

  state = update_header_line_state(state, '\r');
  assert(state == HEADER_STATE_R_1, "\\r");

  state = update_header_line_state(state, '\n');
  assert(state == HEADER_STATE_N_2, "\\n");
}

int test_failure() {
  printf("Test Extra Space:\n");
  
  enum HEADER_LINE_STATE state = init_header_line_state();
  state = update_header_line_state(state, 'C');
  state = update_header_line_state(state, '-');
  state = update_header_line_state(state, 'L');
  state = update_header_line_state(state, ':');
  state = update_header_line_state(state, ' ');
  state = update_header_line_state(state, '1');
  state = update_header_line_state(state, '\r');
  state = update_header_line_state(state, '\t');
  assert(state == HEADER_STATE_START, "Fail on \r");

  state = init_header_line_state();
  state = update_header_line_state(state, 'C');
  state = update_header_line_state(state, '-');
  state = update_header_line_state(state, 'L');
  state = update_header_line_state(state, ':');
  state = update_header_line_state(state, ' ');
  state = update_header_line_state(state, '1');
  state = update_header_line_state(state, '\t');
  assert(state == HEADER_STATE_START, "Fail on 1");

  state = init_header_line_state();
  state = update_header_line_state(state, 'C');
  state = update_header_line_state(state, '-');
  state = update_header_line_state(state, 'L');
  state = update_header_line_state(state, ':');
  state = update_header_line_state(state, '\t');
  assert(state == HEADER_STATE_START, "Fail on :");

  state = init_header_line_state();
  state = update_header_line_state(state, 'C');
  state = update_header_line_state(state, '-');
  state = update_header_line_state(state, 'L');
  state = update_header_line_state(state, '\t');
  assert(state == HEADER_STATE_START, "Fail on L");

  state = init_header_line_state();
  state = update_header_line_state(state, 'C');
  state = update_header_line_state(state, '-');
  state = update_header_line_state(state, '\t');
  assert(state == HEADER_STATE_START, "Fail on \t");

  state = init_header_line_state();
  state = update_header_line_state(state, 'C');
  state = update_header_line_state(state, '\t');
  assert(state == HEADER_STATE_START, "Fail on C");

  state = init_header_line_state();
  state = update_header_line_state(state, '\t');
  assert(state == HEADER_STATE_START, "Fail on start");
}

int main() {
  printf("Header Test:\n");
  test_basic();
  test_failure();
}
