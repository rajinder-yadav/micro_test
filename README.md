# Micro Test For C++11

Testing just got a whole lot simpler, faster and easy to get done, you have no more excuse not to test!

## Beautiful Test Code
Write beautiful easy to read test code with Micro Test. To get going, all you need is a single include. In fact the entire framework is contained inside a single file less than 100 lines of code!

![Test Code Image](https://bytebucket.org/rajinder_yadav/micro_test/raw/bcbf4e0a0ab2ef09804f07b623cf39561169e8b2/micro-test.png)

## Beautiful Test Summary
![Test Summary Image](https://bytebucket.org/rajinder_yadav/micro_test/raw/e264a3fb0022dd4d5b841f08a7292901e9aa0dc1/test-run.png)

## Capturing Test Output

You can redirect the test output to a file using the following command on Linux:
```
./micro_tester &> test.log
```

## KISS Principle
Micro Test is a very small and lean unit test framework that is both easy and simple to use. The framework was intentionally kept simple, feel free to extend it as you see fit. There is no immediate plan to build it out further. This project exists for those who need something minimal to get going with testing, without the headache of complexity!

Here are the following steps you need to start testing with 'Micro Test'.

Copy the file micro-test.hpp into the root of your test folder.

Include the following header files from the source file of your test project.

```
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

#include "micro-test.hpp"
```

Create an instance of MicroTest::TestRunner, it's a good idea to use the name 'test' as it will become very obvious when you see the code examples.

```C++
MicroTest::TestRunner test;
```
## Pass/Fail Testing
For each test, use the following template, note we assign a string to object 'test', an instance of TestRunner.

```C++
test = "Description of testing being performed";
{
  // Test code goes here.
}
```

Inside the test block, pass a boolean value to object 'test' to indicate success or failure of the test.

```C++
test = "Add values of 1 and 2, return sum of 3";
{
  test( Add( 1, 2 ) == 3 );
}
```

Alternatively you can assign the test success value to the 'status' boolean member as the following code demonstrates. Note you still need to call 'test()' at the end.

```C++
test = "Add values of 1 and 2, return sum of 3";
{
  int sum1 = Add( 1, 2 );
  int sum2 = Add( 5, -2 );
  test.status = (sum1 == 3) && (sum2 == 3);
  test();
}
```

## Exception Testing
If you would like to check that a function threw an exception, make use of the method ex.

```
TestRunner::ex( Fn, boolean );

Function signature of Fn is: void func()
In C++11 Fn should be using a lambda function.
```

The first argument will be a lambda function, inside it make other calls or perform operations that could throw an exception.

The second argument is a boolean flag indicating if an exception was expected.

* true  - Indicates an exception should get thrown.
* false - Indicates an exception will not be thrown.


```C++
test = "Description of testing being performed";
{
  test.ex( [] {
    // Place code that could throw an exception inside lambda block!
    throw(1);
  }, <true_or_false> );
}
```

See example usage inside main.cpp, notice how beautiful the testing code looks!

If you like this please share it with others :-) and send me some love!!!
