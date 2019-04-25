#include <catch2/catch.hpp>

#include "list/doubly_linked_list.h"

TEMPLATE_TEST_CASE("doubly_linked_list empty() is coherent", "[doubly_linked_list]", int, std::string)
{
	SECTION("Given an empty doubly_linked_list")
	{
		data_structures_cpp::doubly_linked_list<TestType> list{};

		REQUIRE(list.empty());
		REQUIRE_THROWS(list.front());
		REQUIRE_THROWS(list.back());
		REQUIRE_THROWS(list.pop_front());
		REQUIRE_THROWS(list.pop_back());
		SECTION("Pushing items 1 and 2 to the front")
		{
			list.push_front(1);
			list.push_front(2);
			SECTION("yields empty() is false")
			{
				REQUIRE_FALSE(list.empty());
			}
			SECTION("Then pushing items 3 and 4 to the back")
			{
				list.push_back(3);
				list.push_back(4);
				SECTION("yields empty() is false")
				{
					REQUIRE_FALSE(list.empty());
				}
				SECTION("Then calling pop_front() twice and pop_back() once")
				{
					list.pop_front();
					list.pop_front();
					list.pop_back();
					SECTION("yields empty() is false")
					{
						REQUIRE_FALSE(list.empty());
					}
					SECTION("then calling pop_front() again")
					{
						list.pop_front();
						SECTION("yields empty() is true")
						{
							REQUIRE(list.empty());
						}
						SECTION("then calling accessor or deleters throws")
						{
							REQUIRE_THROWS(list.front());
							REQUIRE_THROWS(list.back());
							REQUIRE_THROWS(list.pop_front());
							REQUIRE_THROWS(list.pop_back());
						}
					}
				}
			}
		}
	}
}

SCENARIO("doubly_linked_list items' ordering is coherent", "[doubly_linked_list]")
{
	GIVEN("an empty doubly_linked_list")
	{
		data_structures_cpp::doubly_linked_list<int> list{};

		REQUIRE(list.empty());
		WHEN("items 1, 2, 3 are pushed front")
		{
			list.push_front(1);
			list.push_front(2);
			list.push_front(3);
			THEN("front() returns item 3")
			{
				REQUIRE(list.front() == 3);
			}
			AND_WHEN("pop_front() is called")
			{
				list.pop_front();
				THEN("front() returns item 2")
				{
					REQUIRE(list.front() == 2);
				}
				AND_WHEN("item 4, 5 are pushed back")
				{
					list.push_back(4);
					list.push_back(5);
					THEN("front() returns item 2")
					{
						REQUIRE(list.front() == 2);
					}
					THEN("back() returns item 5")
					{
						REQUIRE(list.back() == 5);
					}
					AND_WHEN("pop_front is called twice and pop_back is called once")
					{
						list.pop_front();
						list.pop_front();
						list.pop_back();
						THEN("front() returns item 4")
						{
							REQUIRE(list.front() == 4);
						}
						THEN("back() returns item 4")
						{
							REQUIRE(list.back() == 4);
						}
						AND_WHEN("pop_front is called again")
						{
							list.pop_front();
							THEN("list is empty")
							{
								REQUIRE(list.empty());
								REQUIRE_THROWS(list.back());
								REQUIRE_THROWS(list.front());
							}
						}
						AND_WHEN("pop_back is called again")
						{
							list.pop_back();
							THEN("list is empty")
							{
								REQUIRE(list.empty());
								REQUIRE_THROWS(list.back());
								REQUIRE_THROWS(list.front());
							}
						}
					}
				}
			}
		}
	}
}