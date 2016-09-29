CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD	# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS0 = q1exception.o			# optional build of given program
EXEC0 = exception

OBJECTS1 = q1flags.o
EXEC1 = flags

OBJECTS2 = q1multiexit.o
EXEC2 = multiexit

OBJECTS00 = q2localfixup.o			# optional build of given program
EXEC00 = localfixup

OBJECTS3 = q2globalfixup.o
EXEC3 = globalfixup

OBJECTS4 = q3main.o q3grammar.o# object files forming 4th executable with prefix "q3"
EXEC4 = grammar

OBJECTS = ${OBJECTS1} ${OBJECTS2} ${OBJECTS3} ${OBJECTS4}
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1} ${EXEC2} ${EXEC3} ${EXEC4}	# all executables

#############################################################

all : ${EXECS}					# build all executables

q1%.o : q1%.cc					# change compiler 1st executable
	g++ ${CXXFLAGS} -c $< -o $@

q2%.o : q2%.cc					# change compiler 2nd executable
	g++ ${CXXFLAGS} -c $< -o $@

${EXEC0} : ${OBJECTS0}				# link step for exception executable
	g++ ${CXXFLAGS} $^ -o $@

${EXEC1} : ${OBJECTS1}				# link step for flags executable
	g++ ${CXXFLAGS} $^ -o $@

${EXEC2} : ${OBJECTS2}				# link step for multiexit executable
	g++ ${CXXFLAGS} $^ -o $@

${EXEC00} : ${OBJECTS00}			# link step for localfixup executable
	g++ ${CXXFLAGS} $^ -o $@

${EXEC3} : ${OBJECTS3}				# link step for globalfixup executable
	g++ ${CXXFLAGS} $^ -o $@

${EXEC4} : ${OBJECTS4}				# link step for grammar executable
	${CXX} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC0} ${EXEC00} ${EXECS}
