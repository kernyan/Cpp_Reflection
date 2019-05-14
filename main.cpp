#include "include/reflection.h"
#include <iostream>

struct Foo
{
  int MemInt;
  bool MemBool;
  float MemFloat;
};

CREATE_MEMBER_CHECK(MemInt);
CREATE_MEMBER_CHECK(MemBool);
CREATE_MEMBER_CHECK(MemFloat);


int main()
{
  Foo o;
  o.MemInt = 5;
  o.MemBool = false;
  o.MemFloat = 1.234;

  auto FooInt = GET_MEMBER(o, MemInt);     // FooInt is 5
  auto FooBool = GET_MEMBER(o, MemBool);   // FooBool is true;
  auto FooFloat = GET_MEMBER(o, MemFloat); // FooFloat is 1.234;

  return 0;
}
