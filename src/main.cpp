/**
 * @file:  main.cpp
 * @brief: Example code
 *
 * @author: Rajinder Yadav
 * @date:   Sep 15, 2016 at 05:03 AM
 *
 * @description
 * Sample code showing the usage of Micro Test
 *
 * License: MIT License (MIT)
 * Copyright (c) 2016 Rajinder Yadav <rajinder.yadav@hotmail.com>
 *
 * Notice: This Software is provided as-is without warrant.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

#include "micro-test.hpp"

int main( int argc, char * argv[] )
{
   /**
    * This will kick off the tests.
    * We place each test inside blocks to localize variable declarations.
    */
   MicroTest::TestRunner test;
   test = "This will Pass";
   {
      test( true );
   }
   test = "This will Fail";
   {
      test( false );
   }
   test = "Checking an exception is thrown (passing test)";
   {
      test.ex( []
      {
         throw ( 1 );
      } );
   }
   test = "Expecting and exception, but failed to get one (failing test)";
   {
      test.ex( []
      {
         // NOP
      } );
   }
   test = "Exception not expected (passing test)";
   {
      test.ex( []
      {
         // NOP
      }, false );
   }

   return 0;
}

