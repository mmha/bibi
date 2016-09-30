======
Random
======

------------
SeedSequence
------------

.. graphviz::

     digraph g {
		Unsigned -> "SeedSequence::result_type";
		DefaultConstructible -> SeedSequence;
     }

Requirements
------------

.. code-block:: c++
	
	(sizeof(typename S::result_type) >= 4) &&
	requires(
		const uint32_t *ib,
		const uint32_t *ie,
		uint32_t *rb,
		uint32_t *re,
		std::initializer_list<typename S::result_type> il,
		S q,
		const S r,
		int16_t *ob)
	{
		{S(ib, ie)};
		{S(il)};
		{q.generate(rb,re)} -> void;
		{r.size()} -> size_t;
		{r.param(ob)} -> void;
	}

Additional Notes
----------------
	:code:`ib, ie` in the above block should be InputIterator, but gcc crashes on implicit template instantiations.
	:code:`rb, re` in the above block should be RandomAccessIterator, but gcc crashes on implicit template instantiations.
	:code:`ob` in the above block should be OutputIterator, but gcc crashes on implicit template instantiations.

-------------------------
UniformRandomBitGenerator
-------------------------

.. graphviz::

     digraph g {
		Unsigned -> "UniformRandomBitGenerator::result_type";
     }

Requirements
------------

.. code-block:: c++
	
	requires(G g)
	{
		{G::min()} -> typename G::result_type;
		{G::max()} -> typename G::result_type;
		{g()} -> typename G::result_type;
	}

------------------
RandomNumberEngine
------------------

.. graphviz::

     digraph g {
		UniformRandomBitGenerator -> RandomNumberEngine;
		DefaultConstructible -> RandomNumberEngine;
		CopyConstructible -> RandomNumberEngine;
		EqualityComparable -> RandomNumberEngine;
     }

Requirements
------------

.. code-block:: c++
	
	requires(E e,
		E &v,
		const E x,
		const E y,
		typename E::result_type s,
		std::seed_seq q,
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
	}

Additional Notes
----------------
	:code:`q` in the above block should be SeedSequence, but gcc crashes on implicit template instantiations.

-------------------------
RandomNumberEngineAdaptor
-------------------------

.. graphviz::

     digraph g {
		RandomNumberEngine -> RandomNumberEngineAdaptor;
     }

Requirements
------------

.. code-block:: c++
	
	requires(E e)
	{
		{e.base()} -> RandomNumberEngine;
	}

------------------------
RandomNumberDistribution
------------------------

.. graphviz::

     digraph g {
		DefaultConstructible -> RandomNumberDistribution;
		CopyConstructible -> RandomNumberDistribution;
		CopyAssignable -> RandomNumberDistribution;
		CopyConstructible -> "RandomNumberDistribution::param_type";
		CopyAssignable -> "RandomNumberDistribution::param_type";
		EqualityComparable -> "RandomNumberDistribution::param_type";
     }

Requirements
------------

.. code-block:: c++
	
	requires(
		D d,
		const D x,
		const D y,
		const typename D::param_type p,
		std::mt19937 g,
		std::mt19937 g1,
		std::mt19937 g2,
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
	}

Additional Notes
----------------
	:code:`g, g1, g2` in the above block should be UniformRandomBitGenerator, but gcc crashes on implicit template instantiations.