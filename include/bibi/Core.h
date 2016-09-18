#pragma once

#include "TypeTraits.h"

namespace bibi
{

template<typename T>
concept bool EqualityComparable =
	requires(const T a, const T b) { {a == b} -> bool; };

template<typename T>
concept bool LessThanComparable =
	requires(const T a, const T b)
	{
		{a < b} -> bool;
	};

template<typename T, typename R, typename... Args>
concept bool Callable = 
	requires(T t, Args... args)
	{
		{t(args...)} -> R;
	};

template<typename T, typename... Args>
concept bool FunctionObject =
	Object<T> &&
	requires(T t, Args... args)
	{
		{t(args...)};
	};

template<typename T>
concept bool Swappable =
	requires(T t, T u) { {std::swap(t, u)}; } ||
	requires(T t, T u) { {swap(t, u)}; };

template<typename T>
concept bool NullablePointer =
	EqualityComparable<T> &&
	DefaultConstructible<T> &&
	CopyConstructible<T> &&
	CopyAssignable<T> &&
	Destructible<T> &&
	requires(T p, T q, nullptr_t np)
	{
		{p = np};
		{p = np};
		{p != q};
		{p == np};
		{np == p};
		{p != np};
		{np != p};
	};

template<typename T, typename Key>
concept bool Hash =
	FunctionObject<T> &&
	CopyConstructible<T> &&
	Destructible<T> &&
	requires(T h, Key k)
	{
		{h(k)} -> size_t;
	};

template<typename T, typename U>
concept bool Predicate = Callable<T, bool, U>;

template<typename T, typename U>
concept bool BinaryPredicate = Callable<T, bool, U, U>;

template<typename T, typename U>
concept bool Compare = Callable<T, bool, U, U>;


template<typename T>
concept bool Numeric =
	isSame<typename std::decay_t<T>, T>() &&
	Trivial<T> &&
	!Abstract<T>;

}
