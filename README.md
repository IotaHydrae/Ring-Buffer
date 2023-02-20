Ring-Buffer
===========

A simple ring buffer (circular buffer) designed for embedded systems.

An example is given in [examples/simple.c](examples/simple.c).

The size of the memory buffer must be a power-of-two.

A new ring buffer is created using the ` ring_buffer_init(&ring_buffer, buff, sizeof(buff))` function:
```c
char buff[64];
ring_buffer_t ring_buffer;
ring_buffer_init(&ring_buffer, buff, sizeof(buff));
```

The module provides the following functions for accessing the ring buffer (documentation can be found in [ringbuffer.h](ringbuffer.h)):
```c
void ring_buffer_queue(ring_buffer_t *buffer, char data);
void ring_buffer_queue_arr(ring_buffer_t *buffer, const char *data, ring_buffer_size_t size);
uint8_t ring_buffer_dequeue(ring_buffer_t *buffer, char *data);
ring_buffer_size_t ring_buffer_dequeue_arr(ring_buffer_t *buffer, char *data, ring_buffer_size_t len);
uint8_t ring_buffer_peek(ring_buffer_t *buffer, char *data, ring_buffer_size_t index);
uint8_t ring_buffer_is_empty(ring_buffer_t *buffer);
uint8_t ring_buffer_is_full(ring_buffer_t *buffer);
ring_buffer_size_t ring_buffer_num_items(ring_buffer_t *buffer);
```

For ringbuffer_any
---------------------

a new ring buffer is created using the marco `RINGBUFFER_INIT(name, buf)` include `ringbuffer_any.h`
```c
struct foo_event {
    int x;
    int y;
};

struct foo_event buf_foo_event[128];

/* init statically */
RINGBUFFER_INIT(rb, buf_foo_event);
```

wrapped marco for accessing the ringbuffer
```c
#define ring_buffer_push(rb, src) \
    ring_buffer_queue(rb, &src, sizeof(__typeof(src)));

#define ring_buffer_pop(rb, dst) \
    ring_buffer_dequeue(rb, &dst, sizeof(__typeof(dst)));

/* an example was given here */
struct foo_event test_event = {
    .x = 20,
    .y = 20,
};

/* pointer is required */
ring_buffer_push(&rb, test_event);
ring_buffer_pop(&rb, test_event);
```

building a makefile like this:
```shell
CC             ?= gcc
CFLAGS         = -Wall -g -O2 -std=c99

BUILDDIR := ./build

all: build rb_any

build:
    mkdir -p $(BUILDDIR)

rb_any: ../ringbuffer_any.c rb_any.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ $^

.PHONY: clean
clean:
    rm -rf $(BUILDDIR)
```

Actually, just copy `ringbuffer_any.c` and `ringbuffer_any.h` into your project is okay.