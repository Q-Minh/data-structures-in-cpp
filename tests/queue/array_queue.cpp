#include <catch2/catch.hpp>

#include "queue/array_queue.h"

SCENARIO("array_queue size is coherent with push_back and pop_front", "[array_queue]")
{
	GIVEN("An empty array_queue")
	{	
		data_structures_cpp::array_queue<int> array_queue{};

		REQUIRE(array_queue.empty() == true);

		WHEN("array_queue has items 1, 2, 3 pushed_back in this order")
		{
			int firstItem = 1, secondItem = 2, thirdItem = 3;
			array_queue.push_back(firstItem);
			array_queue.push_back(secondItem);
			array_queue.push_back(thirdItem);

			THEN("the size is changed accordingly")
			{
				REQUIRE(array_queue.size() == 3);
				AND_THEN("pop_front updates size to 2")
				{
					array_queue.pop_front();
					REQUIRE(array_queue.size() == 2);
				}
			}
			AND_WHEN("pop_front is called until empty() returns true")
			{
				while (!array_queue.empty()) array_queue.pop_front();
				THEN("size is 0")
				{
					REQUIRE(array_queue.size() == 0);
				}
			}
		}
	}
}