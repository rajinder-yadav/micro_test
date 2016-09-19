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
 * Copyright (c) 2016 Rajinder Yadav <info@devmentor.org>
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
   const double version{1.5};

   class TestRunner
   {
      // RAII fixture helper.
      class Fixture
      {
         TestRunner * tr;
      public:

         Fixture( TestRunner * p ): tr( p )
         {
            if ( tr->setup )
            {
               tr->setup();
            }
         }
         ~Fixture()
         {
            if ( tr->cleanup )
            {
               tr->cleanup();
            }
         }
      };

      typedef std::function<void()> lambda_t;

      // Test success & fail counts
      uint32_t pass;
      uint32_t fail;

      bool fail_mode;

      lambda_t setup;
      lambda_t cleanup;

      // To capture cerr output
      std::stringstream err_out;
      std::streambuf * cerr_buf;

      std::string test_description;

      void Pass()
      {
         ++pass;

         if ( ! fail_mode )
         {
            clog << char( 0x1B )
                 << "[32mPass: "
                 << test_description
                 << char( 0x1B )
                 << "[37m"
                 << "\n"
                 << std::flush;
         }
      }

      void Fail()
      {
         ++fail;
         clog << char( 0x1B )
              << "[31mFail: "
              << test_description
              << char( 0x1B )
              << "[37m"
              << "\n"
              << std::flush;
      }

      void check( bool status )
      {
         Fixture fix( this );

         if ( status )
         {
            Pass();
         }
         else
         {
            Fail();
         }

         // Clear error buffer & error states
         err_out.str( "" );
         err_out.clear();
      }

      template <typename TEX>
      void exception( lambda_t fn, bool exception_expected = true )
      {
         bool exception_thrown = false;
         Fixture fix( this );

         try
         {
            fn();
            exception_thrown = false;
         }
         catch ( TEX & ex )
         {
            exception_thrown = true;
         }
         catch ( ... )
         {
            // Not the exception tested for.
            exception_thrown = false;
         }

         if ( ( exception_thrown && exception_expected ) ||
              ( !exception_thrown && !exception_expected ) )
         {
            Pass();
         }
         else
         {
            Fail();
         }

         // Clear error buffer & error states
         err_out.str( "" );
         err_out.clear();
      }

   public:

      explicit TestRunner( bool enable_fail_mode = false )
         : pass{}
         , fail{}
         , fail_mode( enable_fail_mode )
         , setup{}
         , cleanup{}
      {
         // Capture cerr, don't want test output polluted.
         cerr_buf = std::cerr.rdbuf( err_out.rdbuf() );
         clog << "\no===================================o\n"
              << "| Micro Test v" << version << " for C++           |\n"
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

      void operator = ( const std::string & message )
      {
         test_description = message;
      }

      void operator()( bool flag )
      {
         check( flag );
      }

      void fixture( lambda_t init = nullptr, lambda_t term = nullptr )
      {
         setup = init;
         cleanup = term;
      }

      /**
       * Equality Test Helper
       */
      template <typename T>
      void t( T v )
      {
         check( v == true );
      }
      template <typename T>
      void f( T v )
      {
         check( v == false );
      }
      template <typename T>
      void eq( T l, T r )
      {
         check( l == r );
      }
      template <typename T>
      void ne( T l, T r )
      {
         check( l != r );
      }
      template <typename T>
      void lt( T l, T r )
      {
         check( l < r );
      }
      template <typename T>
      void gt( T l, T r )
      {
         check( l > r );
      }
      template <typename T>
      void lte( T l, T r )
      {
         check( l <= r );
      }
      template <typename T>
      void gte( T l, T r )
      {
         check( l >= r );
      }

      /**
       * Exception Test Helper
       */

      // Test exception T is thrown.
      template <typename T>
      void ex( lambda_t fn )
      {
         exception<T>( fn, true );
      }
      // Test exception T is never thrown.
      template <typename T>
      void no_ex( lambda_t fn )
      {
         exception<T>( fn, false );
      }
      // Test any exception is thrown.
      void any_ex( lambda_t fn )
      {
         Fixture fix( this );

         try
         {
            fn();
            Fail();
         }
         catch ( ... )
         {
            Pass();
         }
      }
      // Test no exception is ever thrown.
      void any_no_ex( lambda_t fn )
      {
         Fixture fix( this );

         try
         {
            fn();
            Pass();
         }
         catch ( ... )
         {
            Fail();
         }
      }
   };

} // namespace MicroTest

#endif // _micro_test_hpp_
