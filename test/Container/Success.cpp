#include <bibi/Container.h>

#include <array>
#include <deque>
//#include <forward_list> Does not fulfill Container (missing size() function)
#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

auto testContainer(bibi::Container)
{

}

auto testReversibleContainer(bibi::ReversibleContainer)
{

}

template<typename T, typename A = typename T::allocator_type>
auto testAllocatorAwareContainer(T)
	requires bibi::AllocatorAwareContainer<T, A>
{

}

auto main() -> int
{
	std::array<int, 42> array;
	std::deque<int> deque;
	std::list<int> list;
	std::map<int, int> map;
	std::multimap<int, int> multimap;
	std::multiset<int> multiset;
	std::set<int> set;
	std::string string;
	std::unordered_map<int, int> unordered_map;
	std::unordered_multimap<int, int> unordered_multimap;
	std::unordered_multiset<int> unordered_multiset;
	std::unordered_set<int> unordered_set;
	std::vector<int> vector;

	testContainer(array);
	testContainer(deque);
	testContainer(list);
	testContainer(map);
	testContainer(multimap);
	testContainer(multiset);
	testContainer(set);
	testContainer(string);
	testContainer(unordered_map);
	testContainer(unordered_multimap);
	testContainer(unordered_multiset);
	testContainer(unordered_set);
	testContainer(vector);

	testReversibleContainer(array);
	testReversibleContainer(deque);
	testReversibleContainer(list);
	testReversibleContainer(vector);
	testReversibleContainer(map);
	testReversibleContainer(multimap);
	testReversibleContainer(set);
	testReversibleContainer(multiset);

	testAllocatorAwareContainer(deque);
	testAllocatorAwareContainer(list);
	testAllocatorAwareContainer(map);
	testAllocatorAwareContainer(multimap);
	testAllocatorAwareContainer(multiset);
	testAllocatorAwareContainer(set);
	testAllocatorAwareContainer(string);
	testAllocatorAwareContainer(unordered_map);
	testAllocatorAwareContainer(unordered_multimap);
	testAllocatorAwareContainer(unordered_multiset);
	testAllocatorAwareContainer(unordered_set);
	testAllocatorAwareContainer(vector);
}