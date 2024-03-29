#include "vector.h"
#include "header.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void vector_init(vector *v)
{

    // initialize size and data

    v->data = NULL;
    v->size = 0;
}

int vector_size(vector *v)
{

    return v->size;
}

char vector_get(vector *v, int idx)
{

    if (idx >= v->size || idx < 0)
    {
        printf("Index %d out of bounds for vector of size %d\n", idx, v->size);
        return -1;
    }

    return v->data[idx];
}

void vector_set(vector *v, unsigned char c, int idx)
{

    if (idx >= v->size || idx < 0)
    {
        printf("Index %d out of bounds for vector of size %d\n", idx, v->size);
        return;
    }

    v->data[idx] = c;
}

void vector_set_size(vector *v, int size)
{

    // Adjusting the size of the vector
    unsigned char *tmp = (unsigned char *)realloc(v->data, size);

    if (tmp)
    {
        v->data = tmp;
        v->size = size;
    }
    else
    {
        printf("Error reallocating memory!\n");
        exit(1);
    }
}

void vector_cpy(vector *v, int size, unsigned char *data)
{

    vector_init(v);
    vector_set_size(v, size);
    memcpy(v->data, data, size);
}

void vector_push(vector *v, unsigned char c, int idx)
{

    vector_set_size(v, v->size + 1);

    if (idx > v->size || idx < 0)
    {
        printf("Index %d out of bounds for vector of size %d\n", idx, v->size);
        return;
    }

    // Shift all elements after idx to the right
    for (int i = v->size - 1; i > idx; i--)
    {
        v->data[i] = v->data[i - 1];
    }
    v->data[idx] = c;
}

void vector_stuff(vector *v)
{

    int i = 4; // packet size

    // Going through the packet
    while (i < v->size)
    {

        unsigned char c = v->data[i];

        // To stuff the flah we need to add 0x7d and 0x5e
        if (c == FLAG)
        {
            v->data[i] = 0x7d;
            vector_push(v, 0x5e, i + 1);
            i++;
        }
        // To stuff the escape we need to add 0x7d and 0x5d
        else if (c == ESCAPE)
        {
            v->data[i] = 0x7d;
            vector_push(v, 0x5d, i + 1);
            i++;
        }

        i++;
    }
}

void vector_remove(vector *v, int idx)
{

    if (idx >= v->size || idx < 0)
    {
        printf("Index %d out of bounds for vector of size %d\n", idx, v->size);
        return;
    }

    // Shift all elements after idx to the left
    for (int i = idx; i < v->size - 1; i++)
    {
        v->data[i] = v->data[i + 1];
    }

    vector_set_size(v, v->size - 1);
}

void vector_delete(vector *v)
{

    free(v->data);
}