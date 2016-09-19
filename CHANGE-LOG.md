# Change Log

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