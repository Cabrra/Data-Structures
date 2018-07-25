#pragma once

template<typename Type> class DLLIter;

template<typename Type>
class DLList
{
private:
	friend class DLLIter<Type>;

	struct Node
	{
		Type data;
		Node* next, *previ;
	};

	Node* head, *tail;
	unsigned int _size;

public:
	DLList();
	~DLList();
	DLList<Type>& operator=(const DLList<Type>& that);
	DLList(const DLList<Type>& that);
	void addHead(const Type& v);
	void addTail(const Type& v);
	void clear();
	void insert(DLLIter<Type>& index, const Type& v);
	void remove(DLLIter<Type>& index);

	void RecursiveHelp(Node* add);
};

template<typename Type>
DLList<Type>::DLList(){
	head = NULL;
	tail = NULL;
	_size = 0;
}

template<typename Type>
DLList<Type>::~DLList(){
	Node* temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	tail = NULL;
}

template<typename Type>
DLList<Type>& DLList<Type>::operator=(const DLList<Type>& that){
	if (this != &that){
		clear();
		RecursiveHelp(that.head);
	}
	return *this;
}

template<typename Type>
void DLList<Type>::RecursiveHelp(Node* add){
	if (add == NULL){
		return;
	}
	else{
		RecursiveHelp(add->next);
		addHead(add->data);
	}
}

template<typename Type>
DLList<Type>::DLList(const DLList<Type>& that){
	head = nullptr;
	tail = nullptr;
	*this = that;
}

template<typename Type>
void DLList<Type>::addHead(const Type& v){
	Node* temp = new Node;
	temp->data = v;
	temp->next = NULL;
	temp->previ = NULL;
	if (tail == head && head == NULL){
		head = temp;
		tail = temp;
		
	}
	else{
		temp->next = head;
		head->previ = temp;
		head = temp;
	}
	_size++;
}

template<typename Type>
void DLList<Type>::addTail(const Type& v){
	Node* temp = new Node;
	temp->data = v;
	if (tail == head && head == NULL){
		head = temp;
		tail = temp;
		head->next = NULL;
		head->previ = NULL;
		tail->next = NULL;
		tail->previ = NULL;

	}
	else{
		temp->next = NULL;
		temp->previ = tail;
		tail->next = temp;
		tail = temp;
	}
	_size++;
}

template<typename Type>
void DLList<Type>::clear(){
	Node* temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	head = NULL;
	tail = NULL;
	_size = 0;
}

template<typename Type>
void DLList<Type>::insert(DLLIter<Type>& index, const Type& v){
	if (index.curr != NULL){
		Node* temp = new Node;
		temp->data = v;
		if (index.curr == head){
			temp->next = head;
			temp->previ = NULL;
			head->previ = temp;
			head = temp;
			index.curr = head;
		}
		else {
			index.curr->previ->next = temp;
			temp->next = index.curr;
			temp->previ = index.curr->previ;
			index.curr->previ = temp;

			index.curr = temp;
		}
		_size++;
	}
}

template<typename Type>
void DLList<Type>::remove(DLLIter<Type>& index){
	Node* temp;
	if (head != NULL){
		if (index.curr == head && index.curr == tail){
			temp = head;
			delete temp;
			tail = NULL;
			head = NULL;
			index.curr = NULL;
		}
		else if (index.curr == head){

			temp = head;
			head = head->next;
			head->previ = NULL;
			delete temp;
			index.curr = head;
		}
		else if (index.curr == tail){
			temp = tail;
			tail = tail->previ;
			tail->next = NULL;
			delete temp;
			index.curr = tail;
		}
		else {
			temp = index.curr;
			temp->next->previ = temp->previ;
			temp-> previ->next = temp->next;
			index.curr = temp->next;
			temp->next = NULL;
			temp->previ = NULL;
			delete temp;

		}
		_size--;
	}
}


template<typename Type> class DLLIter;

template<typename Type>
class DLLIter
{
private:
	friend class DLList<Type>;
	typename DLList<Type>::Node *curr;
	DLList<Type>* list;

public:
	DLLIter(DLList<Type>& listToIterate);
	void beginHead();
	void beginTail();
	bool end() const;
	DLLIter<Type>& operator++();
	DLLIter<Type>& operator--();
	Type& current() const;
};

template<typename Type>
DLLIter<Type>::DLLIter(DLList<Type>& listToIterate){
	list = &listToIterate;
	curr = listToIterate.head;
}

template<typename Type>
void DLLIter<Type>::beginHead(){
	if (list->head != NULL){
		curr = list->head;
	}
}

template<typename Type>
void DLLIter<Type>::beginTail(){
	if (list->tail != NULL){
		curr = list->tail;
	}
}

template<typename Type>
bool DLLIter<Type>::end() const{
	return (curr != NULL) ? false : true;
}

template<typename Type>
DLLIter<Type>& DLLIter<Type>::operator++(){
	if (curr != NULL){
		curr = curr->next;
	}
	return *this;
}

template<typename Type>
DLLIter<Type>& DLLIter<Type>::operator--(){
	if (curr != NULL){
		curr = curr->previ;
	}
	return *this;
}

template<typename Type>
Type& DLLIter<Type>::current() const{
	return curr->data;
}
