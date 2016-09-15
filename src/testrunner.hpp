//==================================================================================================
// The MIT License (MIT)
//
// Copyright (c) 2016 Rajinder Yadav <rajinder.yadav@hotmail.com>
//==================================================================================================

#ifndef _test_runner_hpp_
#define _test_runner_hpp_

//#include <iostream>
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <functional>

using std::cout;

class TestRunner
{
   // Test success & fail counts
   int pass;
   int fail;
   int exceptions;

   // To capture cerr output
   std::stringstream err_out;
   std::streambuf * cerr_buf;

   std::string test;

   typedef std::function<void()> func_t;

public:
   TestRunner()
      : pass( 0 )
      , fail( 0 )
      , exceptions( 0 )
   {
      // Capture cerr, don't want test output polluted.
      cerr_buf = std::cerr.rdbuf( err_out.rdbuf() );
      cout << "Running tests\n"
           << "=============\n";
   }

   virtual ~TestRunner()
   {
      cout << "===================================\n";
      cout << "Tests run(" << pass + fail << ") "
           << "Passed(" << pass << ") "
           << "Failed(" << fail << ")\n\n";
      // Restore cerr
      std::cerr.rdbuf( cerr_buf );
   }

   void operator= ( const std::string & s )
   {
      test = s;
   }

   void operator()( bool f )
   {
      check( f );
   }

   void ex( func_t fn )
   {
      try
      {
         fn();
         ++fail;
         cout << char( 0x1B ) << "[31mFail: " << test << char( 0x1B ) << "[37m" << "\n";
      }
      catch ( ... )
      {
         ++pass;
         cout << char( 0x1B ) << "[32mPass: " << test << char( 0x1B ) << "[37m" << "\n";
      }
      // Clear error buffer & error states
      err_out.str( "" );
      err_out.clear();
   }

   void check( bool b )
   {
      if ( b )
      {
         ++pass;
         cout << char( 0x1B ) << "[32mPass: " << test << char( 0x1B ) << "[37m" << "\n";
      }
      else
      {
         ++fail;
         cout << char( 0x1B ) << "[31mFail: " << test << char( 0x1B ) << "[37m" << "\n";
      }
      // Clear error buffer & error states
      err_out.str( "" );
      err_out.clear();
   }
};

#endif // _test_runner_hpp_

