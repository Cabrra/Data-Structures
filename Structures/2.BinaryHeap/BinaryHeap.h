#include "DynArray.h"
#pragma once

template<typename Type>
class BinaryHeap : protected DynArray<Type>{

public:
	void enqueue(const Type &v);
	Type dequeue();
	Type& operator[](int index);
	void clear();
	unsigned int size();
};

template<typename Type>
void BinaryHeap<Type>::enqueue(const Type &v){
	DynArray::append(v);
	Type temp = v;

	for (int i = _size-1; i >= 0;){

		if (element[(i - 1) / 2] > temp){
			element[i] = element[(i - 1) / 2];
			element[(i - 1) / 2] = temp;
			i = (i - 1) / 2;
		}
		else
			break;
	}
}

template<typename Type>
Type BinaryHeap<Type>::dequeue(){
	if (_size == 0)
		return Type();
	Type temp = element[0];
	element[0] = element[_size - 1];
	_size--;

	Type aux;

	for (unsigned int i = 0; i < _size;){
		if (element[i] > element[i * 2 + 1] || element[i] > element[i * 2 + 2]){
			if ((i * 2 + 2) < _size){
				if (element[i * 2 + 1] > element[i * 2 + 2]){
					aux = element[i];
					element[i] = element[i * 2 + 2];
					element[i * 2 + 2] = aux;
					i = i * 2 + 2;
				}
				else{
					aux = element[i];
					element[i] = element[i * 2 + 1];
					element[i * 2 + 1] = aux;
					i = i * 2 + 1;
				}
			}
			else if ( (i * 2 + 1) < _size){
				aux = element[i];
				element[i] = element[i * 2 + 1];
				element[i * 2 + 1] = aux;
				i = i * 2 + 1;
			}
			else
				break;
		}
		else
			break;
	}
	return temp;
}

template<typename Type>
Type& BinaryHeap<Type>::operator[](int index){
	return DynArray::operator[](index);
}

template<typename Type>
void BinaryHeap<Type>::clear(){
	DynArray::clear();
}

template<typename Type>
unsigned int BinaryHeap<Type>::size(){
	return DynArray::size();
}