#pragma once

#include "SLList.h"
#include "DynArray.h"
#include "DLList.h"

struct Edge;
template<typename Type> struct Vertex;

template<typename Type>
class Graph
{
public:
	struct Edge{
		unsigned int toVertex;
	};

	struct Vertex{
		Type element;
		SLList<Edge> edges;

		void addEdge(const unsigned int& toVertex);
	};

private:
	DynArray<Vertex> myVertexes;

public:

	unsigned int addVertex(const Type& value);
	Vertex& operator[](const unsigned int& index);
	unsigned int size() const;
	void clear();
	void printBreadthFirst(const unsigned int& startVertex);

};

template<typename Type>
void typename Graph<Type>::Vertex::addEdge(const unsigned int& toVertex){
	Edge temp;
	temp.toVertex = toVertex;

	edges.addHead(temp);
}

template<typename Type>
unsigned int Graph<Type>::addVertex(const Type& value){
	
	Vertex temp = Vertex();
	temp.element = value;

	myVertexes.append(temp);
	return myVertexes.size() - 1;
}

template<typename Type>
typename Graph<Type>::Vertex&  Graph<Type>::operator[](const unsigned int& index){
	return myVertexes[index];
}

template<typename Type>
unsigned int Graph<Type>::size() const{
	return myVertexes.size();
}

template<typename Type>
void Graph<Type>::clear(){
	myVertexes.clear();
}

template<typename Type>
void Graph<Type>::printBreadthFirst(const unsigned int& startVertex){

	DLList<int> queue;
	DynArray<Vertex> aux = myVertexes;
	DynArray<int> repeat;
	repeat.reserve(aux.size());
	for (unsigned int i = 0; i < aux.size(); i++){
		repeat[i] = -1;
	}

	repeat[startVertex] = 0;
	//cout << aux[startVertex].element << " : " << "0\n";

	queue.addTail(startVertex);
	//aux.remove(startVertex);

	DLLIter<int> myDouIter(queue);
	myDouIter.beginHead();
	
	//int depth = 0;
	while (queue.Size() > 0){

		myDouIter.beginHead();
		int index = myDouIter.current();
		queue.remove(myDouIter);


		SLLIter<Edge> myIter(aux[index].edges);
		myIter.begin();

		while (!myIter.end()){
			//cout << myIter.current() << " : " << depth << '\n';
			if (repeat[myIter.current().toVertex] == -1){
				repeat[myIter.current().toVertex] = repeat[index] + 1;
				queue.addTail(myIter.current().toVertex);
			}
			//aux.remove(myIter.current().toVertex);
			++myIter;
		}

		cout << aux[index].element << " : " << repeat[index] << "\n";


		
	}
}