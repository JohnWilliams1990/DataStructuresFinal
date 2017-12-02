// John Williams 
// 105201054
// HW9
// 11-02-16

#ifndef BST_H
#define BST_H

#include "Data.h"
#include "node.h"

template<class type>
class BST
{
private:
	Node<type>* root;
	vector<vector<string> > item;
	int count;
public:
	BST();
	Node<type>* rootPtr() { return root; };
	void setRoot(Node<type>* Ptr) { root = Ptr; }
	void addNode(Node<type>* nodePtr,type item);
	void printPreOrder(Node<type>* node);
	void printInOrder(Node<type>* node);
	void printPostOrder(Node<type>* node);
	Node<type>* minimum(Node<type>*  Ptr);
	Node<type>* searchBST(Node<type>* node, string number);
	Node<Data>* deleteNode(Node<Data>* root, string key);
	void printPostOrder(Node<Data>* node, ostream & out);
	void contains(Node<Data>* node, string item,int function, vector<Node<Data>*> &found);
	vector < vector <string> > getVector(Node<Data>* node);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////*Authored by Dr. Augustine*//////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	void freeNode(Node<type>* leaf);
	void deleteNode(type key);
	Node<type>* deleteNode(Node<type>* root, type key);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	void searchBST(Node<type>* node, string item, int choice, vector<Node<Data>*> &found);
	Node<Data>* searchBST(Node<type>* node, string item, int choice);
	// make specific definitions for strings for an alphabetical order
	
	friend bool operator > (const Node<type>* curPtr, const string& item)
	{
		return (curPtr->getItem() > item);
	}	
	friend bool operator < (const Node<type>* curPtr, const string& item)
	{
		string stringItem = curPtr->getItem();
		return (stringItem < item);
	}
};

///////////////////////////////////////////////////////////////
// input: nothing
// description: 
// this function is used to ititialize the root of the binary search tree
// output: unfortunately nothing via constructor
///////////////////////////////////////////////////////////////
template<class type>
BST<type>::BST()
{
	root = nullptr;
	
}

///////////////////////////////////////////////////////////////
// input: a nodePtr and a type item 
// description: this function is the generic function used to add an item to the tree recursively.
// I made specific type of this function below this function. 
// output: unfortunately nothing
///////////////////////////////////////////////////////////////
template<class type>
void BST<type>::addNode(Node<type>* nodePtr, type item)
{
	Node<type>* curPtr = nullptr;
	if (root == nullptr)// if we are at a leaf in the tree
	{
		root = new Node<type>;
		root->setItem(item);//Item
		root->setParent(nodePtr);
		
	}
	else
	{
		// set left if it is less than the item in question and we are at a leaf
		if (item < nodePtr->getItem() && nodePtr->leftPtr() == nullptr)
		{
			curPtr = new Node<type>;
			curPtr->setItem(item);
			nodePtr->setLeft(curPtr);
			curPtr = nullptr;
			
			return;
			
		}
		// set Right if it is greater than the item in question and we are at a leaf
		if (item > nodePtr->getItem() && nodePtr->rightPtr() == nullptr)
		{
			curPtr = new Node<type>;
			curPtr->setItem(item);
			nodePtr->setRight(curPtr);
			curPtr = nullptr;
			return;
		}
		// if the item in question is less that the item being used then we go right in the tree

		if (item < nodePtr->getItem() && nodePtr->leftPtr() != nullptr)
		{
			addNode(nodePtr->leftPtr(), item);

		}
		// if the item in question is less that the item being used then we go left in the tree

		if (item > nodePtr->getItem() && nodePtr->rightPtr() != nullptr)
		{
			addNode(nodePtr->rightPtr(), item);

		}


	}

}

/////---------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
// input: a nodePtr and a type item 
// description: this function is the specific function used to add 
// an item to the tree recursively
//  
// output: unfortunately nothing
///////////////////////////////////////////////////////////////
template<>
void BST<Data>::addNode(Node<Data>* nodePtr, Data item)
{
	Node<Data>* curPtr = nullptr;
	if (root == nullptr) //if root is null then make a root for the tree
	{
		root = new Node<Data>;
		root->setItem(item);
		root->setParent(nodePtr);
		count++;
	}

	else
	{
		// if the item is less than the item in question and we are at a leaf 
		if (item.getEmployeeNumber() < nodePtr->getItem().getEmployeeNumber() && nodePtr->leftPtr() == nullptr)
		{
			curPtr = new Node<Data>;
			curPtr->setItem(item);
			nodePtr->setLeft(curPtr);
			curPtr->setParent(nodePtr);////////////////////////////////////////////////////////
			curPtr = nullptr;
			delete curPtr;
			count++;
			return;

		}
		// if the item is greater than the item in question and we are at a leaf 
		if (item.getEmployeeNumber() > nodePtr->getItem().getEmployeeNumber() && nodePtr->rightPtr() == nullptr)
		{
			curPtr = new Node<Data>;
			curPtr->setItem(item);
			nodePtr->setRight(curPtr);
			curPtr->setParent(nodePtr);////////////////////////////////////////////////////////

			curPtr = nullptr;
			delete curPtr;
			count++;
			return;

		}
		// if the item is less than the item in question and we are not at a leaf => traverse left
		if (item.getEmployeeNumber() < nodePtr->getItem().getEmployeeNumber() && nodePtr->leftPtr() != nullptr)
		{
			addNode(nodePtr->leftPtr(), item);

		}
		// if the item is greater than the item in question and we are not at a leaf => traverse right 
		if (item.getEmployeeNumber() > nodePtr->getItem().getEmployeeNumber() && nodePtr->rightPtr() != nullptr)
		{
			addNode(nodePtr->rightPtr(), item);

		}


	}

}

///////////////////////////////////////////////////////////////
// input: a node Ptr of Data type 
// description: this function is the specific function used to 
// print the tree inorder uisng an inorder traversal recursively.
// 
// output: unfortunately nothing
///////////////////////////////////////////////////////////////

template<>
void BST<Data>::printInOrder(Node<Data>* node)
{
	
	if (node != nullptr)
	{
		if (node->leftPtr() != nullptr)// go left 
		{
			printInOrder(node->leftPtr());
		}
		if (node != nullptr)// visit node 
		{
			cout << node->getItem();
		}
		if (node->rightPtr() != nullptr)// go right
		{
			printInOrder(node->rightPtr());
		}


	}

}
///////////////////////////////////////////////////////////////
// input: a node Ptr of Data type , and an ostream operator
// description: this function is the specific function used to print the tree in a postorder
// using an postorder traversal recursively.
// 
// output: unfortunately nothing
///////////////////////////////////////////////////////////////

template<>
void BST<Data>::printPostOrder(Node<Data>* node, ostream & out)
{

	if (node != nullptr)// if we are not at nullptr
	{


		if (node->leftPtr() != nullptr)//visit left 
		{
			printPostOrder(node->leftPtr(), out);
		}
		if (node->rightPtr() != nullptr)// visit right
		{
			printPostOrder(node->rightPtr(), out);
		}
		if (node != nullptr)//// output the node
		{
			out << node;
		}

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// input: a node Ptr of Data type,
// description: this function is the specific function used to take the tree and push it into a 2d 
// vector using an inorder treaversal of the treerecursively..
// output: a 2d vector of string type containing the tree
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
vector < vector <string> > BST<Data>::getVector(Node<Data>* node)
{

	/*make the vector a member variable and initialize it in the Constructor
		remove it from the parameters and at the end of the function return the whole vector or have 
		another function pass the vector at the end of this block*/

	


		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)// go left if applicable
			{
				getVector(node->leftPtr());
			}
			if (node != nullptr)// when we visit the node take the item in question
			{
				item.push_back(vector<string>());// push into vector a new vector for the item in question 
				//push the item in question into the vector
				item[item.size()-1].push_back(node->getItem().getEmployeeNumber());
				item[item.size()-1].push_back(node->getItem().getFirstName());
				item[item.size() - 1].push_back(node->getItem().getMiddleName());
				item[item.size() - 1].push_back(node->getItem().getLastName());
				item[item.size() - 1].push_back(node->getItem().getCompanyName());
				item[item.size() - 1].push_back(node->getItem().getHomePhone());
				item[item.size() - 1].push_back(node->getItem().getWorkPhone());
				item[item.size() - 1].push_back(node->getItem().getEmail());
				item[item.size() - 1].push_back(node->getItem().getCellPhone());
				item[item.size() - 1].push_back(node->getItem().getHomeAddress());
				item[item.size() - 1].push_back(node->getItem().getCity());
				item[item.size() - 1].push_back(node->getItem().getState());
				item[item.size() - 1].push_back(node->getItem().getZip());
				item[item.size() - 1].push_back(node->getItem().getCountry());
				item[item.size() - 1].push_back(node->getItem().getAffiliatesString());
			}
			if (node->rightPtr() != nullptr)// go right
			{
				getVector(node->rightPtr());
			}
		}	
		return item; //return the vector
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// input: a node Ptr of Data type, a string for the item, a function number for the field, and a 
// vector of Nodes by reference, containing the results. 
// description: this function is the specific function used to search the tree and push the results into a vector 
// using an inorder treaversal of the tree recursively.. this depencds on the choice of the field being searched on.
// output: nothing unfortunately
////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
void BST<Data>::searchBST(Node<Data>* node, string item, int choice, vector<Node<Data>*> &found)
{

	// every search should visit each node in the tree /\/\/\/\ except the search for Id Numbers

	if (choice == 1)// firstname
	{	
				//return node; 
			if (node != nullptr)
			{
				if (node->leftPtr() != nullptr)
				{
					searchBST(node->leftPtr(), item, choice, found);
					
				}
				if (node != nullptr&&item == node->getItem().getFirstName())
				{
						found.push_back(node);
				}
				if (node->rightPtr() != nullptr)
				{
					searchBST(node->rightPtr(), item, choice, found);
				}
			}
	}
	else if (choice == 2)// middlename
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getMiddleName())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	else if (choice == 3)// last name
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getLastName())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	else if (choice == 4)// company name 
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getCompanyName())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}

	else if(choice == 5)// home phone
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getHomePhone())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	else if (choice == 6)//office phone number 
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getWorkPhone())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}

	else if (choice == 7)//email
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getEmail())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	
	else if (choice == 8)//mobile number
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getCellPhone())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	else if (choice == 9)// address 
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getHomeAddress())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	else if (choice == 10)// city 
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getCity())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	else if (choice == 11)//state
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getState())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	else if (choice == 12)//ZIP
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getZip())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	else if (choice == 13)//country
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);

			}
			if (node != nullptr&&item == node->getItem().getCountry())
			{
				found.push_back(node);
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	else if (choice == 14)// affiliate first name
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);
			}
			if (node != nullptr)
			{
				for (int i = 0; i < node->getItem().getNumberOfAffiliates() - 1; i++)
				{
					if (item == node->getItem().getAffiliates(i, 0))
					{
						found.push_back(node);
					}
				}
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	else if (choice == 15)// affiliate phone number
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);
			}
			if (node != nullptr)
			{
				for (int i = 0; i < node->getItem().getNumberOfAffiliates(); i++)
				{
					if (item == node->getItem().getAffiliates(i, 1))
					{
						found.push_back(node);
					}
				}
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
	else if (choice == 16)// affiliate email address 
	{
		if (node != nullptr)
		{
			if (node->leftPtr() != nullptr)
			{
				searchBST(node->leftPtr(), item, choice, found);
			}
			if (node != nullptr)
			{
				for (int i = 0; i < node->getItem().getNumberOfAffiliates(); i++)
				{
					if (item == node->getItem().getAffiliates(i, 2))
					{
						found.push_back(node);
					}
				}
			}
			if (node->rightPtr() != nullptr)
			{
				searchBST(node->rightPtr(), item, choice, found);
			}
		}
	}
}
////------------------------------------------------------------------------------

template<>
void BST<Data>::contains(Node<Data>* node, string item, int function, vector<Node<Data>*> &found)
{
	std::size_t foundIT;
	switch (function)
	{
	case 0://employee number
		if (node != nullptr)
		{

			foundIT = node->getItem().getEmployeeNumber().find(item);
			if (foundIT != std::string::npos)

				//if (node->getItem().getEmployeeNumber().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																	//cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;

	case 1://search by first name
		if (node != nullptr)
		{
			foundIT = node->getItem().getFirstName().find(item);
			if (foundIT != std::string::npos)
				
			//if (node->getItem().getFirstName().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 2:// middle name
		if (node != nullptr)
		{
			foundIT = node->getItem().getMiddleName().find(item);
			if (foundIT != std::string::npos)

//			if (node->getItem().getMiddleName().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 3:// last name
		if (node != nullptr)
		{

			foundIT = node->getItem().getLastName().find(item);
			if (foundIT != std::string::npos)

//			if (node->getItem().getLastName().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 4:// company name
		if (node != nullptr)
		{
			

			foundIT = node->getItem().getCompanyName().find(item);
			if (foundIT != std::string::npos)

			//if (node->getItem().getCompanyName().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 5://home phone
		if (node != nullptr)
		{
			foundIT = node->getItem().getHomePhone().find(item);
			if (foundIT != std::string::npos)
			//if (node->getItem().getHomePhone().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 6:// office phone
		if (node != nullptr)
		{

			foundIT = node->getItem().getWorkPhone().find(item);
			if (foundIT != std::string::npos)
			//if (node->getItem().getWorkPhone().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}

		break;
	case 7://email 
		if (node != nullptr)
		{
			foundIT = node->getItem().getEmail().find(item);
			if (foundIT != std::string::npos)

			//if (node->getItem().getEmail().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 8://cellPhone
		if (node != nullptr)
		{

			foundIT = node->getItem().getCellPhone().find(item);
			if (foundIT != std::string::npos)
			//if (node->getItem().getCellPhone().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 9://street address 
		if (node != nullptr)
		{
			foundIT = node->getItem().getHomeAddress().find(item);
			if (foundIT != std::string::npos)
			//if (node->getItem().getHomeAddress().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 10://city
		if (node != nullptr)
		{

			foundIT = node->getItem().getCity().find(item);
			if (foundIT != std::string::npos)
			//if (node->getItem().getCity().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 11://State
		if (node != nullptr)
		{

			foundIT = node->getItem().getState().find(item);
			if (foundIT != std::string::npos)
			//if (node->getItem().getState().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 12://zip
		if (node != nullptr)
		{
			foundIT = node->getItem().getZip().find(item);
			if (foundIT != std::string::npos)
			//if (node->getItem().getZip().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 13://country
		if (node != nullptr)
		{

			foundIT = node->getItem().getCountry().find(item);
			if (foundIT != std::string::npos)

			//if (node->getItem().getCountry().compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
			{
				found.push_back(node);
			}
			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
																 //cout << node->leftPtr()->getNumber() << " ";
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;


		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	case 14://affiliate firstname
		if (node != nullptr)
		{

			for (int i = 0; i < node->getItem().getNumberOfAffiliates(); i++)
			{
				foundIT = node->getItem().getAffiliates(i, 0).find(item);
				if (foundIT != std::string::npos)

				//if (node->getItem().getAffiliates(i,0).compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
				{
					found.push_back(node);
				}
			}

			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 15://affiliate firstname
		if (node != nullptr)
		{
			for (int i = 0; i < node->getItem().getNumberOfAffiliates(); i++)
			{
				foundIT = node->getItem().getAffiliates(i, 1).find(item);
				if (foundIT != std::string::npos)

				//if (node->getItem().getAffiliates(i, 1).compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
				{
					found.push_back(node);
				}
			}

			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;
	case 16://affiliate firstname
		if (node != nullptr)
		{
			for (int i = 0; i < node->getItem().getNumberOfAffiliates(); i++)
			{
				foundIT = node->getItem().getAffiliates(i, 2).find(item);
				if (foundIT != std::string::npos)

				//if (node->getItem().getAffiliates(i, 2).compare(0, item.size(), item) == 0)//compare(0, item.size(), item)
				{
					found.push_back(node);
				}
			}

			if (node->leftPtr() != nullptr)
			{
				contains(node->leftPtr(), item, function, found);// visit the left
			}
			if (node->rightPtr() != nullptr)
			{
				contains(node->rightPtr(), item, function, found);// visit the right 
			}
		}
		break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////

	default:

		break;
	}

	//if (node != nullptr)
	//{
	//	
	//	cout << "find-->" << node->getItem().getEmail() << " with " << item;
	//	cout << " gives: " << node->getItem().getEmail().compare(0,item.size(), item) << endl;//compare(0, item.size(), item)

	//	if (node->leftPtr() != nullptr)
	//	{
	//		contains(node->leftPtr(), item);// visit the left
	//									//cout << node->leftPtr()->getNumber() << " ";
	//	}
	//	if (node->rightPtr() != nullptr)
	//	{
	//		contains(node->rightPtr(), item);// visit the right 
	//									 //cout << node->rightPtr()->getNumber() << " ";

	//	}
	//}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// input: a node Ptr of Data type, 
// description: this function is the general template function used to traverse the tree recursively in preorder soas to print it out
// output: nothing unfortunately
////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class type>
void BST<type>::printPreOrder(Node<type>* node)
{
	if (node != nullptr)
	{
		cout << node->getItem() << " ";// visit the root 

		if (node->Left() != nullptr)
		{
			printPreorder(node->Left());// visit the left
										//cout << node->leftPtr()->getNumber() << " ";
		}
		if (node->Right() != nullptr)
		{
			printPreorder(node->Right());// visit the right 
										 //cout << node->rightPtr()->getNumber() << " ";

		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// input: a node Ptr of Data type, 
// description: this function is the general template function used to traverse the tree recursively inordersoas to print it out.
// output: nothing unfortunately
////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class type>
void BST<type>::printInOrder(Node<type>* node)
{
	
	if (node != nullptr)
	{
		if (node->leftPtr() != nullptr)
		{
			printInOrder(node->leftPtr());
		}
		if (node != nullptr)
		{				
			cout << (node->getItem()) << " ";
		}
		if (node->rightPtr() != nullptr)
		{
			printInOrder(node->rightPtr());
		}

		
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// input: a node Ptr of Data type, 
// description: this function is the general template function used to traverse the tree recursively in postorder soas to print it out.
// output: nothing unfortunately
////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class type>
void BST<type>::printPostOrder(Node<type>* node)
{

	if (node != nullptr)
	{


		if (node->leftPtr() != nullptr)
		{
			printPostOrder(node->leftPtr());
		}
		if (node->rightPtr() != nullptr)
		{
			printPostOrder(node->rightPtr());
		}
		if (node != nullptr)
		{
			cout << node->getItem();
		}

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// input: a node Ptr of Data type, and string for a number 
// description: this function is the general template function used to traverse the tree recursively in preorder soas to find a specific node.
// output: a node Ptr of data type if found or null if not found 
////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class type>
Node<type>* BST<type>::searchBST(Node<type>* node, string number)
{

	if (node != nullptr)
	{
		node->getItem().getEmployeeNumber();
		
		if (node != nullptr&&node->getItem().getEmployeeNumber() == number)// visit node and compare the items 
		{
				node = node;
				return node;
		}
		if (number < node->getItem().getEmployeeNumber())// if the item is less than we go left if applicable 
		{
			if (node->leftPtr() != nullptr)
			{
				node = searchBST(node->leftPtr(), number);
			}
			else if (node->leftPtr() == nullptr)
			{
				
				return nullptr;
			}
		}
		if (node != nullptr && number > node->getItem().getEmployeeNumber())// if the item is less than we go right if applicable 
		{
			if (node->rightPtr() != nullptr)
			{
				node = searchBST(node->rightPtr(), number);
			}
			else if (node->rightPtr() == nullptr)
			{
				return nullptr;
			}
		}

	}

	return node;// return the node 

}

// Free the node
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// input: a node Ptr of Data type
// description: this function is the general template function used to free a specific node that is passed into the fuction.
// output: unfortunately nothing 
////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class type>
void BST<type>::freeNode(Node<type>* leaf)
{

	if (this->Root() == leaf)
	{

	}
	else if (leaf != nullptr)
	{
		freeNode(leaf->Left());
		freeNode(leaf->Right());
		delete leaf;
	}

}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//deleteNode (Private)
template<class type>
Node<Data>* BST<type>::deleteNode(Node<Data>* root, string key)// Node<type>* BST<type>::deleteNode(Node<type>* root, type key)
{

	/* Given a binary search tree and a key, this function deletes the key
	and returns the new root */


	if (root == nullptr) return root;
	else if (key < root->getItem().getEmployeeNumber())
		root->setLeft(deleteNode(root->leftPtr(), key));
	else if (key > root->getItem().getEmployeeNumber())//else if (key > root->getItem().getEmployeeNumber())
		root->setRight(deleteNode(root->rightPtr(), key));
	else {
		// Case 1: No Child
		if (root->leftPtr() == nullptr && root->rightPtr() == nullptr) {
			delete root;
			root = nullptr;
			
			// Case 2: one child
		}
		else if (root->leftPtr() == nullptr) {
			Node<Data> *temp = root;
			root = root->rightPtr();
			delete temp;
		}
		else if (root->rightPtr() == nullptr) {
			Node<Data> *temp = root;
			root = root->leftPtr();
			delete temp;
		}
		else {
			/*Node<Data> *temp = minimum(root->leftPtr());
			root->setItem(temp->getItem());
			root->setLeft(deleteNode(root->leftPtr(), temp->getItem()));*/


			
			Node<Data> *temp = minimum(root->rightPtr());
			root->setItem(temp->getItem());
			root->setRight(deleteNode(root->rightPtr(), temp->getItem()));
		}
	}
	return root;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Delete a node
// (1) If leaf just delete
// (2) If only one child delete this node and replace
// with the child
// (3) If 2 children. Find the predecessor (or successor).
// Delete the predecessor (or successor). Replace the
// node to be deleted with the predecessor (or successor).
template<class type>
void BST<type>::deleteNode(type key)
{
	if (deleteNode(rootPtr(), key) == nullptr)
		setRoot(nullptr);
}

//deleteNode (Private)
template<class type>
Node<type>* BST<type>::deleteNode(Node<type>* root, type key)// Node<type>* BST<type>::deleteNode(Node<type>* root, type key)
{

	/* Given a binary search tree and a key, this function deletes the key
	and returns the new root */


	if (root == nullptr) return root;
	else if (key < root)
		root->setLeft(deleteNode(root->leftPtr(), key));
	else if (key > root)
		root->setRight(deleteNode(root->rightPtr(), key));
	else {
		// Case 1: No Child
		if (root->leftPtr() == nullptr && root->rightPtr() == nullptr) {
			delete root;
			root = nullptr;
			// Case 2: one child
		}
		else if (root->leftPtr() == nullptr) {
			Node<type> *temp = root;
			root = root->rightPtr();
			delete temp;
		}
		else if (root->rightPtr() == nullptr) {
			Node<type> *temp = root;
			root = root->leftPtr();
			delete temp;
		}
		else {
			Node<type> *temp = minimum(root->rightPtr());
			root->setItem(temp->getItem());
			root->setRight(deleteNode(root->rightPtr(), temp->getItem()));
		}
	}
	return root;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// input: a node Ptr of Data type
// description: this function is the general template function used to free a specific node that is passed into the fuction.
// output: unfortunately nothing 
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class type>
Node<type>* BST<type>::minimum(Node<type>*  node)
{
	type item = node->getItem();
	if (node == nullptr)
	{
		return node;
	}
	
	else if (node->leftPtr() != nullptr&&node->leftPtr()->getItem() > item)
	{
		node = minimum(node->leftPtr());
	}
	else if (node->rightPtr() != nullptr&&node->rightPtr()->getItem() < item)
	{
		node = minimum(node->leftPtr());
	}
	
		return node;
	

}

//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// input: a node Ptr of Data type
// description: this function is the specific template function used to find the minimum node by traversing to the left until we are at the nullPtr.
// output: a node<data>* pointer
////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
Node<Data>* BST<Data>::minimum(Node<Data>*  node)
{
	Node<Data>* item = node;
	if (node == nullptr)
	{
		item = nullptr;
	}

	else if (node->leftPtr() != nullptr)//else if (node->leftPtr() != nullptr&&node->leftPtr()->getItem() > item)
	{
		item = minimum(node->leftPtr());
	}
	else
		item = node;

	return item;


}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////
// old SEARCH FUNCTIION THAT USED A NUMBER TO DISCERN THE GIVEN FIELD AND RETURNED A GIVEN NODE
//								**********NOTE**********
//				THIS FUNCTION WAS PART OF THE ORIGIONAL PROJECT UNTIL I DETERMINED THAT WE NEEDED A 
//				VECTOR OF RESULTS TO BE RETURN. 
//////////////////////////////////////////////////////////////////////////////////////////////////
//input: a node<data> Pointer, a string to search for, and a choice of a field of data to search on.
//description: this function was designed to find the item in question and return a pointer to that specific 
//node. the problem is covering ,multiple occurances of the found item. I overloaded this function in order to 
//facilitate having a vector of nodes returned and have since abandoned this function.
//
//output: a node<data> pointer
//////////////////////////////////////////////////////////////////////////////////////////////////
template<>
Node<Data>* BST<Data>::searchBST(Node<Data>* node, string item, int choice)
{

	// every search should visit each node in the tree /\/\/\/\ except the search for Id Numbers

	if (choice == 1)// firstname
	{
		if (node != nullptr)
		{
			if (item == node->getItem().getFirstName())
				return node; 
			if (item != node->getItem().getFirstName() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getFirstName() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getFirstName()!= item)
			{
				node = searchBST(node->rightPtr(), item, choice);
					//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;
	}
	if (choice == 2)// middlename
	{
		if (node != nullptr)
		{
			if (item == node->getItem().getMiddleName())
				return node;
			if (item != node->getItem().getMiddleName() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getMiddleName() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getMiddleName() != item)
			{
				node = searchBST(node->rightPtr(), item, choice);
				//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;

	}if (choice == 3)// last name
	{
		if (node != nullptr)
		{
			if (item == node->getItem().getLastName())
				return node;
			if (item != node->getItem().getLastName() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getLastName() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getLastName() != item)
			{
				node = searchBST(node->rightPtr(), item, choice);
				//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;


	}
	if (choice == 4)
	{
		if (node != nullptr)
		{
			if (item == node->getItem().getCompanyName())
				return node;
			if (item != node->getItem().getCompanyName() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getCompanyName() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getCompanyName() != item)
			{
				node = searchBST(node->rightPtr(), item, choice);
				//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;
	}

	if(choice == 5)
	{
		if (node != nullptr)
		{
			if (item == node->getItem().getHomePhone())
				return node;
			if (item != node->getItem().getHomePhone() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getHomePhone() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getHomePhone()!= item)
			{
				node = searchBST(node->rightPtr(), item, choice);
				//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;
	}
	if (choice == 6)
	{

		if (node != nullptr)
		{
			if (item == node->getItem().getWorkPhone())
				return node;
			if (item != node->getItem().getWorkPhone() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getWorkPhone() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getWorkPhone() != item)
			{
				node = searchBST(node->rightPtr(), item, choice);
				//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;
	}

	if (choice == 7)
	{
		if (node != nullptr)
		{
			if (item == node->getItem().getEmail())
				return node;
			if (item != node->getItem().getEmail() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getEmail() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getEmail() != item)
			{
				node = searchBST(node->rightPtr(), item, choice);
				//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;

	}
	
	if (choice == 8)
	{
		if (node != nullptr)
		{
			if (item == node->getItem().getCellPhone())
				return node;
			if (item != node->getItem().getCellPhone() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getCellPhone() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getCellPhone() != item)
			{
				node = searchBST(node->rightPtr(), item, choice);
				//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;

	}if (choice == 9)
	{
		if (node != nullptr)
		{
			if (item == node->getItem().getHomeAddress())
				return node;
			if (item != node->getItem().getHomeAddress() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getHomeAddress() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getHomeAddress() != item)
			{
				node = searchBST(node->rightPtr(), item, choice);
				//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;

	}
	if (choice == 10)
	{
		if (node != nullptr)
		{
			if (item == node->getItem().getCity())
				return node;
			if (item != node->getItem().getCity() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getCity() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getCity() != item)
			{
				node = searchBST(node->rightPtr(), item, choice);
				//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;

	}if (choice == 11)
	{
		if (node != nullptr)
		{
			if (item == node->getItem().getState())
				return node;
			if (item != node->getItem().getState() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getState() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getState() != item)
			{
				node = searchBST(node->rightPtr(), item, choice);
				//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;

	}
	if (choice == 12)
	{
		if (node != nullptr)
		{
			if (item == node->getItem().getZip())
				return node;
			if (item != node->getItem().getZip() && node->leftPtr() == nullptr && node->rightPtr() == nullptr)//MAKE SURE THIS WORKS1111111111111111111111111111111111111111111111111
				return nullptr;
			if (node != nullptr&&node->leftPtr() != nullptr&&node->getItem().getZip() != item)
			{

				node = searchBST(node->leftPtr(), item, choice);
				//cout << node->leftPtr()->getItem() << " ";
			}
			if (node != nullptr&&node->rightPtr() != nullptr&&node->getItem().getZip() != item)
			{
				node = searchBST(node->rightPtr(), item, choice);
				//cout << node->rightPtr()->getItem() << " ";

			}
		}
		return node;


	}
}


////-----------string-------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////////////////////
// old add FUNCTIION THAT USED A string int eh template TO add a node to the tree as a string type
//								**********NOTE**********
//				THIS FUNCTION WAS PART OF THE ORIGIONAL PROJECT WHICH I USED TO LEARN MORE ABOUT TEMPLATES SOAS TO 
//				ACCOMPLISH THIS PROJECT USING A TEMPLATED SYSTEM
//////////////////////////////////////////////////////////////////////////////////////////////////
//input: a node<data> Pointer, a string to ADD TO THE TREE.
//description: this function was designed to add a string to a specific tree based on the implamentation 
// of this project using templates. I needed to usnderstand templating a class that was the binary search tree.
//
//output: unfortunatly nothing.
//////////////////////////////////////////////////////////////////////////////////////////////////

template<>
void BST<string>::addNode(Node<string>* nodePtr, string item)
{
	Node<string>* curPtr = nullptr;
	if (root == nullptr)
	{
		root = new Node<string>;
		root->setItem(item);
		root->setParent(nodePtr);
	}

	else
	{

		if (item < nodePtr->getItem() && nodePtr->leftPtr() == nullptr)
		{
			curPtr = new Node<string>;
			curPtr->setItem(item);
			nodePtr->setLeft(curPtr);
			curPtr = nullptr;
			return;

		}
		//if (item > nodePtr->getItem() && nodePtr->rightPtr() == nullptr)  ---> changed the > to >=
		if (item >= nodePtr->getItem() && nodePtr->rightPtr() == nullptr)
		{
			curPtr = new Node<string>;
			curPtr->setItem(item);
			nodePtr->setRight(curPtr);
			curPtr = nullptr;
			return;
		}
		if (item < nodePtr->getItem() && nodePtr->leftPtr() != nullptr)
		{
			addNode(nodePtr->leftPtr(), item);

		}

		//if (item > nodePtr->getItem() && nodePtr->rightPtr() != nullptr)  ---> changed the > to >=
		if (item >= nodePtr->getItem() && nodePtr->rightPtr() != nullptr)
		{
			addNode(nodePtr->rightPtr(), item);

		}


	}

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//template<class type>
//Node<type>* BST<type>::searchBST(Node<type>* node, type number)
//{
//	if (node != nullptr)
//	{
//		if (node != nullptr)
//		{
//			if (node->getItem() == number)
//			{
//				node = node;
//				return node;
//			}
//		}
//		if (number < node->getItem())
//		{
//			if (node->leftPtr() != nullptr)
//			{
//				/*if (node->leftPtr()->getItem() == number)
//				{
//				node = node->leftPtr();
//				return node;
//				}
//				if (node->rightPtr()->getItem() == number)
//				{
//				node = node->rightPtr();
//				return node;
//				}*/
//				node = searchBST(node->leftPtr(), number);
//			}
//			else if (node->leftPtr() == nullptr)
//			{
//				return nullptr;
//			}
//		}
//		if (node != nullptr && number > node->getItem())
//		{
//			if (node->rightPtr() != nullptr)
//			{
//				/*if (node->leftPtr()->getItem() == number)
//				{
//				node = node->leftPtr();
//				return node;
//				}
//				if (node->rightPtr()->getItem() == number)
//				{
//				node = node->rightPtr();
//				return node;
//				}*/
//				node = searchBST(node->rightPtr(), number);
//			}
//			else if (node->rightPtr() == nullptr)
//			{
//				return nullptr;
//			}
//		}
//
//	}
//
//	return node;
//
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif