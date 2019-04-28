#include <catch2/catch.hpp>

#include <string>
#include <string_view>

#include "tree/multi_way_entry_ordered_map.h"
#include "tree/multi_way_tree_node.h"

TEST_CASE("multi_way_entry_ordered_map maintains order and size coherently", "[multi_way_entry_ordered_map]")
{
	SECTION("given an empty multi_way_entry_ordered_map of capacity 4")
	{
		auto node = std::make_shared<data_structures_cpp::multi_way_node<int, int, 2, 4>>();
		node->build();
		REQUIRE(node->size() == 0);
		REQUIRE(node->empty());

		SECTION("adding elements (4,4), (2,2), (3,3), (1,1)")
		{
			node->insert(4, 4);
			node->insert(2, 2);
			node->insert(3, 3);
			node->insert(1, 1);
			REQUIRE(node->size() == 4);
			REQUIRE_FALSE(node->empty());

			SECTION("yields 1, 2, 3, 4 in order")
			{
				auto it = node->begin();
				REQUIRE((*it)->key() == 1); it++;
				REQUIRE((*it)->key() == 2); it++;
				REQUIRE((*it)->key() == 3); it++;
				REQUIRE((*it)->key() == 4); it++;
				REQUIRE(it == node->last()); it++;
				REQUIRE(it == node->end());
			}
			SECTION("adding one more element throws")
			{
				REQUIRE_THROWS(node->insert(5, 5));
			}
			SECTION("accessing elements is coherent")
			{
				REQUIRE((*node->find(4))->value() == 4);
				REQUIRE((*node->find(3))->value() == 3);
				REQUIRE((*node->find(2))->value() == 2);
				REQUIRE((*node->find(1))->value() == 1);
				REQUIRE(node->find(5) == node->end());
				REQUIRE(node->find(-4) == node->end());
				REQUIRE(node->find(0) == node->end());
			}
			SECTION("greater_than and less_than are coherent")
			{
				REQUIRE((*node->greater_than(3))->key() == 4);
				REQUIRE((*node->less_than(3))->key() == 2);
				REQUIRE((*node->less_than(100))->key() == 4);
				REQUIRE(node->greater_than(4) == node->last());
				REQUIRE((*node->less_than(4))->key() == 3);
				REQUIRE(node->less_than(1) == node->end());
			}
			SECTION("erasing inexisting fails")
			{
				auto size = node->size();
				REQUIRE_THROWS(node->erase(5));
				REQUIRE(size == node->size());
			}
			SECTION("erasing elements 2, 3 yields current sequence of 1, 4")
			{
				node->erase(2);
				node->erase(3);
				REQUIRE(node->size() == 2);
				auto it = node->begin();
				REQUIRE((*it)->key() == 1); it++;
				REQUIRE((*it)->key() == 4); it++;
				REQUIRE(it == node->last()); it++;
				REQUIRE(it == node->end());
				SECTION("and then readding elements -3 and 3")
				{
					node->insert(-3, -3);
					node->insert(3, 3);
					REQUIRE(node->size() == 4);
					SECTION("yields order -3, 1, 3, 4")
					{
						auto it = node->begin();
						REQUIRE((*it)->key() == -3); it++;
						REQUIRE((*it)->key() == 1); it++;
						REQUIRE((*it)->key() == 3); it++;
						REQUIRE((*it)->key() == 4); it++;
						REQUIRE(it == node->last()); it++;
						REQUIRE(it == node->end());
					}
					SECTION("greater_than and less_than are still coherent")
					{
						REQUIRE((*node->greater_than(3))->key() == 4);
						REQUIRE((*node->less_than(3))->key() == 1);
						REQUIRE(node->greater_than(4) == node->last());
						REQUIRE((*node->less_than(4))->key() == 3);
						REQUIRE((*node->less_than(1))->key() == -3);
						REQUIRE(node->less_than(-3) == node->end());
						REQUIRE((*node->greater_than(-3))->key() == 1);
						REQUIRE((*node->greater_than(1))->key() == 3);
					}
					SECTION("adding another element throws")
					{
						REQUIRE_THROWS(node->insert(5, 5));
					}
				}
			}
		}
	}
	SECTION("multi_way_entry_ordered_map with elements (1,1), (2,2), (3,3), (4,4), (5,5)")
	{
		auto node = std::make_shared<data_structures_cpp::multi_way_node<int, int, 3, 5>>();
		node->build();
		node->insert(1, 1);
		node->insert(2, 2);
		node->insert(3, 3);
		node->insert(4, 4);
		node->insert(5, 5);
		SECTION("less_than is coherent")
		{
			REQUIRE(node->less_than(1) == node->end());
			REQUIRE((*node->less_than(2))->key() == 1);
			REQUIRE((*node->less_than(5))->key() == 4);
			REQUIRE((*node->less_than(4))->key() == 3);
			REQUIRE(node->less_than(0) == node->end());
			REQUIRE((*node->less_than(6))->key() == 5);
			REQUIRE((*node->less_than(50))->key() == 5);
		}
		SECTION("greater_than is coherent")
		{
			REQUIRE((*node->greater_than(1))->key() == 2);
			REQUIRE((*node->greater_than(2))->key() == 3);
			REQUIRE((*node->greater_than(3))->key() == 4);
			REQUIRE(node->greater_than(5) == node->last());
			REQUIRE((*node->greater_than(4))->key() == 5);
			REQUIRE((*node->greater_than(0))->key() == 1);
			REQUIRE(node->greater_than(6) == node->last());
			REQUIRE(node->greater_than(50) == node->last());
		}
		SECTION("inserting another element throws")
		{
			REQUIRE_THROWS(node->insert(0, 0));
			REQUIRE(node->size() == 5);
		}
	}
}