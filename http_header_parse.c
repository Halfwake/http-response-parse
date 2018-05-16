#include "http_header_parse.h"
#include "debug.h"

enum HEADER_LINE_STATE init_header_line_state() {
  return HEADER_STATE_START;
}

/*
 * Check if argument is a valid part of a word.
 * @param True if argument is a digit or alpha.
 */
static int valid_value_letter(char letter) {
  int is_digit = (48 <= letter) && (letter <= 57);
  int is_alpha_down = (65 <= letter) && (letter <= 90);
  int is_alpha_up = (97 <= letter) && (letter <= 122);
  int is_dash = letter == '-';
  int is_slash = letter == '/';
  int is_colon = letter == ':';
  int is_semicolon = letter == ';';
  int is_comma = letter == ',';
  int is_dot = letter == '.';
  int is_space = letter == ' ';
  int is_equal = letter == '=';
  return is_digit || is_alpha_down || is_alpha_up || is_dash || is_slash || is_colon || is_semicolon || is_comma || is_dot || is_space || is_equal;
}

static int valid_key_letter(char letter) {
  int is_digit = (48 <= letter) && (letter <= 57);
  int is_alpha_down = (65 <= letter) && (letter <= 90);
  int is_alpha_up = (97 <= letter) && (letter <= 122);
  int is_dash = letter == '-';
  int is_slash = letter == '/';
  int is_semicolon = letter == ';';
  int is_comma = letter == ',';
  int is_dot = letter == '.';
  return is_digit || is_alpha_down || is_alpha_up || is_dash || is_slash || is_semicolon || is_comma || is_dot;
}

enum HEADER_LINE_STATE update_header_line_state(enum HEADER_LINE_STATE state, char input) {
  enum HEADER_LINE_STATE new_state;
  switch (state) {
  case HEADER_STATE_START:
    if (valid_key_letter(input)) {
      new_state = HEADER_STATE_NAME;
    } else {
      new_state = HEADER_STATE_START;
    }
    break;
  case HEADER_STATE_NAME:
    if (valid_key_letter(input)) {
      new_state = HEADER_STATE_NAME;
    } else if (input == ':') {
      new_state = HEADER_STATE_SEP;
    } else {
      new_state = HEADER_STATE_START;
    }
    break;
  case HEADER_STATE_SEP:
    if (input == ' ') {
      new_state = HEADER_STATE_SPACE;
    } else if (valid_value_letter(input)) {
      new_state =  HEADER_STATE_VAL;
    } else {
      new_state = HEADER_STATE_START;
    }    
    break;
  case HEADER_STATE_SPACE:
    if (valid_value_letter(input)) {
      new_state = HEADER_STATE_VAL;
    } else {
      new_state = HEADER_STATE_START;
    }
    break;
  case HEADER_STATE_VAL:
    if (valid_value_letter(input)) {
      new_state = HEADER_STATE_VAL;      
    } else if (input == '\r') {
      new_state = HEADER_STATE_R_1;
    } else {
      new_state = HEADER_STATE_START;
    }
    break;
  case HEADER_STATE_R_1:
    if (input == '\n') {
      new_state = HEADER_STATE_N_2;
    } else {
      new_state = HEADER_STATE_START;
    }
    break;
  case HEADER_STATE_N_2:
    new_state = HEADER_STATE_N_2;
    break;
  default:
    dbgPanic(0);
  }
  return new_state;
}
