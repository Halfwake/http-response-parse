#include "http_status_parse.h"
#include <stdio.h>

void assert(int check, char * description) {
  printf("[%s] - %s\n", check ? "T" : "F", description);
}

int test_basic() {
  printf("Basic Test:\n");
  
  enum STATUS_LINE_STATE state = init_status_line_state();
  assert(state == STATUS_STATE_START, "Start");
  
  state = update_status_line_state(state, 'H');    
  assert(state == STATUS_STATE_H_1, "H");
  
  state = update_status_line_state(state, 'T');  
  assert(state == STATUS_STATE_T_2, "T");
  
  state = update_status_line_state(state, 'T');  
  assert(state == STATUS_STATE_T_3, "T");
  
  state = update_status_line_state(state, 'P');  
  assert(state == STATUS_STATE_P_4, "P");

  state = update_status_line_state(state, '/');  
  assert(state == STATUS_STATE_SLASH_5, "/");
  
  state = update_status_line_state(state, '1');  
  assert(state == STATUS_STATE_1_6, "1");
  
  state = update_status_line_state(state, '.');  
  assert(state == STATUS_STATE_DOT_7, ".");
  
  state = update_status_line_state(state, '1');  
  assert(state == STATUS_STATE_1_8, "1");
  
  state = update_status_line_state(state, ' ');  
  assert(state == STATUS_STATE_SPACE_1, " ");
  
  state = update_status_line_state(state, '2');
  assert(state == STATUS_STATE_1_2, "2");

  state = update_status_line_state(state, '0');
  assert(state == STATUS_STATE_2_0, "0");

  state = update_status_line_state(state, '0');
  assert(state == STATUS_STATE_3_0, "0");

  state = update_status_line_state(state, ' ');
  assert(state == STATUS_STATE_SPACE_2, " ");

  state = update_status_line_state(state, 'O');
  assert(state == STATUS_STATE_1_O, "O");

  state = update_status_line_state(state, 'K');
  assert(state == STATUS_STATE_2_K, "K");

  state = update_status_line_state(state, '\r');
  assert(state == STATUS_STATE_R_1, "\\r");

  state = update_status_line_state(state, '\n');
  assert(state == STATUS_STATE_N_2, "\\n");	 
}

int test_extra_spaces() {
  printf("Extra Spaces Test:\n");
    
  enum STATUS_LINE_STATE state = init_status_line_state();
  assert(state == STATUS_STATE_START, "Start");
  
  state = update_status_line_state(state, 'H');    
  assert(state == STATUS_STATE_H_1, "H");
  
  state = update_status_line_state(state, 'T');  
  assert(state == STATUS_STATE_T_2, "T");
  
  state = update_status_line_state(state, 'T');  
  assert(state == STATUS_STATE_T_3, "T");
  
  state = update_status_line_state(state, 'P');  
  assert(state == STATUS_STATE_P_4, "P");

  state = update_status_line_state(state, '/');  
  assert(state == STATUS_STATE_SLASH_5, "/");
  
  state = update_status_line_state(state, '1');  
  assert(state == STATUS_STATE_1_6, "1");
  
  state = update_status_line_state(state, '.');  
  assert(state == STATUS_STATE_DOT_7, ".");
  
  state = update_status_line_state(state, '1');  
  assert(state == STATUS_STATE_1_8, "1");
  
  state = update_status_line_state(state, ' ');  
  assert(state == STATUS_STATE_SPACE_1, " ");

  state = update_status_line_state(state, ' ');  
  assert(state == STATUS_STATE_SPACE_1, " ");

  state = update_status_line_state(state, ' ');  
  assert(state == STATUS_STATE_SPACE_1, " ");
  
  state = update_status_line_state(state, '2');
  assert(state == STATUS_STATE_1_2, "2");

  state = update_status_line_state(state, '0');
  assert(state == STATUS_STATE_2_0, "0");

  state = update_status_line_state(state, '0');
  assert(state == STATUS_STATE_3_0, "0");

  state = update_status_line_state(state, ' ');
  assert(state == STATUS_STATE_SPACE_2, " ");

  state = update_status_line_state(state, ' ');
  assert(state == STATUS_STATE_SPACE_2, " ");

  state = update_status_line_state(state, ' ');
  assert(state == STATUS_STATE_SPACE_2, " ");

  state = update_status_line_state(state, 'O');
  assert(state == STATUS_STATE_1_O, "O");

  state = update_status_line_state(state, 'K');
  assert(state == STATUS_STATE_2_K, "K");

  state = update_status_line_state(state, '\r');
  assert(state == STATUS_STATE_R_1, "\\r");

  state = update_status_line_state(state, '\n');
  assert(state == STATUS_STATE_N_2, "\\n");	 
}

int test_failure() {
  printf("Test Failure:\n");
  
  enum STATUS_LINE_STATE state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, '.');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, ' ');  
  state = update_status_line_state(state, '2');
  state = update_status_line_state(state, '0');
  state = update_status_line_state(state, '0');
  state = update_status_line_state(state, ' ');
  state = update_status_line_state(state, 'O');
  state = update_status_line_state(state, 'K');
  state = update_status_line_state(state, '\r');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at \\n");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, '.');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, ' ');  
  state = update_status_line_state(state, '2');
  state = update_status_line_state(state, '0');
  state = update_status_line_state(state, '0');
  state = update_status_line_state(state, ' ');
  state = update_status_line_state(state, 'O');
  state = update_status_line_state(state, 'K');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at \\r");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, '.');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, ' ');  
  state = update_status_line_state(state, '2');
  state = update_status_line_state(state, '0');
  state = update_status_line_state(state, '0');
  state = update_status_line_state(state, ' ');
  state = update_status_line_state(state, 'O');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at \\K");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, '.');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, ' ');  
  state = update_status_line_state(state, '2');
  state = update_status_line_state(state, '0');
  state = update_status_line_state(state, '0');
  state = update_status_line_state(state, ' ');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at \\O");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, '.');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, ' ');  
  state = update_status_line_state(state, '2');
  state = update_status_line_state(state, '0');
  state = update_status_line_state(state, '0');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at ' '");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, '.');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, ' ');  
  state = update_status_line_state(state, '2');
  state = update_status_line_state(state, '0');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at 0");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, '.');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, ' ');  
  state = update_status_line_state(state, '2');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at 0");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, '.');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, ' ');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at '2'");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, '.');  
  state = update_status_line_state(state, '1');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at ' '");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');  
  state = update_status_line_state(state, '1');  
  state = update_status_line_state(state, '.');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at .");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');  
  state = update_status_line_state(state, '1');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at 1");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');  
  state = update_status_line_state(state, '/');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at /");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'P');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at P");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');  
  state = update_status_line_state(state, 'T');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at T");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');    
  state = update_status_line_state(state, 'T');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at T");

  state = init_status_line_state();
  state = update_status_line_state(state, 'H');
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at H");

  state = init_status_line_state();
  state = update_status_line_state(state, 'F');
  assert(state == STATUS_STATE_START, "Fail at Init");
  
}

int main() {
  printf("Starting HTTP Status Line Parse Tests");
  test_basic();
  test_extra_spaces();
  test_failure();
}
