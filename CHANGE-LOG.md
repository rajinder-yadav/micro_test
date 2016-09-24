# Change Log

## Version 1.7.0
Support added for optional program argument passing.

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


---
## Version 1.6.3
Changed test output for Windows as it cannot use ANSI terminal control characters for color output.

Fixed CMake Makefile, removed pthread, not required and was breaking builds on Windows.

Micro Test now builds and runs on Linux, Mac, Windows.

---
## Version 1.6.2

Updated Equality test helpers TestRunner::eq and TestRunner::ne for improved string comparison support.

---

## Version 1.6.1
Breaking changes: Equality test helpers lte, gte changed.

* lte renamed to le
* gte renamed to ge

---
## Version 1.6.0

Enhancement, added new helper TestRunner::all(...) for compound testing.

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
---
## Version 1.5.1

Bug Fix: Critical Fixture bug fixed.

Added lambda defines for Fixture.

* setup_fixture
* cleanup_fixture

Added test coverage for all test checkers, code placed under new folder src/test.

MicroTest framework file moved to new folder src/include.

---
## Version 1.5

**Breaking changes.**

* Status flag removed.

New test helper template functions.

```
1. Equality Test Helpers

    * t    - Test for true
    * f    - Test for false
    * eq   - Test ==
    * ne   - Test !=
    * lt   - Test <
    * gt   - Test >
    * lte  - Test <=
    * gte  - Test >=

2. Exception Test Helpers

    * ex<T>     - Exception type T thrown.
    * ex_not<T> - Exception type T never thrown.
    * ex_any    - Any type of exception thrown.
    * ex_none   - Any type of exception never thrown.
```

---