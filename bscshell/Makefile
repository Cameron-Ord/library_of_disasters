# Compiler
CC := gcc

# Compiler flags
CFLAGS := -std=c11 -Wall

# Source files
SRCDIR := src
SOURCES := $(wildcard $(SRCDIR)/*.c)

# Header files
INCDIR := include
HEADERS := $(wildcard $(INCDIR)/*.h)

# Object files
OBJDIR := obj
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Executable
BINDIR := bin
EXECUTABLE := $(BINDIR)/myprogram

# Main target
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $<

# Create directories if they don't exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Clean rule
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# PHONY targets
.PHONY: all clean
