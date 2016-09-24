# Micro Test For Testing C++ Code

Testing just got a whole lot simpler, faster and fun to get done, you have no more excuse not to write test code. If you're like me, you value your time, want to stay productive and most of all be writing solid production code and not having to wrestle a testing framework or test project.

I wrote Micro Test because I believe writing tests and setting up a test project should be simple and painless.

## Say No and GO!

1. No need to build a separate library.
1. No linking or DLL hell.
1. No Complex build process.
1. No Complex project setup.

If you can make a "Hello World" program in C++, then you can go straight to _running_ with Micro Test.

### Micro Test Community - Getting Help

If you have questions, need help or have suggestions for improvements, join the Micro Test community on Gitter [Micro Test Group](https://gitter.im/devmentor-org/microtest)

## Super Fast Execution
Micro Test is blazing fast, an order of magititue faster than other C++ test frameworks, which I consider unnecessarily large and complex.

## Beautiful Test Code
Write beautiful easy to read test code with Micro Test. To get going, all you need is a single include. In fact the entire framework is contained inside a single file less than 100 lines of code!

```C++
   MicroTest::TestRunner test;
   test = "Adding negated values should return zero";
   {
      // Pass boolean value to test.
      // Test true condition.
      test( Add( 5, -5 ) == 0 );
   }
   test = "Add values 5 and -3, return sum of 2";
   {
      // Alternatively use test helper.
      test.eq( Add( 5, -3 ), 2 );
   }
   test = "Any type of exception throw";
   {
      test.ex_any( []
      {
         throw ( "BOOM!" );
      } );
   }
   test = "Check exception TestException is thrown";
   {
      test.ex<TestException>( []
      {
         throw TestException();
      } );
   }
   test = "Exception type int not thrown";
   {
      // An exception type int could get thrown, we're testing it will not!
      test.ex_not<int>( []
      {
         // Code that might throw an exception of type int.
      } );
   }
```

## Beautiful Test Summary
This following test output was taken from the sample code provided.

![Test Summary Image](https://bytebucket.org/rajinder_yadav/micro_test/raw/ec86091c1170fdedb104b6af2d1edb63acc16f4c/test-summary.png)

## Capturing Test Output

If the test program is called 'micro_tester', you can redirect the test output to a file using the following command on Linux or Mac:
```
./micro_tester &> test.log
```

## KISS Principle
Micro Test is a very small and lean test framework that is easy to learn and simple to setup. The framework has been intentionally kept simple, however I am aways open to feedback and suggestions for improvement here: [Micro Test Group on Gitter](https://gitter.im/devmentor-org/microtest)

This project exists for those who need something minimal to get going with testing, without the headache of complexity!

Here are the following steps you need to start testing with 'Micro Test'.

Copy the file **micro-test.hpp** into the root of your test folder.

Include the following header files from the source file of your test project.

```
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

#include "micro-test.hpp"
```

Create an instance of **MicroTest::TestRunner**, it's a good idea to use the name **'test'** as it will become very obvious when you see the code examples.

```C++
MicroTest::TestRunner test;
```
We will make use of the **test** object in steps 1 and 3 below!

## Test Block
A Test block is a single test you want to perform against a API (function). A test is comprised of 3 items:

1. Test description.
1. Test block with the test code.
1. Call test validating method.

```C++
test = "Description of testing being performed";  // Step 1
{                                                 // Step 2
  // Test code goes here.
  test( <boolean_test_result> );                  // Step 3
}
```

## Pass/Fail Testing
As good test writers, we assign a string to object 'test', an instance of MicroTest::TestRunner. This serves two purposes:

1. It's the message displayed during the test run.
1. It documents the test code block.

```C++
test = "Add values of 1 and 2, return sum of 3";
{
  test( Add( 1, 2 ) == 3 );
}
```

Above, in the test call, a boolean value is passed to indicate success or failure of the test execution.

## Equality Test Helpers
There following test helpers are method of MicroTest::TestRunner.

|Method|Operation|Usage|Description|
|------|---------|-----|-----------|
|t( r )|Truthy|test.t( r )|Test result is true.|
|f( r )|Falsely|test.f( r )|Test result is false.|
|( r )|Pass/Fail|test( a == b )|true is pass, false is fail.|
|eq( a, b )|a == b|test.eq( 12, a )|Test values are equal.|
|ne( a, b )|a != b|test.ne( b, -5 )|Test values are not equal.|
|lt( a, b )|a < b|test.lt( a, b )|Test less than.|
|gt( a, b )|a > b|test.gt( a, b )|The greater than.|
|le( a, b )|a <= b|test.le( a, b )|Test less than or equal.|
|ge( a, b )|a >= b|test.ge( a , b)|Test greater than or equal.|

## String Comparison
Since strings in C++ can come in many forms:

1. Literal string in quotes.
1. String in a char array.
1. String as a pointer to char.
1. C++ std::string object.

When comparing strings, make use of TestRunner::eq and TestRunner::ne helpers.

```C++
const char * s1 = "Micro Test makes testing fun!";
std::string s2( "Micro Test makes testing fun!" );
char s3[100] = "Micro Test makes testing fun!";

test.eq( s1, s2 );
test.eq( s1, "Micro Test make testing fun!" );
test.eq( s1, s3 );
test.eq( s2, s3 );
```

## Compound Tests
You may have a need to run a battery of tests in a single test block and make sure they all pass, there is a helper to make it simple.

Use **TestRunner::all**(...) for compound testing.

**Test Tip** - This helper is really good for cases when you want to test a call sequence and check the progression of state.

```C++
test = "Add 3 values 1+2, -5+3, 12+(-12)";
{
   // Better way to perform compound tests.
   test.all(
      Add( 1, 2 ) == 3,
      Add( 5, -3 ) == 2,
      Add( 12, -12 ) == 0
   );
}
```

## Exception Test Helpers

More details on exception testing is provided under section 'Exception Testing'. See also example at top on usage as well as sample provided code.

|Method|Usage|Description|
|------|-----|-----------|
|ex<T>|test.ex<MyException>(lambda)|Check exception of type T is thrown.|
|ex_not<T>|test.ex_not<int>(lambda)|Check exception of type T not thrown.|
|ex_any|test.ex_any(lambda)|Check any exception is thrown.|
|ex_none|test.ex_none(lambda)|Check no exception is thrown.|

Below is a discussion on using a lambda function as it relates to exception testing and fixtures.

## Lamdba Function
A lambda function is an anonymous function. Currently it is used when testing for exception and when using a fixture. If you don't need either, you can skip this section.

This is the very basic you need to understand about a lambda as it applies to Micro Test. In it's most concise format, it is declared like this:

```C++
[] { /* Code goes here. */ }

// Using line breaks, the lambda can be written in this style.

[]
{
   // Code goes here.
}
```

When you see that a function is required for a MicroTest::TestRunner method, you can make use of a simple lambda. The function signature of the lambda is a void argument and void return.

Best practice is to use a lambda right at the test block, this keeps all the test code in the same place. It makes for improved readability and ease of code change because you avoid the need to hunt down external function code.

## Exception Testing
If you would like to check that a function threw a certain type of exception (or not), make use of these template helper function.

```C++
1. TestRunner::ex<ExceptionType>( Fn );
2. TestRunner::ex_not<ExceptionType>( Fn );
3. TestRunner::ex_any( Fn );
4. TestRunner::ex_none( Fn );

Function signature of Fn is: void func()
In C++11 for Fn use a lambda function.
```

```C++
test = "Check exception gets thrown!";
{
  test.ex<ExceptionFoo>( []
  {
     // Code that 'should' throw ExceptionFoo.
  } );
}
```

## Adding Test Modes
We all love to see those green passing tests light up, but what we really care about is the failing test. Once you got all passing tests, it's time to switch to (fail mode) seeing only failing test. It's less clutter and when you're refactoring and making changes, you only care about fixing the failing test.

**Speed TIP** - Large tests will execute much faster in fail or summary mode, since the bottleneck is output to the terminal.

To enable mode testing, pass the program argument from main to **MicroTest::TestRunner** constructor.

Make sure main entry point is coded as:

```C++
int main( int argc, char * argv[] )
```

Now just modify the test object constructor to:

```C++
MicroTest::TestRunner test( argc, argv );
```

You will now have the following _optional_ test modes.

|Option|Test Mode|
|------|-----------|
|      |No options passed, show all test results.|
| -a   |Show all test results.|
| -f   |Show only failing test results.|
| -s   |Show only the summary report.|
| -h   |Show  this usage message.|


**Fail Mode Example**

![Failing Test Images](https://bytebucket.org/rajinder_yadav/micro_test/raw/d10a0c15c07ecac1523b1d899c5d2972f20df4ea/fails-only.png)

## Test Fixtures
A test fixture is something that must be prepared and ready before a test block is executed. We can do this ourself, but it would become repetitive and bloat our test code unnecessarily. This is where a test fixture comes.

A fixture is optional, since most test cases can be performed without a fixture.

A fixture will have two stage:

1. A setup stage were code is executed to prepares test artifacts.
1. A cleanup stage were the setup artifacts are destroyed.

To specify fixtures, make use of the call **TestRunner::fixture( SetupFunc, CleanupFunc )**.

A fixture is declared below, within each function block you provide

```C++
// Declare variables to be used by the fixture first.
// Variables must be accessible by the tests and fixture functions.
MessageQueue mq;
char * buffer = nullptr;

test.fixture(
   setup_fixture
   {
      mq.create("test-exchange");
      mq.connect("test-topic");
      buffer = new char[1000];
      std::memset(buffer, 0, sizeof buffer);
   },
   cleanup_fixture
   {
      mq.disconnect();
      mq.close();
      delete[] buffer;
      buffer = nullptr;
   } );
```

## Fixture Usage Details
1. Variables must be declared before a fixture declaration.
1. Varabiles must be visible to the test using the fixture.

If you're familiar and comfortable with C++11 lambda, you can use '[&]' to replace both 'setup_fixture' and 'cleanup_fixture', both of which are defines to it.

```C++
test.fixture(
   [&]
   {
      // Put setup code here.
   },
   [&]
   {
      // Put cleanup code here.
   } );
```

## Removing Test Fixture
When you no longer have need for a fixture, to remove it, make the following call.

```C++
test.fixture();
```

All subsequent tests will run without a fixture.

## Test Suites
To make use of test suites, it's as simple as separating each test suite in it's own test file. You've already seen how easy it's to create a test project. Just do the same with a new file to group your test as you see fit.

## Building Notes
The Micro Test framework can be used to test C/C++ code, however you will require a C++11 or later compiler to build the Micro Test code, then use existing C or C++ code to test.

You will need CMake to build the sample test project. Step to build the project from the terminal:

Building steps for Linux and MacOS
```
git clone https://rajinder_yadav@bitbucket.org/rajinder_yadav/micro_test.git
cd micro_test
mkdir build
cd build
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE="Release" ../src
make

Run the sample code.

./micro_tester

For Windows change the cmake command above to:

cmake -G "NMake Makefiles" -D CMAKE_BUILD_TYPE="Release" ../src
```

## Building With MinGW on Windows

Building with MinGW (No MSYS)
```
cmake -G "MinGW Makefiles" CMAKE_BUILD_TYPE="Release" ../src
mingw32-make
```

Building from MSYS with MinGW
```
cmake -G "MinGW Makefiles" CMAKE_BUILD_TYPE="Release" ../src
make
```

## Sample Code
Find test examples inside **main.cpp**, it will have the most up to date coding examples.

## Contact
If you like Micro Test, please share it with others :-) and shoot me an email to let me know you found it very helpful for your next project!

**Rajinder Yadav**

**Labs DevMentor.org Corp.**

**Web:** http://labs.devmentor.org

**Email:** info@devmentor.org

Happy Safe Coding :-)