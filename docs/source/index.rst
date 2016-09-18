================================
Welcome to bibi's documentation!
================================

bibi is a small header-only library which tries to implement the C++ Standard Library concepts using the Concepts Lite TS Syntax. In contrary to already existing libraries like `origin <https://github.com/asutton/origin>`_ or `range-v3 <https://github.com/ericniebler/range-v3>`_ its goal is to implement the concepts currently defined in the standard, therefore making it easy to introduce concepts to an existing codebase.

------------
Get the Code
------------

The source code repository is avaliable `here <https://github.com/mmha/bibi>`_.

-------------
Quick Example
-------------

.. code-block:: c++

	#include <bibi/Core.h>
	#include <iostream>

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
		std::cout << negativeSum(1, 2, 3.0, 4ll) << std::endl;
		return 0;
	}

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

-------------------
What is not working
-------------------
* Not all Container concepts are implemented yet
* TimedLockable and SharedTimedMutex are underconstrained (possibly a gcc bug?)
* Some Random Concepts are underconstrined due to a gcc bug (a workaround is possible, but not implemented yet)
* TrivialClock is underconstrained (does not recursively check the constraints)

--------------------------------
What would be nice in the future
--------------------------------
* Extending the Library to some Boost Concepts, most notably Boost.graph and Boost.asio
* Extending to the Ranges TS or range-v3

-------------
Documentation
-------------
.. toctree::
	:maxdepth: 2

	getting_started
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