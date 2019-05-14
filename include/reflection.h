#ifndef __reflection_h__
#define __reflection_h__

#include<type_traits>
 
///////////////////////////////////////////////
// from https://stackoverflow.com/a/14523787 //

/*
    - Multiple nheritance forces ambiguity of member names.
    - SFINAE is used to make aliases to member names.
    - Expression SFINAE is used in just one generic has_member that can accept
      any alias we pass it.
*/

template <typename... Args> struct ambiguate : public Args... {};

template<typename A, typename = void>
struct got_type : std::false_type {};

template<typename A>
struct got_type<A> : std::true_type {
    typedef A type;
};

template<typename T, T>
struct sig_check : std::true_type {};

template<typename Alias, typename AmbiguitySeed>
struct has_member {
    template<typename C> static char ((&f(decltype(&C::value))))[1];
    template<typename C> static char ((&f(...)))[2];

    //Make sure the member name is consistently spelled the same.
    static_assert(
        (sizeof(f<AmbiguitySeed>(0)) == 1)
        , "Member name specified in AmbiguitySeed is different from member name specified in Alias, or wrong Alias/AmbiguitySeed has been specified."
    );

    static bool const value = sizeof(f<Alias>(0)) == 2;
};

////////////////////////////////////////////////////////////////////////////
///// MACRO ////////////////////////////////////////////////////////////////
  
#define CREATE_MEMBER_CHECK(member)                                         \
                                                                            \
template<typename T, typename = std::true_type>                             \
struct Alias_##member;                                                      \
                                                                            \
template<typename T>                                                        \
struct Alias_##member <                                                     \
    T, std::integral_constant<bool, got_type<decltype(&T::member)>::value>> \
{ static const decltype(&T::member) value; };                               \
                                                                            \
struct AmbiguitySeed_##member { char member; };                             \
                                                                            \
template<typename T>                                                        \
struct has_member_##member {                                                \
    static const bool value                                                 \
        = has_member<                                                       \
            Alias_##member<ambiguate<T, AmbiguitySeed_##member>>            \
            , Alias_##member<AmbiguitySeed_##member>                        \
        >::value;                                                           \
};                                                                          \
                                                                            \
template<typename T>                                                        \
auto Get_##member(T &o)                                                     \
{                                                                           \
  if constexpr(has_member_##member<T>::value)                               \
  {                                                                         \
    return o.member;                                                        \
  }                                                                         \
  else                                                                      \
  {                                                                         \
    return 0;                                                               \
  }                                                                         \
}

#define HAS_MEMBER(Class, Member) \
has_member_##Member<Class>::value;

#define GET_MEMBER(Instance, Member) \
Get_##Member(Instance);


#endif // __reflection_h__
