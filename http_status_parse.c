#include "http_status_parse.h"
#include "debug.h"

enum STATUS_LINE_STATE init_status_line_state() {
  return STATUS_STATE_START;
}

enum STATUS_LINE_STATE update_status_line_state(enum STATUS_LINE_STATE state, char input) {
  enum STATUS_LINE_STATE new_state;
  switch (state) {
  case STATUS_STATE_START:
    if (input == 'H') {
      new_state = STATUS_STATE_H_1;
    }
    break;
  case STATUS_STATE_H_1:
    if (input == 'T') {
      new_state = STATUS_STATE_T_2;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_T_2:
    if (input == 'T') {
      new_state = STATUS_STATE_T_3;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_T_3:
    if (input == 'P') {
      new_state = STATUS_STATE_P_4;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_P_4:
    if (input == '/') {
      new_state = STATUS_STATE_SLASH_5;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_SLASH_5:
    if (input == '1') {
      new_state = STATUS_STATE_1_6;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_1_6:
    if (input == '.') {
      new_state = STATUS_STATE_DOT_7;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_DOT_7:
    if (input == '1') {
      new_state = STATUS_STATE_1_8;
    } else {
      new_state = STATUS_STATE_START;
    }    
    break;
  case STATUS_STATE_1_8:
    if (input == ' ') {
      new_state = STATUS_STATE_SPACE_1;
    } else {
      new_state = STATUS_STATE_START;
    }    
    break;
  case STATUS_STATE_SPACE_1:
    if (input == '2') {
      new_state = STATUS_STATE_1_2;
    } else if (input == ' ') {
      new_state = STATUS_STATE_SPACE_1;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_1_2:
    if (input == '0') {
      new_state = STATUS_STATE_2_0;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_2_0:
    if (input == '0') {
      new_state = STATUS_STATE_3_0;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_3_0:
    if (input == ' ') {
      new_state = STATUS_STATE_SPACE_2;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_SPACE_2:
    if (input == 'O') {
      new_state = STATUS_STATE_1_O;
    } else if (input == ' ') {
      new_state = STATUS_STATE_SPACE_2;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_1_O:
    if (input == 'K') {
      new_state = STATUS_STATE_2_K;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_2_K:
    if (input == '\r') {
      new_state = STATUS_STATE_R_1;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_R_1:
    if (input == '\n') {
      new_state = STATUS_STATE_N_2;
    } else {
      new_state = STATUS_STATE_START;
    }
    break;
  case STATUS_STATE_N_2:
    new_state = state;
    break;
  default:
    dbgPanic(0);
  }
  return new_state;
}
