# C++ Reflection

C++ has no language supported reflection, but we can approximate some reflection functionality using template SFINAE and if constexpr.

## Features

* Returns true if member exists (credits to [Andy Prowl](https://stackoverflow.com/a/14523787))
* Returns value of member if exists, 0 otherwise

## Mechanism

* Uses SFINAE to resolve to 0 or 1 depending on existence of member variable/function
* Uses if constexpr in template function to exclude compilation of code that refers to non-existing member

## Restrictions

* Not runtime reflection
* Requires c++17

## Examples

* struct definition in question
  ```cpp
  struct Foo
  {
    int MemInt;
    bool MemBool;
    float MemFloat;
  };
  ```
* Set up
  ```cpp
  #include "include/reflection.h"

  // declare members that we need to check if exist, or retrive value
  // these members should be declared regardless of them actually existing or not
  CREATE_MEMBER_CHECK(MemInt);
  CREATE_MEMBER_CHECK(MemBool);
  CREATE_MEMBER_CHECK(MemFloat);
  CREATE_MEMBER_CHECK(MemDouble); // doesn't exist
  CREATE_MEMBER_CHECK(MemLong);   // doesn't exist
  ```

* Test if exist
  ```cpp
  bool HasMemInt = HAS_MEMBER(Foo, MemInt);       // true
  bool HasMemDouble = HAS_MEMBER(Foo, MemDouble); // false
  ```

* Retrieve value if exist, 0 if not (member type must be constructible from 0)
  ```cpp
  Foo o;
  o.MemInt = 5;
  o.MemFloat = 1.234;

  auto FooInt = GET_MEMBER(o, MemInt);    // FooInt is 5
  auto FooFloat = GET_MEMBER(o, MemFloat);  // FooFloat is 1.234
  auto FooDouble = GET_MEMBER(o, MemDouble); // FooDouble is 0
  ```
