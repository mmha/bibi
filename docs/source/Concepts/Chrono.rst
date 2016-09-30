======
Chrono
======

-----
Clock
-----

.. graphviz::

     digraph g {
		Arithmetic -> "Clock::rep";
		isSame -> "Clock::duration";
		isSame -> "std::chrono::duration<Clock::rep, Clock::period>";
		isVariableSpecializationOf -> "std::intmax_t, Clock::period, std::ratio";
     }

Requirements
------------

.. code-block:: c++

	requires
	{
		{C::is_steady} -> bool;
		{C::now()} -> typename C::time_point;
	}

------------
TrivialClock
------------

.. graphviz::

     digraph g {
		Clock -> TrivialClock;
		TrivialClockNumeric -> "typename TrivialClock::rep";
		EqualityComparable -> TrivialClockNumeric;
		LessThanComparable -> TrivialClockNumeric;
		DefaultConstructible -> TrivialClockNumeric;
		CopyConstructible -> TrivialClockNumeric;
		CopyAssignable -> TrivialClockNumeric;
		Destructible -> TrivialClockNumeric;
		Numeric -> TrivialClockNumeric;
		Swappable -> TrivialClockNumeric;
     }
