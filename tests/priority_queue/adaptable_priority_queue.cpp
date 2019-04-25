#include <catch2/catch.hpp>

#include "priority_queue/adaptable_priority_queue.h"

TEST_CASE("adaptable_priority_queue remains sorted", "[adaptable_priority_queue]")
{
	SECTION("given an empty adaptable_priority_queue")
	{
		data_structures_cpp::adaptable_priority_queue<int> queue{};
		REQUIRE(queue.empty());
		REQUIRE(queue.size() == 0);
		SECTION("adding elements 3, 5, 1, 23, 4, 4")
		{
			auto p2 = queue.insert(3);
			auto p5 = queue.insert(5);
			auto p1 = queue.insert(1);
			auto p6 = queue.insert(23);
			auto p3 = queue.insert(4);
			auto p4 = queue.insert(4);
			SECTION("elements can be removed by their associated position")
			{
				queue.remove(p2);
				REQUIRE(queue.size() == 5);
			}
			SECTION("queue still preserves ordering on element replacements")
			{
				p2 = queue.replace(p2, 90);
				p5 = queue.replace(p5, -3);
				while (queue.size() < 1)
				{
					auto min = queue.front();
					queue.pop();
					REQUIRE(min <= queue.front());
				}
			}
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
						queue.insert(13);
						queue.insert(940);
						queue.insert(-3);
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