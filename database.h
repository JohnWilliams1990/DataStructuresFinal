// John Williams 
// 105201054
// HW9
// 11-02-16

#ifndef DATABASE_H
#define DATABASE_H
#include "Data.h"
class Database
{

public:
	//	This function is used to run the main menu and be the focal point of the entire program
	//  for the main and sub menu's.
	//	From here we will have sub menu's that will incorporate Reading in from a file, 
	//  adding a contact, removing a contact, searching on one field, searching on two fields, 
	//	and writing the current tree to a specific file. 
	void mainMenu();

	//this function is used to display a specific node
	void display(Node<Data>* nodePtr);
	// this functions is used to readin the given file //////I may allow the user to specifiy this file name
	void read(BST<Data>* dataPtr);
	// this function is used to add a contact to the Binary search tree
	void addContact(BST<Data>* dataPtr);
	// this function is used to delete a contact from the given tree
	void deleteContact(BST<Data>* dataPtr);

	///////////////////////////////////////////////////////////////////////////////
	// functions that pertain to the 2d vector which weas used to write the tree to a file
	/////////////////////////////////////////////////////////////////////////////////////////////////
	void sort(vector<Node<Data>*>& container, int functionNumber);
	void finalSort(vector<vector<string> > & item, int functionNumber);
	void viewVector(vector<vector<string> > item);
	void SecondaryFinalSort(vector<vector<string> >& item, int PriorField, int newField);
	/////////////////////////////////////////////////////////////////////////////////////////////////
	void edit(BST<Data>* dataPtr);
	void cleanMemory(vector<Node<Data>*>& item);
	string checkCase(string temp);
	Node<Data>* searchInital(BST<Data>* dataPtr, int functionNumber, vector<Node<Data>*> results);
	Node<Data>* SecondarySearchContact(BST<Data>* dataPtr, vector<Node<Data>*> results);
	vector<Node<Data>*> finalComparison(string temp, int functionNumber, vector<Node<Data>*> results);
	void contains(BST<Data>* dataPtr, int functionNumber, vector<Node<Data>*>& results);
	void saveFile(BST<Data>* dataPtr, string filename);
	//////////////////////////////////////////////////////////////////////////////

	// this function is used to perform a specific search on the given tree
	Node<Data>* searchContact(BST<Data>* dataPtr);

	// this function 'may' be called to do a search on the given tree as a secondary search
//---->changed this function 	Node<Data>* SecondarySearchContact(BST<Data>* dataPtr);
	// this is used to write the given tree to the file. we will probably use this as a save option and a exit option. 
	void WriteToFile(BST<Data>* dataPtr);



	

};
#endif