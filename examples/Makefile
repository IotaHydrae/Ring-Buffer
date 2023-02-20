CC             ?= gcc
CFLAGS         = -Wall -g -O2 -std=c99

BUILDDIR := ./build
EXAMPLES := simple test rb_any

all: build $(EXAMPLES)

build:
	mkdir -p $(BUILDDIR)

simple: ../ringbuffer.c simple.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ $^

test: ../ringbuffer.c test.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ $^

rb_any: ../ringbuffer_any.c rb_any.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ $^

.PHONY: clean
clean:
	rm -f $(BUILDDIR)
