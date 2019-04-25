#include <catch2/catch.hpp>

#include "list/singly_linked_list.h"

TEMPLATE_TEST_CASE("singly_linked_list empty() is coherent", "[singly_linked_list]", int, std::string)
{
	SECTION("Given an empty singly_linked_list")
	{
		data_structures_cpp::singly_linked_list<TestType> list{};

		REQUIRE(list.empty());
		REQUIRE_THROWS(list.front());
		REQUIRE_THROWS(list.pop_front());
		SECTION("Pushing items 1, 2, 3 to the front")
		{
			list.push_front(1);
			list.push_front(2);
			list.push_front(3);
			SECTION("yields empty() is false")
			{
				REQUIRE_FALSE(list.empty());
			}
			SECTION("Then calling pop_front() twice")
			{
				list.pop_front();
				list.pop_front();
				SECTION("yields empty() is false")
				{
					REQUIRE_FALSE(list.empty());
				}
				SECTION("Then pushing items 4, 5 to the front")
				{
					list.push_front(4);
					list.push_front(5);
					SECTION("yields empty() is false")
					{
						REQUIRE_FALSE(list.empty());
					}
					SECTION("then calling pop_front() thrice again")
					{
						list.pop_front();
						list.pop_front();
						list.pop_front();
						SECTION("yields empty() is true")
						{
							REQUIRE(list.empty());
						}
						SECTION("then calling accessor or deleters throws")
						{
							REQUIRE_THROWS(list.front());
							REQUIRE_THROWS(list.pop_front());
						}
					}
				}
			}
		}
	}
}

SCENARIO("singly_linked_list items' ordering is coherent", "[singly_linked_list]")
{
	GIVEN("an empty singly_linked_list")
	{
		data_structures_cpp::singly_linked_list<int> list{};

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
				AND_WHEN("item 4, 5 are pushed front")
				{
					list.push_front(4);
					list.push_front(5);
					THEN("front() returns item 5")
					{
						REQUIRE(list.front() == 5);
					}
					AND_WHEN("pop_front is called three times")
					{
						list.pop_front();
						list.pop_front();
						list.pop_front();
						THEN("front() returns item 1")
						{
							REQUIRE(list.front() == 1);
						}
					}
				}
			}
		}
	}
}