#pragma once

#include "Core.h"
#include "Iterator.h"
#include "Random.h"
#include <algorithm>

namespace bibi
{

// Non-modifying sequence operations

auto all_of(InputIterator first, InputIterator last, Predicate<decltype(*first)> p)
{
	return std::all_of(first, last, p);
}

auto any_of(InputIterator first, InputIterator last, Predicate<decltype(*first)> p)
{
	return std::any_of(first, last, p);
}

auto none_of(InputIterator first, InputIterator last, Predicate<decltype(*first)> p)
{
	return std::none_of(first, last, p);
}

auto for_each(InputIterator first, InputIterator last, Callable<void, decltype(*first)> f)     
{
	return std::for_each(first, last, f);
}

auto count(InputIterator first, InputIterator last, const auto &value)                      
{
	return std::count(first, last, value);
}

auto count_if(InputIterator first, InputIterator last, Predicate<decltype(*first)> p)
{
	return std::count_if(first, last, p);
}

template<InputIterator A, InputIterator B>
auto mismatch(A first, A last, B first2)                   
{
	return std::mismatch(first, last, first2); 
}

template<InputIterator A, InputIterator B>
auto mismatch(A first, A last, B first2, Callable<bool, decltype(*first), decltype(*first2)> p)
{
	return std::mismatch(first, last, p);
}

template<InputIterator A, InputIterator B>
auto equal(A first, A last, B first2)
{
	return std::equal(first, last, first2);
}

template<InputIterator A, InputIterator B>
auto equal(A first, A last, B first2, Callable<bool, decltype(*first), decltype(*first2)> p)
{
	return std::equal(first, last, p);
}

template<InputIterator A, InputIterator B>
auto equal(A first, A last, B first2, B last2)
{
	return std::equal(first, last, first2, last2);
}

template<InputIterator A, InputIterator B>
auto equal(A first, A last, B first2, B last2, Callable<bool, decltype(*first), decltype(*first2)> p)
{
	return std::equal(first, last, first2, last2, p);
}

template<InputIterator A, InputIterator B>
auto find(InputIterator first, InputIterator last, const auto &value)
{
	return std::find(first, last, value);
}

auto find_if(InputIterator first, InputIterator last, Predicate<decltype(*first)> p)
{
	return std::find_if(first, last, p);
}

auto find_if_not(InputIterator first, InputIterator last, Predicate<decltype(*first)> p)
{
	return std::find_if_not(first, last, p);
}

template<InputIterator A, ForwardIterator B>
auto find_end(A first, A last, B s_first, B s_last)
{
	return std::find_end(first, last, s_first, s_last);
}

template<InputIterator A, ForwardIterator B>
auto find_end(A first, A last, B s_first, B s_last, Callable<bool, decltype(*first), decltype(*s_first)> p)
{
	return std::find_end(first, last, s_first, s_last, p);
}

template<InputIterator A, ForwardIterator B>
auto find_first_of(A first, A last, B s_first, B s_last)
{
	return std::find_first_of(first, last, s_first, s_last);
}

template<InputIterator A, ForwardIterator B>
auto find_first_of(A first, A last, B s_first, B s_last, Callable<bool, decltype(*first), decltype(*s_first)> p)
{
	return std::find_first_of(first, last, s_first, s_last, p);
}

auto adjacent_find(ForwardIterator first, ForwardIterator last)
{
	return std::adjacent_find(first, last);
}

auto adjacent_find(ForwardIterator first, ForwardIterator last, Predicate<decltype(*first)> p)
{
	return std::adjacent_find(first, last, p);
}

template<ForwardIterator A, ForwardIterator B>
auto search(A first, A last, B s_first, B s_last)
{
	return std::search(first, last, s_first, s_last);
}

template<ForwardIterator A, ForwardIterator B>
auto search(A first, A last, B s_first, B s_last, Callable<bool, decltype(*first), decltype(*s_first)> p)
{
	return std::search(first, last, s_first, s_last);
}

auto search_n(ForwardIterator first, ForwardIterator last, auto count, const auto &value)
{
	return std::search_n(first, last, count, value);
}

auto search_n(ForwardIterator first, ForwardIterator last, auto count, const auto &value, Callable<bool, decltype(*first), decltype(*first)> p)
{
	return std::search_n(first, last, count, value);
}

// Modifying sequence operations

auto copy(InputIterator first, InputIterator last, OutputIterator d_first)
{
	return std::copy(first, last, d_first);
}

auto copy_if(InputIterator first, InputIterator last, OutputIterator d_first, Predicate<decltype(*first)> p)
{
	return std::copy_if(first, last, d_first, p);
}

auto copy_n(InputIterator first, auto count, OutputIterator result)
{
	return std::copy_n(first, count, result);
}

template<BidirectionalIterator A, BidirectionalIterator B>
auto copy_backward(A first, A last, B d_last)
{
	return std::copy_backward(first, last, d_last);
}

auto move(InputIterator first, InputIterator last, OutputIterator d_first)
{
	return std::move(first, last, d_first);
}

template<BidirectionalIterator A, BidirectionalIterator B>
auto move_backward(A first, A last, B d_first)
{
	return std::move_backward(first, last, d_first);
}

auto fill(ForwardIterator first, ForwardIterator last, const auto &value)
{
	std::fill(first, last, value);
}

auto fill_n(ForwardIterator first, auto count, const auto &value)
{
	std::fill_n(first, count, value);
}

template<InputIterator A, OutputIterator Out>
auto transform(A first, A last, Out d_first, Callable<std::decay_t<decltype(*d_first)>, decltype(*first)> unary_op)
{
	return std::transform(first, last, d_first, unary_op);
}

template<InputIterator A, InputIterator B, OutputIterator Out>
auto transform(A first, A last, B first2, B last2, Out d_first, Callable<std::decay_t<decltype(*d_first)>, decltype(*first), decltype(*first2)> binary_op)
{
	return std::transform(first, last, first2, last2, d_first, binary_op);
}

auto generate(ForwardIterator first, ForwardIterator last, Callable<std::decay_t<decltype(*first)>> g)
{
	std::generate(first, last, g);
}

auto generate_n(OutputIterator first, auto count, Callable<std::decay_t<decltype(*first)>> g)
{
	return std::generate_n(first, count, g);
}

auto remove(ForwardIterator first, ForwardIterator last, const auto &value)
{
	return std::remove(first, last, value);
}

auto remove_if(ForwardIterator first, ForwardIterator last, Predicate<decltype(*first)> p)
{
	return std::remove(first, last, p);
}

auto remove_copy(InputIterator first, InputIterator last, OutputIterator d_first, const auto &value)
{
	return std::remove_copy(first, last, d_first, value);
}

auto remove_copy_if(InputIterator first, InputIterator last, OutputIterator d_first, Predicate<decltype(*first)> p)
{
	return std::remove_copy_if(first, last, d_first, p);
}

template<ForwardIterator A, typename T>
auto replace(A first, A last, const T &value, const T &new_value)
{
	return std::replace(first, last, value, new_value);
}

auto replace_if(ForwardIterator first, ForwardIterator last, Predicate<decltype(*first)> p, const auto &new_value)
{
	return std::replace_if(first, last, p, new_value);
}

template<InputIterator A, OutputIterator B, typename T>
auto replace_copy(A first, A last, B d_first, const T &value)
{
	return std::replace_copy(first, last, d_first, value);
}

auto replace_copy_if(InputIterator first, InputIterator last, OutputIterator d_first, Predicate<decltype(*first)> p, const auto &value)
{
	return std::replace_copy_if(first, last, d_first, p, value);
}

template<typename T>
auto swap(T &a, T &b)
{
	std::swap(a, b);
}

template<typename T, size_t N>
auto swap(T (&a)[N], T (&b)[N])
{
	std::swap(a, b);
}

template<ForwardIterator A, ForwardIterator B>
auto swap_ranges(A first, A last, B first2)
{
	return std::swap_ranges(first, last, first2);
}

template<ForwardIterator A, ForwardIterator B>
auto iter_swap(A a, B b)
{
	std::iter_swap(a, b);
}

auto reverse(BidirectionalIterator first, BidirectionalIterator last)
{
	std::reverse(first, last);
}

auto reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator d_first)
{
	return std::reverse_copy(first, last, d_first);
}

auto rotate(ForwardIterator first, ForwardIterator n_first, ForwardIterator last)
{
	return std::rotate(first, n_first, last);
}

auto rotate_copy(ForwardIterator first, ForwardIterator n_first, ForwardIterator last, OutputIterator d_first)
{
	return std::rotate_copy(first, n_first, last, d_first);
}

auto shuffle(RandomAccessIterator first, RandomAccessIterator last, UniformRandomBitGenerator &&g)
{
	return std::shuffle(first, last, std::forward<UniformRandomBitGenerator>(g));
}

auto unique(ForwardIterator first, ForwardIterator last)
{
	return std::unique(first, last);
}

auto unique(ForwardIterator first, ForwardIterator last, Callable<bool, decltype(*first), decltype(*first)> p)
{
	return std::unique(first, last, p);
}

auto unique_copy(InputIterator first, InputIterator last, OutputIterator d_first)
{
	return std::unique_copy(first, last, d_first);
}

auto unique_copy(InputIterator first, InputIterator last, OutputIterator d_first, Callable<bool, decltype(*first), decltype(*first)> p)
{
	return std::unique_copy(first, last, d_first, p);
}

// Partitioning operations

auto is_partitioned(InputIterator first, InputIterator last, Predicate<decltype(*first)> p)
{
	return std::is_partitioned(first, last, p);
}

auto partition(ForwardIterator first, ForwardIterator last, Predicate<decltype(*first)> p)
{
	return std::partition(first, last, p);
}

template<InputIterator A, OutputIterator B, OutputIterator C>
auto partition_copy(A first, A last, B d_first, C d_first_false, Predicate<decltype(*first)> p)
{
	return std::partition_copy(first, last, d_first, d_first_false, p);
}

auto stable_partition(BidirectionalIterator first, BidirectionalIterator last, Predicate<decltype(*first)> p)
{
	return std::stable_partition(first, last, p);
}

auto partition_point(ForwardIterator first, ForwardIterator last, Predicate<decltype(*first)> p)
{
	return std::partition_point(first, last, p);
}

// Sorting operations

auto is_sorted(ForwardIterator first, ForwardIterator last)
{
	return std::is_sorted(first, last);
}

auto is_sorted(ForwardIterator first, ForwardIterator last, Compare<decltype(*first)> comp)
{
	return std::is_sorted(first, last, comp);
}

auto is_sorted_until(ForwardIterator first, ForwardIterator last)
{
	return std::is_sorted_until(first, last);
}

auto is_sorted_until(ForwardIterator first, ForwardIterator last, Compare<decltype(*first)> comp)
{
	return std::is_sorted_until(first, last);
}

auto sort(RandomAccessIterator first, RandomAccessIterator last)
{
	std::sort(first, last);
}

auto sort(RandomAccessIterator first, RandomAccessIterator last, Compare<decltype(*first)> comp)
{
	std::sort(first, last, comp);
}
#if 0
auto partial_sort()
{
	return std::partial_sort(first, last, );
}

auto partial_sort_copy()
{
	return std::partial_sort_copy(first, last, );
}

auto stable_sort()
{
	return std::stable_sort(first, last, );
}

auto nth_element()
{
	return std::nth_element(first, last, );
}

// Binary search operations (on sorted ranges)

auto lower_bound
{
	return std::lower_bound(first, last, );
}

auto upper_bound
{
	return std::upper_bound(first, last, );
}

auto binary_search
{
	return std::binary_search(first, last, );
}

auto equal_range
{
	return std::equal_range(first, last, );
}
 
// Set operations (on sorted ranges)

auto merge()
{
	return std::merge(first, last, );
}

auto inplace_merge()
{
	return std::inplace_merge(first, last, );
}

auto includes()
{
	return std::includes(first, last, );
}

auto set_difference()
{
	return std::set_difference(first, last, );
}

auto set_intersection()
{
	return std::set_intersection(first, last, );
}

auto set_symmetric_difference()
{
	return std::set_symmetric_difference(first, last, );
}

auto set_union()
{
	return std::set_union(first, last, );
}

// Heap operations

auto is_heap()
{
	return std::is_heap(first, last, );
}

auto is_heap_until()
{
	return std::is_heap_until(first, last, );
}

auto make_heap()
{
	return std::make_heap(first, last, );
}

auto push_heap()
{
	return std::push_heap(first, last, );
}

auto pop_heap()
{
	return std::pop_heap(first, last, );
}

auto sort_heap()
{
	return std::sort_heap(first, last, );
}

// Minimum/maximum operations

auto max()
{
	return std::max(first, last, );
}

auto max_element()
{
	return std::max_element(first, last, );
}

auto min()
{
	return std::min(first, last, );
}

auto min_element()
{
	return std::min_element(first, last, );
}

auto minmax()
{
	return std::minmax(first, last, );
}

auto minmax_element()
{
	return std::minmax_element(first, last, );
}

auto lexicographical_compare()
{
	return std::lexicographical_compare(first, last, );
}

auto is_permutation()
{
	return std::is_permutation(first, last, );
}

auto next_permutation()
{
	return std::next_permutation(first, last, );
}

auto prev_permutation()
{
	return std::prev_permutation(first, last, );
}
#endif

}