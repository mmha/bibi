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
			{a.crbegin()} -> typename C::const_reverse_iterator;
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

	//TODO allocators, emplace_back(args...)
	template<typename X>
	concept bool SequenceContainer =
		Container<X> &&
		requires(
			X && a,
			typename X::const_iterator p,
			typename X::const_iterator q,
			typename X::const_iterator q1,
			typename X::const_iterator q2,
			typename X::value_type *i, // Should be InputIterator
			typename X::value_type *j, // Should be InputIterator
			std::initializer_list<typename X::value_type> il,
			typename X::size_type n,
			const typename X::value_type &&t,
			typename X::value_type &&rv)
		{
			{X(n, t)};
			{X(i, j)};
			{X(i, j)};
			{X(il)};
			{a = il} -> X &;
			//{a.emplace(p,args)} -> typename X::iterator;
			{a.insert(p,t)} -> typename X::iterator;
			{a.insert(p,rv)} -> typename X::iterator;
			{a.insert(p,n,t)} -> typename X::iterator;
			{a.insert(p,i,j)} -> typename X::iterator;
			{a.insert(p, il)} -> typename X::iterator;
			{a.erase(q)} -> typename X::iterator;
			{a.erase(q1,q2)} -> typename X::iterator;
			{a.clear()} -> void;
			{a.assign(i,j)} -> void;
			{a.assign(il)} -> void;
			{a.assign(n,t)} -> void;
			{a.front()} -> typename X::const_reference;
		};

	template<typename X>
	concept bool AssociativeContainer =
		Container<X> &&
		BinaryPredicate<typename X::value_compare, typename X::value_type> &&
		requires(
			X a,
			X a2, // should be T
			const X b,
			typename X::value_type i,
			typename X::value_type j,
			typename X::const_iterator p,
			typename X::const_iterator q,
			typename X::iterator r,
			typename X::const_iterator q1,
			typename X::const_iterator q2,
			std::initializer_list<typename X::value_type> il,
			typename X::value_type t,
			typename X::key_type k,
			typename X::key_compare c)
		{
			{X(c)};
			{X(i, j, c)};
			{X(i, j)};
			{X(il)};
			{a = il} -> X &;
			{a.key_comp()} -> typename X::key_compare;
			{a.value_comp()} -> typename X::value_compare;				
		};

	template<typename X>
	concept bool UnorderedAssociativeContainer =
		AllocatorAwareContainer<X> &&
		Hash<typename X::hasher, typename X::key_type> &&
		BinaryPredicate<typename X::key_equal, typename X::key_type> &&
		requires(
			X a,
			const X b,
			const X *i,
			const X *j,
			typename X::const_iterator p,
			typename X::const_iterator q2,
			typename X::const_iterator q,
			typename X::const_iterator q1,
			std::initializer_list<typename X::value_type> il,
			typename X::value_type t,
			typename X::key_type k,
			typename X::hasher hf,
			typename X::key_equal eq,
			typename X::size_type n,
			float z)
		{
			typename X::mapped_type;
			typename X::local_iterator;
			typename X::const_local_iterator;

			{X(n,hf,eq)};
			{X(n,hf)};
			{X(n,hf)};
			{X(i,j,n,hf,eq)};
			{X(i,j,n,hf)};
			{X(i,j,n)};
			{X(i,j)};
			{X(il)};
			{X(il,n)};
			{X(il,n,hf)};
			{X(il,n,hf,eq)};
			{X(b)};
			{a = b} -> X &;
			{a = il} -> X &;
		};
}
