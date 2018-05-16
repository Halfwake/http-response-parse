CLAGS=-g

test: test_http_status_parse.out test_http_blank_line_parse.out test_http_header_parse.out test_http_parse.out
	./test_http_status_parse.out
	./test_http_blank_line_parse.out
	./test_http_header_parse.out
	./test_http_parse.out

test_http_parse.out: test_http_parse.c http_parse.o http_header_parse.o http_blank_line_parse.o http_status_parse.o
	gcc $(CFLAGS) -o test_http_parse.out test_http_parse.c http_parse.o debug.o http_header_parse.o http_blank_line_parse.o http_status_parse.o

test_http_header_parse.out: test_http_header_parse.c http_header_parse.o debug.o
	gcc $(CFLAGS) -o test_http_header_parse.out test_http_header_parse.c http_header_parse.o debug.o

test_http_blank_line_parse.out: test_http_blank_line_parse.c http_blank_line_parse.o debug.o
	gcc $(CFLAGS) -o test_http_blank_line_parse.out test_http_blank_line_parse.c http_blank_line_parse.o debug.o

test_http_status_parse.out: test_http_status_parse.c http_status_parse.o debug.o
	gcc $(CFLAGS) -o test_http_status_parse.out test_http_status_parse.c http_status_parse.o debug.o

http_parse.o: http_parse.c http_parse.h
	gcc $(CFLAGS) -c http_parse.c

http_header_parse.o: http_header_parse.c http_header_parse.h
	gcc $(CFLAGS) -c http_header_parse.c

http_blank_line_parse.o: http_blank_line_parse.c http_blank_line_parse.h
	gcc $(CFLAGS) -c http_blank_line_parse.c

http_status_parse.o: http_status_parse.c http_status_parse.h
	gcc $(CFLAGS) -c http_status_parse.c

debug.o: debug.c debug.h
	gcc $(CFLAGS) -c debug.c
