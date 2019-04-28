#include <catch2/catch.hpp>

#include "tree/multi_way_tree_node.h"

TEST_CASE("multi_way_tree_node has coherent key sequencing", "[multi_way_tree]")
{
	SECTION("given an empty multi_way_tree_node (2, 4)")
	{
		auto tree_node = std::make_shared<data_structures_cpp::multi_way_tree_node<int, int, 2, 4>>();
		tree_node->build();

		SECTION("multi_way_tree_node recognizes if it is external")
		{
			REQUIRE(tree_node->external());
			tree_node->insert(1, 1);
			REQUIRE_FALSE(tree_node->external());
		}
		SECTION("inserting pairs (4,4), (1,1), (400,3)")
		{
			tree_node->insert(4, 4);
			tree_node->insert(1, 1);
			tree_node->insert(400, 3);

			REQUIRE(tree_node->size() == 3);

			SECTION("single multi_way_tree_node has no parent")
			{
				REQUIRE(tree_node->parent() == nullptr);
			}
			SECTION("yields coherent less_than and greater_than")
			{
				REQUIRE((*tree_node->less_than(400))->key() == 4);
				REQUIRE((*tree_node->less_than(400))->value() == 4);
				REQUIRE(tree_node->greater_than(400) == tree_node->last());

				REQUIRE((*tree_node->greater_than(4))->key() == 400);
				REQUIRE((*tree_node->greater_than(4))->value() == 3);
				REQUIRE((*tree_node->less_than(4))->key() == 1);
				REQUIRE((*tree_node->less_than(4))->value() == 1);

				REQUIRE((*tree_node->greater_than(1))->key() == 4);
				REQUIRE((*tree_node->greater_than(1))->value() == 4);
				REQUIRE(tree_node->less_than(1) == tree_node->end());
			}
			SECTION("yields correct ordered sequence")
			{
				auto it = tree_node->begin();
				REQUIRE((*it)->key() == 1); it++;
				REQUIRE((*it)->key() == 4); it++;
				REQUIRE((*it)->key() == 400); it++;
				REQUIRE(it == tree_node->last()); it++;
				REQUIRE(it == tree_node->end());
			}
			SECTION("multi_way tree node should not be able to overflow by 1 without throwing on exceeded capacity")
			{
				REQUIRE_NOTHROW(tree_node->insert(150, 0));
				REQUIRE(tree_node->full());
				REQUIRE(tree_node->size() == 4);
			}
			SECTION("erasing an entry should yield tree_node not full")
			{
				tree_node->erase(4);
				REQUIRE_FALSE(tree_node->full());
				REQUIRE(tree_node->size() == 2);
			}
		}
	}
}
