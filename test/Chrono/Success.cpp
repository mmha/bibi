#include <bibi/Chrono.h>
#include <chrono>
#include <vector>

void testClock(bibi::chrono::Clock)
{
}

void testTrivialClock(bibi::chrono::TrivialClock)
{
}

auto main() -> int
{
	std::chrono::system_clock system_clock;
	std::chrono::steady_clock steady_clock;
	std::chrono::high_resolution_clock high_resolution_clock;

	testClock(system_clock);
	testClock(steady_clock);
	testClock(high_resolution_clock);

	testTrivialClock(system_clock);
	testTrivialClock(steady_clock);
	testTrivialClock(high_resolution_clock);

	return 0;
}