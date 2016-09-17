/**
 * @file:  micro-test.hpp
 * @brief: Micro Test
 *
 * @author: Rajinder Yadav
 * @date:   Sep 15, 2016 at 05:03 AM
 *
 * @description
 * A micro testing framework for C++11 code.
 *
 * License: MIT License (MIT)
 * Copyright (c) 2016 Rajinder Yadav <rajinder.yadav@hotmail.com>
 *
 * Notice: This Software is provided as-is without warrant.
 */

#ifndef _micro_test_hpp_
#define _micro_test_hpp_

// Header files to include for Micro Test (Best practice, add to your source).
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <functional>
//#include "micro-test.hpp"

using std::clog;

namespace MicroTest
{
   const std::string version("Micro Test v1.1");

   class TestRunner
   {
      // Test success & fail counts
      int pass;
      int fail;

      // To capture cerr output
      std::stringstream err_out;
      std::streambuf * cerr_buf;

      std::string test;

      typedef std::function<void()> func_t;

   public:
      // Success flag of current test.
      bool status;

      TestRunner()
         : pass( 0 )
         , fail( 0 )
      {
         // Capture cerr, don't want test output polluted.
         cerr_buf = std::cerr.rdbuf( err_out.rdbuf() );
         clog << "\no===================================o\n"
              << "| " << version << " for C++           |\n"
              << "|                                   |\n"
              << "| Running Tests                     |\n"
              << "o===================================o\n"
              << std::flush;
      }

      virtual ~TestRunner()
      {
         clog << "==============================================\n";
         clog << "Test Summary: Tests(" << pass + fail << ") "
              << "Passed(" << pass << ") "
              << "Failed(" << fail << ")\n\n";
         // Restore cerr
         std::cerr.rdbuf( cerr_buf );
      }

      void operator = ( const std::string & s )
      {
         test = s;
      }

      void operator()(bool f)
      {
         status = f;
         check();
      }

      void operator()()
      {
         check();
      }

      void ex( func_t fn, bool expecting_exception = true )
      {
         bool exception_thrown = false;

         try
         {
            fn();
            exception_thrown = false;
         }
         catch ( ... )
         {
            exception_thrown = true;
         }

         if ( ( exception_thrown && expecting_exception ) ||
              ( !exception_thrown && !expecting_exception ) )
         {
            ++pass;
            clog << char( 0x1B ) << "[32mPass: " << test << char( 0x1B ) << "[37m" << "\n" << std::flush;
         }
         else
         {
            ++fail;
            clog << char( 0x1B ) << "[31mFail: " << test << char( 0x1B ) << "[37m" << "\n" << std::flush;
         }

         // Clear error buffer & error states
         err_out.str( "" );
         err_out.clear();
      }

      void check()
      {
         if ( status )
         {
            ++pass;
            clog << char( 0x1B ) << "[32mPass: " << test << char( 0x1B ) << "[37m" << "\n" << std::flush;
         }
         else
         {
            ++fail;
            clog << char( 0x1B ) << "[31mFail: " << test << char( 0x1B ) << "[37m" << "\n" << std::flush;
         }

         // Clear error buffer & error states
         err_out.str( "" );
         err_out.clear();
         status = false;
      }
   };

} // namespace MicroTest

#endif // _micro_test_hpp_