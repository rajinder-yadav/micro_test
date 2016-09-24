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
 * Copyright (c) 2016 Rajinder Yadav <info@devmentor.org>
 *
 * Notice: This Software is provided as-is without warrant.
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

#include "micro-test.hpp"

class TestException
{
};

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
   MicroTest::TestRunner test( argc, argv );

   /* Example for setting a Fixture.
    * Setup is called before each test.
    * Cleanup is called after each test.
    *
    * To reset(clear) fixtures, simply make the call: test.fixture();
    * Fixture will not be use after this call.
    */

   // Set this to true to see how fixtures would behave.
   bool enable_fixture = false;

   if ( enable_fixture )
   {
      test.fixture(
         setup_fixture
      {
         std::clog << "Setting up fixture.\n" << std::flush;
      },
      cleanup_fixture
      {
         std::clog << "Cleaning up fixture.\n" << std::flush;
      } );
   }

   test = "Adding negated values should return zero";
   {
      // Pass boolean value to test.
      // Test true condition.
      test( Add( 5, -5 ) == 0 );
   }
   test = "Add values 5 and -3, return sum of 2";
   {
      // Alternatively use test helper.
      test.eq( Add( 5, -3 ), 2 );
   }
   test = "Add positive and negative values";
   {
      int sum1 = Add( 1, 2 );
      int sum2 = Add( 5, -2 );

      bool status = ( sum1 == 3 ) && ( sum2 == 3 );
      test( status );
   }
   test = "Add 3 values 1+2, -5+3, 12+(-12)";
   {
      // Better way to perform compound tests.
      test.all(
         Add( 1, 2 ) == 3,
         Add( 5, -3 ) == 2,
         Add( 12, -12 ) == 0
      );
   }
   test = "Check exception of type 'int' is thrown";
   {
      test.ex<int>( []
      {
         throw ( 1 );
      } );
   }
   test = "Check exception of type 'int' is thrown";
   {
      // We're expecting an exception, none is thrown, so test fails.
      test.ex<int>( []
      {
         // Code that might throw an exception of type int.
      } );
   }
   test = "Exception type int not thrown";
   {
      // An exception type int could get thrown, we're testing it will not!
      test.ex_not<int>( []
      {
         // Code that might throw an exception of type int.
      } );
   }
   test = "Check exception TestException is thrown";
   {
      test.ex<TestException>( []
      {
         throw TestException();
      } );
   }
   test = "Check if correct exception is thrown";
   {
      // Expecting an exception of type TestException to be thrown.
      test.ex<TestException>( []
      {
         throw ( 12 );
      } );
   }
   test = "Any type of exception throw";
   {
      test.ex_any( []
      {
         throw ( "BOOM!" );
      } );
   }
   test = "Any type of exception not throw";
   {
      test.ex_none( []
      {
         //throw("BOOM!");
      } );
   }
   return 0;
}
