/**
 * @file node.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-02-20
 *
 * MIT License
 *
 * Copyright 2022 IotaHydrae(writeforever@foxmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *
 */
#include <stdio.h>
#include "../ringbuffer_any.h"

struct foo_event {
    int x;
    int y;
} test_event = {
    .x = 20,
    .y = 20,
}, test_event_1 = {
    .x = 40,
    .y = 40,
};

struct foo_event buf_foo_event[128];

int main(int argc, char **argv)
{
    struct foo_event tmp;

    RINGBUFFER_INIT(rb, buf_foo_event);
    printf("%ld, mask = %ld\n", sizeof(struct foo_event), rb.buffer_mask);

    ring_buffer_push(&rb, test_event);
    ring_buffer_pop(&rb, tmp);
    printf("x : %d, y : %d\n", tmp.x, tmp.y);

    if (ring_buffer_is_empty(&rb)) {
        printf("list is empty!\n");
    }

    for (int i = 0; i < 100; i++) {
        if (i % 2) {
            ring_buffer_push(&rb, test_event_1);
            continue;
        }
        ring_buffer_push(&rb, test_event);
    }

    for (int i = 0; i < 100; i++) {
        ring_buffer_pop(&rb, tmp);
        printf("x : %d, y : %d\n", tmp.x, tmp.y);
    }

    return 0;
}