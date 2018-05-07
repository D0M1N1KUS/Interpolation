#include "MyArrayList.h"
#include<iostream>

using namespace std;

//template<typename T_type>
//MyArrayList<T_type>::MyArrayList(const T_type* tab, unsigned int size)
//{
//	this->size = size;
//	this->first = createNewNode(tab[0]);
//	
//	MyArrayNode* prevNode = this->first;
//	for(auto i=1; i<size; i++)
//	{
//		MyArrayNode* newNode = createNewNode(tab[i], prevNode);
//		prevNode->next = newNode;
//		prevNode = newNode;
//	}
//	this->last = prevNode;
//}
//
//template<typename T_type>
//MyArrayList<T_type>::MyArrayList(const T_type val)
//{
//	this->size = 1;
//	this->first = createNewNode(val);
//	this->last = this->first;
//}
//
//template<typename T_type>
//MyArrayList<T_type>::MyArrayList()
//{
//	this->first = nullptr;
//	this->last = nullptr;
//	this->size = 0;
//}

//template<typename T_type>
//MyArrayList<T_type>::~MyArrayList()
//{
//	MyArrayNode* prevNode = this->first;
//	for(auto i=0; i<this->size; i++)
//	{
//		MyArrayNode* nextNode = prevNode->next;
//		delete prevNode;
//		prevNode = nextNode;
//	}
//}

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
	if (node <= this->size / 2) {
		nodeToGet = this->first;
		for (auto i = 0; i < node; i++)
		{
			nodeToGet = nodeToGet->next;
		}
	}
	else
	{
		nodeToGet = this->last;
		for (auto i = this->size - 1; i > node; i--)
		{
			nodeToGet = nodeToGet->prev;
		}
	}
	return nodeToGet;
}


template<typename T_type>
void MyArrayList<T_type>::push(T_type val)
{
	MyArrayNode* newNode = createNewNode(val, nullptr, this->first);
	this->first = newNode;
	
	if(this->last == nullptr || newNode->next->next == nullptr)
	{
		this->last = newNode;
	}
	this->size++;
}

template<typename T_type>
void MyArrayList<T_type>::pushBack(T_type val)
{
	if(this->size == 0)
	{
		push(val);
	}
	else
	{
		MyArrayNode* newNode = createNewNode(val, this->last);
		this->last = newNode;
		this->size++;
	}
}

template<typename T_type>
void MyArrayList<T_type>::insertAfter(unsigned int nodeNr, T_type val)
{
	if(nodeNr == 0)
	{
		push(val);
	}
	else if(nodeNr == this->size - 1)
	{
		pushBack(val);
	}
	else
	{
		MyArrayNode* searchedNode = get(nodeNr);
		this->insertAfter(searchedNode, val);
	}
}

template<typename T_type>
void MyArrayList<T_type>::insertAfter(MyArrayNode* node, T_type val)
{
	if(node == this->last)
	{
		pushBack(val);
	}
	else
	{
		MyArrayNode* newNode = createNewNode(val, node, node->next);
		node->next = newNode;
		this->size++;
	}
}

template<typename T_type>
void MyArrayList<T_type>::insertBefore(unsigned int nodeNr, T_type val)
{
	if (this->size == 0 || nodeNr == 0)
	{
		push(val);
	}
	else
	{
		MyArrayNode* searchedNode = get(nodeNr);
		this->insertBefore(searchedNode, val);
	}
}

template<typename T_type>
void MyArrayList<T_type>::insertBefore(MyArrayNode* node, T_type val)
{
	if(node == this->first)
	{
		push(val);
	}
	else
	{
		MyArrayNode* newNode = createNewNode(val, node->prev, node);
		node->prev = newNode;
		this->size++;
	}
}

template<typename T_type>
void MyArrayList<T_type>::swap(MyArrayNode* node1, MyArrayNode* node2)
{

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
	removeNode(this->size - 1);
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
	else if (nodeNr == this->size - 1)
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
	this->size--;
}

template<typename T_type>
void MyArrayList<T_type>::sortInsert(T_type val)
{
	MyArrayNode* currentNode = this->first;
	for(auto i=0; i<this->size; i++)
	{
		if(currentNode->value >= val)
		{
			insertBefore(currentNode, val);
			return;
		}
		currentNode = currentNode->next;
	}
	pushBack(val);
}

template<typename T_type>
void MyArrayList<T_type>::show()
{
	MyArrayNode* nodeToPrint = this->first;
	cout << "[ ";
	for(auto i=0; i<this->size; i++)
	{
		cout << nodeToPrint->value << " ";
		nodeToPrint = nodeToPrint->next;
	}
	cout << "]" << endl;
}
