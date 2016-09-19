# Change Log

## Version 1.5

Breaking changes
* Status flag removed.

New test helper template functions.

1. Equality Test Helpers
    * t - Test for true
    * f - Test for false
    * eq - Test ==
    * ne - Test !=
    * lt - Test <
    * gt - Test >
    * lte - Test <=
    * gte - Test >=

1. Exception Test Helpers
    * ex - Exception type T thrown.
    * no_ex - Exception type T never thrown.
    * any_ex - Any type of exception thrown.
    * any_no_ex - Any type of exception never thrown.

---