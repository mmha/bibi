#pragma once

#include <chrono>
#include "Core.h"

namespace bibi
{
	namespace chrono
	{
		namespace detail
		{
			template<typename T>
			concept bool TrivialClockNumeric =
				EqualityComparable<T> &&
				LessThanComparable<T> &&
				DefaultConstructible<T> &&
				CopyConstructible<T> &&
				CopyAssignable<T> &&
				Destructible<T> &&
				Numeric<T> &&
				Swappable<T>;

			template<typename T>
			concept bool Duration = isSpecializationOf<T, std::chrono::duration>;

			template<typename T>
			concept bool TimePoint = isSpecializationOf<T, std::chrono::time_point>;
		}

		template<typename C>
		concept bool Clock =
			Arithmetic<typename C::rep> &&
			isSame<typename C::duration, std::chrono::duration<typename C::rep, typename C::period>>() &&
			//isSame<typename C::time_point, std::chrono::time_point<Clock, typename C::duration>>() &&
			isVariableSpecializationOf<std::intmax_t, typename C::period, std::ratio>() &&
			requires
			{
				{C::is_steady} -> bool;
				{C::now()} -> typename C::time_point;
			};



		template<typename TC>
		concept bool TrivialClock = 
			Clock<TC> &&
			detail::TrivialClockNumeric<typename TC::rep>;
			//TrivialClock<typename TC::time_point::clock>;
	}
}