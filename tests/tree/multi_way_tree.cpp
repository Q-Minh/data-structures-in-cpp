#include <catch2/catch.hpp>

#include "tree/multi_way_tree.h"

TEST_CASE("multi_way_node has coherent key sequencing", "[multi_way_tree]")
{
	SECTION("given an empty multi_way_node (2, 4)")
	{
		data_structures_cpp::multi_way_node<int, int, 2, 4> tree_node;
		
		SECTION("inserting pairs (4,4), (1,1), (400,3), (203,2)")
		{
			tree_node.insert(4, 4);
			tree_node.insert(1, 1);
			tree_node.insert(400, 3);
			tree_node.insert(203, 2);

		}
	}
}