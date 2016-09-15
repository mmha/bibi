bibi
====

This is a small library trying to implement the C++ standard library concepts (and maybe some boost ones) using the Concepts Lite TS.

**Heavily WIP!** Currently only a small wrapper around the `type_traits` header, iterator concepts and the most important core concepts are implemented. Also, its nearly completely untested, so use it with care.

Usage
-----

Currently, only gcc >= 6.1 implements the Concepts TS. Make sure you enable it with the `-fconcepts` flag, along with `-std=c++1z`.

This is a header only library. You can copy the contents of the `include` folder into your project. If you use CMake, `add_subdirectory` and link against the `bibi::bibi` target.

A CMake package config is provided.

Example
-------

```cpp
#include <bibi/Core.h> // Iterator Concepts are avaliable in Iterator.h
#include <iostream>

using namespace std::literals;
using namespace bibi;

auto negate(Signed s) {
	return -s;
}

template<typename T>
concept bool SignedArithmetic = Arithmetic<T> && Signed<T>;

template<SignedArithmetic... Num>
auto negativeSum(Num... num)
{
	return (negate(num) + ...);
}

int main() {
	std::cout << negativeSum(1, 2, 3.0, 4ll) << std::endl;
	return 0;
}
```