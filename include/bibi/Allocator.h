#pragma once

#include "Core.h"
#include <memory>

namespace bibi
{
	template<typename A>
	concept bool Allocator =
		EqualityComparable<A> &&
		CopyConstructible<A> &&
		CopyAssignable<A> &&
		MoveConstructible<A> &&
		MoveAssignable<A> &&
		requires(A a, A a1, A a2,
		         typename std::allocator_traits<A>::size_type n,
		         typename std::allocator_traits<A>::pointer ptr,
		         typename std::allocator_traits<A>::const_pointer cptr,
		         typename std::allocator_traits<A>::void_pointer vptr,
		         typename std::allocator_traits<A>::const_void_pointer cvptr)
		{
			typename A::value_type;
			{*ptr} -> typename A::value_type;
			{*cptr} -> std::add_const_t<typename A::value_type>;
			{a.allocate(n)} -> typename A::pointer;
			{a.deallocate(ptr, n)};
			{a1 != a2} -> bool;
		};
}
