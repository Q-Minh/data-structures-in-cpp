#include <string>

#include <catch2/catch.hpp>

#include "vector/vector.h"
#include "list/doubly_linked_list.h"

TEMPLATE_TEST_CASE("array based vector size is coherent", "[vector]", int, std::string)
{
	SECTION("given an empty array based vector")
	{
		using vector_t = data_structures_cpp::vector<TestType>;
		vector_t vector{};
		REQUIRE(vector.size() == 0);
		REQUIRE(vector.empty());
		REQUIRE(vector.begin() == vector.end());
		REQUIRE(vector.capacity() > 0);
		REQUIRE_THROWS(vector.at(0));
		REQUIRE_THROWS(vector.pop_back());
		REQUIRE_THROWS(vector.erase(0));
		SECTION("reserving 4096 elements' space")
		{
			vector.reserve(4096);
			SECTION("yields capacity() == 4096")
			{
				REQUIRE(vector.capacity() == 4096);
			}
			SECTION("size doesn't change")
			{
				REQUIRE(vector.empty());
				REQUIRE(vector.begin() == vector.end());
				REQUIRE(vector.size() == 0);
			}
		}
		SECTION("inserting 3 elements")
		{
			vector_t::iterator_t it = vector.begin();
			vector_t::position_t pos = it - vector.begin();
			vector.insert(pos, 1);
			++it;
			pos = it - vector.begin();
			vector.insert(pos, 2);
			++it;
			pos = it - vector.begin();
			vector.insert(pos, 3);
			SECTION("yields size() == 3")
			{
				REQUIRE_FALSE(vector.empty());
				REQUIRE_FALSE(vector.begin() == vector.end());
				REQUIRE(vector.size() == 3);
			}
			SECTION("writing with at() to index 3 throws")
			{
				REQUIRE_THROWS(vector.at(3) = 2);
			}
			SECTION("writing with operator[] to index 3 does not throw but is undefined")
			{
				REQUIRE_NOTHROW(vector[3] = 2);
			}
		}
		SECTION("calling push_back twice")
		{
			vector.push_back(1);
			vector.push_back(2);
			SECTION("yields size() == 2")
			{
				REQUIRE_FALSE(vector.empty());
				REQUIRE(vector.size() == 2);
			}
			SECTION("accessing elements > 0 and < size with at() doesn't throw")
			{
				REQUIRE_NOTHROW(vector.at(0));
				REQUIRE_NOTHROW(vector.at(1));
			}
			SECTION("accessing elements < 0 or >= size with at() throws")
			{
				REQUIRE_THROWS(vector.at(-1));
				REQUIRE_THROWS(vector.at(2));
			}
			SECTION("calling insert twice")
			{
				vector.insert(0, 3);
				vector.insert(0, 4);
				SECTION("yields size() == 4")
				{
					REQUIRE_FALSE(vector.empty());
					REQUIRE(vector.size() == 4);
				}
				SECTION("calling pop_back 3 times")
				{
					vector.pop_back();
					vector.pop_back();
					vector.pop_back();
					SECTION("yields size() == 1")
					{
						REQUIRE(vector.size() == 1);
						REQUIRE_FALSE(vector.empty());
					}
					SECTION("calling pop_back once more")
					{
						vector.pop_back();
						SECTION("yields size() == 0")
						{
							REQUIRE(vector.size() == 0);
							REQUIRE(vector.empty());
						}
						SECTION("accessing elements with at() throws")
						{
							REQUIRE_THROWS(vector.at(0));
						}
						SECTION("accessing element with operator[] doesn't throw but is undefined")
						{
							REQUIRE_NOTHROW(vector[0]);
							REQUIRE_NOTHROW(vector[3]);
						}
						SECTION("calling pop_back once more throws")
						{
							REQUIRE_THROWS(vector.pop_back());
						}
					}
				}
			}
		}
	}
}

// TODO : this test case fails miserably!! vector's doubly_linked_list specialization is not
// implemented correctly. Please fix it.
TEMPLATE_TEST_CASE("array or linked_list based vector elements' ordering is coherent", "[!mayfail][!throws][.vector]", int, std::string)
{
	SECTION("given an empty doubly_linked_list based vector")
	{
		using vector_t = data_structures_cpp::vector<TestType, data_structures_cpp::doubly_linked_list>;
		vector_t vector{};
		REQUIRE(vector.size() == 0);
		REQUIRE(vector.empty());
		REQUIRE(vector.begin() == vector.end());
		REQUIRE_THROWS(vector.at(0));
		REQUIRE_THROWS(vector.pop_back());
		REQUIRE_THROWS(vector.erase(0));
		SECTION("inserting 3 elements")
		{
			vector_t::iterator_t it = vector.begin();
			vector_t::position_t pos = it - vector.begin();
			vector.insert(pos, 1);
			++it;
			pos = it - vector.begin();
			vector.insert(pos, 2);
			++it;
			pos = it - vector.begin();
			vector.insert(pos, 3);
			SECTION("yields size() == 3")
			{
				REQUIRE_FALSE(vector.empty());
				REQUIRE_FALSE(vector.begin() == vector.end());
				REQUIRE(vector.size() == 3);
			}
			SECTION("writing with at() to index 3 throws")
			{
				REQUIRE_THROWS(vector.at(3) = 2);
			}
			SECTION("writing with operator[] to index 3 does not throw but is undefined")
			{
				REQUIRE_NOTHROW(vector[3] = 2);
			}
		}
		SECTION("calling push_back twice")
		{
			vector.push_back(1);
			vector.push_back(2);
			SECTION("yields size() == 2")
			{
				REQUIRE_FALSE(vector.empty());
				REQUIRE(vector.size() == 2);
			}
			SECTION("accessing elements > 0 and < size with at() doesn't throw")
			{
				REQUIRE_NOTHROW(vector.at(0));
				REQUIRE_NOTHROW(vector.at(1));
			}
			SECTION("accessing elements < 0 or >= size with at() throws")
			{
				REQUIRE_THROWS(vector.at(-1));
				REQUIRE_THROWS(vector.at(2));
			}
			SECTION("calling insert twice")
			{
				vector.insert(0, 3);
				vector.insert(0, 4);
				SECTION("yields size() == 4")
				{
					REQUIRE_FALSE(vector.empty());
					REQUIRE(vector.size() == 4);
				}
				SECTION("calling pop_back 3 times")
				{
					vector.pop_back();
					vector.pop_back();
					vector.pop_back();
					SECTION("yields size() == 1")
					{
						REQUIRE(vector.size() == 1);
						REQUIRE_FALSE(vector.empty());
					}
					SECTION("calling pop_back once more")
					{
						vector.pop_back();
						SECTION("yields size() == 0")
						{
							REQUIRE(vector.size() == 0);
							REQUIRE(vector.empty());
						}
						SECTION("accessing elements with at() throws")
						{
							REQUIRE_THROWS(vector.at(0));
						}
						SECTION("accessing element with operator[] doesn't throw but is undefined")
						{
							REQUIRE_NOTHROW(vector[0]);
							REQUIRE_NOTHROW(vector[3]);
						}
						SECTION("calling pop_back once more throws")
						{
							REQUIRE_THROWS(vector.pop_back());
						}
					}
				}
			}
		}
	}
}