#include <catch2/catch.hpp>

#include <string>
#include <string_view>

#include "map/array_ordered_map.h"

TEST_CASE("array_ordered_map maintains order and size coherently", "[array_ordered_map]")
{
	SECTION("given an empty array_ordered_map of capacity 4")
	{
		data_structures_cpp::array_ordered_map<int, int, 4> map;
		REQUIRE(map.size() == 0);
		REQUIRE(map.empty());

		SECTION("adding elements (4,4), (2,2), (3,3), (1,1)")
		{
			map.insert(4, 4);
			map.insert(2, 2);
			map.insert(3, 3);
			map.insert(1, 1);
			REQUIRE(map.size() == 4);
			REQUIRE_FALSE(map.empty());

			SECTION("yields 1, 2, 3, 4 in order")
			{
				auto it = map.begin();
				REQUIRE((it++)->key() == 1);
				REQUIRE((it++)->key() == 2);
				REQUIRE((it++)->key() == 3);
				REQUIRE((it++)->key() == 4);
				REQUIRE(it == map.end());
			}
			SECTION("adding one more element throws")
			{
				REQUIRE_THROWS(map.insert(5, 5));
			}
			SECTION("accessing elements is coherent")
			{
				REQUIRE(map.find(4)->value() == 4);
				REQUIRE(map.find(3)->value() == 3);
				REQUIRE(map.find(2)->value() == 2);
				REQUIRE(map.find(1)->value() == 1);
				REQUIRE(map.find(5) == map.end());
				REQUIRE(map.find(-4) == map.end());
				REQUIRE(map.find(0) == map.end());
			}
			SECTION("greater_than and less_than are coherent")
			{
				REQUIRE(map.greater_than(3)->key() == 4);
				REQUIRE(map.less_than(3)->key() == 2);
				REQUIRE(map.greater_than(4) == map.end());
				REQUIRE(map.less_than(4)->key() == 3);
				REQUIRE(map.less_than(1) == map.end());
			}
			SECTION("erasing inexisting fails")
			{
				auto size = map.size();
				REQUIRE_THROWS(map.erase(5));
				REQUIRE(size == map.size());
			}
			SECTION("erasing elements 2, 3 yields current sequence of 1, 4")
			{
				map.erase(2);
				map.erase(3);
				REQUIRE(map.size() == 2);
				auto it = map.begin();
				REQUIRE((it++)->key() == 1);
				REQUIRE((it++)->key() == 4);
				REQUIRE(it == map.end());
				SECTION("and then readding elements -3 and 3")
				{
					map.insert(-3, -3);
					map.insert(3, 3);
					REQUIRE(map.size() == 4);
					SECTION("yields order -3, 1, 3, 4")
					{
						auto it = map.begin();
						REQUIRE((it++)->key() == -3);
						REQUIRE((it++)->key() == 1);
						REQUIRE((it++)->key() == 3);
						REQUIRE((it++)->key() == 4);
						REQUIRE(it == map.end());
					}
					SECTION("greater_than and less_than are still coherent")
					{
						REQUIRE(map.greater_than(3)->key() == 4);
						REQUIRE(map.less_than(3)->key() == 1);
						REQUIRE(map.greater_than(4) == map.end());
						REQUIRE(map.less_than(4)->key() == 3);
						REQUIRE(map.less_than(1)->key() == -3);
						REQUIRE(map.less_than(-3) == map.end());
						REQUIRE(map.greater_than(-3)->key() == 1);
						REQUIRE(map.greater_than(1)->key() == 3);
					}
					SECTION("adding another element throws")
					{
						REQUIRE_THROWS(map.insert(5, 5));
					}
				}
			}
		}
	}
}