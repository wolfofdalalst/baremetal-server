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

# Test files and test binaries
TESTSOURCES := $(wildcard $(TESTDIR)/*.c)
TESTOBJECTS := $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/test/%.o,$(TESTSOURCES))
TESTBINS := $(patsubst $(TESTDIR)/%.c, $(BINDIR)/test_%, $(TESTSOURCES))

# Main binary
BAREMETAL = $(BINDIR)/baremetal
MAIN_OBJ := $(OBJDIR)/main.o
TEST_OBJS := $(filter-out $(MAIN_OBJ), $(OBJECTS))

# Targets
all: baremetal

baremetal: $(BAREMETAL)

test: $(TESTBINS)
	@for bin in $^; do \
		echo "Running $$bin..."; \
		./$$bin || exit 1; \
	done

clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Create bin and obj directories if not present
$(BINDIR) $(OBJDIR):
	mkdir -p $@

# Build main binary
$(BAREMETAL): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Build individual test binaries (excluding main.o)
$(BINDIR)/test_%: $(OBJDIR)/test/%.o $(TEST_OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files to object files
$(OBJDIR)/test/%.o: $(TESTDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Run a specific test: make test_hello
test_%: $(BINDIR)/test_%
	@echo "Running $<..."
	./$<
