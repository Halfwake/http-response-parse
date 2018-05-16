#ifndef _TEAM11_HTTP_HEADER_PARSE_H
#define _TEAM11_HTTP_HEADER_PARSE_H

enum HEADER_LINE_STATE {
  HEADER_STATE_START,
  HEADER_STATE_NAME,
  HEADER_STATE_SEP,
  HEADER_STATE_SPACE,
  HEADER_STATE_VAL,
  HEADER_STATE_R_1,
  HEADER_STATE_N_2
};

/*
 * The initial state for the HTTP header line parser.
 * @return The initial state value for the HTTP header line parser.
 */
enum HEADER_LINE_STATE init_header_line_state();

/*
 * Update the state for the HTTP header line parser.
 * @param state The current state.
 * @param input The input character.
 * @return The new state.
 */
enum HEADER_LINE_STATE update_header_line_state(enum HEADER_LINE_STATE state, char input);

#endif
