
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

struct Node {
   int data;
   Node* previous = nullptr;
   Node* next = nullptr;
};

struct LinkedList {
   Node* head = nullptr;
   Node* tail = nullptr;
   int length = 0;
};


bool linkedListIsEmpty(LinkedList* llist) {
   if (llist->length > 0) { return false; }
   else { return true; }
}

int linkedListSize(LinkedList* llist) {
   return llist->length;
}

int linkedListFront(LinkedList* llist){
   return llist->head->data;
}

int linkedListBack(LinkedList* llist) {
   return llist->tail->data;
}

static Node* _createNode() {
   Node* newNode = (Node*)malloc(sizeof(Node));

   if (newNode == nullptr) {
      fprintf(stdout, "There was an error making the node.");
      return newNode;
   }
   newNode->previous = nullptr;
   newNode->next = nullptr;

   return newNode;
}

static void _freeNode(Node* node) {
   try {free(node); }
   catch (...) { fprintf(stdout, "There was an error removing the node."); }
}

LinkedList* linkedListCreate() {
   LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));
   if (newList == nullptr) {
      fprintf(stdout, "There was an error making the list.");
      return newList;
   }
   newList->head = nullptr;
   newList->tail = nullptr;
   newList->length = 0;
   return newList;
}


void linkedListDestroy(LinkedList* llist) {
   Node* cursor = llist->head;

   while (cursor->next != nullptr) {
      cursor = cursor->next;
      _freeNode(cursor->previous);
   }
   try { free(llist); }
   catch (...) { fprintf(stdout, "There was an error destroying the list."); }
   llist->head = nullptr;
   llist->tail = nullptr;
   llist->length = 0;
}

static Node* _getByPosition(LinkedList* llist, int index) {
   if (index <= 0 || index > llist->length) {
      fprintf(stdout, "Index %d out of range. List length is: %d\n", index, llist->length);
      return nullptr;
   }
   Node* cursor = llist->head;
   int count = 0;

   while (cursor != nullptr) {
      count++;
      if (index == count) {
         return cursor;
      }
      cursor = cursor->next;
   }
   return nullptr; //What to do here?
}

int linkedListGet(LinkedList* llist, int index) {
   Node* out = _getByPosition(llist, index);
   if (out == nullptr) { return INT_MIN; }
   return out->data;
}

static Node* _findValue(Node* head, int value) {
   Node* out = nullptr;

   while (head != nullptr) {
      if (value == head->data) { 
         out = head;
         return out; 
      }
      head = head->next;
   }
   return out;
}

int linkedListFind(LinkedList* llist, int value) {
   Node* match = _findValue(llist->head, value);
   if (!match) {
      fprintf(stdout, "Value %d not found.\n", value);
      return INT_MIN;
   }
   return match->data;
}

void linkedListErase(LinkedList* llist, int index) {
   Node* match = _getByPosition(llist, index);
   if (!match) { 
      fprintf(stdout, "Could not erase value at index %d.\n", index);
      return; 
   }

   if (match->previous == nullptr) {
      llist->head = match->next;
      llist->head->previous = nullptr;
      _freeNode(match);
      llist->length -= 1;
   }

   else if (match->next == nullptr) {
      llist->tail = match->previous;
      llist->tail->next = nullptr;
      _freeNode(match);
      llist->length -= 1;
   }

   else {
      match->previous->next = match->next;
      match->next->previous = match->previous;
      _freeNode(match);
      llist->length -= 1;
   }
}

void linkedListPushFront(LinkedList* llist, int value) {
   Node* newNode = _createNode();
   newNode->data = value;
   newNode->next = llist->head;
   if (llist->head != nullptr) {
      llist->head->previous = newNode;
   }
   if (llist->tail == nullptr) {
      llist->tail = newNode;
   }
   llist->head = newNode;
   llist->length += 1;
}


void linkedListPushBack(LinkedList* llist, int value) {
   Node* newNode = _createNode();
   newNode->data = value;
   newNode->previous = llist->tail;
   if (llist->tail != nullptr) {
      llist->tail->next = newNode;
   }
   if (llist->head == nullptr) {
      llist->head = newNode;
   }
   llist->tail = newNode;
   llist->length += 1;
}

void linkedListRemove(LinkedList* llist, int value) {
   Node* match = _findValue(llist->head, value);
   if (!match) {
      fprintf(stdout, "Attempted to delete %d...Not found in list.\n", value);
      return;
   }

   if (match->previous == nullptr) {
      llist->head = match->next;
      llist->head->previous = nullptr;
      _freeNode(match);
      llist->length -= 1;
   }

   else if (match->next == nullptr) {
      llist->tail = match->previous;
      llist->tail->next = nullptr;
      _freeNode(match);
      llist->length -= 1;
   }

   else {
      match->previous->next = match->next;
      match->next->previous = match->previous;
      _freeNode(match);
      llist->length -= 1;
   }
}

int linkedListPopFront(LinkedList* llist) {
   int out = llist->head->data;
   Node* target = llist->head;

   llist->head = target->next;
   llist->head->previous = nullptr;
   _freeNode(target);
   llist->length -= 1;
   return out;
}

int linkedListPopBack(LinkedList* llist) {
   int out = llist->tail->data;
   Node* target = llist->tail;

   llist->tail = target->previous;
   llist->tail->next = nullptr;
   _freeNode(target);
   llist->length -= 1;
   return out;

}

void linkedListInsert(LinkedList* llist, int index, int value){
   Node* match = _getByPosition(llist, index);
   if (!match) {
      fprintf(stdout, "Index out of range %d.\n", index);
      return;
   }

   if (match->previous == nullptr) {
      linkedListPushFront(llist, value);
      return;
   }

   else {
      Node* newNode = _createNode();
      newNode->data = value;
      
      newNode->next = match;
      newNode->previous = match->previous;
      
      match->previous->next = newNode;
      match->previous = newNode;
      
      llist->length += 1;
   }
}

void linkedListPrintItems(LinkedList* llist) {
   Node* cursor = llist->head;
   fprintf(stdout, "----CURRENT LIST-----\n");
   int count = 0;
   while (cursor != nullptr) {
      count++;
      fprintf(stdout, "%d %d\n", count, cursor->data);
      cursor = cursor->next;
   }
   fprintf(stdout, "---------\n");
}

void linkedListTestFuncs() {
   //initialize list with value 3
   fprintf(stdout, "Initialize the linked list \n");
   LinkedList* llist = linkedListCreate();
   fprintf(stdout, "Check if list is empty(1 is true): %d \n", linkedListIsEmpty(llist));
   linkedListPrintItems(llist);

   //test add to front
   fprintf(stdout, "Adding values 2 and 5 to start\n");
   linkedListPushFront(llist, 2);
   linkedListPushFront(llist, 5);

   linkedListPrintItems(llist);

   //test add to end
   fprintf(stdout, "Adding values 3 and 8 to the end\n");
   linkedListPushBack(llist, 3);
   linkedListPushBack(llist, 8);

   linkedListPrintItems(llist);

   fprintf(stdout, "Getting value at index 2: %d \n", linkedListGet(llist, 2));
   fprintf(stdout, "Getting value at index 4: %d \n", linkedListGet(llist, 4));
   fprintf(stdout, "Getting value at index 6: %d \n", linkedListGet(llist, 6));

   //test deleting a specific value
   fprintf(stdout, "Deleting values 2, 8, and NULL\n");
   linkedListRemove(llist, 2);
   linkedListRemove(llist, 8);
   linkedListRemove(llist, NULL);

   linkedListPrintItems(llist);

   //test finding a value
   fprintf(stdout, "Looking for value 3 and 2...\n");
   fprintf(stdout, "Return value: %d\n", linkedListFind(llist, 3));
   fprintf(stdout, "Return value: %d\n", linkedListFind(llist, 2));

   fprintf(stdout, "Adding values 7 and 6 to start\n");
   linkedListPushFront(llist, 7);
   linkedListPushFront(llist, 6);

   fprintf(stdout, "Adding values 1 and 9 to end\n");
   linkedListPushBack(llist, 1);
   linkedListPushBack(llist, 9);

   linkedListPrintItems(llist);

   fprintf(stdout, "Erasing items at indices 2\n");
   linkedListErase(llist, 2);

   linkedListPrintItems(llist);

   fprintf(stdout, "Erasing items at indices 5\n");
   linkedListErase(llist, 5);

   linkedListPrintItems(llist);

   //test popping
   fprintf(stdout, "Popped from start: %d \n", linkedListPopFront(llist));

   linkedListPrintItems(llist);

   fprintf(stdout, "Popped from end: %d \n", linkedListPopBack(llist));

   linkedListPrintItems(llist);

   linkedListInsert(llist, 2, 10);
   linkedListInsert(llist, 1, 15);

   linkedListPrintItems(llist);

   //test list length
   fprintf(stdout, "List length: %d \n", linkedListSize(llist));

   linkedListDestroy(llist);
}