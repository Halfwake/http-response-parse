#ifndef _TEAM11_HTTP_STATUS_PARSE_H
#define _TEAM11_HTTP_STATUS_PARSE_H

enum STATUS_LINE_STATE {
  STATUS_STATE_START,
  STATUS_STATE_H_1,
  STATUS_STATE_T_2,
  STATUS_STATE_T_3,
  STATUS_STATE_P_4,
  STATUS_STATE_SLASH_5,
  STATUS_STATE_1_6,
  STATUS_STATE_DOT_7,
  STATUS_STATE_1_8,  
  STATUS_STATE_SPACE_1,
  STATUS_STATE_1_2,
  STATUS_STATE_2_0,
  STATUS_STATE_3_0,
  STATUS_STATE_SPACE_2,
  STATUS_STATE_1_O,
  STATUS_STATE_2_K,
  STATUS_STATE_R_1,
  STATUS_STATE_N_2,
};

/*
 * The initial state for the HTTP status line parser.
 * @return The initial state value for the HTTP status line parser.
 */
enum STATUS_LINE_STATE init_status_line_state();

/*
 * Update the state for the HTTP status line parser.
 * @param state The current state.
 * @param input The input character.
 * @return The new state.
 */
enum STATUS_LINE_STATE update_status_line_state(enum STATUS_LINE_STATE state, char input);

#endif
