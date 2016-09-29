CXX = u++								# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD -DTYPE="${TYPE}"		# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}				# makefile name

OBJECTS1 = q1main.o q1printer.o q1player.o
EXEC1 = cardgame							# 1st executable name

OBJECTS3 = q3main.o q3searcher.o
EXEC3 = searcher							# 3rd executable name

OBJECTS = ${OBJECTS1} ${OBJECTS3}					# all object files
DEPENDS = ${OBJECTS:.o=.d}						# substitute ".o" with ".d"
EXECS = ${EXEC1} ${EXEC3}						# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}								# build all executables

${EXEC1} : ${OBJECTS1}							# link step 1st executable
	${CXX} $^ -o $@

${EXEC3} : ${OBJECTS3}							# link step 2nd executable
	${CXX} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}						# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}							# include *.d files containing program dependences

clean :									# remove files that can be regenerated
	rm -f *.d *.o ${EXECS}

