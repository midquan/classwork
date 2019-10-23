# $Id: Makefile,v 1.1 2016-01-21 16:27:37-08 - - $

SOURCES   = hello.c
OBJECTS   = ${SOURCES:.c=.o}
ALLSRCS   = ${SOURCES} Makefile
EXECBIN   = hello

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu11

all: ${EXECBIN}

${EXECBIN}: ${OBJECTS}
	${GCC} ${OBJECTS} -o ${EXECBIN}

%.o : %.c
	- checksource $<
	cid + $<
	${GCC} -c $< -o $@

test: 
	${EXECBIN} > test1.out 2> test1.err; echo$$? > test1.status
	${EXECBIN} world > test2.out 2> test2.err; echo $$? > test2.status 
