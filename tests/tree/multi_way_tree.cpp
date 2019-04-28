#include <catch2/catch.hpp>

#include <memory>

#include "tree/multi_way_tree_node.h"
#include "tree/multi_way_tree.h"

TEST_CASE("multi_way_node has coherent key sequencing", "[multi_way_tree]")
{
	SECTION("given an empty multi_way_node (2, 4)")
	{
		auto tree_node = std::make_shared<data_structures_cpp::multi_way_node<int, int, 2, 4>>();
		tree_node->build();
		
		SECTION("multi_way_node recognizes if it is external")
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
			
			SECTION("single multi_way_node has no parent")
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

TEST_CASE("multi_way_tree has coherent reads and writes", "[multi_way_tree]")
{
	SECTION("given an empty multi_way_tree")
	{
		data_structures_cpp::multi_way_tree<std::string, std::string, 2, 4> tree;
		REQUIRE(tree.size() == 0);
		REQUIRE(tree.empty());
		REQUIRE(tree.begin() == tree.end());
		SECTION("inserting elements is possible")
		{
			tree.insert("a", "a");
			tree.insert("b", "a");
			tree.insert("c", "a");
			tree.insert("d", "a");
			tree.insert("e", "a");
			tree.insert("f", "a");
			tree.insert("g", "a");
			REQUIRE(tree.size() == 7);
			REQUIRE_FALSE(tree.empty());
			SECTION("retrieving elements is possible")
			{
				auto it = tree.find("a");
				REQUIRE((*it)->key() == "a");
				REQUIRE((*it)->value() == "a");
				it = tree.find("d");
				REQUIRE((*it)->key() == "d");
				REQUIRE((*it)->value() == "a");
				it = tree.find("g");
				REQUIRE((*it)->key() == "g");
				REQUIRE((*it)->value() == "a");
			}
			SECTION("inserting many more elements")
			{
				tree.insert("h", "a");
				tree.insert("i", "a");
				tree.insert("j", "a");
				tree.insert("k", "a");
				tree.insert("l", "a");
				tree.insert("m", "a");
				tree.insert("n", "a");
				tree.insert("o", "a");
				tree.insert("p", "a");
				tree.insert("q", "a");
				tree.insert("r", "a");
				tree.insert("s", "a");
				tree.insert("t", "a");
				tree.insert("u", "a");
				tree.insert("v", "a");
				tree.insert("w", "a");
				tree.insert("x", "a");
				tree.insert("y", "a");
				tree.insert("z", "a");
				REQUIRE(tree.size() == 26);
				SECTION("retrieving all elements is possible")
				{
					auto it = tree.find("a");
					REQUIRE((*it)->key() == "a");
					REQUIRE((*it)->value() == "a");
					it = tree.find("b");
					REQUIRE((*it)->key() == "b");
					REQUIRE((*it)->value() == "a");
					it = tree.find("c");
					REQUIRE((*it)->key() == "c");
					REQUIRE((*it)->value() == "a");
					it = tree.find("d");
					REQUIRE((*it)->key() == "d");
					REQUIRE((*it)->value() == "a");
					it = tree.find("e");
					REQUIRE((*it)->key() == "e");
					REQUIRE((*it)->value() == "a");
					it = tree.find("f");
					REQUIRE((*it)->key() == "f");
					REQUIRE((*it)->value() == "a");
					it = tree.find("g");
					REQUIRE((*it)->key() == "g");
					REQUIRE((*it)->value() == "a");
					it = tree.find("h");
					REQUIRE((*it)->key() == "h");
					REQUIRE((*it)->value() == "a");
					it = tree.find("i");
					REQUIRE((*it)->key() == "i");
					REQUIRE((*it)->value() == "a");
					it = tree.find("j");
					REQUIRE((*it)->key() == "j");
					REQUIRE((*it)->value() == "a");
					it = tree.find("k");
					REQUIRE((*it)->key() == "k");
					REQUIRE((*it)->value() == "a");
					it = tree.find("l");
					REQUIRE((*it)->key() == "l");
					REQUIRE((*it)->value() == "a");
					it = tree.find("m");
					REQUIRE((*it)->key() == "m");
					REQUIRE((*it)->value() == "a");
					it = tree.find("n");
					REQUIRE((*it)->key() == "n");
					REQUIRE((*it)->value() == "a");
					it = tree.find("o");
					REQUIRE((*it)->key() == "o");
					REQUIRE((*it)->value() == "a");
					it = tree.find("p");
					REQUIRE((*it)->key() == "p");
					REQUIRE((*it)->value() == "a");
					it = tree.find("q");
					REQUIRE((*it)->key() == "q");
					REQUIRE((*it)->value() == "a");
					it = tree.find("r");
					REQUIRE((*it)->key() == "r");
					REQUIRE((*it)->value() == "a");
					it = tree.find("s");
					REQUIRE((*it)->key() == "s");
					REQUIRE((*it)->value() == "a");
					it = tree.find("t");
					REQUIRE((*it)->key() == "t");
					REQUIRE((*it)->value() == "a");
					it = tree.find("u");
					REQUIRE((*it)->key() == "u");
					REQUIRE((*it)->value() == "a");
					it = tree.find("v");
					REQUIRE((*it)->key() == "v");
					REQUIRE((*it)->value() == "a");
					it = tree.find("w");
					REQUIRE((*it)->key() == "w");
					REQUIRE((*it)->value() == "a");
					it = tree.find("x");
					REQUIRE((*it)->key() == "x");
					REQUIRE((*it)->value() == "a");
					it = tree.find("y");
					REQUIRE((*it)->key() == "y");
					REQUIRE((*it)->value() == "a");
					it = tree.find("z");
					REQUIRE((*it)->key() == "z");
					REQUIRE((*it)->value() == "a");
				}
				SECTION("inserting eeeeven more elements")
				{
					tree.insert("aa", "a");
					tree.insert("bb", "a");
					tree.insert("cc", "a");
					tree.insert("dd", "a");
					tree.insert("ee", "a");
					tree.insert("ff", "a");
					tree.insert("gg", "a");
					tree.insert("hh", "a");
					tree.insert("ii", "a");
					
					// adding a duplicate!
					tree.insert("ii", "a");

					tree.insert("jj", "a");
					tree.insert("kk", "a");
					tree.insert("ll", "a");
					tree.insert("mm", "a");
					tree.insert("nn", "a");
					tree.insert("oo", "a");
					tree.insert("pp", "a");
					tree.insert("qq", "a");
					tree.insert("rr", "a");
					tree.insert("ss", "a");
					tree.insert("tt", "a");
					tree.insert("uu", "a");
					tree.insert("vv", "a");
					tree.insert("ww", "a");
					tree.insert("xx", "a");
					tree.insert("yy", "a");
					tree.insert("zz", "a");
					REQUIRE(tree.size() == 53);
					SECTION("retrieving all elements is possible")
					{
						auto it = tree.find("a");
						REQUIRE((*it)->key() == "a");
						REQUIRE((*it)->value() == "a");
						it = tree.find("b");
						REQUIRE((*it)->key() == "b");
						REQUIRE((*it)->value() == "a");
						it = tree.find("c");
						REQUIRE((*it)->key() == "c");
						REQUIRE((*it)->value() == "a");
						it = tree.find("d");
						REQUIRE((*it)->key() == "d");
						REQUIRE((*it)->value() == "a");
						it = tree.find("e");
						REQUIRE((*it)->key() == "e");
						REQUIRE((*it)->value() == "a");
						it = tree.find("f");
						REQUIRE((*it)->key() == "f");
						REQUIRE((*it)->value() == "a");
						it = tree.find("g");
						REQUIRE((*it)->key() == "g");
						REQUIRE((*it)->value() == "a");
						it = tree.find("h");
						REQUIRE((*it)->key() == "h");
						REQUIRE((*it)->value() == "a");
						it = tree.find("i");
						REQUIRE((*it)->key() == "i");
						REQUIRE((*it)->value() == "a");
						it = tree.find("j");
						REQUIRE((*it)->key() == "j");
						REQUIRE((*it)->value() == "a");
						it = tree.find("k");
						REQUIRE((*it)->key() == "k");
						REQUIRE((*it)->value() == "a");
						it = tree.find("l");
						REQUIRE((*it)->key() == "l");
						REQUIRE((*it)->value() == "a");
						it = tree.find("m");
						REQUIRE((*it)->key() == "m");
						REQUIRE((*it)->value() == "a");
						it = tree.find("n");
						REQUIRE((*it)->key() == "n");
						REQUIRE((*it)->value() == "a");
						it = tree.find("o");
						REQUIRE((*it)->key() == "o");
						REQUIRE((*it)->value() == "a");
						it = tree.find("p");
						REQUIRE((*it)->key() == "p");
						REQUIRE((*it)->value() == "a");
						it = tree.find("q");
						REQUIRE((*it)->key() == "q");
						REQUIRE((*it)->value() == "a");
						it = tree.find("r");
						REQUIRE((*it)->key() == "r");
						REQUIRE((*it)->value() == "a");
						it = tree.find("s");
						REQUIRE((*it)->key() == "s");
						REQUIRE((*it)->value() == "a");
						it = tree.find("t");
						REQUIRE((*it)->key() == "t");
						REQUIRE((*it)->value() == "a");
						it = tree.find("u");
						REQUIRE((*it)->key() == "u");
						REQUIRE((*it)->value() == "a");
						it = tree.find("v");
						REQUIRE((*it)->key() == "v");
						REQUIRE((*it)->value() == "a");
						it = tree.find("w");
						REQUIRE((*it)->key() == "w");
						REQUIRE((*it)->value() == "a");
						it = tree.find("x");
						REQUIRE((*it)->key() == "x");
						REQUIRE((*it)->value() == "a");
						it = tree.find("y");
						REQUIRE((*it)->key() == "y");
						REQUIRE((*it)->value() == "a");
						it = tree.find("z");
						REQUIRE((*it)->key() == "z");
						REQUIRE((*it)->value() == "a");

						it = tree.find("aa");
						REQUIRE((*it)->key() == "aa");
						REQUIRE((*it)->value() == "a");
						it = tree.find("bb");
						REQUIRE((*it)->key() == "bb");
						REQUIRE((*it)->value() == "a");
						it = tree.find("cc");
						REQUIRE((*it)->key() == "cc");
						REQUIRE((*it)->value() == "a");
						it = tree.find("dd");
						REQUIRE((*it)->key() == "dd");
						REQUIRE((*it)->value() == "a");
						it = tree.find("ee");
						REQUIRE((*it)->key() == "ee");
						REQUIRE((*it)->value() == "a");
						it = tree.find("ff");
						REQUIRE((*it)->key() == "ff");
						REQUIRE((*it)->value() == "a");
						it = tree.find("gg");
						REQUIRE((*it)->key() == "gg");
						REQUIRE((*it)->value() == "a");
						it = tree.find("hh");
						REQUIRE((*it)->key() == "hh");
						REQUIRE((*it)->value() == "a");
						it = tree.find("ii");
						REQUIRE((*it)->key() == "ii");
						REQUIRE((*it)->value() == "a");
						it = tree.find("jj");
						REQUIRE((*it)->key() == "jj");
						REQUIRE((*it)->value() == "a");
						it = tree.find("kk");
						REQUIRE((*it)->key() == "kk");
						REQUIRE((*it)->value() == "a");
						it = tree.find("ll");
						REQUIRE((*it)->key() == "ll");
						REQUIRE((*it)->value() == "a");
						it = tree.find("mm");
						REQUIRE((*it)->key() == "mm");
						REQUIRE((*it)->value() == "a");
						it = tree.find("nn");
						REQUIRE((*it)->key() == "nn");
						REQUIRE((*it)->value() == "a");
						it = tree.find("oo");
						REQUIRE((*it)->key() == "oo");
						REQUIRE((*it)->value() == "a");
						it = tree.find("pp");
						REQUIRE((*it)->key() == "pp");
						REQUIRE((*it)->value() == "a");
						it = tree.find("qq");
						REQUIRE((*it)->key() == "qq");
						REQUIRE((*it)->value() == "a");
						it = tree.find("rr");
						REQUIRE((*it)->key() == "rr");
						REQUIRE((*it)->value() == "a");
						it = tree.find("ss");
						REQUIRE((*it)->key() == "ss");
						REQUIRE((*it)->value() == "a");
						it = tree.find("tt");
						REQUIRE((*it)->key() == "tt");
						REQUIRE((*it)->value() == "a");
						it = tree.find("uu");
						REQUIRE((*it)->key() == "uu");
						REQUIRE((*it)->value() == "a");
						it = tree.find("vv");
						REQUIRE((*it)->key() == "vv");
						REQUIRE((*it)->value() == "a");
						it = tree.find("ww");
						REQUIRE((*it)->key() == "ww");
						REQUIRE((*it)->value() == "a");
						it = tree.find("xx");
						REQUIRE((*it)->key() == "xx");
						REQUIRE((*it)->value() == "a");
						it = tree.find("yy");
						REQUIRE((*it)->key() == "yy");
						REQUIRE((*it)->value() == "a");
						it = tree.find("zz");
						REQUIRE((*it)->key() == "zz");
						REQUIRE((*it)->value() == "a");
					}
				}
			}
		}
	}
}