#include <catch2/catch.hpp>

#include "tree/avl_tree.h"

TEST_CASE("avl_tree behaves coherently as map", "[avl_tree]")
{
	SECTION("given an empty avl_tree")
	{
		data_structures_cpp::avl_tree<std::string, std::string> tree{};

		REQUIRE(tree.empty());
		REQUIRE(tree.size() == 0);
		SECTION("inserting elements 'i am minh','a vietnamese' and 'i am afsa','a persian', 'i am ahzeen','a persian'")
		{
			// inserting "i am minh" at root
			tree.insert("i am minh", "a vietnamese");
			// inserting "i am afsa" should go to root's left on lexicographical compare
			tree.insert("i am afsa", "a persian");
			// inserting "i am ahzeen" should go to root's left's right on lexicographical compare
			// and trigger a trinode restructuring
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
			SECTION("executes restructuring/self-balancing operation")
			{
				auto minh = tree.find("i am minh");
				auto afsa = tree.find("i am afsa");
				auto ahzeen = tree.find("i am ahzeen");
				REQUIRE(minh->height() == 1);
				REQUIRE(afsa->height() == 1);
				REQUIRE(ahzeen->height() == 2);
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