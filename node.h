// John Williams 
// 105201054
// HW9
// 11-02-16

#ifndef NODE_H
#define NODE_H

#include "Data.h"
#include <iostream>
using namespace std;


template<class type>//forward declaration
class BST;

// this is the node class we were given By Mr Augustine except that I have Put a template on it soas to 
// facititate using the Data class inside of it. 

template<class type>
class Node
{
private:

	Node * parent = nullptr;
	Node * left = nullptr;
	Node * right = nullptr;
	type item;
	//int key;
	
public:
	void setItem(type newitem) { item = newitem; }
	type getItem() const { return item; }
	type getItem() { return item; }
	void setParent(Node* newParent) { parent = newParent; }
	void setLeft(Node* newLeft) { left = newLeft; }
	void setRight(Node* newRight) { right = newRight; }
	
	Node* leftPtr() { return left; };
	Node* rightPtr() { return right; };
	Node* parentPtr() { return parent; };
	Node<type>()
	{
	}
	

	Node<type>* operator =(const Node<type>* stuff)
	{
		*this = stuff;
	}
};

#endif