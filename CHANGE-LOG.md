# Change Log
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