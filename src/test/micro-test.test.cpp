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
      test.lte( 12, 12 );
   }
   test = "Test helper for >=";
   {
      test.gte( 12, 12 );
   }
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

}
