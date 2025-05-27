PACKAGE = cc
VERSION = 1.0
prefix = /usr/local
bindir = $(prefix)/bin

CC = cc
LD = ld
INSTALL = install
MKDIR = mkdir -p
RM = rm -rf
FIND = find

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

TARGET = $(BIN_DIR)/cc

SRCS = $(shell $(FIND) $(SRC_DIR) -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.d, $(SRCS))

CFLAGS = -std=c89 -pedantic-errors -I$(INC_DIR) -Werror -Wall -Wextra -g -O2
LDFLAGS = -L/usr/lib
LDLIBS = -lc

all: $(TARGET)

help:
	@echo "GNU Makefile for $(PACKAGE) $(VERSION)"
	@echo "Usage: make [target]"
	@echo "Targets:"
	@echo "  all       - Build the $(PACKAGE) executable (default)"
	@echo "  install   - Install $(PACKAGE) to $(bindir)"
	@echo "  uninstall - Remove $(PACKAGE) from $(bindir)"
	@echo "  clean     - Remove build and binary directories"
	@echo "  distclean - Remove all generated files, including dependencies"
	@echo "  help      - Show this help message"

$(BUILD_DIR) $(BIN_DIR):
	$(MKDIR) $@

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -M -MT $@ -o $(BUILD_DIR)/$*.d $<
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	$(MKDIR) $(bindir)
	$(INSTALL) -m 755 $(TARGET) $(bindir)/$(PACKAGE)

uninstall:
	$(RM) $(bindir)/$(PACKAGE)

clean:
	$(RM) $(BUILD_DIR) $(BIN_DIR)

distclean: clean
	$(RM) $(DEPS)

-include $(DEPS)

.PHONY: all help install uninstall clean distclean