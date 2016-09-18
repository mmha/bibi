#pragma once

#include "Core.h"
#include "Chrono.h"

namespace bibi
{
	template<typename L>
	concept bool BasicLockable =
		requires(L m)
		{
			{m.lock()};
			{m.unlock()};
		};

	template<typename L>
	concept bool Lockable =
		BasicLockable<L> &&
		requires(L m)
		{
			{m.try_lock()} -> bool;
		};

	template<typename L>
	concept bool TimedLockable =
		Lockable<L>;
		//requires(L m)
		//{
			//{m.try_lock_for()}; // TODO duration
			//{m.try_lock_until()}; // TODO time_point
		//};

	template<typename M>
	concept bool Mutex =
		Lockable<M> &&
		DefaultConstructible<M> &&
		Destructible<M> &&
		!CopyConstructible<M> &&
		!CopyAssignable<M> &&
		!MoveConstructible<M> &&
		!MoveAssignable<M>;

	template<typename M>
	concept bool TimedMutex =
		TimedLockable<M> &&
		Mutex<M>;

	template<typename M>
	concept bool SharedMutex =
		Mutex<M> &&
		requires(M m)
		{
			{m.lock_shared()};
			{m.try_lock_shared()};
			{m.unlock_shared()};
		};

	template<typename M>
	concept bool SharedTimedMutex =
		TimedMutex<M> &&
		SharedMutex<M>;
		//requires(M m)
		//{
			//{m.try_lock_shared_for()}; // TODO duration
			//{m.try_lock_shared_until()}; // TODO duration
		//};
}