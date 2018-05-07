/*
 *Author: Dominikus Noah Preugszas
 *
 * MyArrayList.h - declares and defines methods for a list-datastructure
 * with additional methods (for example sortinsert)
 * The List may contain can store any kind of object.
 */
#pragma once

template <typename T_type> class MyArrayList
{
public:
	struct MyArrayNode
	{
		T_type value;
		MyArrayNode* prev;
		MyArrayNode* next;
	};

	explicit MyArrayList(const T_type* tab, unsigned int size)
	{
		this->_size = size;
		this->first = createNewNode(tab[0]);

		MyArrayNode* prevNode = this->first;
		for (auto i = 1; i<size; i++)
		{
			MyArrayNode* newNode = createNewNode(tab[i], prevNode);
			prevNode->next = newNode;
			prevNode = newNode;
		}
		this->last = prevNode;
	}

	explicit MyArrayList(const T_type val)
	{
		this->_size = 1;
		this->first = createNewNode(val);
		this->last = this->first;
	}

	explicit MyArrayList()
	{
		this->first = nullptr;
		this->last = nullptr;
		this->_size = 0;
	}
	//MyArrayList(const MyArrayList<T_type>& original);
	~MyArrayList()
	{
		destroyList();
	}

	T_type at(unsigned int i);

	void push(T_type val);
	void pushBack(T_type val);
	void insertAfter(unsigned int nodeNr, T_type val);
	void insertBefore(unsigned int nodeNr, T_type val);

	T_type pop();
	T_type popBack();

	void sortInsert(T_type val);
	T_type abs(T_type val);

	void show();
	T_type multiplyAllFromFirst();
	T_type sumAllFromFirst();

	T_type operator [](int i) { return get(i)->value; }

	void removeNode(unsigned int nodeNr);
	void emptyList();

	int size() { return this->_size; }
private:
	unsigned int _size;

	MyArrayNode* first;
	MyArrayNode* last;


	MyArrayNode* createNewNode(T_type val, MyArrayNode* prev = nullptr,
		MyArrayNode* next = nullptr);
	
	MyArrayNode* get(unsigned int node);
	void p_insertAfter(MyArrayNode* node, T_type val);
	void p_insertBefore(MyArrayNode* node, T_type val);
	void swap(MyArrayNode* node1, MyArrayNode* node2);

	void destroyList();
};


#include<iostream>

using namespace std;


template<typename T_type>
typename MyArrayList<T_type>::MyArrayNode* MyArrayList<T_type>::createNewNode(T_type val,
	MyArrayNode* prev = nullptr, MyArrayNode* next = nullptr)
{
	MyArrayNode* newNode = new MyArrayNode;
	newNode->value = val;
	newNode->next = next;
	newNode->prev = prev;
	return newNode;
}

template<typename T_type>
typename MyArrayList<T_type>::MyArrayNode* MyArrayList<T_type>::get(unsigned int node)
{
	MyArrayNode* nodeToGet;
	if (node <= this->_size / 2) {
		nodeToGet = this->first;
		for (auto i = 0; i < node; i++)
		{
			nodeToGet = nodeToGet->next;
		}
	}
	else
	{
		nodeToGet = this->last;
		for (auto i = this->_size - 1; i > node; i--)
		{
			nodeToGet = nodeToGet->prev;
		}
	}
	return nodeToGet;
}


template<typename T_type>
inline T_type MyArrayList<T_type>::at(unsigned int i)
{
	if(i >= this->_size)
	{
		std::exception OutOfArrayException = std::exception("Index does not exist");
		throw OutOfArrayException;
	}
	MyArrayNode* node = get(i);

	return node->value;
}

template<typename T_type>
void MyArrayList<T_type>::push(T_type val)
{
	MyArrayNode* newNode = createNewNode(val, nullptr, this->first);
	this->first = newNode;

	if (this->_size == 0)
	{
		this->last = newNode;
	}
	else
	{
		newNode->next->prev = newNode;
	}
	this->_size++;
}

template<typename T_type>
void MyArrayList<T_type>::pushBack(T_type val)
{
	if (this->_size == 0)
	{
		push(val);
	}
	else
	{
		MyArrayNode* newNode = createNewNode(val, this->last);
		this->last->next = newNode;
		this->last = newNode;
		this->_size++;
	}
}

template<typename T_type>
void MyArrayList<T_type>::insertAfter(unsigned int nodeNr, T_type val)
{
	if (this->_size == 0)
	{
		push(val);
	}
	else if (nodeNr == this->_size - 1)
	{
		pushBack(val);
	}
	else
	{
		MyArrayNode* searchedNode = get(nodeNr);
		this->p_insertAfter(searchedNode, val);
	}
}

template<typename T_type>
void MyArrayList<T_type>::p_insertAfter(MyArrayNode* node, T_type val)
{
	if (node == this->last)
	{
		pushBack(val);
	}
	else
	{
		MyArrayNode* newNode = createNewNode(val, node, node->next);
		node->next = newNode;
		this->_size++;
	}
}

template<typename T_type>
void MyArrayList<T_type>::insertBefore(unsigned int nodeNr, T_type val)
{
	if (this->_size == 0 || nodeNr == 0)
	{
		push(val);
	}
	else
	{
		MyArrayNode* searchedNode = get(nodeNr);
		this->p_insertBefore(searchedNode, val);
	}
}

template<typename T_type>
void MyArrayList<T_type>::p_insertBefore(MyArrayNode* node, T_type val)
{
	if (node == this->first)
	{
		push(val);
	}
	else
	{
		MyArrayNode* newNode = createNewNode(val, node->prev, node);
		node->prev->next = newNode;
		node->prev = newNode;
		this->_size++;
	}
}

template<typename T_type>
void MyArrayList<T_type>::swap(MyArrayNode* node1, MyArrayNode* node2)
{

}

template<typename T_type>
inline void MyArrayList<T_type>::destroyList()
{
	MyArrayNode* prevNode = this->first;
	for (auto i = 0; i<this->_size; i++)
	{
		MyArrayNode* nextNode = prevNode->next;
		delete prevNode;
		prevNode = nextNode;
	}
}

template<typename T_type>
T_type MyArrayList<T_type>::pop()
{
	T_type retunValue = this->first->value;
	removeNode(0);
	return retunValue;
}

template<typename T_type>
T_type MyArrayList<T_type>::popBack()
{
	T_type returnValue = this->last->value;
	removeNode(this->_size - 1);
	return returnValue;
}

template<typename T_type>
void MyArrayList<T_type>::removeNode(unsigned int nodeNr)
{
	if (nodeNr == 0)
	{
		MyArrayNode* newFirst = this->first->next;
		newFirst->prev = nullptr;
		delete this->first;
		this->first = newFirst;
	}
	else if (nodeNr == this->_size - 1)
	{
		MyArrayNode* newLast = this->last->prev;
		newLast->next = nullptr;
		delete this->last;
		this->last = newLast;
	}
	else
	{
		MyArrayNode* nodeToDelete = get(nodeNr);
		nodeToDelete->prev->next = nodeToDelete->next;
		nodeToDelete->next->prev = nodeToDelete->prev;
		delete nodeToDelete;
	}
	this->_size--;
}

template<typename T_type>
inline void MyArrayList<T_type>::emptyList()
{
	destroyList();
	this->_size = 0;
	this->first = nullptr;
	this->last = nullptr;
}

template<typename T_type>
void MyArrayList<T_type>::sortInsert(T_type val)
{
	MyArrayNode* currentNode = this->first;
	for (auto i = 0; i<this->_size; i++)
	{
		if (abs(currentNode->value) >= abs(val))
		{
			p_insertBefore(currentNode, val);
			return;
		}
		currentNode = currentNode->next;
	}
	pushBack(val);
}

template<typename T_type>
inline T_type MyArrayList<T_type>::abs(T_type val)
{
	if (val >= 0)
		return val;
	return -val;
}

template<typename T_type>
void MyArrayList<T_type>::show()
{
	MyArrayNode* nodeToPrint = this->first;
	cout << "[ ";
	for (auto i = 0; i<this->_size; i++)
	{
		cout << nodeToPrint->value << " ";
		nodeToPrint = nodeToPrint->next;
	}
	cout << "]" << endl;
}

template<typename T_type>
T_type MyArrayList<T_type>::multiplyAllFromFirst()
{
	T_type result = 0;
	if (this->size() > 1) {
		MyArrayNode* current = this->first;
		result = 1;
		while (current->next != nullptr)
		{
			result *= current->value;
			current = current->next;
		}
		result *= current->value;
	}
	return result;

}

template<typename T_type>
inline T_type MyArrayList<T_type>::sumAllFromFirst()
{
	T_type result = 0;
	if (this->size() > 0) {
		MyArrayNode* current = this->first;
		while (current->next != nullptr)
		{
			result += current->value;
			current = current->next;
		}
		result += current->value;
	}
	return result;
}
