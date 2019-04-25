# CMakeList.txt : CMake project for DataStructuresAndAlgorithmsForCpp_ch05, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (data-structures-algorithms-cpp INTERFACE)

# Fill in dependencies
target_include_directories(data-structures-algorithms-cpp
	INTERFACE 
		${CMAKE_CURRENT_LIST_DIR}
	)
