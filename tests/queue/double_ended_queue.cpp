#include <catch2/catch.hpp>

#include "queue/double_ended_queue.h"

SCENARIO("double_ended_queue size is coherent", "[double_ended_queue]")
{
	GIVEN("an empty double ended queue")
	{
		data_structures_cpp::double_ended_queue<int> deque;

		REQUIRE(deque.empty());
		REQUIRE(deque.size() == 0);

		WHEN("items 1 and 2 are pushed front")
		{
			deque.push_front(1);
			deque.push_front(2);
			THEN("size is 2")
			{
				REQUIRE(deque.size() == 2);
				REQUIRE_FALSE(deque.empty());
			}
			AND_WHEN("items 3 and 4 are pushed back")
			{
				deque.push_back(3);
				deque.push_back(4);
				THEN("size is 4")
				{
					REQUIRE(deque.size() == 4);
					REQUIRE_FALSE(deque.empty());
				}
				AND_WHEN("pop_front is called three times")
				{
					deque.pop_front();
					deque.pop_front();
					deque.pop_front();
					THEN("size is 1")
					{
						REQUIRE(deque.size() == 1);
						REQUIRE_FALSE(deque.empty());
					}
					AND_WHEN("pop_back is called once")
					{
						deque.pop_back();
						THEN("size is 0")
						{
							REQUIRE(deque.size() == 0);
							REQUIRE(deque.empty());
						}
						AND_WHEN("pop_back, pop_front, front or back are called")
						{
							THEN("an exception is thrown")
							{
								REQUIRE_THROWS(deque.pop_back());
								REQUIRE_THROWS(deque.pop_front());
								REQUIRE_THROWS(deque.front());
								REQUIRE_THROWS(deque.back());
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO("double_ended_queue elements' ordering is coherent", "[double_ended_queue]")
{
	GIVEN("an empty double ended queue")
	{
		data_structures_cpp::double_ended_queue<int> deque;

		WHEN("items 1 and 2 are pushed front")
		{
			int first = 1, second = 2;
			deque.push_front(first);
			deque.push_front(second);
			
			THEN("front() returns item 2")
			{
				REQUIRE(deque.front() == second);
			}
			THEN("back() returns item 1")
			{
				REQUIRE(deque.back() == first);
			}
			AND_WHEN("items 3 and 4 are pushed_back")
			{
				int third = 3, fourth = 4;
				deque.push_back(third);
				deque.push_back(fourth);
				THEN("back() returns item 4")
				{
					REQUIRE(deque.back() == fourth);
					AND_THEN("front() returns item 2")
					{
						REQUIRE(deque.front() == second);
					}
				}
			}
		}
	}
}