/**
 * @file:   main.cpp
 * @brief:
 *
 * @author:
 * @date:   Sep 15, 2016 at 05:03 AM
 *
 * @description
 * <Enter long description here>
 *
 * License: MIT License (MIT)
 * License: GNU Public License (GNU GPL)
 * Copyright (c) <year> <copyright holders>
 *
 * Notice: This Software is provided as-is without warrant.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

#include "testrunner.hpp"

using std::clog;
using std::cout;
using std::endl;

int main( int argc, char * argv[] )
{
   /**
    * This will kick off the tests.
    * We place each test inside blocks to localize variable declarations.
    */
   TestRunner test;
   test = "This will Pass";
   {
      test( true );
   }
   test = "This will Fail";
   {
      test( false );
   }
   test = "This will throw an exception";
   {
      test.ex( [] {
            throw(1);
      } );
   }
   test = "Exception expected!";
   {
      test.ex( [] {
            // NOP
      } );
   }

   return 0;
}

