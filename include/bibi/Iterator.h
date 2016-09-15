#pragma once

#include "Core.h"
#include <iterator>

namespace bibi
{

template<typename It>
concept bool Iterator =
	CopyConstructible<It> &&
	CopyAssignable<It> &&
	Destructible<It> &&
	Swappable<It> &&
	requires(It r)
	{
		{*r} -> typename std::iterator_traits<It>::reference;
		{++r} -> It &;
	};
	
template<typename It>
concept bool InputIterator =
	Iterator<It> &&
	EqualityComparable<It> &&
	requires(It i, It j)
	{
		{i != j} -> bool;
		{*i} -> typename std::iterator_traits<It>::reference;
		//{i->m};
		{*i++} -> typename std::iterator_traits<It>::value_type;
	};

template<typename It>
concept bool OutputIterator =
	Iterator<It> &&
	requires(It r)//, Writable o, Writable a)
	{
		//{*r = o};
		{++r} -> It &;
		{r++} -> It;
		//{*r++ = o};
	};
	
template<typename It>
concept bool ForwardIterator =
	InputIterator<It> &&
	DefaultConstructible<It> &&
	(OutputIterator<It> && !Const<typename std::iterator_traits<It>::value_type> ||
	!OutputIterator<It> &&  Const<typename std::iterator_traits<It>::value_type>) &&
	requires(It i)
	{
		{i++} -> It;
		{*i++} -> typename std::iterator_traits<It>::reference;
	};
	
	
template<typename It>
concept bool BidirectionalIterator =
	ForwardIterator<It> &&
	requires(It a)
	{
		{--a} -> It &;
		{a--} -> It;
		{*a--} -> typename std::iterator_traits<It>::reference;
	};
	
template<typename It>
concept bool RandomAccessIterator = 
	BidirectionalIterator<It> &&
	requires(	It i,
				It a,
				It b,
				It &r,
				typename std::iterator_traits<It>::difference_type n)
	{
		{r + n}  -> It;
		{a + n}  -> It;
		{n + a}  -> It;

		{r -= n} -> It &;
		{i - n}  -> It;
		{b - a}  -> typename std::iterator_traits<It>::difference_type;
		{i[n]}   -> typename std::iterator_traits<It>::reference;
	};

template<typename T>
concept bool Mutable = ForwardIterator<T> && OutputIterator<T>;

template<typename T>
concept bool ValueSwappable = 
	Iterator<T> &&
	requires(T t, T u) { {std::swap(*t, *u)}; } || 
	requires(T t, T u) { {swap(*t, *u) }; };

}
