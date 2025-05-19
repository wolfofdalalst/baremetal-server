# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I$(INCDIR) -I$(INCDIR)/datastructures
OBJDIR = obj
BINDIR = bin
SRCDIR = src
INCDIR = include
TESTDIR = test

# Source files
SOURCES := $(shell find $(SRCDIR) -name '*.c')
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Test files
TESTSOURCES := $(wildcard $(TESTDIR)/*.c)
TESTOBJECTS := $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/test/%.o,$(TESTSOURCES))
TESTBIN = $(BINDIR)/test_runner

# Main binary
MAINBIN = $(BINDIR)/main
MAIN_OBJ := $(OBJDIR)/main.o
TEST_OBJS := $(filter-out $(MAIN_OBJ), $(OBJECTS))

# Targets
all: $(MAINBIN)

test: $(TESTBIN)
	./$(TESTBIN)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Create bin and obj directories if not present
$(BINDIR) $(OBJDIR):
	mkdir -p $@

# Build main binary
$(MAINBIN): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Build test binary (excluding main.o)
$(TESTBIN): $(TEST_OBJS) $(TESTOBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files to object files
$(OBJDIR)/test/%.o: $(TESTDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
