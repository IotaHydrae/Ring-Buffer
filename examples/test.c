#include <stdio.h>
#include "../ringbuffer.h"

int main()
{
    printf("Hello world\n");

    ring_buffer_t rb;
    char buf_arr[128];
    char tmp;

    ring_buffer_init(&rb, buf_arr, sizeof(buf_arr));

    for (int i=0;i < 150;i++)
        ring_buffer_queue(&rb, i);

    for (int cnt = 0; ring_buffer_dequeue(&rb, &tmp) > 0; cnt ++)
    {
        printf("read : %d\n", tmp);
    }
    return 0;
}

