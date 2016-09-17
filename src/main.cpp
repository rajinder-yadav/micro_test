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

int Add( const int a, const int b )
{
   return a + b;
}

int main( int argc, char * argv[] )
{
   /**
    * This will kick off the tests.
    * We place each test inside blocks to localize variable declarations.
    */
   MicroTest::TestRunner test;
   test = "This will Pass";
   {
      // Set test boolean success status.
      // true  for Pass
      // false for Fail
      test.status = true;

      // Show & collect test result.
      test();
   }
   test = "This will Fail";
   {
      // Alternatively pass boolean success status.
      test( false );
   }
   test = "Add values 2 and 3, return sum of 5";
   {
      int sum1 = Add( 1, 2 );
      int sum2 = Add( 5, -2 );

      test.status = ( sum1 == 3 ) && ( sum2 == 3 );
      test();
   }
   test = "Add values 5 and -3, return sum of 2";
   {
      test( Add( 5, -3 ) == 2 );
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
