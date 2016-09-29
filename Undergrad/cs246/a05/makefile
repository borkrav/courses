#  CS246.  February 2011.  Make file for setcalc program.
#     Run this using gmake (not make)
#     On Linux, the gmake command is spelled as make

CXX = g++
CXXFLAGS = -g -Wall 
OBJECTS = help.o strset2.o setcalc2.o

EXEC = setcalc2

all : ${EXEC}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o $@
	
help.o : help.h

strset2.o : strset2.h

setcalc2.o : help.h strset2.h

clean :
	rm -f ${EXEC} ${OBJECTS}
