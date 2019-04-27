#include <catch2/catch.hpp>

#include <memory>

#include "tree/multi_way_tree.h"

TEST_CASE("multi_way_node has coherent key sequencing", "[multi_way_tree]")
{
	SECTION("given an empty multi_way_node (2, 4)")
	{
		auto tree_node = std::make_shared<data_structures_cpp::multi_way_node<int, int, 2, 4>>();
		
		SECTION("inserting pairs (4,4), (1,1), (400,3)")
		{
			tree_node->insert(4, 4, tree_node);
			tree_node->insert(1, 1, tree_node);
			tree_node->insert(400, 3, tree_node);
			
			REQUIRE(tree_node->size() == 3);
			
			SECTION("single multi_way_node has no parent")
			{
				REQUIRE(tree_node->parent() == nullptr);
			}
			SECTION("yields coherent less_than and greater_than")
			{
				REQUIRE(tree_node->less_than(400)->key() == 4);
				REQUIRE(tree_node->less_than(400)->value() == 4);
				REQUIRE(tree_node->greater_than(400) == tree_node->end());
						
				REQUIRE(tree_node->greater_than(4)->key() == 400);
				REQUIRE(tree_node->greater_than(4)->value() == 3);
				REQUIRE(tree_node->less_than(4)->key() == 1);
				REQUIRE(tree_node->less_than(4)->value() == 1);
						
				REQUIRE(tree_node->greater_than(1)->key() == 4);
				REQUIRE(tree_node->greater_than(1)->value() == 4);
				REQUIRE(tree_node->less_than(1) == tree_node->end());
			}
			SECTION("yields correct ordered sequence")
			{
				auto it = tree_node->begin();
				REQUIRE((it++)->key() == 1);
				REQUIRE((it++)->key() == 4);
				REQUIRE((it++)->key() == 400);
				REQUIRE(it == tree_node->end());
			}
			SECTION("multi_way tree node should not be able to overflow by 1 without throwing on exceeded capacity")
			{
				REQUIRE_NOTHROW(tree_node->insert(150, 0, tree_node));
				REQUIRE(tree_node->full());
				REQUIRE(tree_node->size() == 4);
			}
			SECTION("erasing an entry should yield tree_node not full")
			{
				tree_node->erase(4);
				REQUIRE_FALSE(tree_node->full());
				REQUIRE(tree_node->size() == 2);
			}
			SECTION("clearing the node yields shared_ptr use count of 1")
			{
				auto count = tree_node.use_count();
				tree_node->clear();
				count = tree_node.use_count();
				REQUIRE(count == 1);
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
			tree.insert("i am minh", "a vietnamese");
			tree.insert("i am afsa", "a persian");
			tree.insert("i am azeen", "a persian");
			tree.insert("i am quoc-anh", "a father");
			tree.insert("i am doan-tran", "a mother");
			tree.insert("i am yahya", "a father");
			tree.insert("i am shahnaz", "a mother");
			REQUIRE(tree.size() == 7);
			REQUIRE_FALSE(tree.empty());
			SECTION("retrieving elements is possible")
			{
				auto it = tree.find("i am minh");
				REQUIRE((*it).key() == "i am minh");
				REQUIRE((*it).value() == "a vietnamese");
				it = tree.find("i am quoc-anh");
				REQUIRE((*it).key() == "i am quoc-anh");
				REQUIRE((*it).value() == "a father");
				it = tree.find("i am shahnaz");
				REQUIRE((*it).key() == "i am shahnaz");
				REQUIRE((*it).value() == "a mother");
			}
		}
	}
}