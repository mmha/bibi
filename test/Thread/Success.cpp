#include <bibi/Thread.h>
#include <mutex>

void testTimedLockable(bibi::TimedLockable &)
{
	
}

auto main() -> int
{
	std::timed_mutex timed_mutex;
	testTimedLockable(timed_mutex);

	return 0;
}