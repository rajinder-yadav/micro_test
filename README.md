#Micro Test For C++11

Testing just got a whole lot simpler, faster and easy to get done, you have no more excuse not to test!

Write beautiful easy to read test code with Micro Test and to get going all you need is a single include, in fact the entire framework is contained inside a single file less than 100 lines of code!

![Test Image](https://bytebucket.org/rajinder_yadav/micro_test/raw/e6f1f379839d51cfff03ca8389a4566fef3da2a7/micro-test.png)

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

```
MicroTest::TestRunner test;
```
# Pass/Fail Testing
For each test, use the following template, note we assign a string to object 'test', an instance of TestRunner.

```
test = "Description of testing being performed";
{
  // Test code goes here.
}
```

Inside the test block, pass a boolean value to object 'test' to indicate success or failure of the test.

```
test = "Add values of 1 and 2, return sum of 3";
{
  int sum = Add( 1, 2 );
  test( sum == 3 );
}
```

## Exception Testing
If you would like to check that a function threw an exception, make use of the method ex.

```
TestRunner::ex( fn, boolean);

Prototype of fn is: 'void fn()', but in C++11 you should just use a lambda.
```

The first argument will be a lambda function, inside it make other calls or perform operations that could throw an exception.

The second argument is a boolean flag indicating if an exception was expected.

* true  - Indicates an exception should get thrown.
* false - Indicates an exception will not be thrown.


```
test = "Description of testing being performed";
{
  int sum = Add( 1, 2 );
  test.ex( [] {
    // Perform operation or make a call inside here
    // that could throw an exception!
  }, <true or false> );
}
```

See example usage inside main.cpp, notice how beautiful the testing code looks!

If you like this please share it with others :-) and send me some love!!!

