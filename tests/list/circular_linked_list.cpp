#include <catch2/catch.hpp>

#include "list/circular_linked_list.h"

SCENARIO("circular_linked_list size is coherent", "[circular_linked_list]")
{
	GIVEN("An empty circular_linked_list")
	{
		data_structures_cpp::circular_linked_list<int> circular_list{};

		REQUIRE(circular_list.empty() == true);
		REQUIRE(circular_list.size() == 0);

		WHEN("circular_linked_list has items 1, 2, 3 pushed_front in this order")
		{
			circular_list.push_front(1);
			circular_list.push_front(2);
			circular_list.push_front(3);

			THEN("the size is changed accordingly")
			{
				REQUIRE(circular_list.size() == 3);
			}
			THEN("back() and front() return the oldest and latest items respectively "
				 "while maintaining size (doesn't remove any item)")
			{
				int back = circular_list.back();
				int front = circular_list.front();
				REQUIRE(back == 1);
				REQUIRE(front == 3);
				REQUIRE(circular_list.size() == 3);
			}
			WHEN("pop_front() is called twice")
			{
				circular_list.pop_front();
				circular_list.pop_front();
				THEN("size is reduced accordingly")
				{
					REQUIRE(circular_list.size() == 1);
				}
			}
			WHEN("advancing the circular_linked_list's cursor once")
			{
				circular_list.advance();
				THEN("front() and back() yield 2 and 3 respectively")
				{
					REQUIRE(circular_list.back() == 3);
					REQUIRE(circular_list.front() == 2);
				}
			}
			WHEN("removing items until empty() is true")
			{
				while (!circular_list.empty()) circular_list.pop_front();
				THEN("size() yields a size of 0")
				{
					REQUIRE(circular_list.size() == 0);
				}
			}
			THEN("pop_front removes front element which is the latest pushed element")
			{
				circular_list.pop_front();
				REQUIRE(circular_list.front() == 2);
			}
		}
	}
}