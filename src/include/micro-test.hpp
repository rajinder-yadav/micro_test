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

/** Header files to include for Micro Test (Best practice, add to your source).
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
   const std::string PASS("Pass: ");
   const std::string FAIL("Fail: ");
   const std::string WHITE("");
   #else
   const std::string PASS("\x1B[32mPass: ");
   const std::string FAIL("\x1B[31mFail: ");
   const std::string WHITE("\x1B[37m");
   #endif

   class TestRunner
   {
      enum ReportMode_e { RM_ALL, RM_FAIL, RM_SUMMARY };

      // RAII fixture helper.
      class Fixture
      {
         TestRunner * tr;

      public:
         Fixture( TestRunner * p ) : tr( p )
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

      void Pass()
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

      void Fail()
      {
         ++fail;
         test_result = false;
         if ( report_mode < RM_SUMMARY )
         clog << FAIL
              << test_description
              << WHITE
              << std::endl;
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

      void ProgramArguments( int argc, char * argv[] )
      {
         if( argc < 2 ) {
            report_mode = RM_ALL;
            return;
         }

         switch( argv[1][1] )
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
                      << argv[0] << " [OPTIONS]\n\n"
                      << "OPTIONS\n"
                      << "   <blank>  No arguments passed, show all test results.\n"
                      << "   -a       Show all test results.\n"
                      << "   -f       Show only failing results.\n"
                      << "   -s       Show only the summary report.\n"
                      << "   -h       Output this usage message and exit.\n\n";
                      exit(1);
         } // switch
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
      explicit TestRunner( int argc = 1, char * argv[] = nullptr )
         : pass{}
         , fail{}
         , setup{}
         , cleanup{}
      {
         ProgramArguments( argc, argv );

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

      void shouldPass() const
      {
         if(test_result == false)
         {
            clog << "Error! Unexpected test result!" << std::endl;
            exit(1);
         }
      }
      void shouldFail() const
      {
         if(test_result == true)
         {
            clog << "Error! Unexpected test result!" << std::endl;
            exit(1);
         }
      }

      void operator=( const std::string & message )
      {
         if ( setup )
         {
            setup();
         }

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
      void le( T l, T r )
      {
         check( l <= r );
      }
      template <typename T>
      void ge( T l, T r )
      {
         check( l >= r );
      }

      template <typename... Args>
      void all( Args... args )
      {
         const int size = sizeof...( args );
         bool status[size] = {args...};

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

      /**
       * String Comparison Helpers
       */
      void eq(const std::string & s1, const std::string & s2)
      {
         check(s1.compare(s2) == 0);
      }
      void eq(const char * s1, const char * s2 )
      {
         check( std::string(s1).compare(s2) == 0 );
      }
      void ne(const std::string & s1, const std::string & s2)
      {
         check(s1.compare(s2) != 0);
      }
      void ne(const char * s1, const char * s2 )
      {
         check( std::string(s1).compare(s2) != 0 );
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
      void ex_not( lambda_t fn )
      {
         exception<T>( fn, false );
      }
      // Test any exception is thrown.
      void ex_any( lambda_t fn )
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
      // Test no exception is ever thrown of any type.
      void ex_none( lambda_t fn )
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
