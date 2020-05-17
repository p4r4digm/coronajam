
#include <stdio.h>
#include <stdlib.h>
#include "myvector.h"
#include <math.h>

struct Vector {

   double growth;
   int length;
   int* data; //Pointer to memory allocated for data array
   int capacity;

};

Vector* vectorCreate (int capacity, double growth) {
   Vector* vector = (Vector*)malloc(sizeof(Vector));
   int* data = nullptr;
   if (capacity <= 0) { capacity = 10; }
   if (growth <= 1) { growth = 2; }
   if (vector) {
      int* data = (int*)malloc(sizeof(int) * capacity);
      if (data) {
         vector->data = data;
         vector->growth = growth; 
         vector->capacity = capacity; 
         vector->length = 0;
         
         return vector;
      }
   }
   return nullptr;
}

int vectorDestroy(Vector* vector) {
   if (vector) {
      if (vector->data) { free(vector->data); }
      free(vector);
      return 1;
   }
   return 0;
}

bool vectorIsEmpty(Vector* vector) {
   if (vector) {
      if (vector->length > 0) { return false; }
   }
   return true;
}

int vectorSize(Vector* vector) {
   if (vector) {
      return vector->length;
   }
   return 0;
}

int vectorMaxSize(Vector* vector) {
   if (vector) {
      return vector->capacity;
   }
   return 0;
}


static int _calcBuffer(Vector* vector){
   int out;
   out = ceil((double)vector->length * vector->growth);
   if (out <= 0) { return 10; }
   return out;
}

static int _vectorReserve(Vector* vector, int newSize) {
   if (vector) {
      int* resizedData = (int*)realloc(vector->data, sizeof(int) * newSize);
      if (resizedData) {
         //fprintf(stdout, "Resizing vector: %d to %d\n", vector->capacity, newSize);
         vector->data = resizedData;
         vector->capacity = newSize;
         return 1;
      }
   }
   return 0;
}

int vectorReserve(Vector* vector, int newSize) {
   if (newSize <= vector->length) { return 0; }
   if (vector) {
      int check = _vectorReserve(vector, newSize);
      if (check != 0) { return 1; }
   }
   return 0;
}

static int _vectorSetOutside(Vector* vector, int index, int value) {
   if (vector) {
      if (index > 0 && index <= vector->capacity) {
         vector->data[index - 1] = value;
         return 1;
      }
   }
   return 0;
}

int vectorResize(Vector* vector, int newSize, int val) {
   if (newSize <= 0) { return 0; }
   if (vector) {
      if (newSize > vector->length && newSize > vector->capacity) {
         int check = _vectorReserve(vector, newSize);
         if (check == 0) { return 0; }
         for (int i = vector->length + 1; i <= newSize; i++) {
            _vectorSetOutside(vector, i, val);
         }
         vector->length = newSize;
         return 1;
      }
      
      if (newSize < vector->length) {
         int check = _vectorReserve(vector, newSize);
         if (check == 0) { return 0; }
         vector->length = newSize;
         return 1;
      }
   }
   return 0;
}

int vectorShrink(Vector* vector) {
   int out = _vectorReserve(vector, vector->length);
   if (out == 0) { return 0; }
   return 1;
}

static int* _vectorGet(Vector* vector, int index) {
   int* out;
   if (vector) {
      if (index > 0 && index <= vector->length) {
         out = (vector->data + index - 1);
         return out;
      }
   }
   return nullptr;
}

int vectorGet(Vector* vector, int index) {
   int* loc = _vectorGet(vector, index);
   if (loc) { return *loc; }
   return INT_MIN;
}


int vectorSet(Vector* vector, int index, int value) {
   if (vector) {
      if (index > 0 && index <= vector->length) {
         vector->data[index - 1] = value;
         return 1;
      }
   }
   return 0;
}

int vectorPushBack(Vector* vector, int value) {
   int check = 0;
   if (vector) {
      if (vector->length == vector->capacity) {
         check = vectorReserve(vector, _calcBuffer(vector));
         if (check == 0) { return 0; }
      }
      if (vector->data) {
         check = _vectorSetOutside(vector, vector->length + 1, value);
         if (check == 0) { return 0; }
         vector->length += 1;
         return 1;
      }
   }
   return 0;
}

int vectorPopBack(Vector* vector) {
   int out;
   if (vector) {
      if (vector->length > 0) {
         int* end = _vectorGet(vector, vector->length);
         if (end) {
            out = *end;
            vector->length -= 1;
            *end = NULL;
            return out;
         }
      }
   }
   return INT_MIN;
}

int vectorFront(Vector* vector) {
   int* loc = _vectorGet(vector, 1);
   if (loc) { return *loc; }
   return INT_MIN;
}

int vectorBack(Vector* vector) {
   int* loc = _vectorGet(vector, vector->length);
   if (loc) { return *loc; }
   return INT_MIN;
}


int vectorSwap(Vector* vector, int first, int second) {
   if (first < 0 && first > vector->length) {
      return 0;
   }
   if (second <= 0 && second > vector->length) {
      return 0;
   }
   int* t1 = _vectorGet(vector, first);
   int* t2 = _vectorGet(vector, second);
   if (t1 && t2) {
      int temp = *t1;
      *t1 = *t2;
      *t2 = temp;
      return 1;
   }
   return 0;
}

int vectorInsert(Vector* vector, int index, int value) {
   if (index < 0 || index > vector->length) {
      return 0;
   }

   if (vector) {
      if (vector->length + 1 >= vector->capacity) {
         int check = _vectorReserve(vector, _calcBuffer(vector));
         if (check == 0) { return 0; }
      }

      int current = vectorGet(vector, index);
      vectorSet(vector, index, value);

      for (int i = index + 1; i <= vector->length + 1; i++) {
         int next = vectorGet(vector, i);
         _vectorSetOutside(vector, i, current);
         current = next;
      }
      vector->length += 1;
      return 1;
   }

   return 0;
}

int vectorErase(Vector* vector, int index) {
   if (index < 0 || index > vector->length) {
      return 0;
   }
   if (index == vector->length) { vector->length -= 1; }

   if (vector) {
      for (int i = index; i < vector->length; i++) {
         int next = vectorGet(vector, i + 1);
         vectorSet(vector, i, next);
      }
      vector->length -= 1;
      return 1;
   }
   return 0;
}

int vectorEmplace(Vector* vector, int index, int value) {
   //How is this different from Insert?
   return 0;
}

int vectorClear(Vector* vector) {
   if (vector) {
      vector->length = 0;
      return 1;
      }
   return 0;
}

void vectortPrintItems(Vector* vector) {
   fprintf(stdout, "----CURRENT LIST-----\n");
   int* cursor = vector->data;
   for (int count = 1; count <= vector->length; count++) {
      fprintf(stdout, "%d %d\n", count, *cursor);
      cursor = cursor + 1;
   }
   fprintf(stdout, "---------\n");
}


void vectorTestFuncs() {
   fprintf(stdout, "Initialize the vector \n");
   Vector* myvec = vectorCreate();
   fprintf(stdout, "Check if vector is empty(1 is true): %d \n", vectorIsEmpty(myvec));

   for (int i = 10; i < 25; i++) { vectorPushBack(myvec, i); }

   vectortPrintItems(myvec);

   for (int i = 1; i < 13; i++) { 
      fprintf(stdout, "Get at %d %p \n", i, _vectorGet(myvec, i) );
   }

   vectorPushBack(myvec, 88);
   vectortPrintItems(myvec);

   fprintf(stdout, "Get at end: %d \n", vectorGet(myvec, myvec->length));

   fprintf(stdout, "Vector max size is: %d \n", vectorMaxSize(myvec));

   fprintf(stdout, "Shrinking vector: %d \n", vectorShrink(myvec));
   fprintf(stdout, "Vector max size is: %d \n", vectorMaxSize(myvec));

   fprintf(stdout, "Vector last is: %d \n", vectorBack(myvec));

   vectorSet(myvec, 2,99);
   vectortPrintItems(myvec);

   fprintf(stdout, "Index out of range: %d \n", vectorSet(myvec, 4, 3));
   vectortPrintItems(myvec);

   fprintf(stdout, "Swapping 7 and 10");
   vectorSwap(myvec, 7, 10);
   vectortPrintItems(myvec);

   fprintf(stdout, "Popping back: %d \n", vectorPopBack(myvec));
   vectortPrintItems(myvec);

   fprintf(stdout, "Vector size: %d \n", vectorSize(myvec));

   vectorInsert(myvec, 3, 88);
   vectortPrintItems(myvec);

   vectorErase(myvec, 3);
   vectortPrintItems(myvec);

   vectorDestroy(myvec);
   fprintf(stdout, "Is empty after destroy: %d \n", vectorIsEmpty(myvec));
}
