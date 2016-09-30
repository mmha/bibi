#pragma once

#include <cstddef>
#include <type_traits>
#include <experimental/type_traits>

namespace bibi
{

// Primary type categories
template<typename T> concept bool Array = std::is_array<T>::value;
template<typename T> concept bool Enum = std::is_enum<T>::value;
template<typename T> concept bool FloatingPoint = std::is_floating_point<T>::value;
template<typename T> concept bool Function = std::is_function<T>::value;
template<typename T> concept bool Integral = std::is_integral<T>::value;
template<typename T> concept bool LvalueReference = std::is_lvalue_reference<T>::value;
template<typename T> concept bool MemberFunctionPointer = std::is_member_function_pointer<T>::value;
template<typename T> concept bool MemberObjectPointer = std::is_member_object_pointer<T>::value;
template<typename T> concept bool NullPointer = std::is_null_pointer<T>::value;
template<typename T> concept bool Pointer = std::is_pointer<T>::value;
template<typename T> concept bool RvalueReference = std::is_rvalue_reference<T>::value;
template<typename T> concept bool Union = std::is_union<T>::value;
template<typename T> concept bool Void = std::is_void<T>::value;

// Composite type categories
template<typename T> concept bool Arithmetic = std::is_arithmetic<T>::value;
template<typename T> concept bool Compound = std::is_compound<T>::value;
template<typename T> concept bool Fundamental = std::is_fundamental<T>::value;
template<typename T> concept bool MemberPointer = std::is_member_pointer<T>::value;
template<typename T> concept bool Object = std::is_object<T>::value;
template<typename T> concept bool Reference = std::is_reference<T>::value;
template<typename T> concept bool Scalar = std::is_scalar<T>::value;

// Type properties
template<typename T> concept bool Abstract = std::is_abstract<T>::value;
template<typename T, typename U> concept bool Assignable = std::is_assignable<T, U>::value;
template<typename T> concept bool Const = std::is_const<T>::value;
//template<typename Fn, typename... ArgTypes, typename R> concept bool Callable = std::experimental::is_callable_v<Fn(ArgTypes...), R>;
template<typename T> concept bool Constructible = std::is_constructible<T>::value;
template<typename T> concept bool CopyAssignable = std::is_copy_assignable<T>::value;
template<typename T> concept bool CopyConstructible = std::is_copy_constructible<T>::value;
template<typename T> concept bool DefaultConstructible = std::is_default_constructible<T>::value;
template<typename T> concept bool Destructible = std::is_destructible<T>::value;
template<typename T> concept bool Empty = std::is_empty<T>::value;
//template<typename T> concept bool HasUniqueObjectRepresentation = std::experimental::has_unique_object_representations_v<T>;
template<typename T> [[deprecated("Deprecated in C++17")]] concept bool LiteralType = std::is_literal_type<T>::value;
template<typename T> concept bool MoveAssignable = std::is_move_assignable<T>::value;
template<typename T> concept bool MoveConstructible = std::is_move_constructible<T>::value;
template<typename T, typename U> concept bool NothrowAssignable = std::is_nothrow_assignable<T, U>::value;
//template<typename Fn, typename... ArgTypes, typename R> concept bool NothrowCallable = std::experimental::is_nothrow_callable_v<Fn(ArgTypes...), R>;
template<typename T> concept bool NothrowConstructible = std::is_nothrow_constructible<T>::value;
template<typename T> concept bool NothrowCopyAssignable = std::is_nothrow_copy_assignable<T>::value;
template<typename T> concept bool NothrowCopyConstructible = std::is_nothrow_copy_constructible<T>::value;
template<typename T> concept bool NothrowDefaultConstructible = std::is_nothrow_default_constructible<T>::value;
template<typename T> concept bool NothrowDestructible = std::is_nothrow_destructible<T>::value;
template<typename T> concept bool NothrowMoveAssignable = std::is_nothrow_move_assignable<T>::value;
template<typename T> concept bool NothrowMoveConstructible = std::is_nothrow_move_constructible<T>::value;
//template<typename T> concept bool NothrowSwappable = std::is_nothrow_swappable<T>::value;
template<typename T> concept bool Pod = std::is_pod<T>::value;
template<typename T> concept bool Polymorphic = std::is_polymorphic<T>::value;
template<typename T> concept bool Signed = std::is_signed<T>::value;
template<typename T> concept bool StandardLayout = std::is_standard_layout<T>::value;
//template<typename T> concept bool Swappable = std::is_swappable<T>::value;
template<typename T> concept bool Trivial = std::is_trivial<T>::value;
template<typename T, typename U> concept bool TriviallyAssignable = std::is_trivially_assignable<T, U>::value;
template<typename T> concept bool TriviallyConstructible = std::is_trivially_constructible<T>::value;
template<typename T> concept bool TriviallyCopyable = std::is_trivially_copyable<T>::value;
template<typename T> concept bool TriviallyCopyAssignable = std::is_trivially_copy_assignable<T>::value;
template<typename T> concept bool TriviallyCopyConstructible = std::is_trivially_copy_constructible<T>::value;
template<typename T> concept bool TriviallyDefaultConstructible = std::is_trivially_default_constructible<T>::value;
template<typename T> concept bool TriviallyDestructible = std::is_trivially_destructible<T>::value;
template<typename T> concept bool TriviallyMoveAssignable = std::is_trivially_move_assignable<T>::value;
template<typename T> concept bool TriviallyMoveConstructible = std::is_trivially_move_constructible<T>::value;
template<typename T> concept bool Unsigned = std::is_unsigned<T>::value;
template<typename T> concept bool HasVirtualDestructor = std::has_virtual_destructor<T>::value;
template<typename T> concept bool Volatile = std::is_volatile<T>::value;

// Property queries
template<typename T> constexpr auto alignmentOf() -> size_t { return std::alignment_of<T>::value; }
template<typename T> constexpr auto extent() -> size_t { return std::extent<T>::value; }
template<typename T> constexpr auto rank() -> size_t { return std::rank<T>::value; }
constexpr auto alignmentOf(auto &&a) -> size_t { return alignmentOf<decltype(a)>(); }
constexpr auto extent(auto &&a) -> size_t { return extent<decltype(a)>(); }
constexpr auto rank(auto &&a) -> size_t { return rank<decltype(a)>(); }

// Type relationships
template<typename T, typename U> constexpr auto isBaseOf() -> bool { return std::is_base_of<T, U>::value; }
template<typename T, typename U> constexpr auto isConvertible() -> bool { return std::is_convertible<T, U>::value; }
template<typename T, typename U> constexpr auto isSame() -> bool { return std::is_same<T, U>::value; }
constexpr auto isBaseOf(auto &&a, auto &&b) -> bool { return isBaseOf<decltype(a), decltype(b)>(); }
constexpr auto isConvertible(auto &&a, auto &&b) -> bool { return isConvertible<decltype(a), decltype(b)>(); }
constexpr auto isSame(auto &&a, auto &&b) -> bool { return isSame<decltype(a), decltype(b)>(); }
template<typename T, typename U> concept bool BaseOf = std::is_base_of<T, U>::value;
template<typename T, typename U> concept bool Convertible = std::is_convertible<T, U>::value;
template<typename T, typename U> concept bool Same = std::is_same<T, U>::value;
//template<typename T, typename U> constexpr auto swappableWith() -> bool { return std::is_swappable_with<T, U>::value; }
//template<typename T, typename U> constexpr auto nothrowSwappableWith() -> bool { return std::is_nothrow_swappable_with<T, U>::value; }
//constexpr auto swappableWith(auto &&a, auto &&b) -> bool { return swappableWith<decltype(a), decltype(b)>(); }
//constexpr auto nothrowSwappableWith(auto &&a, auto &&b) -> bool { return nothrowSwappableWith<decltype(a), decltype(b)>(); }


template<typename T, template<typename...> typename Base>
struct is_specialization_of : public std::false_type {};
template<template<typename...> typename Base, typename... Args>
struct is_specialization_of<Base<Args...>, Base> : public std::true_type {};

template<typename Var, typename T, template<Var...> typename Base>
struct is_variable_specialization_of : public std::false_type {};
template<typename Var, template<Var...> typename Base, Var... Args>
struct is_variable_specialization_of<Var, Base<Args...>, Base> : public std::true_type {};

template<typename T, template<typename...> typename Base> constexpr bool is_specialization_of_v = is_specialization_of<T, Base>::value;
template<typename T, template<typename...> typename Base> constexpr auto isSpecializationOf() -> bool { return is_specialization_of_v<T, Base>; }

template<typename Var, typename T, template<Var...> typename Base> constexpr bool is_variable_specialization_of_v = is_variable_specialization_of<Var, T, Base>::value;
template<typename Var, typename T, template<Var...> typename Base> constexpr auto isVariableSpecializationOf() -> bool { return is_variable_specialization_of_v<Var, T, Base>; }


template <typename T>
constexpr std::add_const_t<T>& as_const(T& t) noexcept
{
    return t;
}

}
