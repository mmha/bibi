========
Iterator
========

--------
Iterator
--------

.. graphviz::

     digraph g {
		CopyConstructible -> Iterator;
		CopyAssignable -> Iterator;
		Destructible -> Iterator;
		Swappable -> Iterator;
     }

Requirements
------------

.. code-block:: c++

	requires(It r)
	{
		{*r};
		{++r} -> It &;
	}

-------------
InputIterator
-------------

.. graphviz::

     digraph g {
		Iterator -> InputIterator;
		EqualityComparable -> InputIterator;
     }

Requirements
------------

.. code-block:: c++

	requires(It i, It j)
	{
		{i != j} -> bool;
		{*i} -> typename std::iterator_traits<It>::reference;
		{*i++} -> typename std::iterator_traits<It>::value_type;
		//{i->m};
	}

--------------
OutputIterator
--------------

.. graphviz::

     digraph g {
		Iterator -> OutputIterator;
     }

Requirements
------------

.. code-block:: c++

	requires(It r)//, Writable o, Writable a)
	{
		{++r} -> It &;
		{r++} -> It;
		//{*r = o};
		//{*r++ = o};
	}

---------------
ForwardIterator
---------------

.. graphviz::

     digraph g {
		InputIterator -> ForwardIterator;
		DefaultConstructible -> ForwardIterator;
		OutputIterator -> ForwardIterator [style=dotted];
     }

Requirements
------------

.. code-block:: c++

	requires(It r)//, Writable o, Writable a)
	{
		{++r} -> It &;
		{r++} -> It;
		//{*r = o};
		//{*r++ = o};
	}

Additional Notes
----------------
Iff :code:`ForwardIterator` satisfies :code:`OutputIterator`, the type :code:`std::iterator_traits<It>::reference` is a const reference.

---------------------
BidirectionalIterator
---------------------

.. graphviz::

     digraph g {
		ForwardIterator -> BidirectionalIterator;
     }

Requirements
------------

.. code-block:: c++

	requires(It a)
	{
		{--a} -> It &;
		{a--} -> It;
		{*a--} -> typename std::iterator_traits<It>::reference;
	}

--------------------
RandomAccessIterator
--------------------

.. graphviz::

     digraph g {
		BidirectionalIterator -> RandomAccessIterator;
     }

Requirements
------------

.. code-block:: c++

	requires(It i,
	         It a,
	         It b,
	         It &r,
	         typename std::iterator_traits<It>::difference_type n)
	{
		{r + n}  -> It;
		{a + n}  -> It;
		{n + a}  -> It;

		{r -= n} -> It &;
		{i - n}  -> It;
		{b - a}  -> typename std::iterator_traits<It>::difference_type;
		{i[n]}   -> typename std::iterator_traits<It>::reference;
	}

---------------
MutableIterator
---------------

.. graphviz::

     digraph g {
		InputIterator -> MutableIterator;
		OutputIterator -> MutableIterator;
     }

--------------
ValueSwappable
--------------

.. graphviz::

     digraph g {
		Iterator -> ValueSwappable;
     }

Requirements
------------

.. code-block:: c++

	requires(T t, T u) { {std::swap(*t, *u)}; } || 
	requires(T t, T u) { {swap(*t, *u) }; };