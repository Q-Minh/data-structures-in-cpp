cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (tests)

# To find and use catch
find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(tests PRIVATE Catch2::Catch2)

target_include_directories(tests
	PRIVATE
		"${CMAKE_SOURCE_DIR}/data-structures-and-algorithms-cpp"
	)

target_sources(tests
	PRIVATE
		./main.cpp
		./queue/array_queue.cpp
		./queue/double_ended_queue.cpp
		./list/circular_linked_list.cpp
		./list/doubly_linked_list.cpp
		./list/singly_linked_list.cpp
		./stack/linked_list_stack.cpp
		./stack/array_stack.cpp
		./stack/double_ended_queue_stack.cpp
		./vector/vector.cpp
		"./tree/linked_binary_tree.cpp"
		"./tree/vector_binary_tree.cpp"
		"./tree/binary_search_tree.cpp"
		"./tree/avl_tree.cpp"
		./priority_queue/list_priority_queue.cpp
		./priority_queue/vector_priority_queue.cpp
		./priority_queue/adaptable_priority_queue.cpp
		./map/separate_chaining_hash_table.cpp
		./map/dictionary.cpp
	)

# TODO: Add tests and install targets if needed.
