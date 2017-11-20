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
 * License: GNU Public License (GNU GPL)
 * Copyright (c) 2016 Rajinder Yadav <devguy.ca@gmail.com>
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
#include <cstdlib>
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
   MicroTest::TestRunner test( argc, argv );

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
      test.should_pass();
   }
   test = "Person p1 and p1 have the same name";
   {
      test.ne( p1->Name(), p1->Name() );
      test.should_fail();
   }
   test = "Person p1 and p2 don't have the same name";
   {
      test.ne( p1->Name(), p2->Name() );
      test.should_pass();
   }
   test = "Person p1 and p2 don't have the same name";
   {
      test.eq( p1->Name(), p2->Name() );
      test.should_fail();
   }
   test = "Person p1 and p3 have the same name";
   {
      test.eq( p1->Name(), p3->Name() );
      test.should_pass();
   }
   test = "Person p1 and p3 have the same name";
   {
      test.ne( p1->Name(), p3->Name() );
      test.should_fail();
   }
   // No longer need fixture.
   test.fixture();

   //=========================
   // Test Equality
   //=========================
   test = "Test boolean";
   {
      test( true );
      test.should_pass();
   }
   test = "Test boolean";
   {
      test( false );
      test.should_fail();
   }
   test = "Test helper for 'true'";
   {
      test.t( true );
      test.should_pass();
   }
   test = "Test helper for 'true'";
   {
      test.t( false );
      test.should_fail();
   }
   test = "Test helper for 'false'";
   {
      test.f( false );
      test.should_pass();
   }
   test = "Test helper for 'false'";
   {
      test.f( true );
      test.should_fail();
   }
   test = "Test helper for ==";
   {
      test.eq( 12, 12 );
      test.should_pass();
   }
   test = "Test helper for ==";
   {
      test.eq( 123, 12 );
      test.should_fail();
   }
   test = "Test helper for !=";
   {
      test.ne( 123, 321 );
      test.should_pass();
   }
   test = "Test helper for !=";
   {
      test.ne( 123, 123 );
      test.should_fail();
   }
   test = "Test helper for <";
   {
      test.lt( 12, 19 );
      test.should_pass();
   }
   test = "Test helper for <";
   {
      test.lt( 122, 19 );
      test.should_fail();
   }
   test = "Test helper for >";
   {
      test.gt( 100, 10 );
      test.should_pass();
   }
   test = "Test helper for >";
   {
      test.gt( 1, 10 );
      test.should_fail();
   }
   test = "Test helper for <=";
   {
      test.le( 12, 12 );
      test.should_pass();
   }
   test = "Test helper for <=";
   {
      test.le( 22, 12 );
      test.should_fail();
   }
   test = "Test helper for >=";
   {
      test.ge( 12, 12 );
      test.should_pass();
   }
   test = "Test helper for >=";
   {
      test.ge( 2, 12 );
      test.should_fail();
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
      test.should_pass();
   }
   test = "Exception type double thrown";
   {
      test.ex<double>( []
      {
         throw ( 12 );
      } );
      test.should_fail();
   }
   test = "Exception TestException thrown";
   {
      test.ex<TestException>( []
      {
         throw TestException();
      } );
      test.should_pass();
   }
   test = "Exception TestException thrown";
   {
      test.ex<TestException>( []
      {
         throw ( "Error" );
      } );
      test.should_fail();
   }
   test = "Exception type int not thrown";
   {
      test.ex_not<int>( []
      {
         // Not the exception we're looking for!
         throw TestException();
      } );
      test.should_pass();
   }
   test = "Exception type int not thrown";
   {
      test.ex_not<int>( []
      {
         // Not the exception we're looking for!
         throw ( 1 );
      } );
      test.should_fail();
   }
   test = "Any exception is thrown";
   {
      test.ex_any( []
      {
         throw std::exception();
      } );
      test.should_pass();
   }
   test = "Any exception is thrown";
   {
      test.ex_any( []
      {
      } );
      test.should_fail();
   }
   test = "No exception is thrown";
   {
      test.ex_none( []
      {
         // NOP
      } );
      test.should_pass();
   }
   test = "No exception is thrown";
   {
      test.ex_none( []
      {
         throw ( "Ex" );
      } );
      test.should_fail();
   }

   //=========================
   // Test Compounds
   //=========================
   test = "Compund statements first fails (should fail)";
   {
      test.all( false, true, true );
      test.should_fail();
   }
   test = "Compund statements last fails (should fail)";
   {
      test.all( true, true, false );
      test.should_fail();
   }
   test = "Compund statements all fails (should fail)";
   {
      test.all( false, false, false );
      test.should_fail();
   }
   test = "Compund statements all pass";
   {
      test.all( true, true, true );
      test.should_pass();
   }

   //=========================
   // Test Strings
   //=========================
   test = "Two C array string comparison";
   {
      const char a1[] = "Sun!";
      const char a2[] = "Sun!";
      test.eq( a1, a2 );
      test.should_pass();
   }
   test = "Two C array string comparison";
   {
      const char a1[] = "Sun!";
      const char a2[] = "Car";
      test.eq( a1, a2 );
      test.should_fail();
   }
   test = "Two C pointer string comparison";
   {
      const char * a1 = "Sun!";
      const char * a2 = "Sun!";
      test.eq( a1, a2 );
      test.should_pass();
   }
   test = "Two C pointer string comparison";
   {
      const char * a1 = "Sun!";
      const char * a2 = "Car";
      test.eq( a1, a2 );
      test.should_fail();
   }
   test = "Two C string comparison";
   {
      test.eq( "Boat", "Boat" );
      test.should_pass();
   }
   test = "Two C string comparison";
   {
      test.eq( "Boat", "Goat" );
      test.should_fail();
   }
   test = "C string with std::string comparison";
   {
      test.eq( "Boat", std::string( "Boat" ) );
      test.should_pass();
   }
   test = "C string with std::string comparison";
   {
      test.eq( "Goat", std::string( "Boat" ) );
      test.should_fail();
   }
   test = "std::string with C string comparison";
   {
      test.eq( std::string( "Boat" ), "Boat" );
      test.should_pass();
   }
   test = "std::string with C string comparison";
   {
      test.eq( std::string( "Goat" ), "Boat" );
      test.should_fail();
   }
   test = "C pointer string and string comparison";
   {
      const char * a1 = "Sun!";
      test.eq( a1, "Sun!" );
      test.should_pass();
   }
   test = "C pointer string and string comparison";
   {
      const char * a1 = "Sun!";
      test.eq( a1, "Fun!" );
      test.should_fail();
   }
   test = "String and C pointer string comparison";
   {
      const char * a2 = "Sun!";
      test.eq( "Sun!", a2 );
      test.should_pass();
   }
   test = "String and C pointer string comparison";
   {
      const char * a2 = "Sun!";
      test.eq( "Fun!", a2 );
      test.should_fail();
   }
   test = "Two std::string comparison";
   {
      std::string s1( "Elephant" );
      std::string s2( "Elephant" );
      test.eq( s1, s2 );
      test.should_pass();
   }
   test = "Two std::string comparison";
   {
      std::string s1( "Elephant" );
      std::string s2( "Hose" );
      test.eq( s1, s2 );
      test.should_fail();
   }

   test = "Two C array string comparison";
   {
      const char a1[] = "Sun!";
      const char a2[10] = "Moon!";
      test.ne( a1, a2 );
      test.should_pass();
   }
   test = "Two C array string comparison";
   {
      const char a1[] = "Sun!";
      const char a2[10] = "Sun!";
      test.ne( a1, a2 );
      test.should_fail();
   }
   test = "Two C pointer string comparison";
   {
      const char * a1 = "Sun!";
      const char * a2 = "Moon!";
      test.ne( a1, a2 );
      test.should_pass();
   }
   test = "Two C pointer string comparison";
   {
      const char * a1 = "Sun!";
      const char * a2 = "Sun!";
      test.ne( a1, a2 );
      test.should_fail();
   }
   test = "Two different C string comparison";
   {
      test.ne( "Boat", "Goat" );
      test.should_pass();
   }
   test = "Two different C string comparison";
   {
      test.ne( "Goat", "Goat" );
      test.should_fail();
   }
   test = "C string with different std::string comparison";
   {
      test.ne( "Boat", std::string( "Goat" ) );
      test.should_pass();
   }
   test = "C string with different std::string comparison";
   {
      test.ne( "Goat", std::string( "Goat" ) );
      test.should_fail();
   }
   test = "std::string with different C string comparison";
   {
      test.ne( std::string( "Boat" ), "Goat" );
      test.should_pass();
   }
   test = "std::string with different C string comparison";
   {
      test.ne( std::string( "Goat" ), "Goat" );
      test.should_fail();
   }
   test = "C pointer string and different string comparison";
   {
      const char * a1 = "Sun!";
      test.ne( a1, "Moon!" );
      test.should_pass();
   }
   test = "C pointer string and different string comparison";
   {
      const char * a1 = "Sun!";
      test.ne( a1, "Sun!" );
      test.should_fail();
   }
   test = "String and different C pointer string comparison";
   {
      const char * a2 = "Moon!";
      test.ne( "Sun!", a2 );
      test.should_pass();
   }
   test = "String and different C pointer string comparison";
   {
      const char * a2 = "Moon!";
      test.ne( "Moon!", a2 );
      test.should_fail();
   }
   test = "Two different std::string comparison";
   {
      std::string s1( "Elephant" );
      std::string s2( "Horse" );
      test.ne( s1, s2 );
      test.should_pass();
   }
   test = "Two different std::string comparison";
   {
      std::string s1( "Elephant" );
      std::string s2( "Elephant" );
      test.ne( s1, s2 );
      test.should_fail();
   }

   // This MUST is the last line in the code.
   clog << "\nMICRO TEST VERIFICATION SUCCESSFULL\n\n";
}
