# Micro Test For Testing C++ Code

Testing just got a whole lot simpler, faster and fun to get done, you have no more excuse not to test! I wrote it because I believe writing tests and setting up a test project should be simple and painless.

### Group - Getting Help

If you have questions or suggestions for improvements, join the MicroTest community on Gitter [MicroTest Group](https://gitter.im/devmentor-org/microtest)

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
![Test Summary Image](https://bytebucket.org/rajinder_yadav/micro_test/raw/ec86091c1170fdedb104b6af2d1edb63acc16f4c/test-summary.png)

## Capturing Test Output

You can redirect the test output to a file using the following command on Linux:
```
./micro_tester &> test.log
```

## KISS Principle
Micro Test is a very small and lean unit test framework that is easy to learn and simple to setup. The framework has been intentionally kept simple, however I am aways open to feedback and suggestions for improvement here: [MicroTest Group on Gitter](https://gitter.im/devmentor-org/microtest)

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
A Test block is a single test you want to perform against a API (function). A test block always have these 3 items:

1. Test description.
1. Test block with you test code.
1. Call to check the test result.

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

## Using Status Flag
Alternatively you can assign the test success value to the **'status'** boolean member as the following code demonstrates. You are still required to call **'test()'** at the end.

```C++
test = "Add positive and negative values";
{
  int sum1 = Add( 1, 2 );
  int sum2 = Add( 5, -2 );
  test.status = (sum1 == 3) && (sum2 == 3);  // Assign to Status flag
  test();
}
```

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
If you would like to check that a function threw a certain type of exception, make use of the template method TestRunner::ex().

```
TestRunner::ex<ExceptionType>( Fn, boolean );

Function signature of Fn is: void func()
In C++11 Fn should be using a lambda function.
```
The exception type is declared as ExceptionType.

The first argument will be a lambda function, inside it make other calls or perform operations that could throw an exception.

The second argument is a boolean flag indicating if an exception was expected.

* true  - Indicates an exception should get thrown.
* false - Indicates an exception will not be thrown.


```C++
test = "Description of testing being performed";
{
  test.ex<int>( [] {
   // Place test code that could throw an exception inside lambda block.
    throw(1);
  }, <true_or_false> );
}
```

## Fail Mode Testing
We all love to see those green passing tests light up, but what we really care about is the failing test. Once you got all passing tests, it's time to switch to (fail mode) seeing only failing test. It's less clutter and when you're refactoring and making changes, you only care about fixing the failing test.

**Speed TIP** - Large tests will execute much faster, since the bottleneck is output to the terminal.

To enable fail mode testing, pass **true** to the test object constructor.

```C++
MicroTest::TestRunner test(true);
```

When switched to fail mode, the output will now look like this.

![Failing Test Images](https://bytebucket.org/rajinder_yadav/micro_test/raw/ec86091c1170fdedb104b6af2d1edb63acc16f4c/fails-only.png)

## Test Fixtures
A test fixture is something that must be prepared and ready before a test block is executed. We can do this ourself, but it would become repetitive and bloat our test code unnecessarily. This is where a test fixture comes in and is optional, since more test cases can be performed about a fixture.

A fixture will have 2 parts stages:

1. A setup stage were code is executed to prepares test artifacts.
1. A cleanup stage were the setup artifacts are destroyed.

To declare fixtures, make use of the call **TestRunner::fixture( SetupFunc, CleanupFunc )**.

```C++
test.fixture(
   [] // Setup
   {
      // Put the setup code here.
   },
   [] // Cleanup
   {
      // Put the cleanup code here.
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

```
cd <project_root_folder>
mkdir build
cd build
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE="Release" ../src
make

Run the sample code.

./micro_tester

For Windows change the cmake command above to:

cmake -G "NMake Makefiles" -D CMAKE_BUILD_TYPE="Release" ../src
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