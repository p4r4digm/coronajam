#include <catch2/catch.hpp>
#include "myvector.cpp"

TEST_CASE("Tests for my Vector", "[myvector]") {

   Vector* myvec = vectorCreate();
   for (int i = 10; i < 25; i++) { vectorPushBack(myvec, i); }

   REQUIRE(myvec->length == 15);
}