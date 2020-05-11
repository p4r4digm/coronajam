#pragma once

typedef struct Vector Vector;

//returns nullptr on failure
Vector* vectorCreate(int initial_size);
//returns 1 on success, 0 on failure
int vectorDestroy(Vector* vector);

bool vectorIsEmpty(Vector* vector);
int vectorSize(Vector* vector);

//returns 1 on success, 0 on failure
int vectorResize(Vector* vector, int newSize);
int vectorGet(Vector* vector, int index);
int vectorSet(Vector* vector, int index, int value);

int vectorFront(Vector* vector);
int vectorBack(Vector* vector);

int vectorPushBack(Vector* vector, int value);

void vectorTestFuncs();

/*
at - return value at index
front
back

empty - bool
size - # of elements

max_size?
capacity
reserve
shrink to fit

clear - whole thing
insert - before index
emplace?
erase - by index
push back
pop back

resize
swap

*/