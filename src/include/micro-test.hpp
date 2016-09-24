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

/*******************************************************
 * CODE GUIDELIVE TO BE FOLLOWED FOUND HERE:
 *
 * https://bitbucket.org/rajinder_yadav/cpp_code_guide
 *
 *******************************************************/

#ifndef _micro_test_hpp_
#define _micro_test_hpp_

/** Header files to include for Micro Test (Best practice, add to your source).
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include "micro-test.hpp"
*/

using std::clog;

namespace MicroTest
{
   const std::string VERSION( "1.7.0" );

#define setup_fixture [&]
#define cleanup_fixture [&]

#if defined ( _WINDOWS ) || defined( _WIN32 ) || defined( _PLAIN_TEXT )
   const std::string PASS( "Pass: " );
   const std::string FAIL( "Fail: " );
   const std::string WHITE( "" );
#else
   const std::string PASS( "\x1B[32mPass: " );
   const std::string FAIL( "\x1B[31mFail: " );
   const std::string WHITE( "\x1B[37m" );
#endif

   class TestRunner
   {
      enum ReportMode_e { RM_ALL, RM_FAIL, RM_SUMMARY };

      // RAII fixture helper.
      class Fixture
      {
         TestRunner * tr;

      public:
         Fixture( TestRunner * i_testrunner ) : tr( i_testrunner )
         {
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

      ReportMode_e report_mode;

      lambda_t setup;
      lambda_t cleanup;

      bool test_result;

      // To capture cerr output
      std::stringstream err_out;
      std::streambuf * cerr_buf;

      std::string test_description;

      void test_status_pass()
      {
         ++pass;
         test_result = true;

         if ( report_mode < RM_FAIL )
         {
            clog << PASS
                 << test_description
                 << WHITE
                 << std::endl;
         }
      }

      void test_status_fail()
      {
         ++fail;
         test_result = false;

         if ( report_mode < RM_SUMMARY )
            clog << FAIL
                 << test_description
                 << WHITE
                 << std::endl;
      }

      void check( const bool i_status )
      {
         Fixture fix( this );

         if ( i_status )
         {
            test_status_pass();
         }
         else
         {
            test_status_fail();
         }

         // Clear error buffer & error states
         err_out.str( "" );
         err_out.clear();
      }

      void program_arguments( const int i_argc, const char * const i_argv[] )
      {
         if ( i_argc < 2 )
         {
            report_mode = RM_ALL;
            return;
         }

         switch ( i_argv[1][1] )
         {
         case 'a':
            report_mode = RM_ALL;
            break;

         case 'f':
            report_mode = RM_FAIL;
            break;

         case 's':
            report_mode = RM_SUMMARY;
            break;

         default:
            std::cout << "\nMicro Test Usage\n"
                      << "================\n\n"
                      << i_argv[0] << " [OPTIONS]\n\n"
                      << "OPTIONS\n"
                      << "   <blank>  No arguments passed, show all test results.\n"
                      << "   -a       Show all test results.\n"
                      << "   -f       Show only failing results.\n"
                      << "   -s       Show only the summary report.\n"
                      << "   -h       Output this usage message and exit.\n\n";
            std::exit( 1 );
         } // switch
      }

      template <typename TEX>
      void exception( const lambda_t i_fn,
                      const bool i_exception_expected = true )
      {
         bool exception_thrown = false;
         Fixture fix( this );

         try
         {
            i_fn();
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

         if ( ( exception_thrown && i_exception_expected ) ||
              ( !exception_thrown && !i_exception_expected ) )
         {
            test_status_pass();
         }
         else
         {
            test_status_fail();
         }

         // Clear error buffer & error states
         err_out.str( "" );
         err_out.clear();
      }

   public:
      explicit TestRunner( const int i_argc = 1,
                           const char * const i_argv[] = nullptr )
         : pass{}
         , fail{}
         , setup{}
         , cleanup{}
      {
         program_arguments( i_argc, i_argv );

         // Capture cerr, don't want test output polluted.
         cerr_buf = std::cerr.rdbuf( err_out.rdbuf() );
         clog << "\no=================================================o\n"
              << "| Micro Test v" << VERSION << " for C/C++                     |\n"
              << "|                                                 |\n"
              << "| https://bitbucket.org/rajinder_yadav/micro_test |\n"
              << "o=================================================o"
              << std::endl;
      }

      virtual ~TestRunner()
      {
         clog << "==============================================\n";
         clog << "Test Summary: Tests(" << pass + fail << ") "
              << "Passed(" << pass << ") "
              << "Failed(" << fail << ")\n" << std::endl;
         // Restore cerr
         std::cerr.rdbuf( cerr_buf );
      }

      void should_pass() const
      {
         if ( test_result == false )
         {
            clog << "Error! Unexpected test result!" << std::endl;
            std::exit( 1 );
         }
      }
      void should_fail() const
      {
         if ( test_result == true )
         {
            clog << "Error! Unexpected test result!" << std::endl;
            std::exit( 1 );
         }
      }

      void operator=( const std::string & i_message )
      {
         if ( setup )
         {
            setup();
         }

         test_description = i_message;
      }

      void operator()( const bool i_flag )
      {
         check( i_flag );
      }

      void fixture( const lambda_t i_setup = nullptr,
                    const lambda_t i_cleanup = nullptr )
      {
         setup = i_setup;
         cleanup = i_cleanup;
      }

      //======================
      // Equality Test Helper
      //======================
      template <typename T>
      void t( T i_v )
      {
         check( i_v == true );
      }
      template <typename T>
      void f( T i_v )
      {
         check( i_v == false );
      }
      template <typename T>
      void eq( T i_l, T i_r )
      {
         check( i_l == i_r );
      }
      template <typename T>
      void ne( T i_l, T i_r )
      {
         check( i_l != i_r );
      }
      template <typename T>
      void lt( T i_l, T i_r )
      {
         check( i_l < i_r );
      }
      template <typename T>
      void gt( T i_l, T i_r )
      {
         check( i_l > i_r );
      }
      template <typename T>
      void le( T i_l, T i_r )
      {
         check( i_l <= i_r );
      }
      template <typename T>
      void ge( T i_l, T i_r )
      {
         check( i_l >= i_r );
      }

      template <typename... Args>
      void all( Args... i_args )
      {
         const int size = sizeof...( i_args );
         bool status[size] = {i_args...};

         for ( int i = 0; i < size; ++i )
         {
            if ( !status[i] )
            {
               check( false );
               return;
            }
         }

         check( true );
      }

      //==========================
      // String Comparison Helpers
      //==========================
      void eq( const std::string & i_s1, const std::string & i_s2 )
      {
         check( i_s1.compare( i_s2 ) == 0 );
      }
      void eq( const char * const i_s1, const char * const i_s2 )
      {
         check( std::string( i_s1 ).compare( i_s2 ) == 0 );
      }
      void ne( const std::string & i_s1, const std::string & i_s2 )
      {
         check( i_s1.compare( i_s2 ) != 0 );
      }
      void ne( const char * const i_s1, const char * const i_s2 )
      {
         check( std::string( i_s1 ).compare( i_s2 ) != 0 );
      }

      //======================
      // Exception Test Helper
      //======================

      // Test exception T is thrown.
      template <typename T>
      void ex( const lambda_t i_fn )
      {
         exception<T>( i_fn, true );
      }
      // Test exception T is never thrown.
      template <typename T>
      void ex_not( const lambda_t i_fn )
      {
         exception<T>( i_fn, false );
      }
      // Test any exception is thrown.
      void ex_any( const lambda_t i_fn )
      {
         Fixture fix( this );

         try
         {
            i_fn();
            test_status_fail();
         }
         catch ( ... )
         {
            test_status_pass();
         }
      }
      // Test no exception is ever thrown of any type.
      void ex_none( const lambda_t i_fn )
      {
         Fixture fix( this );

         try
         {
            i_fn();
            test_status_pass();
         }
         catch ( ... )
         {
            test_status_fail();
         }
      }
   };

} // namespace MicroTest

#endif // _micro_test_hpp_
