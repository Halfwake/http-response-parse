#ifndef _TEAM11_HTTP_BLANK_PARSE_H
#define _TEAM11_HTTP_BLANK_PARSE_H

enum BLANK_LINE_STATE {
  BLANK_STATE_START,
  BLANK_STATE_R_1,
  BLANK_STATE_N_2,
};

/*
 * The initial state for the HTTP blank line parser.
 * @return The initial state value for the HTTP blank line parser.
 */
enum BLANK_LINE_STATE init_blank_line_state();

/*
 * Update the state for the HTTP blank line parser.
 * @param state The current state.
 * @param input The input character.
 * @return The new state.
 */
enum BLANK_LINE_STATE update_blank_line_state(enum BLANK_LINE_STATE state, char input);

#endif
