#include <catch2/catch.hpp>

#include <string>

#include "tree/linked_binary_tree.h"

TEMPLATE_TEST_CASE("linked_binary_tree's size is coherent", "[linked_binary_tree]", int, std::string)
{
	SECTION("given an empty linked_binary_tree")
	{
		data_structures_cpp::linked_binary_tree<TestType> tree{};
		REQUIRE(tree.empty());
		REQUIRE(tree.size() == 0);
		SECTION("adding the root to the tree")
		{
			tree.add_root();
			SECTION("yields size() == 1")
			{
				REQUIRE(tree.size() == 1);
				REQUIRE_FALSE(tree.empty());
				REQUIRE_THROWS(tree.add_root());
			}
			SECTION("expanding the root")
			{
				auto root = tree.root();
				*root = 1;
				tree.expand_external(root);
				auto left = root.left();
				*left = 2;
				auto right = root.right();
				*right = 3;
				SECTION("yields size = 3")
				{
					REQUIRE(tree.size() == 3);
					REQUIRE_FALSE(tree.empty());
				}
				SECTION("expanding both subsequent subtrees")
				{
					tree.expand_external(left);
					auto leftleft = left.left();
					auto leftright = left.right();
					*leftleft = 4;
					*leftright = 5;
					tree.expand_external(right);
					auto rightleft = right.left();
					auto rightright = right.right();
					*rightleft = 6;
					*rightright = 7;
					auto positions = tree.positions();
					SECTION("yields size = 7")
					{
						REQUIRE(tree.size() == 7);
						REQUIRE_FALSE(tree.empty());
					}
					SECTION("removing above lower left leaf")
					{
						tree.remove_above_external(leftleft);
						SECTION("yields size = 5")
						{
							REQUIRE(tree.size() == 5);
							REQUIRE_FALSE(tree.empty());
						}
					}
				}
			}
		}
	}
}