#include "catch.hpp"
#include <coronajam/myvector.h>

TEST_CASE("Tests for my Vector", "[myvector]") {

   Vector* myvec = vectorCreate();
   REQUIRE(myvec != nullptr);

   Vector* anotherVec = vectorCreate(88, 4);
   REQUIRE(vectorMaxSize(anotherVec) == 88);

   REQUIRE(vectorDestroy(anotherVec) == 1);

   
   for (int i = 10; i < 25; i++) { vectorPushBack(myvec, i); }

   REQUIRE(vectorFront(myvec) == 10);
   REQUIRE(vectorBack(myvec) == 24);
   REQUIRE(vectorPopBack(myvec) == 24);

   vectorSet(myvec, 14, 99);
   REQUIRE(vectorGet(myvec, 14) == 99);
   vectorResize(myvec, 100);
   REQUIRE(vectorMaxSize(myvec) == 100);

   vectorDestroy(myvec);
}