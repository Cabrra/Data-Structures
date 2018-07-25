#pragma once

#include "SLList.h"

template<typename Type>
class HTable
{
private:
	unsigned int buckets;
	unsigned int(*f) (const Type&);
	SLList<Type>* myPointer;

public:

	HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v));
	~HTable();
	HTable<Type>& operator=(const HTable<Type>& that);
	HTable(const HTable<Type>& that);
	void insert(const Type& v);
	bool findAndRemove(const Type& v);
	void clear();
	int find(const Type& v) const;
};

template<typename Type>
HTable<Type>::HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v)){
	buckets = numOfBuckets;
	f = hFunction;
	myPointer = new SLList<Type>[buckets];
}

template<typename Type>
HTable<Type>::~HTable(){
	delete[] myPointer;
}

template<typename Type>
HTable<Type>& HTable<Type>::operator=(const HTable<Type>& that){
	if (this != &that){
		delete[] myPointer;
		buckets = that.buckets;
		myPointer = new SLList<Type>[buckets];
		f = that.f;
		
		for (unsigned int i = 0; i < buckets; i++)
			myPointer[i] = that.myPointer[i];
	}
	return *this;
}

template<typename Type>
HTable<Type>::HTable(const HTable<Type>& that){
	*this = that;
}

template<typename Type>
void HTable<Type>::insert(const Type& v){
	unsigned int  match = (*f)(v);
	if (match >= 0){
		myPointer[match].addHead(v);
	}
}

template<typename Type>
bool HTable<Type>::findAndRemove(const Type& v){
	int match = find(v);
	if (match >= 0){
		SLLIter<Type> *myIter = new SLLIter<Type>(myPointer[match]);
		myIter->begin();
		while (myIter->current() != v)
			(*myIter)++;

		myPointer[match].remove(*myIter);
		delete myIter;
		return true;
	}
	return false;
}

template<typename Type>
void HTable<Type>::clear(){
	for (unsigned int i = 0; i < buckets; i++){
		myPointer[i].clear();
	}

}

template<typename Type>
int HTable<Type>::find(const Type& v) const{
	unsigned int  match = (*f)(v);
	if (match >= 0){
		SLLIter<Type> *myIter = new SLLIter<Type>(myPointer[match]);
		myIter->begin();
		for (unsigned int i = 0; i < myPointer[match].size(); i++){
			if (!myIter->end()){
				if (myIter->current() == v){
					delete myIter;
					return match;
				}
				else
					(*myIter)++;
			}
		}
		delete myIter;
		return -1;
	}
	else
		return -1;
}