#include <catch2/catch.hpp>

#include "stack/array_stack.h"

TEMPLATE_TEST_CASE("array_stack size is coherent", "[array_stack]", int, std::string)
{
	SECTION("an empty array_stack")
	{
		data_structures_cpp::array_stack<TestType> stack{ 5 };

		REQUIRE(stack.empty());
		REQUIRE(stack.size() == 0);

		SECTION("pushing items 1, 2 and 3 on top")
		{
			stack.push(1);
			stack.push(2);
			stack.push(3);
			SECTION("yields size is 3")
			{
				REQUIRE(stack.size() == 3);
			}
			SECTION("popping from the stack once")
			{
				stack.pop();
				SECTION("yields size is 2")
				{
					REQUIRE_FALSE(stack.empty());
					REQUIRE(stack.size() == 2);
				}
				SECTION("pushing items 4, 5")
				{
					stack.push(4);
					stack.push(5);
					SECTION("yields size is 4")
					{
						REQUIRE_FALSE(stack.empty());

						REQUIRE(stack.size() == 4);
					}
				}
				SECTION("popping twice more")
				{
					stack.pop();
					stack.pop();
					SECTION("yields size is 0")
					{
						REQUIRE(stack.empty());
						REQUIRE(stack.size() == 0);
					}
					SECTION("popping once more")
					{
						SECTION("throws an exception")
						{
							REQUIRE_THROWS(stack.pop());
						}
					}
				}
			}
		}
	
		SECTION("pushing items 1, 2, 3, 4, 5")
		{
			stack.push(1);
			stack.push(2);
			stack.push(3);
			stack.push(4);
			stack.push(5);
			SECTION("yields size is 5")
			{
				REQUIRE(stack.size() == 5);
			}
			SECTION("and pushing one more item (item 6)")
			{
				SECTION("throws an exception")
				{
					REQUIRE_THROWS(stack.push(6));
				}
			}
		}
	}
}

SCENARIO("array_stack items' ordering is coherent", "[array_stack]")
{
	GIVEN("an empty array_stack")
	{
		data_structures_cpp::array_stack<int> stack{};

		REQUIRE(stack.empty());
		REQUIRE(stack.size() == 0);
		WHEN("items 1, 2, 3 are pushed on the stack")
		{
			int first = 1, second = 2, third = 3;
			stack.push(first);
			stack.push(second);
			stack.push(third);

			THEN("top() returns item 3")
			{
				REQUIRE(stack.top() == third);
			}
			AND_WHEN("pop() is called")
			{
				stack.pop();
				THEN("top() returns item 2")
				{
					REQUIRE(stack.top() == second);
				}
				AND_WHEN("item 4 is pushed on the stack")
				{
					int fourth = 4;
					stack.push(fourth);
					THEN("top() returns item 4")
					{
						REQUIRE(stack.top() == fourth);
					}
					AND_WHEN("pop is called twice")
					{
						stack.pop();
						stack.pop();
						THEN("top() returns item 1")
						{
							REQUIRE(stack.top() == first);
						}
					}
				}
			}
		}
	}
}