#include "http_blank_line_parse.h"

enum BLANK_LINE_STATE init_blank_line_state() {
  return BLANK_STATE_START;
}

enum BLANK_LINE_STATE update_blank_line_state(enum BLANK_LINE_STATE state, char input) {
  enum BLANK_LINE_STATE new_state;
  switch (state) {
  case BLANK_STATE_START:
    if (input == '\r') {
      new_state = BLANK_STATE_R_1;
    } else {
      new_state = BLANK_STATE_START;
    }
    break;    
  case BLANK_STATE_R_1:
    if (input == '\n') {
      new_state = BLANK_STATE_N_2;
    } else {
      new_state = BLANK_STATE_START;
    }    
    break;
  case BLANK_STATE_N_2:
    new_state = BLANK_STATE_N_2;
    break;
  }
  return new_state;
}
