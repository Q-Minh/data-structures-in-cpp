#include <catch2/catch.hpp>

#include <string>

#include "tree/vector_binary_tree.h"

TEMPLATE_TEST_CASE("vector_binary_tree's size is coherent", "[vector_binary_tree]", int, std::string)
{
	SECTION("given an empty vector_binary_tree")
	{
		data_structures_cpp::vector_binary_tree<TestType> tree{};
		REQUIRE(tree.empty());
		REQUIRE(tree.size() == 0);
		SECTION("adding the root to the tree")
		{
			tree.add_root();
			SECTION("yields size() == 1")
			{
				REQUIRE(tree.size() == 1);
				REQUIRE_FALSE(tree.empty());
			}
			SECTION("expanding the root")
			{
				auto root{ tree.root() };
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
						positions = tree.positions();
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

TEST_CASE("vector_binary_tree respects binary tree rules", "[vector_binary_tree]")
{
	SECTION("given an empty vector_binary_tree")
	{
		using tree_t = data_structures_cpp::vector_binary_tree<std::string>;
		tree_t tree{};
		REQUIRE(tree.empty());
		REQUIRE(tree.size() == 0);
		SECTION("adding a root and setting its value to 'i am root'")
		{
			tree.add_root();
			auto root{ tree.root() };
			*root = "i am root";

			SECTION("return value of root() has root() == true and external() == true and dereferencing it returns 'i am root'")
			{
				REQUIRE(root.root());
				REQUIRE(root.external());
				REQUIRE(*root == "i am root");
			}
			SECTION("adding left and right children of 'i am left child' and 'i am right child'")
			{
				tree.expand_external(root);
				auto left = root.left();
				*left = "i am left child";
				auto right = root.right();
				*right = "i am right child";

				SECTION("yields a position list in preorder order")
				{
					std::list<data_structures_cpp::vector_binary_tree_position<std::string>> list{};
					list.push_back(root);
					list.push_back(left);
					list.push_back(right);
					auto positions = tree.positions();
					for (auto it = list.cbegin(), pos = positions.cbegin(); it != list.cend(); ++it, ++pos)
					{
						REQUIRE(*(*it) == *(*pos));
					}
				}
				SECTION("expanding left child and right child")
				{
					tree.expand_external(left);
					tree.expand_external(right);
					auto leftleft = left.left();
					auto leftright = left.right();
					*leftleft = "i am left child of left child";
					*leftright = "i am right child of left child";
					auto rightleft = right.left();
					auto rightright = right.right();
					*rightleft = "i am left child of right child";
					*rightright = "i am right child of right child";

					SECTION("yields yet again position list in preorder order")
					{
						std::list<data_structures_cpp::vector_binary_tree_position<std::string>> list{};
						list.push_back(root);
						list.push_back(left);
						list.push_back(leftleft);
						list.push_back(leftright);
						list.push_back(right);
						list.push_back(rightleft);
						list.push_back(rightright);
						auto positions = tree.positions();
						for (auto it = list.cbegin(), pos = positions.cbegin(); it != list.cend(); ++it, ++pos)
						{
							REQUIRE(*(*it) == *(*pos));
						}
					}
					SECTION("removing above internal nodes left throws exception")
					{
						REQUIRE_THROWS(tree.remove_above_external(left));
					}
					SECTION("removing above internal nodes right throws exception")
					{
						REQUIRE_THROWS(tree.remove_above_external(right));
					}
					SECTION("removing above internal nodes root throws exception")
					{
						REQUIRE_THROWS(tree.remove_above_external(root));
					}
					SECTION("removing above external node right-left")
					{
						tree.remove_above_external(rightleft);
						SECTION("preserves preorder ordering")
						{
							std::list<data_structures_cpp::vector_binary_tree_position<std::string>> list{};
							list.push_back(root);
							list.push_back(left);
							list.push_back(leftleft);
							list.push_back(leftright);
							list.push_back(rightright);
							auto positions = tree.positions();
							for (auto it = list.cbegin(), pos = positions.cbegin(); it != list.cend(); ++it, ++pos)
							{
								REQUIRE(*(*it) == *(*pos));
							}
						}
					}
					SECTION("removing above external node left-right")
					{
						tree.remove_above_external(leftright);
						SECTION("preserves preorder ordering")
						{
							std::list<data_structures_cpp::vector_binary_tree_position<std::string>> list{};
							list.push_back(root);
							list.push_back(leftleft);
							list.push_back(right);
							list.push_back(rightleft);
							list.push_back(rightright);
							auto positions = tree.positions();
							for (auto it = list.cbegin(), pos = positions.cbegin(); it != list.cend(); ++it, ++pos)
							{
								REQUIRE(*(*it) == *(*pos));
							}
						}
					}
					SECTION("removing above external node left-left")
					{
						tree.remove_above_external(leftleft);
						SECTION("preserves preorder ordering")
						{
							std::list<data_structures_cpp::vector_binary_tree_position<std::string>> list{};
							list.push_back(root);
							list.push_back(leftright);
							list.push_back(right);
							list.push_back(rightleft);
							list.push_back(rightright);
							auto positions = tree.positions();
							for (auto it = list.cbegin(), pos = positions.cbegin(); it != list.cend(); ++it, ++pos)
							{
								REQUIRE(*(*it) == *(*pos));
							}
						}
					}
					SECTION("removing above external node right-right")
					{
						tree.remove_above_external(rightright);
						SECTION("preserves preorder ordering")
						{
							std::list<data_structures_cpp::vector_binary_tree_position<std::string>> list{};
							list.push_back(root);
							list.push_back(left);
							list.push_back(leftleft);
							list.push_back(leftright);
							list.push_back(rightleft);
							auto positions = tree.positions();
							for (auto it = list.cbegin(), pos = positions.cbegin(); it != list.cend(); ++it, ++pos)
							{
								REQUIRE(*(*it) == *(*pos));
							}
						}
						SECTION("then removing above right")
						{
							tree.remove_above_external(right);
							SECTION("preserves preorder ordering")
							{
								std::list<data_structures_cpp::vector_binary_tree_position<std::string>> list{};
								list.push_back(left);
								list.push_back(leftleft);
								list.push_back(leftright);
								auto positions = tree.positions();
								REQUIRE(positions.size() == list.size());
								for (auto it = list.cbegin(), pos = positions.cbegin(); it != list.cend(); ++it, ++pos)
								{
									REQUIRE(*(*it) == *(*pos));
								}
							}
						}
					}
				}
			}
		}
	}
}