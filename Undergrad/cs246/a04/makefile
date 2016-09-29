#  CS246.  February 2011.  Make file for setcalc program.
#     Run this using gmake (not make)
#     On Linux, the gmake command is spelled as make

CXX = g++
CXXFLAGS = -g -Wall 
OBJECTS = help.o strset.o setcalc.o

EXEC = setcalc

all : ${EXEC}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o $@
	
help.o : help.h

strset.o : strset.h

setcalc.o : help.h strset.h

clean :
	rm -f ${EXEC} ${OBJECTS}
