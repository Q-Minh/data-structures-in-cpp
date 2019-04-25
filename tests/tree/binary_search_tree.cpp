#include <catch2/catch.hpp>

#include "tree/binary_search_tree.h"

TEST_CASE("binary_search_tree behaves coherently as map", "[binary_search_tree]")
{
	SECTION("given an empty binary_search_tree")
	{
		data_structures_cpp::binary_search_tree<std::string, std::string> tree{};

		REQUIRE(tree.empty());
		REQUIRE(tree.size() == 0);
		SECTION("inserting elements 'i am minh','a vietnamese' and 'i am afsa','a persian', 'i am ahzeen','a persian'")
		{
			tree.insert("i am minh", "a vietnamese");
			tree.insert("i am afsa", "a persian");
			tree.insert("i am ahzeen", "a persian");
			SECTION("yields size() == 3")
			{
				REQUIRE(tree.size() == 3);
				REQUIRE_FALSE(tree.empty());
			}
			SECTION("offers correct accessing methods")
			{
				auto minh = tree.find("i am minh");
				auto afsa = tree.find("i am afsa");
				auto ahzeen = tree.find("i am ahzeen");
				REQUIRE(minh->key() == "i am minh");
				REQUIRE(minh->value() == "a vietnamese");
				REQUIRE(afsa->key() == "i am afsa");
				REQUIRE(afsa->value() == "a persian");
				REQUIRE(ahzeen->key() == "i am ahzeen");
				REQUIRE(ahzeen->value() == "a persian");
			}
			SECTION("offers correct ordering")
			{
				auto it = tree.begin();
				REQUIRE(it->key() == "i am afsa");
				REQUIRE((++it)->key() == "i am ahzeen");
				REQUIRE((++it)->key() == "i am minh");
				REQUIRE(++it == tree.end());
			}
			SECTION("erasing 'i am minh','a vietnamese'")
			{
				tree.erase(tree.find("i am minh"));
				SECTION("yields size() == 1")
				{
					REQUIRE(tree.size() == 2);
					REQUIRE_FALSE(tree.empty());
				}
				SECTION("yields begin() is 'i am afsa','a persian'")
				{
					REQUIRE(*tree.begin() == data_structures_cpp::key_value_pair<std::string, std::string>("i am afsa", "a persian"));
				}
			}

		}
	}
}