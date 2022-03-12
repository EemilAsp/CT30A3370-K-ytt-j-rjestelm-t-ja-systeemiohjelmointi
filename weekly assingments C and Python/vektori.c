

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

struct vector
{
    int * data;
    int size;
    int capacity;
};

void vector_insertAtEnd(struct vector * v, int value) {
    if (v->size == v->capacity) {
        v->capacity = v->capacity * 2;
        v->data = (int *) realloc(v->data, v->capacity * sizeof(int));
    }
    (v->data)[v->size++] = value;
}

void vector_deleteAtEnd(struct vector * v) {
    (v->data)[--(v->size)] = 0;
    if (v->size == (int)(v->capacity / 4)) {
        v->capacity = (int)(v->capacity / 2);
        v->data = (int *) realloc(v->data, v->capacity * sizeof(int));
    }
}

void vector_free(struct vector * v) {
    free(v->data);
    v->size = 0;
    v->capacity = 0;
}

int main(int argc, char *argv[]) {
    struct vector v = {.data = (int *)malloc(sizeof(int)), .size = 1, .capacity = 1};
    v.data[0] = 4;
    struct vector *vp = &v;
    vector_insertAtEnd(vp, 5);
    vector_insertAtEnd(vp, 6);
    vector_insertAtEnd(vp, 7);
    vector_deleteAtEnd(vp);

    printf("first value: %d\n", v.data[0]);
    printf("second value: %d\n", v.data[1]);
    printf("third value: %d\n", v.data[2]);
    printf("size: %d\n", v.size);
    printf("capacity: %d\n", v.capacity);

    vector_free(vp);

    return 0;
}