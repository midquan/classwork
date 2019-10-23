# $ID$

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu11
MKDEPS   = gcc -MM

EXECBINS = numsort linesort
LIBSRC   = numsort.c linesort.c inssort.h inssort.c
OBJECTS  = ${EXECBINS:=.o} numsort.o linesort.o inssort.o 
SOURCES  = ${LIBSRC} ${EXECBINS:=.c} Makefile README
DEPFILE  = Makefile.deps
SUBMIT   = submit cmps012b-wm.w16 lab9

all: ${EXECBINS}

numsort: numsort.o inssort.o
	${GCC} -o $@ $^ -lm

linesort: linesort.o inssort.o
	${GCC} -o $@ $^ -lm

%.o: %.c
	${GCC} -c $<

ci: ${SOURCES}
	checksource ${SOURCES}
	cid + ${SOURCES}

%.out: %
	$< >$@ 2>&1

${DEPFILE}:
	${MKDEPS} ${SOURCES} >${DEPFILE}

dep:
	- rm ${DEPFILE}
	make --no-print-directory ${DEPFILE}

submit: ${SOURCES}
	${SUBMIT} ${SOURCES}

include ${DEPFILE}
