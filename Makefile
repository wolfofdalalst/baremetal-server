# compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

# directories
SRCDIR = src
OBJDIR = obj
BIN = baremetal

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# target
all: $(BIN)

# build binary
$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# create object directory if it doesn't exist
$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(BIN)

run: $(BIN)
	./$(BIN)

.PHONY: all clean run