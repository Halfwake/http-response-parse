#include "http_blank_line_parse.h"
#include "debug.h"
#include <stdio.h>

void assert(int check, char * description) {
  printf("[%s] - %s\n", check ? "T" : "F", description);
}

void test_basic() {
  printf("Testing Basic\n");
  enum BLANK_LINE_STATE state = init_blank_line_state();
  assert(state == BLANK_STATE_START, "Start");

  state = update_blank_line_state(state, '\r');
  assert(state == BLANK_STATE_R_1, "\\r");

  state = update_blank_line_state(state, '\n');
  assert(state == BLANK_STATE_N_2, "\\n");
}

void test_failure() {
  printf("Testing Failure\n");
  enum BLANK_LINE_STATE state = init_blank_line_state();
  state = update_blank_line_state(state, '\r');
  state = update_blank_line_state(state, 'F');
  assert(state == BLANK_STATE_START, "Break at \\n");
  
  state = init_blank_line_state();
  state = update_blank_line_state(state, 'F');
  assert(state == BLANK_STATE_START, "Break at \\n");
}

int main() {
  printf("Starting HTTP Blank Line Parse Tests\n");
  test_basic();
  test_failure();
}
