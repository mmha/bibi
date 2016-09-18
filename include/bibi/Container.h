#pragma once

#include "Allocator.h"
#include "Core.h"
#include "Iterator.h"

namespace bibi
{
	template<typename C>
	concept bool Container =
		DefaultConstructible<C> &&
		Swappable<C> &&
		CopyConstructible<C> &&
		CopyAssignable<C> &&
		requires(C a, C b, const C constant)
		{
			typename C::value_type;
			typename C::reference;
			typename C::const_reference;
			typename C::iterator;
			typename C::const_iterator;
			typename C::difference_type;
			typename C::size_type;

			{(&a)->~C()} -> void;

			{a.begin()} -> typename C::iterator;
			{constant.begin()} -> typename C::const_iterator;
			{constant.cbegin()} -> typename C::const_iterator;
			{a.end()} -> typename C::iterator;
			{constant.end()} -> typename C::const_iterator;
			{constant.cend()} -> typename C::const_iterator;

			{a.size()} -> typename C::size_type;
			{a.max_size()} -> typename C::size_type;
			{a.empty()} -> bool;

			/*
			if(EqualityComparable<typename C::value_type>)
			{
				EqualityComparable<C> &&
				{a != b}	-> bool;
			};
			*/
		};

	template<typename C>
	concept bool ReversibleContainer =
		Container<C> &&
		BidirectionalIterator<typename C::iterator> &&
		BidirectionalIterator<typename C::const_iterator> &&
		requires(C a)
		{
			typename C::reverse_iterator;
			typename C::const_reverse_iterator;

			{a.rbegin()} -> typename C::reverse_iterator;
			{a.rend()} -> typename C::reverse_iterator;
			{a.crbegin()}	-> typename C::const_reverse_iterator;
			{a.crend()} -> typename C::const_reverse_iterator;
		};

	template<typename C>
	concept bool AllocatorAwareContainer = 
		Container<C> &&
		isSame<typename C::allocator_type::value_type, typename C::value_type>() &&
		DefaultConstructible<typename C::allocator_type> &&
		CopyConstructible<typename C::value_type> &&
		requires(C a,
		         typename C::allocator_type m,
		         C t)
		{
			{a.get_allocator()} -> Allocator;
			{a.get_allocator()} -> typename C::allocator_type;
			{C(m)} -> C;
			{C(t, m)} -> C;
		};
}