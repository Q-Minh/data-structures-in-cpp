# data-structures-in-cpp
amateur implementations of classic data structures in c++

The implementations follow [this book](https://o6ucs.files.wordpress.com/2012/11/data-structures-and-algorithms-in-c.pdf)
and provide minor modifications and fill-in-the-blanks add-ons to the examples presented. The book has been an amazing
learning experience so far, and is thus suggested to everyone interested and wanting to start learning data structures.
The implementations try to be short and concise and try to make use of modern C++ features, although the focus is not on
using the latest and greatest language features. Suggestions and feedback are appreciated, though note that I am not trying
to write the most optimized data structures ever, but simply trying to help myself or others learn. Previous knowledge on
c++ templates is recommended if wanting to understand the implementation code. C++ templates are most assuredly not the same
as Java and C# generics, so beware.

## building
The project uses CMake and has only been tested on Windows 10 in Visual Studio 2017, but should work on other platforms as well.

On Windows, you can use Visual Studio to open CMake Project choosing root CMakeLists.txt file. By default, Visual Studio will use `Ninja` as CMake's build generator. I suggest using [vcpk](https://github.com/Microsoft/vcpkg) as package manager as it is very easy to use with CMake and offers a wide range of popular and standard C++ libraries. If you are the same, you should change your CMake build generator to use `Visual Studio 15 2017` instead to enable vcpkg cmake integration seamlessly. If not using Visual Studio, I don't know what to say since I have no experience developing C++ on Windows without VS.

On Linux platforms: `mkdir build && cd build && cmake .. && make;`
Unix Makefiles should be default build generator.

I have never used macOS and assume same commands as linux should work.

Building should be easy as project is header-only.

## running
There is a tests subfolder which uses [Catch2](https://github.com/catchorg/Catch2) as a testing framework. The CMakeLists.txt file used for building the tests uses the `find_package(...)` command, so make sure Catch2 is discoverable by CMake if wanting to build the tests. Again, I suggest enabling system wide integration through [vcpkg](https://github.com/Microsoft/vcpkg) to enable easy discoverability.
The tests are by no means complete, they are there to prove some minimal degree of functionality and to try out Catch2.

In the future, I would like to add benchmarks comparing theory to practice, as well as try out different memory allocation schemes to try to preserve the simplicity of node-based linked data structures and obtain performance enhancements from optimizing cache temporal/spatial locality and avoiding memory fragmentation of node-based linked data structures.

## lists
### currently implemented data structures are
- singly linked list
- doubly linked list
- circular linked list
### coming up next
- skip list

## queues
### currently implemented
- array based queue
- doubly linked list based queue (deque)
- linked list based priority queue
- extendable array vector based priority queue
- linked list based adaptable priority queue

## stacks
### currently implemented
- array based stack
- deque based stack
- linked list based stack (singly or doubly)

## vector
### currently implemented
- extendable array based vector

## trees
### currently implemented
- node based linked general tree
- vector based binary tree **(failing tests)**
- vector based heap using complete binary tree
- node based linked binary search tree
- avl tree extending node based linked binary tree
### coming up next
- multi-way tree
- red-black tree
- standard trie
- compression trie

## maps
### currently implemented
- hash table with separate chaining collision handling scheme
- dictionary that extends map by allowing duplicate entries

## sets
### coming up next
- **to be determined**

## graphs
### coming up next
- node based adjacency list
- array based adjacency matrix
