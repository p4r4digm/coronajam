#pragma once

typedef struct LinkedList LinkedList;

LinkedList* linkedListCreate();
void linkedListDestroy(LinkedList* llist);

void linkedListPushFront(LinkedList* llist, int value);
void linkedListPushBack(LinkedList* llist, int value);
void linkedListInsert(LinkedList* llist, int index, int value);

int linkedListFind(LinkedList* llist, int value);
int linkedListGet(LinkedList* llist, int index);
int linkedListFront(LinkedList* llist);
int linkedListBack(LinkedList* llist);

void linkedListRemove(LinkedList* llist, int value);
void linkedListErase(LinkedList* llist, int index);

int linkedListPopFront(LinkedList* llist);
int linkedListPopBack(LinkedList* llist);

bool linkedListIsEmpty(LinkedList* llist);
int linkedListSize(LinkedList* llist);

void linkedListTestFuncs();
void linkedListPrintItems(LinkedList* llist);


