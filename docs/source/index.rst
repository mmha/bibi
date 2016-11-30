================================
Welcome to bibi's documentation!
================================

bibi is a small header-only library which tries to implement the C++ Standard Library concepts using the Concepts Lite TS Syntax. In contrary to already existing libraries like `origin <https://github.com/asutton/origin>`_, `cmcstl2 <https://github.com/CaseyCarter/cmcstl2>`__ or `range-v3 <https://github.com/ericniebler/range-v3>`_ its goal is to implement the concepts currently defined in the standard, therefore making it easy to introduce concepts to an existing codebase.

------------
Get the Code
------------

The source code repository is avaliable `here <https://github.com/mmha/bibi>`_.

-------------
Quick Example
-------------

.. code-block:: c++

	#include <bibi/Core.h>
	#include <bibi/Algorithm.h>
	#include <iostream>
	#include <vector>

	using namespace bibi;

	auto negate(Signed s) {
		return -s;
	}

	template<typename T>
	concept bool SignedArithmetic = Arithmetic<T> && Signed<T>;

	template<SignedArithmetic... Num>
	auto negativeSum(Num... num) {
		return (negate(num) + ...);
	}

	int main() {
		std::vector<int> lst{10, 42, -3141};
		//  Whoops, our predicate lacks a parameter
		bibi::sort(lst.begin(), lst.end(), [](auto &){ return true; });

		std::cout << negativeSum(1, 2, 3.0, 4ll) << std::endl;
		return 0;
	}

Resulting compiler output (gcc 7.0 trunk):

.. raw:: html

	<div class="highlight"><pre>
	<span style="font-weight:bold;">demo.cpp:</span> In function ‘<span style="font-weight:bold;">int main()</span>’:
	<span style="font-weight:bold;">demo.cpp:23:63:</span> <span style="color:red;font-weight:bold;">error: </span>no matching function for call to ‘<span style="font-weight:bold;">sort(std::vector&lt;int&gt;::iterator, std::vector&lt;int&gt;::iterator, main()::&lt;lambda(auto:67&amp;)&gt;)</span>’
	  bibi::sort(lst.begin(), lst.end(), [](auto &amp;){ return true; }<span style="color:red;font-weight:bold;">)</span>;
	                                                               <span style="color:red;font-weight:bold;">^</span>
	In file included from <span style="font-weight:bold;">demo.cpp:2:0</span>:
	<span style="font-weight:bold;">/usr/include/bibi/Algorithm.h:345:6:</span> <span style="color:teal;font-weight:bold;">note: </span>candidate: template&lt;class auto:63&gt;  requires  RandomAccessIterator&lt;auto:63&gt; auto bibi::sort(auto:63, auto:63)
	 auto <span style="color:teal;font-weight:bold;">sort</span>(RandomAccessIterator first, RandomAccessIterator last)
	      <span style="color:teal;font-weight:bold;">^~~~</span>
	<span style="font-weight:bold;">/usr/include/bibi/Algorithm.h:345:6:</span> <span style="color:teal;font-weight:bold;">note: </span>  template argument deduction/substitution failed:
	<span style="font-weight:bold;">demo.cpp:23:63:</span> <span style="color:teal;font-weight:bold;">note: </span>  candidate expects 2 arguments, 3 provided
	  bibi::sort(lst.begin(), lst.end(), [](auto &amp;){ return true; }<span style="color:teal;font-weight:bold;">)</span>;
	                                                               <span style="color:teal;font-weight:bold;">^</span>
	In file included from <span style="font-weight:bold;">demo.cpp:2:0</span>:
	<span style="font-weight:bold;">/usr/include/bibi/Algorithm.h:350:6:</span> <span style="color:teal;font-weight:bold;">note: </span>candidate: auto bibi::sort(auto:64, auto:64, auto:65) [with auto:64 = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; auto:65 = main()::&lt;lambda(auto:67&amp;)&gt;]
	 auto <span style="color:teal;font-weight:bold;">sort</span>(RandomAccessIterator first, RandomAccessIterator last, Compare&lt;decltype(*first)&gt; comp)
	      <span style="color:teal;font-weight:bold;">^~~~</span>
	<span style="font-weight:bold;">/usr/include/bibi/Algorithm.h:350:6:</span> <span style="color:teal;font-weight:bold;">note: </span>  constraints not satisfied
	In file included from <span style="font-weight:bold;">demo.cpp:1:0</span>:
	<span style="font-weight:bold;">/usr/include/bibi/Core.h:74:14:</span> <span style="color:teal;font-weight:bold;">note: </span>within ‘<span style="font-weight:bold;">template&lt;class T, class U&gt; concept const bool bibi::Compare&lt;T, U&gt; [with T = main()::&lt;lambda(auto:67&amp;)&gt;; U = int&amp;]</span>’
	 concept bool <span style="color:teal;font-weight:bold;">Compare</span> = Callable&lt;T, bool, U, U&gt;;
	              <span style="color:teal;font-weight:bold;">^~~~~~~</span>
	<span style="font-weight:bold;">/usr/include/bibi/Core.h:20:14:</span> <span style="color:teal;font-weight:bold;">note: </span>within ‘<span style="font-weight:bold;">template&lt;class T, class R, class ... Args&gt; concept const bool bibi::Callable&lt;T, R, Args ...&gt; [with T = main()::&lt;lambda(auto:67&amp;)&gt;; R = bool; Args = {int&amp;, int&amp;}]</span>’
	 concept bool <span style="color:teal;font-weight:bold;">Callable</span> =
	              <span style="color:teal;font-weight:bold;">^~~~~~~~</span>
	<span style="font-weight:bold;">/usr/include/bibi/Core.h:20:14:</span> <span style="color:teal;font-weight:bold;">note: </span>    with ‘<span style="font-weight:bold;">main()::&lt;lambda(auto:67&amp;)&gt; t</span>’
	<span style="font-weight:bold;">/usr/include/bibi/Core.h:20:14:</span> <span style="color:teal;font-weight:bold;">note: </span>    with ‘<span style="font-weight:bold;">int&amp; args#0</span>’
	<span style="font-weight:bold;">/usr/include/bibi/Core.h:20:14:</span> <span style="color:teal;font-weight:bold;">note: </span>    with ‘<span style="font-weight:bold;">int&amp; args#1</span>’
	<span style="font-weight:bold;">/usr/include/bibi/Core.h:20:14:</span> <span style="color:teal;font-weight:bold;">note: </span>the required expression ‘<span style="font-weight:bold;">t(args ...)</span>’ would be ill-formed
	</pre></div>

Comparison with calling std::sort directly:

.. raw:: html

	<div class="highlight"><pre>
	In file included from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algobase.h:71:0</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/char_traits.h:39</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ios:40</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ostream:38</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/iterator:64</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Iterator.h:4</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Algorithm.h:4</span>,
	                 from <span style="font-weight:bold;">demo.cpp:2</span>:
	/usr/include/c++/7.0.0/bits/predefined_ops.h: In instantiation of ‘<span style="font-weight:bold;">constexpr bool __gnu_cxx::__ops::_Iter_comp_iter&lt;_Compare&gt;::operator()(_Iterator1, _Iterator2) [with _Iterator1 = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Iterator2 = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Compare = main()::&lt;lambda(auto:67&amp;)&gt;]</span>’:
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algo.h:1844:14:</span>   required from ‘<span style="font-weight:bold;">void std::__insertion_sort(_RandomAccessIterator, _RandomAccessIterator, _Compare) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Compare = __gnu_cxx::__ops::_Iter_comp_iter&lt;main()::&lt;lambda(auto:67&amp;)&gt; &gt;]</span>’
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algo.h:1882:25:</span>   required from ‘<span style="font-weight:bold;">void std::__final_insertion_sort(_RandomAccessIterator, _RandomAccessIterator, _Compare) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Compare = __gnu_cxx::__ops::_Iter_comp_iter&lt;main()::&lt;lambda(auto:67&amp;)&gt; &gt;]</span>’
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algo.h:1968:31:</span>   required from ‘<span style="font-weight:bold;">void std::__sort(_RandomAccessIterator, _RandomAccessIterator, _Compare) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Compare = __gnu_cxx::__ops::_Iter_comp_iter&lt;main()::&lt;lambda(auto:67&amp;)&gt; &gt;]</span>’
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algo.h:4778:18:</span>   required from ‘<span style="font-weight:bold;">void std::sort(_RAIter, _RAIter, _Compare) [with _RAIter = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Compare = main()::&lt;lambda(auto:67&amp;)&gt;]</span>’
	<span style="font-weight:bold;">demo.cpp:23:62:</span>   required from here
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/predefined_ops.h:123:18:</span> <span style="color:red;font-weight:bold;">error: </span>no match for call to ‘<span style="font-weight:bold;">(main()::&lt;lambda(auto:67&amp;)&gt;) (int&amp;, int&amp;)</span>’
	         { return <span style="color:red;font-weight:bold;">bool(_M_comp(*__it1, *__it2))</span>; }
	                  <span style="color:red;font-weight:bold;">^~~~~~~~~~~~~~~~~~~~~~~~~~~~~</span>
	<span style="font-weight:bold;">demo.cpp:23:45:</span> <span style="color:teal;font-weight:bold;">note: </span>candidate: template&lt;class auto:67&gt; constexpr main()::&lt;lambda(auto:67&amp;)&gt;::operator decltype (((const main()::&lt;lambda(auto:67&amp;)&gt;*)((const main()::&lt;lambda(auto:67&amp;)&gt;* const)0u))-&gt;operator()(static_cast&lt;auto:67&amp;&gt;(&lt;anonymous&gt;))) (*)(auto:67&amp;)() const
	  std::sort(lst.begin(), lst.end(), [](auto &amp;<span style="color:teal;font-weight:bold;">)</span>{ return true; });
	                                             <span style="color:teal;font-weight:bold;">^</span>
	<span style="font-weight:bold;">demo.cpp:23:45:</span> <span style="color:teal;font-weight:bold;">note: </span>  template argument deduction/substitution failed:
	In file included from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algobase.h:71:0</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/char_traits.h:39</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ios:40</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ostream:38</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/iterator:64</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Iterator.h:4</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Algorithm.h:4</span>,
	                 from <span style="font-weight:bold;">demo.cpp:2</span>:
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/predefined_ops.h:123:18:</span> <span style="color:teal;font-weight:bold;">note: </span>  candidate expects 1 argument, 2 provided
	         { return <span style="color:teal;font-weight:bold;">bool(_M_comp(*__it1, *__it2))</span>; }
	                  <span style="color:teal;font-weight:bold;">^~~~~~~~~~~~~~~~~~~~~~~~~~~~~</span>
	<span style="font-weight:bold;">demo.cpp:23:45:</span> <span style="color:teal;font-weight:bold;">note: </span>candidate: template&lt;class auto:67&gt; main()::&lt;lambda(auto:67&amp;)&gt;
	  std::sort(lst.begin(), lst.end(), [](auto &amp;<span style="color:teal;font-weight:bold;">)</span>{ return true; });
	                                             <span style="color:teal;font-weight:bold;">^</span>
	<span style="font-weight:bold;">demo.cpp:23:45:</span> <span style="color:teal;font-weight:bold;">note: </span>  template argument deduction/substitution failed:
	In file included from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algobase.h:71:0</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/char_traits.h:39</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ios:40</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ostream:38</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/iterator:64</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Iterator.h:4</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Algorithm.h:4</span>,
	                 from <span style="font-weight:bold;">demo.cpp:2</span>:
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/predefined_ops.h:123:18:</span> <span style="color:teal;font-weight:bold;">note: </span>  candidate expects 1 argument, 2 provided
	         { return <span style="color:teal;font-weight:bold;">bool(_M_comp(*__it1, *__it2))</span>; }
	                  <span style="color:teal;font-weight:bold;">^~~~~~~~~~~~~~~~~~~~~~~~~~~~~</span>
	/usr/include/c++/7.0.0/bits/predefined_ops.h: In instantiation of ‘<span style="font-weight:bold;">bool __gnu_cxx::__ops::_Iter_comp_val&lt;_Compare&gt;::operator()(_Iterator, _Value&amp;) [with _Iterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Value = int; _Compare = main()::&lt;lambda(auto:67&amp;)&gt;]</span>’:
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_heap.h:129:48:</span>   required from ‘<span style="font-weight:bold;">void std::__push_heap(_RandomAccessIterator, _Distance, _Distance, _Tp, _Compare) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Distance = long int; _Tp = int; _Compare = __gnu_cxx::__ops::_Iter_comp_val&lt;main()::&lt;lambda(auto:67&amp;)&gt; &gt;]</span>’
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_heap.h:230:23:</span>   required from ‘<span style="font-weight:bold;">void std::__adjust_heap(_RandomAccessIterator, _Distance, _Distance, _Tp, _Compare) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Distance = long int; _Tp = int; _Compare = __gnu_cxx::__ops::_Iter_comp_iter&lt;main()::&lt;lambda(auto:67&amp;)&gt; &gt;]</span>’
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_heap.h:335:22:</span>   required from ‘<span style="font-weight:bold;">void std::__make_heap(_RandomAccessIterator, _RandomAccessIterator, _Compare) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Compare = __gnu_cxx::__ops::_Iter_comp_iter&lt;main()::&lt;lambda(auto:67&amp;)&gt; &gt;]</span>’
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algo.h:1669:23:</span>   required from ‘<span style="font-weight:bold;">void std::__heap_select(_RandomAccessIterator, _RandomAccessIterator, _RandomAccessIterator, _Compare) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Compare = __gnu_cxx::__ops::_Iter_comp_iter&lt;main()::&lt;lambda(auto:67&amp;)&gt; &gt;]</span>’
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algo.h:1930:25:</span>   required from ‘<span style="font-weight:bold;">void std::__partial_sort(_RandomAccessIterator, _RandomAccessIterator, _RandomAccessIterator, _Compare) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Compare = __gnu_cxx::__ops::_Iter_comp_iter&lt;main()::&lt;lambda(auto:67&amp;)&gt; &gt;]</span>’
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algo.h:1945:27:</span>   required from ‘<span style="font-weight:bold;">void std::__introsort_loop(_RandomAccessIterator, _RandomAccessIterator, _Size, _Compare) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Size = long int; _Compare = __gnu_cxx::__ops::_Iter_comp_iter&lt;main()::&lt;lambda(auto:67&amp;)&gt; &gt;]</span>’
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algo.h:1965:25:</span>   required from ‘<span style="font-weight:bold;">void std::__sort(_RandomAccessIterator, _RandomAccessIterator, _Compare) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Compare = __gnu_cxx::__ops::_Iter_comp_iter&lt;main()::&lt;lambda(auto:67&amp;)&gt; &gt;]</span>’
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algo.h:4778:18:</span>   required from ‘<span style="font-weight:bold;">void std::sort(_RAIter, _RAIter, _Compare) [with _RAIter = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Compare = main()::&lt;lambda(auto:67&amp;)&gt;]</span>’
	<span style="font-weight:bold;">demo.cpp:23:62:</span>   required from here
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/predefined_ops.h:144:11:</span> <span style="color:red;font-weight:bold;">error: </span>no match for call to ‘<span style="font-weight:bold;">(main()::&lt;lambda(auto:67&amp;)&gt;) (int&amp;, int&amp;)</span>’
	  { return <span style="color:red;font-weight:bold;">bool(_M_comp(*__it, __val))</span>; }
	           <span style="color:red;font-weight:bold;">^~~~~~~~~~~~~~~~~~~~~~~~~~~</span>
	<span style="font-weight:bold;">demo.cpp:23:45:</span> <span style="color:teal;font-weight:bold;">note: </span>candidate: template&lt;class auto:67&gt; constexpr main()::&lt;lambda(auto:67&amp;)&gt;::operator decltype (((const main()::&lt;lambda(auto:67&amp;)&gt;*)((const main()::&lt;lambda(auto:67&amp;)&gt;* const)0u))-&gt;operator()(static_cast&lt;auto:67&amp;&gt;(&lt;anonymous&gt;))) (*)(auto:67&amp;)() const
	  std::sort(lst.begin(), lst.end(), [](auto &amp;<span style="color:teal;font-weight:bold;">)</span>{ return true; });
	                                             <span style="color:teal;font-weight:bold;">^</span>
	<span style="font-weight:bold;">demo.cpp:23:45:</span> <span style="color:teal;font-weight:bold;">note: </span>  template argument deduction/substitution failed:
	In file included from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algobase.h:71:0</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/char_traits.h:39</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ios:40</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ostream:38</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/iterator:64</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Iterator.h:4</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Algorithm.h:4</span>,
	                 from <span style="font-weight:bold;">demo.cpp:2</span>:
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/predefined_ops.h:144:11:</span> <span style="color:teal;font-weight:bold;">note: </span>  candidate expects 1 argument, 2 provided
	  { return <span style="color:teal;font-weight:bold;">bool(_M_comp(*__it, __val))</span>; }
	           <span style="color:teal;font-weight:bold;">^~~~~~~~~~~~~~~~~~~~~~~~~~~</span>
	<span style="font-weight:bold;">demo.cpp:23:45:</span> <span style="color:teal;font-weight:bold;">note: </span>candidate: template&lt;class auto:67&gt; main()::&lt;lambda(auto:67&amp;)&gt;
	  std::sort(lst.begin(), lst.end(), [](auto &amp;<span style="color:teal;font-weight:bold;">)</span>{ return true; });
	                                             <span style="color:teal;font-weight:bold;">^</span>
	<span style="font-weight:bold;">demo.cpp:23:45:</span> <span style="color:teal;font-weight:bold;">note: </span>  template argument deduction/substitution failed:
	In file included from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algobase.h:71:0</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/char_traits.h:39</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ios:40</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ostream:38</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/iterator:64</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Iterator.h:4</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Algorithm.h:4</span>,
	                 from <span style="font-weight:bold;">demo.cpp:2</span>:
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/predefined_ops.h:144:11:</span> <span style="color:teal;font-weight:bold;">note: </span>  candidate expects 1 argument, 2 provided
	  { return <span style="color:teal;font-weight:bold;">bool(_M_comp(*__it, __val))</span>; }
	           <span style="color:teal;font-weight:bold;">^~~~~~~~~~~~~~~~~~~~~~~~~~~</span>
	In file included from <span style="font-weight:bold;">/usr/include/c++/7.0.0/algorithm:62:0</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Algorithm.h:5</span>,
	                 from <span style="font-weight:bold;">demo.cpp:2</span>:
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algo.h:1818:5:</span> <span style="color:purple;font-weight:bold;">warning: </span>‘<span style="font-weight:bold;">void std::__unguarded_linear_insert(_RandomAccessIterator, _Compare) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator&lt;int*, std::vector&lt;int&gt; &gt;; _Compare = __gnu_cxx::__ops::_Val_comp_iter&lt;main()::&lt;lambda(auto:67&amp;)&gt; &gt;]</span>’ used but never defined
	     <span style="color:purple;font-weight:bold;">__unguarded_linear_insert</span>(_RandomAccessIterator __last,
	     <span style="color:purple;font-weight:bold;">^~~~~~~~~~~~~~~~~~~~~~~~~</span>
	In file included from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/stl_algobase.h:71:0</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/char_traits.h:39</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ios:40</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/ostream:38</span>,
	                 from <span style="font-weight:bold;">/usr/include/c++/7.0.0/iterator:64</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Iterator.h:4</span>,
	                 from <span style="font-weight:bold;">/usr/include/bibi/Algorithm.h:4</span>,
	                 from <span style="font-weight:bold;">demo.cpp:2</span>:
	<span style="font-weight:bold;">/usr/include/c++/7.0.0/bits/predefined_ops.h:179:5:</span> <span style="color:purple;font-weight:bold;">warning: </span>‘<span style="font-weight:bold;">__gnu_cxx::__ops::_Val_comp_iter&lt;_Compare&gt; __gnu_cxx::__ops::__val_comp_iter(__gnu_cxx::__ops::_Iter_comp_iter&lt;_Compare&gt;) [with _Compare = main()::&lt;lambda(auto:67&amp;)&gt;]</span>’ used but never defined
	     <span style="color:purple;font-weight:bold;">__val_comp_iter</span>(_Iter_comp_iter&lt;_Compare&gt; __comp)
	     <span style="color:purple;font-weight:bold;">^~~~~~~~~~~~~~~</span>
	</pre></div>

------------
Requirements
------------

* A compiler with support for the Concepts Lite TS (at the time of writing, this only applies to gcc >= 6.1)
* A C++14 compliant standard library
* CMake 3.6 - Older Versions are very likely to work

----------------------
What is mostly working
----------------------
* Allocator (although optional constraints are not implemented)
* Type Traits
* Core Concepts
* Iterator
* Chrono
* Random
* Thread
* The algorithm header
* A very early Boost.GIL implementation

-------------------
What is not working
-------------------
* The numerics header has not been started yet
* Container Concepts are lacking, to say the least
* TimedLockable and SharedTimedMutex are underconstrained (possibly a gcc bug?)
* Some Random Concepts are underconstrined due to a gcc bug (a workaround is possible, but not implemented yet)
* TrivialClock is underconstrained (does not recursively check the constraints)

--------------------------------
What would be nice in the future
--------------------------------
* More tests (a lot more)
* Extending the Library to some Boost Concepts, most notably Boost.graph and Boost.asio
* Extending to the Ranges TS or range-v3

-------------
Documentation
-------------
.. toctree::
	:maxdepth: 2

	getting_started
	Algorithm
	Concepts/Allocator
	Concepts/Chrono
	Concepts/Container
	Concepts/Core
	Concepts/Iterator
	Concepts/Random
	Concepts/Thread
	Concepts/TypeTraits

-------
License
-------
This library is released under the Boost Software License 1.0.
