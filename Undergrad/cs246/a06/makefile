#  CS 246  Winter 2011  Assignment 6
#     Makefile for driver (SL Interpreter)
#     Run this using gmake (not make)
#     On Linux, the gmake command in spelled as make

CC = g++
CCFLAGS = -g -O0 -Wall

OBJECTS1 = token.o tokenbuffer.o dumper.o
EXEC1 = dumper

OBJECTS2 = token.o tokenbuffer.o strset3.o extstrset3.o driver.o
EXEC2 = driver

OBJECTS = ${OBJECTS1} ${OBJECTS2}
EXECS = ${EXEC1} ${EXEC2}

##################################################################

.PHONY : all clean

all : ${EXECS}

${EXEC1} : ${OBJECTS1}
	${CC} ${CCFLAGS} ${OBJECTS1} -o $@

${EXEC2} : ${OBJECTS2}
	${CC} ${CCFLAGS} ${OBJECTS2} -o $@

#################################################################

clean :
	rm -f token.o tokenbuffer.o extstrset3.o dumper.o driver.o ${EXECS}

