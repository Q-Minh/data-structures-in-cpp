#include <catch2/catch.hpp>

#include "tree/multi_way_tree.h"

TEST_CASE("multi_way_node has coherent key sequencing", "[multi_way_tree]")
{
	SECTION("given an empty multi_way_node (2, 4)")
	{
		data_structures_cpp::multi_way_node<int, int, 2, 4> tree_node;
		
		SECTION("inserting pairs (4,4), (1,1), (400,3)")
		{
			tree_node.insert(4, 4);
			tree_node.insert(1, 1);
			tree_node.insert(400, 3);
			
			REQUIRE(tree_node.size() == 3);
			
			SECTION("yields coherent less_than and greater_than")
			{
				REQUIRE(tree_node.less_than(400)->key() == 4);
				REQUIRE(tree_node.less_than(400)->value() == 4);
				REQUIRE(tree_node.greater_than(400) == tree_node.end());

				REQUIRE(tree_node.greater_than(4)->key() == 400);
				REQUIRE(tree_node.greater_than(4)->value() == 3);
				REQUIRE(tree_node.less_than(4)->key() == 1);
				REQUIRE(tree_node.less_than(4)->value() == 1);

				REQUIRE(tree_node.greater_than(1)->key() == 4);
				REQUIRE(tree_node.greater_than(1)->value() == 4);
				REQUIRE(tree_node.less_than(1) == tree_node.end());
			}
			SECTION("yields correct ordered sequence")
			{
				auto it = tree_node.begin();
				REQUIRE((it++)->key() == 1);
				REQUIRE((it++)->key() == 4);
				REQUIRE((it++)->key() == 400);
				REQUIRE(it == tree_node.end());
			}
			SECTION("multi_way tree node should be able to overflow by 1 without throwing on exceeded capacity")
			{
				REQUIRE_NOTHROW(tree_node.insert(150, 0));
				REQUIRE(tree_node.size() == 4);

			}
		}
	}
}