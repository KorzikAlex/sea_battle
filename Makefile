CC = g++
CFLAGS = -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wconversion -Weffc++ -Wfloat-equal -fstack-protector-strong -fPIE -pie -O2 -g -fsanitize=address -fsanitize=undefined -fno-strict-aliasing -DDEBUG -fvisibility=hidden
LIBS =
SRCDIR = src
INCDIR = include
OBJDIR = build
DOCDIR = docs

SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

EXECUTABLE = bin/SeaBattle.exe

DOXYGEN_CONFIG = Doxyfile

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(OBJDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	$(RM) -rf $(OBJDIR) $(EXECUTABLE)

clean_objects:
	$(RM) -rf $(OBJDIR)

docs:
	@doxygen $(DOXYGEN_CONFIG)

clean_docs:
	@rm -rf $(DOCDIR)

.PHONY: all clean docs clean_objects clean_docs