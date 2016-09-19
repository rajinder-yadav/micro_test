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
   MicroTest::TestRunner test;

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
         [] // Setup
      {
         std::clog << "Setting up fixture.\n" << std::flush;
      },
      [] // Cleanup
      {
         std::clog << "Cleaning up fixture.\n" << std::flush;
      } );
   }

   test = "This will Pass";
   {
      // Show & collect test result.
      test( true );
   }
   test = "This will Fail";
   {
      // Alternatively pass boolean success status.
      test( false );
   }
   test = "Add positive and negative values";
   {
      int sum1 = Add( 1, 2 );
      int sum2 = Add( 5, -2 );

      bool status = (sum1 == 3 ) && ( sum2 == 3 );
      test( status );
   }
   test = "Add values 5 and -3, return sum of 2";
   {
      //test( Add( 5, -3 ) == 2 );
      test.eq( Add( 5, -3 ), 2 );
   }
   test = "Checking an exception is thrown (passing test)";
   {
      // By default we expect an exception to get thrown.
      test.ex<int>( []
      {
         throw ( 1 );
      } );
   }
   test = "Expecting and exception, but failed to get one (failing test)";
   {
      // We're expecting an exception, none is thrown, so test fails.
      test.ex<int>( []
      {
         // Call methods that might throw an exception here.
      } );
   }
   test = "Exception not expected (passing test)";
   {
      // An exception could get thrown, we're testing it will not!
      test.no_ex<int>( []
      {
         // Call methods that might throw an exception here.
      } );
   }
   test = "Check custom exception is thrown";
   {
      // Expecting an exception of type TestException to be thrown.
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
      test.any_ex( []
      {
         throw ( "BOOM!" );
      } );
   }
   test = "Any type of exception not throw";
   {
      test.any_no_ex( []
      {
         //throw("BOOM!");
      } );
   }
   return 0;
}
