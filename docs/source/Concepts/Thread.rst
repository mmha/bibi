======
Thread
======

-------------
BasicLockable
-------------

Requirements
------------

.. code-block:: c++

	requires(L m)
	{
		{m.lock()};
		{m.unlock()};
	}

--------
Lockable
--------

.. graphviz::

     digraph g {
		BasicLockable -> Lockable;
     }

Requirements
------------

.. code-block:: c++

	requires(L m)
	{
		{m.try_lock()} -> bool;
	};

-------------
TimedLockable
-------------

.. graphviz::

     digraph g {
		Lockable -> TimedLockable;
     }

Requirements
------------

.. code-block:: c++

	//requires(L m)
	//{
		//{m.try_lock_for()};
		//{m.try_lock_until()};
	//};

Additional Notes
----------------
Requirements are not yet inforced because gcc cannot handle implicit template instantiations in :code:`requires` expressions.

-----
Mutex
-----

.. graphviz::

     digraph g {
		Lockable -> Mutex;
		DefaultConstructible -> Mutex;
		Destructible -> Mutex;
		"NOT CopyConstructible" -> Mutex;
		"NOT CopyAssignable" -> Mutex;
		"NOT MoveConstructible" -> Mutex;
		"NOT MoveAssignable" -> Mutex;
     }

----------
TimedMutex
----------

.. graphviz::

     digraph g {
		TimedLockable -> TimedMutex;
		Mutex -> TimedMutex;
     }

-----------
SharedMutex
-----------

.. graphviz::

     digraph g {
		Mutex -> SharedMutex;
     }

Requirements
------------

.. code-block:: c++

	requires(M m)
	{
		{m.lock_shared()};
		{m.try_lock_shared()};
		{m.unlock_shared()};
	}

----------------
SharedTimedMutex
----------------

.. graphviz::

     digraph g {
		TimedMutex -> SharedTimedMutex;
		SharedMutex -> SharedTimedMutex;
     }

Requirements
------------

.. code-block:: c++

	//requires(M m)
	//{
		//{m.try_lock_shared_for()};
		//{m.try_lock_shared_until()};
	//};

Additional Notes
----------------
Requirements are not yet inforced because gcc cannot handle implicit template instantiations in :code:`requires` expressions.