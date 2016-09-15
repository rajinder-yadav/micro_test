#Micro Test For C++11

Testing just got a whole lot simpler, faster and easy to do.

Write beautiful easy to read test code with Micro Test, and to get going all you need in a single include.

Micro Test is a very small and lean unit test framework that is both easy and simple to use. The framework has intentional kept simple, feel free to extend is as you see fit, there is no immediate plan to build it out futher. This project exist for those who need something minimal to get going with testing without the headache of complexity!

Here are the following steps you need to start testing with 'Micro Tester'.

Include the following header files.

```
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
```

Create an instance of TestRunner, it's a good idea to use the name 'test' as it will become very obvious when you see the code.

```
MicroTest::TestRunner test;
```
# Pass/Fail Testing
For each test, follow the following template, note we assign a string to object 'test', an instance of TestRunner.

```
test = "Description of testing being performed";
{

}
```

Inside the test block, pass a boolean value to object 'test' to indicate success or failure of the test.

```
test = "Description of testing being performed";
{
  int sum = Add( 1, 2 );
  test( sum == 3 );
}
```

## Exception Testing
If you would like to check that a function threw an exception, make use of the method ex.

TestRunner::ex( fn, boolean);

The first argument will be a lambda function, inside it make other calls or perform operations that could throw an exception.

The second argument is a boolean flag indicating if an exception was expected.

* true  - Indicates an exception should get thrown.
* false - Indicates an exception will not be thrown.

The 2nd argument


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


