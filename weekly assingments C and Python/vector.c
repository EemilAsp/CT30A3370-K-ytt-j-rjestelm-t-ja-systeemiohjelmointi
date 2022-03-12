#include <stdio.h>
#include <stdlib.h>

//Source https://github.com/martalist/ostep/blob/master/chapter_13/hw13/vector.c

typedef struct vect {
    int *data;
    int size;
    int capacity;
} Vector;

void freeMem(Vector *v)
{
    free(v->data);
    free(v);
}

Vector *insert(Vector *v, int numb) 
{
    if (v->capacity >= v->size) {
        v->data = realloc(v->data, (v->size + 1) * sizeof(int));
        v->size++;
    }
    *(v->data + v->capacity++) = numb;
    return v;
}

int main()
{
    int x;
    Vector *vector = (Vector *) malloc(sizeof(Vector));
    if (vector == NULL){
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }
    vector->size = 0;
    vector->capacity = 0;
    vector->data = (int *) calloc(0, sizeof(int));
    if (vector->data == NULL){
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    printf("Start:\n");
    printf("Vector has %d spaces and %d items stored\n", vector->size, vector->capacity);

    printf("Insert number to the vector:");
    scanf("%d", &x);
    vector = insert(vector, x);
    printf("Vector has %d spaces and %d items stored\n", vector->size,vector->capacity);
    printf("The value at index %d is %d\n", 0, vector->data[0]);
    printf("Insert number to the vector:");
    scanf("%d", &x);
    vector = insert(vector, x);
    printf("Vector has %d spaces and %d items stored\n", vector->size,vector->capacity);
    printf("The value at index %d is %d\n", 1, vector->data[1]);
    freeMem(vector);
    return 0;
}



