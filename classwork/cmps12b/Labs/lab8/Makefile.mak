GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99
CSOURCES = mstat.c
SOURCES  = ${CSOURCES} Makefile README
EXECBINS = mstat
SUBMIT   = submit cmps012b-wm.w16 lab8

all : ${EXECBINS}

% : %.c
	${GCC} $< -o $@

ci :
	cid + ${SOURCES}
	- checksource $<

clean :
	- rm -vf core

spotless : clean
	- rm -vf ${EXECBINS}

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all