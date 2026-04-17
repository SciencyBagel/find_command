BIN      = findf
CC       := g++
SRCDIR   = src
INCDIR   = include
BUILDDIR = build

CXXFLAGS_BASE    = -std=c++14 -I$(INCDIR) -Wall -Wextra
CXXFLAGS_RELEASE = $(CXXFLAGS_BASE) -O2
CXXFLAGS_DEBUG   = $(CXXFLAGS_BASE) -g -O0

BUILD ?= release
ifeq ($(BUILD),debug)
    CXXFLAGS = $(CXXFLAGS_DEBUG)
else
    CXXFLAGS = $(CXXFLAGS_RELEASE)
endif

OBJS    = $(BUILDDIR)/findf.o $(BUILDDIR)/utilities.o
PREFIX ?= /usr/local

.PHONY: all clean test install uninstall help

all: $(BIN)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@

$(BUILDDIR)/findf.o: $(SRCDIR)/findf.cpp $(INCDIR)/utilities.h | $(BUILDDIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/utilities.o: $(SRCDIR)/utilities.cpp $(INCDIR)/utilities.h | $(BUILDDIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

test: $(BIN)
	@chmod +x tests/run_tests.sh && tests/run_tests.sh

install: $(BIN)
	install -m 755 $(BIN) $(PREFIX)/bin/$(BIN)

uninstall:
	rm -f $(PREFIX)/bin/$(BIN)

clean:
	rm -f $(BIN) $(BUILDDIR)/*.o
	@rmdir --ignore-fail-on-non-empty $(BUILDDIR) 2>/dev/null || true

help:
	@echo "Targets: all (default), test, install, uninstall, clean, help"
	@echo "Options: BUILD=debug  PREFIX=/usr/local"
