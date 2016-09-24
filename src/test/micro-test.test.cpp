/**
 * @file:  micro-test.test.cpp
 * @brief: Tests for MicroTest Framework.
 *
 * @author: Rajinder Yadav
 * @date:   Mon Sep 19 16:18:50 EDT 2016
 *
 * @description
 * Unit Test to validate MicroTest.
 *
 * License: MIT License (MIT)
 * Copyright (c) 2016 Rajinder Yadav <info@devmentor.org>
 *
 * Notice: This Software is provided as-is without warrant.
 */

// =============================================================================
// IMPORTANT - This health check must pass, before any code change is commited.
// IMPORTANT - This health check must pass, before any code change is commited.
// IMPORTANT - This health check must pass, before any code change is commited.
// =============================================================================

// MICRO TEST HEALTH CHECK
//
// This file contains a set of test to be run against Micro Test.
// Each "Test Helper" is verified with a pair of passing and failing test.
// If a test helper fails, the program will terminate with the error message:
//
// Error! Unexpected test result
//
// If this message is encountered, the test helper and Micro Test code must be
// investigated and corrected.
//
// The health check message we should see is:
//
// MICRO TEST VERIFICATION SUCCESSFULL.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

#include "micro-test.hpp"

class Person
{
   std::string name;
public:
   Person() {}
   Person( const std::string & n ): name( n ) {}

   std::string Name()
   {
      return name;
   }
};

class TestException
{
};

int main( int argc, char * argv[] )
{
   MicroTest::TestRunner test;

   Person * p1;
   Person * p2;
   Person * p3;

   //=========================
   // Test Fixture
   //=========================
   test.fixture(
      setup_fixture
   {
      clog << "Setting up fixture\n" << std::flush;
      p1 = new Person( "Same" );
      p2 = new Person( "Other" );
      p3 = new Person( "Same" );
   },
   cleanup_fixture
   {
      clog << "Cleaning up fixture\n" << std::flush;
      delete p1;
      p1 = nullptr;
      delete p2;
      p2 = nullptr;
      delete p3;
      p3 = nullptr;
   } );

   test = "Person p1 and p1 have the same name";
   {
      test.eq( p1->Name(), p1->Name() );
      test.shouldPass();
   }
   test = "Person p1 and p1 have the same name";
   {
      test.ne( p1->Name(), p1->Name() );
      test.shouldFail();
   }
   test = "Person p1 and p2 don't have the same name";
   {
      test.ne( p1->Name(), p2->Name() );
      test.shouldPass();
   }
   test = "Person p1 and p2 don't have the same name";
   {
      test.eq( p1->Name(), p2->Name() );
      test.shouldFail();
   }
   test = "Person p1 and p3 have the same name";
   {
      test.eq( p1->Name(), p3->Name() );
      test.shouldPass();
   }
   test = "Person p1 and p3 have the same name";
   {
      test.ne( p1->Name(), p3->Name() );
      test.shouldFail();
   }
   // No longer need a fixture.~
   test.fixture();

   //=========================
   // Test Equality
   //=========================
   test = "Test boolean";
   {
      test( true );
      test.shouldPass();
   }
   test = "Test boolean";
   {
      test( false );
      test.shouldFail();
   }
   test = "Test helper for 'true'";
   {
      test.t( true );
      test.shouldPass();
   }
   test = "Test helper for 'true'";
   {
      test.t( false );
      test.shouldFail();
   }
   test = "Test helper for 'false'";
   {
      test.f( false );
      test.shouldPass();
   }
   test = "Test helper for 'false'";
   {
      test.f( true );
      test.shouldFail();
   }
   test = "Test helper for ==";
   {
      test.eq( 12, 12 );
      test.shouldPass();
   }
   test = "Test helper for ==";
   {
      test.eq( 123, 12 );
      test.shouldFail();
   }
   test = "Test helper for !=";
   {
      test.ne( 123, 321 );
      test.shouldPass();
   }
   test = "Test helper for !=";
   {
      test.ne( 123, 123 );
      test.shouldFail();
   }
   test = "Test helper for <";
   {
      test.lt( 12, 19 );
      test.shouldPass();
   }
   test = "Test helper for <";
   {
      test.lt( 122, 19 );
      test.shouldFail();
   }
   test = "Test helper for >";
   {
      test.gt( 100, 10 );
      test.shouldPass();
   }
   test = "Test helper for >";
   {
      test.gt( 1, 10 );
      test.shouldFail();
   }
   test = "Test helper for <=";
   {
      test.le( 12, 12 );
      test.shouldPass();
   }
   test = "Test helper for <=";
   {
      test.le( 22, 12 );
      test.shouldFail();
   }
   test = "Test helper for >=";
   {
      test.ge( 12, 12 );
      test.shouldPass();
   }
   test = "Test helper for >=";
   {
      test.ge( 2, 12 );
      test.shouldFail();
   }

   //=========================
   // Test Exceptions
   //=========================
   test = "Exception type double thrown";
   {
      test.ex<double>( []
      {
         throw ( 12.34 );
      } );
      test.shouldPass();
   }
   test = "Exception type double thrown";
   {
      test.ex<double>( []
      {
         throw ( 12 );
      } );
      test.shouldFail();
   }
   test = "Exception TestException thrown";
   {
      test.ex<TestException>( []
      {
         throw TestException();
      } );
      test.shouldPass();
   }
   test = "Exception TestException thrown";
   {
      test.ex<TestException>( []
      {
         throw ( "Error" );
      } );
      test.shouldFail();
   }
   test = "Exception type int not thrown";
   {
      test.ex_not<int>( []
      {
         // Not the exception we're looking for!
         throw TestException();
      } );
      test.shouldPass();
   }
   test = "Exception type int not thrown";
   {
      test.ex_not<int>( []
      {
         // Not the exception we're looking for!
         throw ( 1 );
      } );
      test.shouldFail();
   }
   test = "Any exception is thrown";
   {
      test.ex_any( []
      {
         throw std::exception();
      } );
      test.shouldPass();
   }
   test = "Any exception is thrown";
   {
      test.ex_any( []
      {
      } );
      test.shouldFail();
   }
   test = "No exception is thrown";
   {
      test.ex_none( []
      {
         // NOP
      } );
      test.shouldPass();
   }
   test = "No exception is thrown";
   {
      test.ex_none( []
      {
         throw ( "Ex" );
      } );
      test.shouldFail();
   }

   //=========================
   // Test Compounds
   //=========================
   test = "Compund statements first fails (should fail)";
   {
      test.all( false, true, true );
      test.shouldFail();
   }
   test = "Compund statements last fails (should fail)";
   {
      test.all( true, true, false );
      test.shouldFail();
   }
   test = "Compund statements all fails (should fail)";
   {
      test.all( false, false, false );
      test.shouldFail();
   }
   test = "Compund statements all pass";
   {
      test.all( true, true, true );
      test.shouldPass();
   }

   //=========================
   // Test Strings
   //=========================
   test = "Two C array string comparison";
   {
      const char a1[] = "Sun!";
      const char a2[] = "Sun!";
      test.eq( a1, a2 );
      test.shouldPass();
   }
   test = "Two C array string comparison";
   {
      const char a1[] = "Sun!";
      const char a2[] = "Car";
      test.eq( a1, a2 );
      test.shouldFail();
   }
   test = "Two C pointer string comparison";
   {
      const char * a1 = "Sun!";
      const char * a2 = "Sun!";
      test.eq( a1, a2 );
      test.shouldPass();
   }
   test = "Two C pointer string comparison";
   {
      const char * a1 = "Sun!";
      const char * a2 = "Car";
      test.eq( a1, a2 );
      test.shouldFail();
   }
   test = "Two C string comparison";
   {
      test.eq( "Boat", "Boat" );
      test.shouldPass();
   }
   test = "Two C string comparison";
   {
      test.eq( "Boat", "Goat" );
      test.shouldFail();
   }
   test = "C string with std::string comparison";
   {
      test.eq( "Boat", std::string( "Boat" ) );
      test.shouldPass();
   }
   test = "C string with std::string comparison";
   {
      test.eq( "Goat", std::string( "Boat" ) );
      test.shouldFail();
   }
   test = "std::string with C string comparison";
   {
      test.eq( std::string( "Boat" ), "Boat" );
      test.shouldPass();
   }
   test = "std::string with C string comparison";
   {
      test.eq( std::string( "Goat" ), "Boat" );
      test.shouldFail();
   }
   test = "C pointer string and string comparison";
   {
      const char * a1 = "Sun!";
      test.eq( a1, "Sun!" );
      test.shouldPass();
   }
   test = "C pointer string and string comparison";
   {
      const char * a1 = "Sun!";
      test.eq( a1, "Fun!" );
      test.shouldFail();
   }
   test = "String and C pointer string comparison";
   {
      const char * a2 = "Sun!";
      test.eq( "Sun!", a2 );
      test.shouldPass();
   }
   test = "String and C pointer string comparison";
   {
      const char * a2 = "Sun!";
      test.eq( "Fun!", a2 );
      test.shouldFail();
   }
   test = "Two std::string comparison";
   {
      std::string s1( "Elephant" );
      std::string s2( "Elephant" );
      test.eq( s1, s2 );
      test.shouldPass();
   }
   test = "Two std::string comparison";
   {
      std::string s1( "Elephant" );
      std::string s2( "Hose" );
      test.eq( s1, s2 );
      test.shouldFail();
   }

   test = "Two C array string comparison";
   {
      const char a1[] = "Sun!";
      const char a2[10] = "Moon!";
      test.ne( a1, a2 );
      test.shouldPass();
   }
   test = "Two C array string comparison";
   {
      const char a1[] = "Sun!";
      const char a2[10] = "Sun!";
      test.ne( a1, a2 );
      test.shouldFail();
   }
   test = "Two C pointer string comparison";
   {
      const char * a1 = "Sun!";
      const char * a2 = "Moon!";
      test.ne( a1, a2 );
      test.shouldPass();
   }
   test = "Two C pointer string comparison";
   {
      const char * a1 = "Sun!";
      const char * a2 = "Sun!";
      test.ne( a1, a2 );
      test.shouldFail();
   }
   test = "Two different C string comparison";
   {
      test.ne( "Boat", "Goat" );
      test.shouldPass();
   }
   test = "Two different C string comparison";
   {
      test.ne( "Goat", "Goat" );
      test.shouldFail();
   }
   test = "C string with different std::string comparison";
   {
      test.ne( "Boat", std::string( "Goat" ) );
      test.shouldPass();
   }
   test = "C string with different std::string comparison";
   {
      test.ne( "Goat", std::string( "Goat" ) );
      test.shouldFail();
   }
   test = "std::string with different C string comparison";
   {
      test.ne( std::string( "Boat" ), "Goat" );
      test.shouldPass();
   }
   test = "std::string with different C string comparison";
   {
      test.ne( std::string( "Goat" ), "Goat" );
      test.shouldFail();
   }
   test = "C pointer string and different string comparison";
   {
      const char * a1 = "Sun!";
      test.ne( a1, "Moon!" );
      test.shouldPass();
   }
   test = "C pointer string and different string comparison";
   {
      const char * a1 = "Sun!";
      test.ne( a1, "Sun!" );
      test.shouldFail();
   }
   test = "String and different C pointer string comparison";
   {
      const char * a2 = "Moon!";
      test.ne( "Sun!", a2 );
      test.shouldPass();
   }
   test = "String and different C pointer string comparison";
   {
      const char * a2 = "Moon!";
      test.ne( "Moon!", a2 );
      test.shouldFail();
   }
   test = "Two different std::string comparison";
   {
      std::string s1( "Elephant" );
      std::string s2( "Horse" );
      test.ne( s1, s2 );
      test.shouldPass();
   }
   test = "Two different std::string comparison";
   {
      std::string s1( "Elephant" );
      std::string s2( "Elephant" );
      test.ne( s1, s2 );
      test.shouldFail();
   }

   // This MUST is the last line in the code.
   clog << "\nMICRO TEST VERIFICATION SUCCESSFULL\n\n";
}
