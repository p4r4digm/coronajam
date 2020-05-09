
#include <stdio.h>
#include <stdlib.h>
#include "myvector.h"

struct Vector {

   double growth_rate = 1.1;
   int length = 0;
   int* array = nullptr; //Pointer to memory allocated for array
   int* last = nullptr; //last item in array
   int* end = nullptr; //end of buffer after last item

};

Vector* vectorCreate (int initial_size = 10) {
   Vector* vector = (Vector*)malloc(sizeof(Vector));
   int* array = nullptr;
   if (vector) {
      int* array = (int*)malloc(sizeof(int)*initial_size);
      if (array) {
         vector->array = array;
         vector->last = nullptr;
         vector->end = vector->last;
         return vector;
      }
   }
   return nullptr;
}

bool vectorIsEmpty(Vector* vector) {
   if (vector) {
      if (vector->length > 0) { return false; }
   }
   return true;
}

int vectorSize(Vector* vector) {
   if (vector) {
      vector->length;
   }
   return 0;
}

static void vectorResize(Vector* vector) {
   if (vector) {
      int* resizedVec = (int*)realloc(vector->array, sizeof(int) * vector->length * vector->growth_rate);
      if (resizedVec) {
         vector->array = resizedVec;
      }
   }
}

static int vectorGet(Vector* vector, int index) {
   int out;
   if (vector) {
      if (index > 0 && index <= vector->length) {
         out = *(vector->array + index - 1);
         return out;
      }
   }
   return INT_MIN;
}

int vectorFront(Vector* vector) {
   int out;
   if (vector) {
      out = *vector->array;
      return out;
   }
   return INT_MIN;
}



void vectorTestFuncs(Vector* vector) {
   fprintf(stdout, "Initialize the vector \n");
   Vector* myvec = vectorCreate();
   fprintf(stdout, "Check if list is empty(1 is true): %d \n", vectorIsEmpty(myvec));
}
