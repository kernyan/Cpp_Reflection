#include "include/reflection.h"
#include <iostream>

struct Foo
{
  int MemInt;
  bool MemBool;
  float MemFloat;
};

// in practice, these are generated code
CREATE_MEMBER_CHECK(MemInt);
CREATE_MEMBER_CHECK(MemBool);
CREATE_MEMBER_CHECK(MemFloat);
CREATE_MEMBER_CHECK(MemDouble); // needs to declare member even if doesn't exist

int main()
{
  Foo o;
  o.MemInt = 5;
  o.MemBool = false;
  o.MemFloat = 1.234;

  // Test if member exists
  auto HasInt = HAS_MEMBER(Foo, MemInt); // HasInt is true

  // Retrieve value if exist, 0 if not
  auto FooInt = GET_MEMBER(o, MemInt);       // FooInt is 5
  auto FooBool = GET_MEMBER(o, MemBool);     // FooBool is true
  auto FooFloat = GET_MEMBER(o, MemFloat);   // FooFloat is 1.234
  auto FooDouble = GET_MEMBER(o, MemDouble); // FooDouble is 0

  return 0;
}
