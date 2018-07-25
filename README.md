Data Structures
===============

## Overview

This package contains template implementations of generic data structures already implemented in C++ provided by STL. The purpose is to familiarize with different data structures and behaviors. 

1- Dynamic Array
	Implementation of a template class, DynArray, that will encapsulate the dynamic array functionality. The default expansion rate is double the current capacity with a minimum of 1.
	
2- BinaryHeap - depends on DynArray class
	Binary Heap implementation using protected inheritance from the [DynArray]() class rather than containment. 
	For a 0-indexed binary heap, the formulas for parents and children are as follows:
			I*2+1 (left child)
			I*2+2 (right child)
			(I-1)/2 (parent)
			
3- Singly Listed List
	Single-ended, singly-linked list templated class implementation named SLList and an iterator class named SLLIter to access the SLList. 
	
4- Doubly Listed List and Iterator
	Implementation of a templated, double-ended, doubly-linked list and an iterator class to access the DLList. 

5- Hash Table - depends on SLList class
	Following Wikipedia's [definition](https://en.wikipedia.org/wiki/Hash_table); implementation of a hash table using the previously implemented singly linked list.
	
6- Binary Search Tree - depends on SLList class
	Following Wikipedia's [definition](https://en.wikipedia.org/wiki/Binary_search_tree); implementation of a hash table using the previously implemented singly linked list.
		
7- Graph - depends on DynArray & SLList & DLList classes
	Implementation of a templated Graph class, with two publicly nested classes named Edge and Vertex. The graph class functions as an adjacency list. Each Edge contains the index of a vertex the edge connects to. Each Vertex contains a piece of data and a singly linked list of edges that stores all of that vertex’s adjacencies. The Graph itself contains a DynArray of vertices representing all the vertices in the graph.

8- Bit Stream
	Implementation of a class that allows streaming individual bits to and from a file. Added some binary files for the tests.

9- Huffman Compression - depends on BitStream class
	Implementation of a series of functions used to compress a file using Huffman’s algorithm. This package contains some util functions to make the tests easier. Also added binary files and decoded output.
	
## The Tests

1- Dynamic Array
	Test1: test append function
	Test2: test reverse function and attempt to make it smaller
	Test3: test reverse function
	Test4: test overwrite behavior
	Test5: test copy constructor, assignment operator and destructor (Trilogy of Evil)
	Test6; test default reserve behavior starting with an empty array
	Test7: test reserve behavior - append, reserve, then call append to add items
	Test8: test assignment edge cases
	Test9: test to try breaking the behavior (weirdness test)
	Test10: test self-Assignment
	Test11: test insert behavior
	Test12: test remove behavior
	
2- Binary Heap
	Test1: test enqueue function
	Test2: test dequeue function
	Test3: test assignment operator
	Test4: if uncommenting this test compiles then the BinaryHeap class is wrong implemented

3- Singly Listed List
	Test1: test insert (addHead) function
	Test2: test insert and remove function
	Test3: test assignment operator
	Test4: stress and edge case testing
	
4- Doubly Listed List
	Test1: test adding to the head and tail
	Test2: test insert and remove at various locations
	Test3: test assignment operator
	Test4: stress and edge case testing
	
5- Hash Table
	Test1: test Constructor, insert, find and clear function
	Test2: test findAndRemove function
	
6- Binary Search Tree
	Test1: test add a few nodes, print, and clear the tree
	Test2: test add a few nodes, do searching on the items, and clear the tree
	Test3: test add a few nodes, remove some, and clear the tree
	Test4: test assignment operator
	
7- Graph
	Test1: test Constructor, addVertex and addEdge function
	Test2: test printBreadthFirst function
	Test3: test Copy Constructor/Assignment Operator
	Test4: test String
	
8- Bit Stream
	Test1: test BitOStream (no Header)
	Test2: test BitOStream (with header)
	Test3: test BitIStream (no header)
	Test4: test BitIStream (with header)
	
9- Huffman Compression
	Test1: test GenerateFrequencyTable function
	Test2: test generateLeafList and generateHuffmanTree function
	Test3: test generateEncodingTable function
	Test4: test writeHuffmanFile
	Test5: test Decode

## Built With

* [Visual Studio](https://visualstudio.microsoft.com/)	- C++ development

## Contributing

Please read [CONTRIBUTING.md](https://github.com/Cabrra/Contributing-template/blob/master/Contributing-template.md) for details on the code of conduct, and the process for submitting pull requests to me.

## Authors

* **Jagoba "Jake" Marcos** 	- [Cabrra](https://github.com/Cabrra)
* **Rodney Stoeffler** 		- Test cases

## License

This project is licensed under the MIT license - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Full Sail University - Game Development Department
