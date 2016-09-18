#include <bibi/Random.h>

void testSeedSequence(const bibi::SeedSequence &)
{
	
}

void testUniformRandomBitGenerator(const bibi::UniformRandomBitGenerator &)
{

}

auto main() -> int
{
	std::seed_seq seed_seq;
	testSeedSequence(seed_seq);

	testUniformRandomBitGenerator(std::minstd_rand0{});
	testUniformRandomBitGenerator(std::minstd_rand{});
	testUniformRandomBitGenerator(std::mt19937{});
	testUniformRandomBitGenerator(std::mt19937_64{});
	testUniformRandomBitGenerator(std::ranlux24_base{});
	testUniformRandomBitGenerator(std::ranlux48_base{});


	return 0;
}