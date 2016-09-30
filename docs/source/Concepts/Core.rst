====
Core
====

Core extends (and therefore includes) the Type Traits concepts.

------------------
EqualityComparable
------------------

Requirements
------------

.. code-block:: c++

	requires(const T a, const T b)
	{
		{a == b} -> bool;
	};

------------------
LessThanComparable
------------------

Requirements
------------

.. code-block:: c++

	requires(const T a, const T b)
	{
		{a < b} -> bool;
	};

--------
Callable
--------

Requirements
------------

.. code-block:: c++

	requires(T t, Args &&... args)
	{
		{t(args...)} -> R;
	};

--------------
FunctionObject
--------------

.. graphviz::

     digraph g {
		Object -> FunctionObject;
     }

Requirements
------------

.. code-block:: c++

	requires(T t, Args &&... args)
	{
		{t(args...)} -> R;
	};

---------
Swappable
---------

Requirements
------------

.. code-block:: c++

	requires(T t, T u) { {std::swap(t, u)}; } ||
	requires(T t, T u) { {swap(t, u)}; };

---------------
NullablePointer
---------------

.. graphviz::

     digraph g {
		EqualityComparable -> NullablePointer;
		DefaultConstructible -> NullablePointer;
		CopyConstructible -> NullablePointer;
		CopyAssignable -> NullablePointer;
		Destructible -> NullablePointer;
     }

Requirements
------------

.. code-block:: c++

	requires(T p, T q, nullptr_t np)
	{
		{p = np};
		{p = np};
		{p != q};
		{p == np};
		{np == p};
		{p != np};
		{np != p};
	};

---------------
Hash
---------------

.. graphviz::

     digraph g {
		FunctionObject -> Hash;
		CopyConstructible -> Hash;
		Destructible -> Hash;
     }

Requirements
------------

.. code-block:: c++

	requires(T h, Key k)
	{
		{h(k)} -> size_t;
	};

---------
Predicate
---------

.. graphviz::

     digraph g {
		"Callable T, bool, U" -> Predicate;
     }

---------------
BinaryPredicate
---------------

.. graphviz::

     digraph g {
		"Callable T, bool, U, U" -> BinaryPredicate;
     }

-------
Compare
-------

.. graphviz::

     digraph g {
		"Callable T, bool, U, U" -> Compare;
     }