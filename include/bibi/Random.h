#pragma once

#include "Core.h"
#include "Iterator.h"
#include <random>

namespace bibi
{
	template<typename S>
	concept bool SeedSequence = 
		Unsigned<typename S::result_type> &&
		(sizeof(typename S::result_type) >= 4) &&
		DefaultConstructible<S> &&
		requires(
			const uint32_t *ib, // Should be InputIterator, but gcc crashes on that
			const uint32_t *ie, // Should be InputIterator, but gcc crashes on that
			uint32_t *rb, // Should be RandomAccessIterators, but gcc crashes on that
			uint32_t *re, // Should be RandomAccessIterators, but gcc crashes on that
			std::initializer_list<typename S::result_type> il,
			S q,
			const S r,
			int16_t *ob) // Should be OutputIterator, but gcc crashes on that
		{
			{S(ib, ie)};
			{S(il)};
			{q.generate(rb,re)} -> void;
			{r.size()} -> size_t;
			{r.param(ob)} -> void;
		};

	template<typename G>
	concept bool UniformRandomBitGenerator =
		Unsigned<typename G::result_type> &&
		requires(G g)
		{
			{G::min()} -> typename G::result_type;
			{G::max()} -> typename G::result_type;
			{g()} -> typename G::result_type;
		};

	template<typename E>
	concept bool RandomNumberEngine =
		UniformRandomBitGenerator<E> &&
		DefaultConstructible<E> &&
		CopyConstructible<E> &&
		EqualityComparable<E> &&
		requires(E e,
			E &v,
			const E x,
			const E y,
			typename E::result_type s,
			std::seed_seq q, // Should be SeedSequence, but gcc crashes on that
			unsigned long long z,
			std::ostream os,
			std::istream is)
		{
			{E(x)};
			{E(s)};
			{E(q)};
			{e.seed()} -> void;
			{e.seed(s)} -> void;
			{e.seed(q)} -> void;
			{e()} -> typename E::result_type;
			{e.discard(z)} -> void;
			{x != y} -> bool;
			{os << x} -> std::ostream &;
			{is >> x} -> std::istream &;
		};

	template<typename E>
	concept bool RandomNumberEngineAdaptor =
		RandomNumberEngine<E> &&
		requires(E e)
		{
			{e.base()} -> RandomNumberEngine;
		};

	template<typename D>
	concept bool RandomNumberDistribution =
		DefaultConstructible<D> &&
		CopyConstructible<D> &&
		CopyAssignable<D> &&
		CopyConstructible<typename D::param_type> &&
		CopyAssignable<typename D::param_type> &&
		EqualityComparable<typename D::param_type> &&
		requires(
			D d,
			const D x,
			const D y,
			const typename D::param_type p,
			std::mt19937 g,  // Should be UniformRandomBitGenerator, but gcc crashes on that
			std::mt19937 g1, // Should be UniformRandomBitGenerator, but gcc crashes on that
			std::mt19937 g2, // Should be UniformRandomBitGenerator, but gcc crashes on that
			std::ostream os,
			std::istream is)
		{
			{D(p)};
			{d.reset()} -> void;
			{x.param()} -> typename D::param_type;
			{d.param(p)} -> void;
			{d(g)} -> typename D::result_type;
			{d(g, p)} -> typename D::result_type;
			{x.min()} -> typename D::result_type;
			{x.max()} -> typename D::result_type;
			{x != y} -> bool;
			{os << x} -> std::ostream &;
			{is >> x} -> std::istream &;
		};
}