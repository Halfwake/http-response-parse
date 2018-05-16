#ifndef _TEAM11_HTTP_H
#define _TEAM11_HTTP_h
#include "FreeRTOS.h"
#include "queue.h"
#include "stdio.h"
#include <string.h>
#include <stdbool.h>
#include "debug_communication.h"
#include "crc32.h"
/*
 * Functions for ending HTTP messages. Should not be used directly by tasks.
 */

/*
 * Create a new object in the database. A HTTP response
 * with the ID of the object will be sent.
 * @param collection A null terminated string with the table name.
 * @param body A buffer of bytes representing a JSON payload.
 * @param size The size of the body buffer.
 * @param sequence_number The sequence number. The response will include it in
 * its body.
 */
void http_generic(char * action, char * collection, char * body, int sequence_number);

/*
 * Create a object that matches all the fields in the body.
 * A HTTP response with the object will be sent.
 * @param collection A null terminated string with the table name.
 * @param body A buffer of bytes representing a JSON payload.
 * @param size The size of the body buffer.
 * @param sequence_number The sequence number. The response will include it in
 * its body.
 */
void http_post(char * collection, char * body, int sequence_number);

/*
 * Return an object that matches all the fields in the body.
 * A HTTP response with the object will be sent.
 * @param collection A null terminated string with the table name.
 * @param body A buffer of bytes representing a JSON payload.
 * @param size The size of the body buffer.
 * @param sequence_number The sequence number. The response will include it in
 * its body.
 */
void http_get(char * collection, char * body, int sequence_number);

/*
 * Delete an object from the database. A HTTP response
 * confirming the deletion will be returned.
 * @param collection A null terminated string with the table name.
 * @param body A buffer of bytes representing a JSON payload.
 * @param size The size of the body buffer.
 * @param sequence_number The sequence number. The response will include it in
 * its body.
 */
void http_delete(char * collection, char * body, int sequence_number);

/*
 * Update an object in database. A HTTP response
 * confirming the update will be returned.
 * @param collection A null terminated string with the table name.
 * @param body A buffer of bytes representing a JSON payload.
 * @param query A buffer of bytes representing a JSON payload.
 * @param size The size of the body buffer.
 * @param sequence_number The sequence number. The response will include it in
 * its body.
 */
void http_update_generic(char * action, char * collection, char * body, char * query, int sequence_number);
void http_update(char * collectoin, char * body, char * query, int sequence_number);

#endif