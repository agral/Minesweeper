CXX=g++
RM=rm -f
CXXFLAGS= -g -c -Wall -Wextra -D_REENTRANT -I/usr/include/SDL2 --std=c++1z
LDFLAGS=
LDLIBS= -lSDL2 -lSDL2_image -lSDL2_ttf

.PHONY: all \
        clean clean_doc clean_program clean_test \
        doc \
        re \
        run \
        test ut

SRCDIR=src
BINDIR=bin
OBJDIR=${BINDIR}/obj
TESTDIR=tests
TESTOBJDIR=${OBJDIR}/tests
DOCDIR=doc

PROGRAM_NAME=Minesweeper
TEST_NAME=TestMinesweeper

COMMON_SOURCES=$(shell find ${SRCDIR} -name "*.cc" ! -name "main.cc")
COMMON_OBJECTS=$(patsubst ${SRCDIR}/%.cc, ${OBJDIR}/%.o, ${COMMON_SOURCES})
PROGRAM_OBJECTS=${OBJDIR}/main.o ${COMMON_OBJECTS}
TEST_SOURCES=$(shell find ${TESTDIR} -name "*.cc")
TEST_OBJECTS=$(patsubst ${TESTDIR}/%.cc, ${TESTOBJDIR}/%.o, ${TEST_SOURCES})

${PROGRAM_NAME}: ${PROGRAM_OBJECTS}
	${CXX} ${LDFLAGS} -o ${PROGRAM_NAME} ${PROGRAM_OBJECTS} ${LDLIBS}

all: ${PROGRAM_NAME} ${TEST_NAME} doc

doc:
	@mkdir -p ${DOCDIR}
	doxygen .doxyconfig


${OBJDIR}/%.o: ${SRCDIR}/%.cc
	@mkdir -p $(dir $@)
	${CXX} ${CXXFLAGS} $< -o $@

${TESTOBJDIR}/%.o: ${TESTDIR}/%.cc
	@mkdir -p $(dir $@)
	${CXX} ${CXXFLAGS} $< -o $@

clean: clean_doc
	${RM} -r ${BINDIR}
	${RM} ${PROGRAM_NAME}
	${RM} ${TEST_NAME}

clean_doc:
	${RM} -r ${DOCDIR}

clean_program:
	${RM} ${PROGRAM_OBJECTS}
	${RM} ${PROGRAM_NAME}

clean_test:
	${RM} ${TEST_OBJECTS}
	${RM} ${TEST_NAME}

re: clean all

run: ${PROGRAM_NAME}
	@./${PROGRAM_NAME}

test: ${TEST_NAME}
	@echo "Making tests..."

ut: ${TEST_NAME}
	@./${TEST_NAME}

${TEST_NAME}: ${COMMON_OBJECTS} ${TEST_OBJECTS}
	${CXX} ${LDFLAGS} -o ${TEST_NAME} ${COMMON_OBJECTS} ${TEST_OBJECTS} ${LDLIBS}

print-%:
	@echo $* = ${$*}
