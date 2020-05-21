#define CATCH_CONFIG_RUNNER
#include "catch2\catch.hpp"
#include "myvector.h"
#include "linked_list.h"


int main(int argc, char* argv[]) {
   // global setup...

   int result = Catch::Session().run(argc, argv);

   // global clean-up...

   return result;
}