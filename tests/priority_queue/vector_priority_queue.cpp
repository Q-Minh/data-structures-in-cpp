#include <catch2/catch.hpp>

#include "priority_queue/vector_priority_queue.h"

TEST_CASE("vector_priority_queue remains sorted", "[vector_priority_queue]")
{
	SECTION("given an empty list_priority_queue")
	{
		data_structures_cpp::vector_priority_queue<int> queue{};
		REQUIRE(queue.empty());
		REQUIRE(queue.size() == 0);
		SECTION("adding elements 3, 5, 1, 23, 4, 4")
		{
			queue.push(3);
			queue.push(5);
			queue.push(1);
			queue.push(23);
			queue.push(4);
			queue.push(4);
			SECTION("yields front() == 1")
			{
				REQUIRE(queue.front() == 1);
			}
			SECTION("popping from the queue")
			{
				queue.pop();
				SECTION("yields front() == 3")
				{
					REQUIRE(queue.front() == 3);
				}
				SECTION("popping from the queue once more")
				{
					queue.pop();
					SECTION("yields front() == 4")
					{
						REQUIRE(queue.front() == 4);
					}
					SECTION("inserting elements 13, 940, -3")
					{
						queue.push(13);
						queue.push(940);
						queue.push(-3);
						SECTION("13 is in fifth place from the start (-3, 4, 4, 5, 13, ...)")
						{
							for (int i = 0; i < 4; ++i)
							{
								queue.pop();
							}
							REQUIRE(queue.front() == 13);
						}
						SECTION("yields front() == -3")
						{
							REQUIRE(queue.front() == -3);
						}
						SECTION("popping until size() == 1")
						{
							while (queue.size() > 1)
							{
								queue.pop();
							}
							SECTION("yields front() == 940")
							{
								REQUIRE(queue.front() == 940);
							}
						}
					}
					SECTION("popping once more")
					{
						queue.pop();
						SECTION("yields front() == 4")
						{
							REQUIRE(queue.front() == 4);
						}
						SECTION("popping once more")
						{
							queue.pop();
							SECTION("yields front() == 5")
							{
								REQUIRE(queue.front() == 5);
							}
							SECTION("popping once more")
							{
								queue.pop();
								SECTION("yields front() == 23")
								{
									REQUIRE(queue.front() == 23);
								}
								SECTION("queue is empty after last pop")
								{
									queue.pop();
									REQUIRE(queue.size() == 0);
									REQUIRE(queue.empty());
								}
							}
						}
					}
				}
			}
		}
	}
}