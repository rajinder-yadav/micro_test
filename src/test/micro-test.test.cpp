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
   }
   test = "Person p1 and p2 don't have the same name";
   {
      test.ne( p1->Name(), p2->Name() );
   }
   test = "Person p1 and p3 have the same name";
   {
      test.eq( p1->Name(), p3->Name() );
   }
   // No longer need a fixture.~
   test.fixture();


   //=========================
   // Test Equality
   //=========================
   test = "Test boolean";
   {
      test( true );
   }
   test = "Test helper for 'true'";
   {
      test.t( true );
   }
   test = "Test helper for 'false'";
   {
      test.f( false );
   }
   test = "Test helper for ==";
   {
      test.eq( 12, 12 );
   }
   test = "Test helper for !=";
   {
      test.ne( 123, 321 );
   }
   test = "Test helper for <";
   {
      test.lt( 12, 19 );
   }
   test = "Test helper for >";
   {
      test.gt( 100, 10 );
   }
   test = "Test helper for <=";
   {
      test.le( 12, 12 );
   }
   test = "Test helper for >=";
   {
      test.ge( 12, 12 );
   }

   //=========================
   // Test Exceptions
   //=========================
   test = "Exception type double thrown";
   {
      test.ex<double>( []
      {
         throw ( 12.34D );
      } );
   }
   test = "Exception TestException thrown";
   {
      test.ex<TestException>( []
      {
         throw TestException();
      } );
   }
   test = "Exception type int not thrown";
   {
      test.ex_not<int>( []
      {
         // Not the exception we're looking for!
         throw TestException();
      } );
   }
   test = "Any exception is thrown";
   {
      test.ex_any( []
      {
         throw std::exception();
      } );
   }
   test = "No exception is thrown";
   {
      test.ex_none( []
      {
         // NOP
      } );
   }

   //=========================
   // Test Compounds
   //=========================
   test = "Compund statements first fails (should fail)";
   {
      test.all( false, true, true );
   }
   test = "Compund statements last fails (should fail)";
   {
      test.all( true, true, false );
   }
   test = "Compund statements all fails (should fail)";
   {
      test.all( false, false, false );
   }
   test = "Compund statements all pass";
   {
      test.all( true, true, true );
   }

   //=========================
   // Test Strings
   //=========================
   test = "Two C array string comparison";
   {
      const char a1[] = "Sun!";
      const char a2[] = "Sun!";
      test.eq( a1, a2 );
   }
   test = "Two C pointer string comparison";
   {
      const char * a1 = "Sun!";
      const char * a2 = "Sun!";
      test.eq( a1, a2 );
   }
   test = "Two C string comparison";
   {
      test.eq( "Boat", "Boat" );
   }
   test = "C string with std::string comparison";
   {
      test.eq( "Boat", std::string( "Boat" ) );
   }
   test = "std::string with C string comparison";
   {
      test.eq( std::string( "Boat" ), "Boat" );
   }
   test = "C pointer string and string comparison";
   {
      const char * a1 = "Sun!";
      test.eq( a1, "Sun!" );
   }
   test = "String and C pointer string comparison";
   {
      const char * a2 = "Sun!";
      test.eq( "Sun!", a2 );
   }
   test = "Two std::string comparison";
   {
      std::string s1( "Elephant" );
      std::string s2( "Elephant" );
      test.eq( s1, s2 );
   }

   test = "Two C array to string comparison";
   {
      const char a1[] = "Sun!";
      const char a2[] = "Moon!";
      test.ne( a1, a2 );
   }
   test = "Two C pointer string comparison";
   {
      const char * a1 = "Sun!";
      const char * a2 = "Moon!";
      test.ne( a1, a2 );
   }
   test = "Two different C string comparison";
   {
      test.ne( "Boat", "Goat" );
   }
   test = "C string with different std::string comparison";
   {
      test.ne( "Boat", std::string( "Goat" ) );
   }
   test = "std::string with different C string comparison";
   {
      test.ne( std::string( "Boat" ), "Goat" );
   }
   test = "C pointer string and different string comparison";
   {
      const char * a1 = "Sun!";
      test.ne( a1, "Moon!" );
   }
   test = "String and different C pointer string comparison";
   {
      const char * a2 = "Moon!";
      test.ne( "Sun!", a2 );
   }
   test = "Two different std::string comparison";
   {
      std::string s1( "Elephant" );
      std::string s2( "Horse" );
      test.ne( s1, s2 );
   }

}
