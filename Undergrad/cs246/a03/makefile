#  "Make file" for Tony's Pizza Place.  CS246

CXX = g++
CXXFLAGS = -g -Wall 
OBJECTS = pizzadata.o pizzaok.o pizzaobject.o pizzamain.o

EXEC = pizzamain

all : ${EXEC}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o $@
	
pizzamain.o : pizzadata.h pizzaobject.h pizzaok.h

pizzadata.o : pizzadata.h

pizzaok.o : pizzaok.h

pizzaobject.o : pizzaobject.h pizzadata.h

clean :
	rm -f ${EXEC} ${OBJECTS}

