=========
Algorithm
=========

The Algorithm header contains thin wrappers around all STL algorithms contained in :code:`<algorithm>`. The signatures are the same, but the concept requirements are checked. This will usually get you better error messages when you are writing template-heavy code using the STL, while also being C++11/14 compliant simply by removing the bibi dependency and switching from the :code:`bibi` namespace to :code:`std`.

.. code-block:: c++
	
	#ifdef __cpp_concepts
	#include <bibi/Algorithm.h>
	namespace algo = bibi;
	#else
	#include <algorithm>
	namespace algo = std;
	#endif

	#include <iostream>
	#include <iterator>
	#include <vector>

	auto main() -> int
	{
		auto list = std::vector<int>{4, 3, 2};
		algo::sort(list.begin(), list.end());
		algo::copy(list.begin(), list.end(), std::ostream_iterator<int>(std::cout, " "));
	}

Since there is no difference between the signatures, this page does not contain any function prototypes. Use the C++ reference of your choice for that.

Note that this header does not yet implement the Parallelism TS and does not implement :code:`random_shuffle`.