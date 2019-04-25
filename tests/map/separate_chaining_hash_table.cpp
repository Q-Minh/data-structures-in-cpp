#include <catch2/catch.hpp>

#include <string>
#include <functional>

#include "map/separate_chaining_hash_table.h"

TEST_CASE("separate_chaining_hash_table read/write is coherent", "[separate_chaining_hash_table]")
{
	SECTION("given an empty separate_chaining_hash_table")
	{
		data_structures_cpp::separate_chaining_hash_table<std::string, std::string, std::hash<std::string>> table{101};
		REQUIRE(table.empty());
		REQUIRE(table.size() == 0);
		SECTION("putting elements 'i am minh','a vietnamese' and 'i am afsa','a persian'")
		{
			table.put("i am minh", "a vietnamese");
			table.put("i am afsa", "a persian");
			SECTION("yields size() == 2")
			{
				REQUIRE(table.size() == 2);
				REQUIRE_FALSE(table.empty());
			}
			SECTION("offers correct accessing methods")
			{
				REQUIRE((*table.find("i am minh", "a vietnamese")).key() == "i am minh");
				REQUIRE((*table.find("i am minh", "a vietnamese")).value() == "a vietnamese");
				REQUIRE((*table.find("i am afsa", "a persian")).key() == "i am afsa");
				REQUIRE((*table.find("i am afsa", "a persian")).value() == "a persian");
			}
			SECTION("erasing 'i am minh','a vietnamese'")
			{
				table.erase(table.find("i am minh", "a vietnamese"));
				SECTION("yields size() == 1")
				{
					REQUIRE(table.size() == 1);
					REQUIRE_FALSE(table.empty());
				}
				SECTION("yields begin() is 'i am afsa','a persian'")
				{
					REQUIRE(*table.begin() == data_structures_cpp::key_value_pair<const std::string, std::string>("i am afsa", "a persian"));
				}
			}
		}
	}
}