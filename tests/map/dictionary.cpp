#include <catch2/catch.hpp>

#include <string>
#include <functional>

#include "map/dictionary.h"

TEST_CASE("dictionary read/write is coherent", "[dictionary]")
{
	SECTION("given an empty separate_chaining_hash_table")
	{
		data_structures_cpp::dictionary<std::string, std::string, std::hash<std::string>> table{ 101 };
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
			SECTION("inserting in two new elements with duplicate key 'i am afsa'")
			{
				table.insert("i am afsa", "minh's boyfriend");
				table.insert("i am afsa", "ahzeen's sister");
				SECTION("yields 3 results for find_all('i am afsa')")
				{
					auto range = table.find_all("i am afsa");
					int i = 0;
					for (auto it = range.begin(); it != range.end(); ++it) ++i;
					REQUIRE(i == 3);
				}
				SECTION("results of find_all reflect correct entries/(k,v) pairs")
				{
					auto range = table.find_all("i am afsa");
					auto it = range.begin();
					REQUIRE(it->key() == "i am afsa");
					REQUIRE(it->value() == "ahzeen's sister");
					++it;
					REQUIRE(it->key() == "i am afsa");
					REQUIRE(it->value() == "minh's boyfriend");
					++it;
					REQUIRE(it->key() == "i am afsa");
					REQUIRE(it->value() == "a persian");
					++it;
					REQUIRE(it == range.end());
					range = table.find_all("i am minh");
					it = range.begin();
					REQUIRE(it->key() == "i am minh");
					REQUIRE(it->value() == "a vietnamese");
					++it;
					REQUIRE(it == range.end());
				}
			}
		}
	}
}