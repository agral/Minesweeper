CXX=g++
RM=rm -f
CXXFLAGS= -g -c -Wall -Wextra -D_REENTRANT -I/usr/include/SDL2 --std=c++1z
LDFLAGS=
LDLIBS= -lSDL2 -lSDL2_image -lSDL2_ttf

.PHONY: all clean dirs re run

SRCDIR=src

BINDIR=bin
OBJDIR=$(BINDIR)/obj

PROGRAM_NAME=Minesweeper


all: $(PROGRAM_NAME)

dirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(SRCDIR)
	@echo "Directory structure has been created."


SOURCES=$(shell find $(SRCDIR) -name "*.cc")
OBJECTS=$(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SOURCES))

$(PROGRAM_NAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(PROGRAM_NAME) $(OBJECTS) $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS)
	$(RM) $(PROGRAM_NAME)


re: clean all

run: ${PROGRAM_NAME}
	@./${PROGRAM_NAME}


print-%:
	@echo $* = $($*)
