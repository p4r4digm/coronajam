#pragma once

typedef struct Vector Vector;

//returns nullptr on failure
Vector* vectorCreate(int capacity = 10, double growth = 2);
//returns 1 on success, 0 on failure
int vectorDestroy(Vector* vector);

bool vectorIsEmpty(Vector* vector);
int vectorSize(Vector* vector);
int vectorMaxSize(Vector* vector);

int vectorReserve(Vector* vector, int newSize);
int vectorShrink(Vector* vector);
int vectorResize(Vector* vector, int newSize, int val = 0);

int vectorGet(Vector* vector, int index);
int vectorSet(Vector* vector, int index, int value);

int vectorFront(Vector* vector);
int vectorBack(Vector* vector);

int vectorPushBack(Vector* vector, int value);
int vectorPopBack(Vector* vector);

int vectorSwap(Vector* vector, int first, int second);
int vectorInsert(Vector* vector, int index, int value);
int vectorErase(Vector* vector, int index);
int vectorEmplace(Vector* vector, int index, int value);



void vectorTestFuncs();

/*

clear - whole thing
insert - before index
emplace?
erase - by index

sort

*/