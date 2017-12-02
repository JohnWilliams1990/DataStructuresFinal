// John Williams 
// 105201054
// HW9
// 11-02-16

#include "BST.h"
#include "database.h"
#include <string>
#include<fstream>


///////////////////////////////////////////////////////////////
// input: nothing 
// description: 
// this function is used as thew main menu for the program and is looped so as to 
// direct the user to the specific item of their choice. 
//	This function is used to run the main menu and be the focal point of the entire program
//	From here we have have sub menu's that will incorporate Reading in from a file, 
//  adding a contact, removing a contact, searching on one field, and writing the current tree 
//	to a specific file. wi also have editing a contact and sorting and writing the final output. 
// 
// output: nothing
///////////////////////////////////////////////////////////////

void Database::mainMenu()
{
	Node<Data>* nodePtr = nullptr; //temperary pointer of node<Data> type 
	BST<Data>* dataPtr = nullptr;//temperary pointer of node<Data> type used to hold the tree 
	dataPtr = new BST<Data>;// create a new nodePtr
	vector<Node<Data>*> results;// vector of Node<Data> type for secondary search results 
	Data item;// temp item for manipulation of the Data items

	string temp;// temp for trhe manipulation of names ect 
	char choice = ' '; // choice for mst of the menu's in this program 

	while (true)/*main manu loop */
	{
		cout << "Main Menu:" << endl;
		cout << "Please select an option->" << endl << endl;
		cout << "A: Read in from a file" << endl;
		cout << "B: Add a contact" << endl;
		cout << "C: Remove a contact" << endl;
		cout << "D: Display current database" << endl;
		cout << "E: Edit a contact" << endl;
		cout << "F: Search for a specific item" << endl;
		cout << "G: Search for an occurance of an item" << endl;
		cout << "H: Save current database" << endl;
		cout << "I: Print the Database to a text file and exit" << endl;
		cout << "X: EXIT" << endl;
		cout << "" << endl;
		
		cin >> choice;
		switch (toupper(choice))// main switch used for the program 
		{
		case 'A':
			read(dataPtr);/*read fucntion called passing the main pointer for the tree*/
			break;

		case 'B':// ADD A CONTACT
			addContact(dataPtr);
			break;
		case 'C':// remove a contact 
				 /* if the treee is empty */
			if (dataPtr->rootPtr() == nullptr)
			{
				cout << endl << endl << "\t\tPlease add files into the database" << endl;
				cout << endl << endl;
				break;
			}
			/*otherwise we call the deelete fuction while passing the dataPtr*/
			deleteContact(dataPtr);
			break;
		case 'D':
			/*if the tree is empty*/
			if (dataPtr->rootPtr() == nullptr)
			{
				cout << endl << endl << "\t\tPlease add files into the database" << endl;
				cout << endl << endl;
				break;
			}
			/*otherwise display the tree*/
			dataPtr->printInOrder(dataPtr->rootPtr());
			//dataPtr->printPreOrder(dataPtr->rootPtr());
			//dataPtr->printPostOrder(dataPtr->rootPtr());

			break;

		case 'E':
			/*call the edit fuction and pass the tree*/
			/*if the tree is empty there is a fall back inside the search function wich has a call
			in the beginning of the edit function*/
			edit(dataPtr);

			break;
			
		case 'F':

			/*if the tree is empty then disregard*/
			if (dataPtr->rootPtr() == nullptr)
			{
				cout << endl << endl << "\t\tPlease add files into the database" << endl;
				cout << endl << endl;
				break;
			}
			/*otherwise nodePtr is catching the node that searchContact returns form the tree. 
			**NOTE** this function is used in other function and returns the node to the 
			functions that have a need of the node*/

			nodePtr = searchContact(dataPtr);


				break;
		case 'G':

			/*if the tree is empty then disregard this*/
			if (dataPtr->rootPtr() == nullptr)
			{
				cout << endl << endl << "\t\tPlease add files into the database" << endl;
				cout << endl << endl;
				break;
			}
			/*otherwise call the contains function and search along a specific field*/
			contains(dataPtr, 1, results);


			break;
		case 'H':
			/*if the tree is empty then disregard */
			if (dataPtr->rootPtr() == nullptr)
			{
				cout << endl << endl << "\t\tPlease add files into the database" << endl;
				cout << endl << endl;
				break;
			}
			/*otherwise determine the file to save to and call savefile() with the tree and the name of the 
			file to save to. */
			else 
			{
				cout << "Would you like to save to a different filename other than the default" << endl;
				cout << "A: yes" << endl;
				cout << "B: no" << endl;
				cin >> choice;
				if (toupper(choice) == 'A')
				{
					cout << "Enter a file name with the approperiate extention (.txt)" << endl;

					//------------------------------------------------------------------------------error checking for the .txt
					cin >> temp;
					saveFile(dataPtr, temp);
					break;
				}

				/*if the answer is no then we look at overwritting the old file */
				cout << "Are you sure you want to save the file" << endl;
				cout << "The current database file will be overwritten" << endl;

				cout << "A: yes" << endl;
				cout << "B: no" << endl;

				cin >> choice;
				
				if (toupper(choice) == 'A') /*if the user wants to overwrite the file */   
				{
					saveFile(dataPtr,"");
					cout << "\t\tFile has been saved to database.txt" << endl;
				}
				else/*else return to the main menu*/
				{
					cout << "Canceling the save operation" << endl;
				}
			}
			
			break;

		case 'I':
			
			/*call the writetofile() with with the tree as the parameter*/
			WriteToFile(dataPtr);

			
			break;
			
		default:
			/*default for the off chance of a miss type */
			cout <<endl<< "\t\tPlease make a VALID selection" <<endl<<endl;
			break;
		case 'X':

			results.clear();
			exit(0);
			break;

		}

	}
}


///////////////////////////////////////////////////////////////
// input: a pointer of Node<Data> type
// description: this function I used to determine what was 
// in the node as I created this database
// output: nothing
///////////////////////////////////////////////////////////////

void Database::display(Node<Data>* nodePtr)
{
	// if the node isn't empty then display it 
	if (nodePtr != nullptr)
	{
		cout << nodePtr->getItem() << endl;
	}
	else
	{// there is nothing in the node
		cout << "EMPTY NODE" << endl;

	}

}


///////////////////////////////////////////////////////////////
// input: a pointer of Node<Data> type by reference 
// description: 
// this function is used to read in a set of contacts from a file. 
// this is based on specific criteria and is outlined in the assignment.
// mostly this read in function is filling a certain fields of data. 
// for the affiliates 
// 
// output: nothing
///////////////////////////////////////////////////////////////

void Database::read(BST<Data>* dataPtr)
{
	// temp place holders for the items being inputed from the file
	string employeeNumber;

	string firstName;
	/*
	string middleName;
	string lastName;
	string companyName;
	string homePhone;
	string cellPhone;
	string workPhone;
	string email;
	string homeAddress;
	string city;
	string state;
	string zip;
	string country;

	
	*/
	int i = 0;
	string firstNameAffiliate;
	string homePhoneAffiliate;
	string emailAffiliate;
	string tempString; 
	Data temp;// temp data to be pushed into the tree 
	int count = 0;
	fstream file;/*file variable*/
	string name;
	Affiliate item;
	/*determine which file to open*/
	char option = ' ';
	while (toupper(option) !='A'&&toupper(option) != 'B'&&toupper(option) != 'C'&&toupper(option) != 'X')
	{
	cout << "Please select a file to use: " << endl << endl;
	cout << "A: databasesmall.txt" << endl;
	cout << "B: databaselarge.txt" << endl;
	cout << "C: other txt file" << endl;
	cout << "X: Exit" << endl;
	cin >> option;
	}
	if (toupper(option) == 'A') {
		name = "databasesmall.txt";
	}
	else if (toupper(option) == 'B') {
		name = "databaselarge.txt";
		
	} else if (toupper(option) == 'C') {

		cout << "Please enter a File name or enter X to return to the main menu" << endl;
		cout << "You can also enter O for the standard file on file" << endl;
		cin >> name;

	}
	else {
		return; 
	}
	



	
		file.open(name, ios::in);/*open the input file */

	if (file.fail())
	{
		char choice = ' ';
		cout << endl << endl << "ERROR READING FILE" << endl << endl << endl;
		cout << "A: Please check the file name and try again.... " << endl;
		cout << endl << "Press any key to continue...." << endl;
		cin.get(choice);
		return;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////@@
	/*while loop for the reading in of the file*/
	while (!file.eof() && (file.peek() != '|'))
	{
		i++;
	

		/*gather the items int he file */
		getline(file, employeeNumber);// get the employee number
		
		if (atol(employeeNumber.c_str()) == 0|| employeeNumber == "|")
		{
			cout << endl << "\t\tERROR READING FILE. PLEASE CHECK THE FILE AND TRY AGAIN."<<endl;
			return;
		}
		/*get the lines of information and stoe them into the given items */
		temp.setEmployeeNumber(employeeNumber);
	
		getline(file, firstName); //firstName
			temp.setFirstName(firstName);
		getline(file, tempString);//middleName
			temp.setMiddleName(tempString);
		getline(file, tempString);//lastName
			temp.setLastName(tempString);
		getline(file, tempString);//companyName
			temp.setCompanyName(tempString);
		getline(file, tempString);//homePhone
			temp.setHomePhone(tempString);
		getline(file, tempString);//workPhone
			temp.setWorkPhone(tempString);
		getline(file, tempString);//email
			temp.setEmail(tempString);
		getline(file, tempString);//cellPhone
			temp.setCellPhone(tempString);
		getline(file, tempString);//homeAddress
			temp.setHomeAddress(tempString);
		getline(file, tempString);//city
			temp.setCity(tempString);
		getline(file, tempString);//state
			temp.setState(tempString);
		getline(file, tempString);//zip
			temp.setZip(tempString);
		getline(file, tempString);//country
			temp.setCountry(tempString);
		/*set the individual items into the temp item of Data type */
		
		
		
		
		
		
		
		
		
		
		
		
		/*
		
		getline(file, firstName); tempString
		getline(file, middleName);
		getline(file, lastName);
		getline(file, companyName);
		getline(file, homePhone);
		getline(file, workPhone);
		getline(file, email);
		getline(file, cellPhone);
		getline(file, homeAddress);
		getline(file, city);
		getline(file, state);
		getline(file, zip);
		getline(file, country);
		temp.setEmployeeNumber(employeeNumber);
		temp.setFirstName(firstName);
		temp.setMiddleName(middleName);
		temp.setLastName(lastName);
		temp.setCompanyName(companyName);
		temp.setHomePhone(homePhone);
		temp.setCellPhone(cellPhone);
		temp.setWorkPhone(workPhone);
		temp.setEmail(email);
		temp.setHomeAddress(homeAddress);
		temp.setCity(city);
		temp.setState(state);
		temp.setZip(zip);
		temp.setCountry(country);

		*/
		count = 0;
		temp.clearAffiliates();

		/*read int he affiliates*/
		while (true)
			{
				//WE NEED TO TEST THE FIRST CHARACTER SO THAT WE AREN'T READING IN THE WHOLE FILE
				// we need to use a get function and then search inside the string we have obtained
				//file >> firstNameAffiliate >> homePhoneAffiliate >> emailAffiliate;

			file >> firstNameAffiliate;

			//getline(file, firstNameAffiliate, ',');
			/*if the firstnameAffiliates is the Pipe*/
			if (firstNameAffiliate == "|") //firstNameAffiliate.compare(0, 1, "|"
			{
				break;
			}
			///*if the firstnameaffiliates */
			if (firstNameAffiliate.compare(0, 1, ","))
			{

				getline(file, employeeNumber, ',');
				firstNameAffiliate += employeeNumber;
			}
			
			//file >> homePhoneAffiliate;
			getline(file, homePhoneAffiliate, ',');
			if (homePhoneAffiliate == "|") //homePhoneAffiliate.compare(0, 3, "\n|\n"
			{
				break;
			}
			
			//file >> emailAffiliate;
			getline(file, emailAffiliate, ';');
			if (emailAffiliate == "|")//emailAffiliate.compare(0, 1, "|") == true
			{
				break;
			}
			/*set the affiliate into the affiliate vector using the Affiliate member function*/
			//temp.setAffiliates(firstNameAffiliate, homePhoneAffiliate, emailAffiliate);

			item.setFirstName(firstNameAffiliate);
			item.setHomePhone(homePhoneAffiliate);
			item.setEmail(emailAffiliate);
			temp.setAffiliates(item);
			count++;
			if (count > 30)
			{
				cout << endl << "\t\tError reading the file\a" << endl;
				cout << endl << "\t\tPlease try reading in a different file or check to determine the file's formatting\a" << endl;
				return;



			}
		} 
		dataPtr->addNode(dataPtr->rootPtr(), temp); /*add the node*/
		file.ignore();/*ignore the pipe*/
		cout << i << ": " << firstName << endl;

		//cout << temp;
		//cout << endl;

		
	}

	file.close();
}

// this function is used to add a contact to the Binary search tree
///////////////////////////////////////////////////////////////
// input: a pointer of Node<Data> type by reference 
// description: 
// this function is used to add a contact to the tree. it gathers the information
// from the user using some error checking and confirming that the user Id number 
// is not already in use. if there is a conflict with the user Number and the file
// that is already in the system, we prompt the user for more information. 
// output: nothing
///////////////////////////////////////////////////////////////

void Database::addContact(BST<Data>* dataPtr)
{

	char affiliateOption = ' '; //menu option 
	Data temp;// temp item of type data 
	

	// placeholders of information for the new contact 
	string employeeNumber;
	string firstName;
	string middleName;
	string lastName;
	string companyName;
	string homePhone;
	string cellPhone;
	string workPhone;
	string email;
	string homeAddress;
	string city;
	string state;
	string zip;
	string country;
	string firstNameAffiliate;
	string homePhoneAffiliate;
	string emailAffiliate;
	Affiliate item;
	// ignore the buffer 
	cin.ignore();
	cout << "Please enter a nine digit Id Number" << endl;
	cout << "or enter X to return to main menu" << endl;

	getline(cin, employeeNumber);

	/*return to menu option */
	if (toupper(employeeNumber[0]) == 'X')
		return;
	/*number checking*/
	while (atol(employeeNumber.c_str()) == 0|| employeeNumber.size() < 9 || employeeNumber.size() > 9 || dataPtr->searchBST(dataPtr->rootPtr(), employeeNumber) != nullptr)
	{				
		if (dataPtr->searchBST(dataPtr->rootPtr(), employeeNumber))
		{
			cout <<endl<< "\tThis Number is already being used by another person and is unavailable" << endl << endl << endl;
		}
		cout << "Please enter a valid Id Number" << endl;
		getline(cin, employeeNumber);
	}

	/*gather the given information and as needed check it for mistakes. set this in*/
	cout << "Please enter a first name and press enter" << endl;
	getline(cin, firstName);
	cout << "Please enter a middle name and press enter" << endl;
	getline(cin, middleName);
	cout << "Please enter a last name and press enter" << endl;
	getline(cin, lastName);
	cout << "Please enter a company name and press enter" << endl;
	getline(cin, companyName);
	cout << "Please enter a home phone number and press enter" << endl;
	getline(cin, homePhone);
	/*check the phone number */
	while (atol(homePhone.c_str()) == 0 || homePhone.size()<10|| homePhone.size()>10)
	{
		cout << "Please enter a VALID home phone number, of ten digits, and press enter" << endl;
		getline(cin, homePhone);
	}
	cout << "Please enter a office phone number and press enter" << endl;
	getline(cin, workPhone);
	/*check the work phone number*/
	while (atol(workPhone.c_str()) == 0 || workPhone.size()<10 || workPhone.size()>10)
	{
		cout << "Please enter a VALID work phone number, of ten digits, and press enter" << endl;
		getline(cin, workPhone);
	}
	cout << "Please enter a email and press enter" << endl;
	getline(cin, email);
	cout << "Please enter a mobile number  and press enter" << endl;
	getline(cin, cellPhone);
	/*check the cell phone number*/
	while (atol(cellPhone.c_str()) == 0 || cellPhone.size()<10 || cellPhone.size()>10)
	{
		cout << "Please enter a VALID mobile phone number, of ten digits, and press enter" << endl;
		getline(cin, cellPhone);
	}
	cout << "Please enter a street adress, without the city, state, or zip and press enter" << endl;
	getline(cin, homeAddress);
	cout << "Please enter a city and press enter" << endl;
	getline(cin, city);
	cout << "Please enter a state and press enter" << endl;
	getline(cin, state);
	cout << "Please enter a zip and press enter" << endl;
	getline(cin, zip);
	/*check the zip code*/
	while (atol(zip.c_str()) == 0 || zip.size()<5 || zip.size()>5)
	{
		cout << "Please enter a VALID zip code, of 5 digits, and press enter" << endl;
		getline(cin, zip);
	}
	cout << "Please enter a country and press enter" << endl;
	getline(cin, country);

	/*while loop to gather the contacts at the discresion of the user*/
	while (true)
	{

		cout << "Please choose an option:" << endl;
		cout << "A: Enter an affiliate" << endl;
		cout << "B: Enter the contact as is, into the current database" << endl;
		cin >> affiliateOption;

		if (toupper(affiliateOption) == 'A')/*if we want to add another contact*/
		{
			cout << "Please enter a first name for an affiliate" << endl;
			cin.ignore();
			getline(cin, firstNameAffiliate);
			cout << "Please enter a phone number for the affiliate" << endl;
			getline(cin, homePhoneAffiliate);
			/*check the phoe number*/
			while (atol(homePhoneAffiliate.c_str()) == 0 || homePhoneAffiliate.size() < 10 || homePhoneAffiliate.size() > 10)
			{
				cout << "Please enter a VALID home phone number, of ten digits, and press enter" << endl;
				getline(cin, homePhoneAffiliate);
			}
			cout << "Please enter an email address for the affiliate" << endl;
			getline(cin, emailAffiliate);


			//temp.setAffiliates(firstNameAffiliate, homePhoneAffiliate, emailAffiliate);
			item.setFirstName(firstNameAffiliate);
			item.setHomePhone(homePhoneAffiliate);
			item.setEmail(emailAffiliate);
			temp.setAffiliates(item);
		}
		/*else break */
		if (toupper(affiliateOption ) == 'B')
		{
			break;
		}
	}
	/*set the item in to the temp data member*/
	temp.setEmployeeNumber(employeeNumber);
	temp.setFirstName(firstName);
	temp.setMiddleName(middleName);
	temp.setLastName(lastName);
	temp.setCompanyName(companyName);
	temp.setHomePhone(homePhone);
	temp.setCellPhone(cellPhone);
	temp.setWorkPhone(workPhone);
	temp.setEmail(email);
	temp.setHomeAddress(homeAddress);
	temp.setCity(city);
	temp.setState(state);
	temp.setZip(zip);
	temp.setCountry(country);
	/*push this item into the tree*/
	dataPtr->addNode(dataPtr->rootPtr(),temp);
}

// this function is used to delete a contact from the given tree
///////////////////////////////////////////////////////////////
// input: a pointer of Node<Data> type by reference 
// description: this function first uses a search, and if applicable, 
// a secondary search to find the record in question. if the record 
// is found then we can proceed to delete it
// output: nothing
///////////////////////////////////////////////////////////////

void Database::deleteContact(BST<Data>* dataPtr)
{
	Node<Data> * nodePtr = nullptr;// catcher for the search function
	char choice = ' ';// choice for the menu item



	nodePtr = searchContact(dataPtr);//---------------------------first search for the contact to delete 
	if (nodePtr != nullptr)
	{
		cout << nodePtr->getItem() << endl;// display the item
		

		cout << endl << "Are you sure you want to delete this File??" << endl;
		cout << "A: Yes" << endl;
		cout << "B: No" << endl;

		cin >> choice;

		if (toupper(choice) == 'A')
		{

			nodePtr = dataPtr->deleteNode(dataPtr->rootPtr(), nodePtr->getItem().getEmployeeNumber());

			// make sure that the item is deleted 
			/*if (nodePtr != nullptr)
			{
				cout << "The file wasn't able to be deleted" << endl;
				cout << nodePtr->getItem();
			}*/
		}
		
	}
	
	


}
// this function is used to perform a specific search on the given tree
///////////////////////////////////////////////////////////////
// input: a pointer of Node<Data> type 
// description: 
// This main search function is used in several of the function 
// and alone as a way to determine weather or not there is a specific 
// item inside the database. if the item is found it is returned to the 
// function and then it is deleted, edited or disregarded. 
// output: a pointer of Node<Data> type to the calling function
///////////////////////////////////////////////////////////////

Node<Data>* Database::searchContact(BST<Data>* dataPtr)
{
	vector<Node<Data>*> results;/*vector for the results of the search*/
	string temp;/*temp item used to hold the item being searched*/
	Node<Data> * nodePtr = nullptr;/*catcher for the secondary search*/
	char choice = ' ';/*menu selection */



	if (dataPtr->rootPtr() == nullptr)/*the tree is empty so return to the main menu*/
	{
		cout << endl << endl << "\t\tPlease add items to the database" << endl;
		return nullptr;
	}
	/*else we will start asking the user for information */
	cout << "Please choose a field to seach on to locate the file" << endl << endl;
	cout << "A: ID Number" << endl;
	cout << "B: First Name" << endl;
	cout << "C: Middle Name" << endl;
	cout << "D: Last Name" << endl;
	cout << "E: Company name" << endl;
	cout << "F: Home Phone" << endl;
	cout << "G: Office Phone" << endl;
	cout << "H: Email" << endl;
	cout << "I: Mobile Number" << endl;
	cout << "J: Address" << endl;
	cout << "K: City" << endl;
	cout << "L: State" << endl;
	cout << "M: Zip" << endl;
	cout << "N: country" << endl;
	cout << "O: Affiliate's first name" << endl;
	cout << "P: Affiliate's phone number" << endl;
	cout << "Q: Affiliate's Email" << endl;
	cout << "X: EXIT" << endl;
	
	cin >> choice; 


	switch (toupper(choice))/*main switch for the search function*/
	{
	case 'A'://employee number
		cout << "Please enter the Employee ID number" << endl;
		cin.ignore();
		getline(cin, temp);
		/*check the employee number from the user*/
		while (atol(temp.c_str()) == 0 || temp.size() < 9 || temp.size() > 9)
		{
			cout << "Please enter a valid Id Number" << endl;
			getline(cin, temp);
		}
		/*call the searchBST from BST.h and catch the results with the nodePtr*/
		nodePtr = dataPtr->searchBST(dataPtr->rootPtr(), temp);

		if (nodePtr != nullptr)/*solong as the nodePtr isn't null cout the item */
		{
			cout << nodePtr->getItem();
		}
		else// item dosen't exist 
		{
			cout << "The File associated with the employee number \'" << temp << "\' Dosen't exist." << endl;
				cout << "Please try again..." << endl;
				cleanMemory(results);
				return nullptr;
		}
		// check to determine if this is the particular file
		cout << endl << endl << "Is this the file??" << endl;
		cout << "A: Yes" << endl;
		cout << "B: No" << endl;
		cin >> choice;

		if (toupper(choice) == 'A')
		{
			cleanMemory(results);
			return nodePtr;
		}
		else if (toupper(choice) == 'B')
		{
			cout << endl << "\tPlease check the file and try again" << endl <<endl;
			cleanMemory(results);
			return nullptr;
		}


		break;

	case 'B'://search by first name
		/*call searchInitial passing the dataPtr, the function number 1, and the vector of nodePtrs 'results' 
		soas to search for the first name*/
		nodePtr = searchInital(dataPtr, 1, results);//searchName(dataPtr, 1);
		// clean out results
		cleanMemory(results);
		return nodePtr;
		break;
	case 'C':// middle name

			 /*call searchInitial passing the dataPtr, the function number 2, and the vector of nodePtrs 'results'
			 soas to search for the middle name*/
		nodePtr = searchInital(dataPtr, 2, results);
		cleanMemory(results);
		return nodePtr;
		break;
	case 'D':// last name

		/*call searchInitial passing the dataPtr, the function number 3, and the vector of nodePtrs 'results'
		soas to search for the last name*/
		nodePtr = searchInital(dataPtr, 3, results);
		cleanMemory(results);
		return nodePtr;
		
		break;
	case 'E':// company name
			 /*call searchInitial passing the dataPtr, the function number 4, and the vector of nodePtrs 'results'
			 soas to search for the company  name*/
		nodePtr = searchInital(dataPtr, 4, results);
		cleanMemory(results);
		return nodePtr;
			break;
	case 'F'://home phone
			 /*call searchInitial passing the dataPtr, the function number 5, and the vector of nodePtrs 'results'
			 soas to search for the homePhone */
		nodePtr = searchInital(dataPtr, 5, results);	
		cleanMemory(results);
		return nodePtr;
		break;
	case 'G':// office phone
			 /*call searchInitial passing the dataPtr, the function number 6, and the vector of nodePtrs 'results'
			 soas to search for the office phone*/
		nodePtr = searchInital(dataPtr, 6, results);
		cleanMemory(results);
		return nodePtr;

		break;
	case 'H'://email 
			 /*call searchInitial passing the dataPtr, the function number 7, and the vector of nodePtrs 'results'
			 soas to search for the Email*/
		nodePtr = searchInital(dataPtr, 7, results);
		cleanMemory(results);
		return nodePtr;
		break;
	case 'I'://cellPhone----------------------------------------------cell
			 /*call searchInitial passing the dataPtr, the function number 8, and the vector of nodePtrs 'results'
			 soas to search for the cellphone*/
		nodePtr = searchInital(dataPtr, 8, results);
		cleanMemory(results);
		return nodePtr;
		break;
	case 'J'://street address 

			 /*call searchInitial passing the dataPtr, the function number 9, and the vector of nodePtrs 'results'
			 soas to search for the street address*/
		nodePtr = searchInital(dataPtr, 9, results);
		cleanMemory(results);
		return nodePtr;
		break;
	case 'K'://city

			 /*call searchInitial passing the dataPtr, the function number 10, and the vector of nodePtrs 'results'
			 soas to search for the city*/
		nodePtr = searchInital(dataPtr, 10, results);
		cleanMemory(results);
		return nodePtr;
		break;
	case 'L'://State
			 /*call searchInitial passing the dataPtr, the function number 11, and the vector of nodePtrs 'results'
			 soas to search for the state*/
		nodePtr = searchInital(dataPtr, 11, results);
		cleanMemory(results);
		return nodePtr;
		break;
	case 'M'://zip

			 /*call searchInitial passing the dataPtr, the function number 12, and the vector of nodePtrs 'results'
			 soas to search for the zip code*/
		nodePtr = searchInital(dataPtr, 12, results);
		cleanMemory(results);
		return nodePtr;
		break;
	case 'N'://country 
			 /*call searchInitial passing the dataPtr, the function number 13, and the vector of nodePtrs 'results'
			 soas to search for the country*/
		nodePtr = searchInital(dataPtr, 13, results);
		cleanMemory(results);
		return nodePtr;
		break;
	case 'O'://Affiliate name
			 /*call searchInitial passing the dataPtr, the function number 14, and the vector of nodePtrs 'results'
			 soas to search for the affiliate name*/
		nodePtr = searchInital(dataPtr, 14, results);
		cleanMemory(results);
		return nodePtr;

		break;
	case 'P'://affiliate phone 
			 /*call searchInitial passing the dataPtr, the function number 15, and the vector of nodePtrs 'results'
			 soas to search for the affiliate phone*/
		nodePtr = searchInital(dataPtr, 15, results);
		cleanMemory(results);
		return nodePtr;

		break;
	case 'Q'://affiliate email
			 /*call searchInitial passing the dataPtr, the function number 16, and the vector of nodePtrs 'results'
			 soas to search for the affiliate email*/
		nodePtr = searchInital(dataPtr, 16, results);
		cleanMemory(results);
		return nodePtr;

		break;



	case 'X':
		/*return to the main menu*/
		return nullptr;
		break;

	default:

		break;
	}
	//return nullptr;
}
///////////////////////////////////////////////////////////////
// input: a pointer of BST<Data> type, an interger facilitating the function 
// type, and a vector of search results of node<data> pointers
// description: 
// This initial search function is used in several of the function 
// and alone as a way to initilally search for and locate any occurances of a particular string in a 
// particular field. if the item is found it is pushed into the vector and returned to this function 
// then the user is asked to validate the items in question or to do a seconadary search if applicable.
// output: a pointer of Node<Data> type to the calling function
///////////////////////////////////////////////////////////////

Node<Data>* Database::searchInital(BST<Data>* dataPtr, int functionNumber, vector<Node<Data>*> results)
{

	char choice = ' ';
	string temp;
	Node<Data>* nodePtr = nullptr;// catcher for the return from a secondary search
	while (true)//main function loop
	{
		cout << "Please enter a name" << endl;
		cin.ignore();
		getline(cin, temp);
		//determine the type of information expected and check the case of the first character with the user
			if (functionNumber > 0 && functionNumber <= 4 || functionNumber > 9 && functionNumber < 12)
			{
				temp = checkCase(temp);
			}
	
			// search for the given item in the tree using the given field as the function number here 
		dataPtr->searchBST(dataPtr->rootPtr(), temp, functionNumber, results);

		//sort the function 
		/////////////////////
		if (results.size()> 1)
		sort(results, functionNumber);
		/////////////////////
		if (results.size() == 0)// if there are no results return 
		{
			cout << endl << "No files were found with the given information" << endl;
			cout << "Please check the file and try again...." << endl;
			
			cin.get(choice);
			return nullptr;
		}
		else if (results.size() > 2)// if there are more than two results give the option to search again withing these items found 
		{
			cout << endl << endl << "We found " << results.size() << " files in the current database with that description." << endl;
			cout << "Would you like to search these " << results.size() << " files on another criteria??" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin>>choice;
			if (toupper(choice) == 'A')// secondary search call
			{
				nodePtr = SecondarySearchContact(dataPtr, results);
				return nodePtr;// return found node to the first search function for use
			}
			else// display the options one at a time
			{

				cout << "Would you like to view ALL of the found files??" << endl;
				cout << "A: Yes" << endl;
				cout << "B: No" << endl;
				cin >> choice;
				if (toupper(choice) == 'A')
				{

					for (int i = 0; i < results.size(); i++)// check if this is the item and if so return it 
					{
						cout << results[i]->getItem();
						cout << endl << "Is this the File?" << endl;
						cout << "A: Yes" << endl;
						cout << "B: No" << endl;
						cin >> choice;
						if (toupper(choice) == 'A')
						{
							return results[i];
						}


					}
				}
				


				return nullptr; // else return nullptr
			}
		}
		else// if we only have 2 0r less items 
		{
			cout << "we found " << results.size() << " files in the current database" << endl;
			int index = 0;

			while (index != results.size())// loop to display each and return the correct one if applicable
			{
				cout << results[index]->getItem() << endl;
				cout << "Is this the file you were looking for? " << endl;
				cout << "A: Yes" << endl;
				cout << "B: No" << endl;
				cin>>choice;
				if (toupper(choice) == 'A')
				{
					return results[index];
				}
				else if (toupper(choice) == 'B')
				{
					index++;
				}
				else
				{
					continue;
				}

			}
		
			if (index == results.size())// if the file wasn't selected 
			{
				cout << "Sorry we didn't find the file." << endl;
				cout << "Please check the file and try again " << endl << endl;
				return nullptr;
			}
		}
	}
}

// this function 'may' be called to do a search on the given tree as a secondary search
///////////////////////////////////////////////////////////////
// input: a pointer of Node<Data> type, and a vector of node<Data> type by reference
// description: 
// The secondary search function recieves a vector of node<data> type Pointers and searches 
// the vector for the item in question from the user on a second field. it then returns it to 
// the primary searching function for further use. this function calls the finalComparison() function
// and gives it a function number based on the user's choice in this function of what they would like 
// for their search parameter.
// output: a pointer of Node<Data> type to the calling function
///////////////////////////////////////////////////////////////

Node<Data>* Database::SecondarySearchContact(BST<Data>* dataPtr, vector<Node<Data>*> results)
{
	

	vector<Node<Data>*> newResults;//a vector for holding the new search results
	char choice = ' '; // menu option
	Node<Data>* nodePtr = nullptr; // temp nodePtr for holding result
	string temp;// string item to search for 
	cout << "Please choose a secondary field to search on "<<endl;
	cout << "A: ID Number" << endl;
	cout << "B: First Name" << endl;
	cout << "C: Middle Name" << endl;
	cout << "D: Last Name" << endl;
	cout << "E: Company name" << endl;
	cout << "F: Home Phone" << endl;
	cout << "G: Office Phone" << endl;
	cout << "H: Email" << endl;
	cout << "I: Mobile Number" << endl;
	cout << "J: Address" << endl;
	cout << "K: City" << endl;
	cout << "L: State" << endl;
	cout << "M: Zip" << endl;
	cout << "N: Country" << endl;
	cout << "O: Affiliate's first name" << endl;
	cout << "P: Affiliate's phone number" << endl;
	cout << "Q: Affiliate's Email" << endl;
	cout << "X: EXIT" << endl;


	cin >> choice;
	switch (toupper(choice))// secondary searching switch 
	{
	case 'A'://employee number
		cout << "Please enter an id number" << endl;
		cin.ignore();
		getline(cin, temp);
		// determine if the number enter is a number and is it 9 characters long
		while (atol(temp.c_str()) == 0 || temp.size() < 9 || temp.size() > 9) 
		{
			cout << "Please enter a valid Id Number" << endl;
			getline(cin, temp);
		}

		//catch a vector of nodePtrs for the final results of the searching
		newResults = finalComparison(temp, 0, results);

		for (int i = 0; i < newResults.size(); i++)//cycle through the results and ask which is what the user is looking for
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin>>choice;
			if (toupper(choice) == 'A')
			{

				//cout << newResults[i]->getItem();//-----------------------------------------------------------remove
				return newResults[i];

			}


		}
		// no other file => return NULL
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;

		break;

	case 'B'://search by first name
		cout << "Please enter a name" << endl;
		cin.ignore();
		getline(cin, temp);
		
		
			temp = checkCase(temp);// check the first letter for capitialization 
		
		// catch the vector of nodes from searching for the firstname in the results vector 
		newResults = finalComparison(temp, 1, results);

		for (int i = 0; i < newResults.size(); i++)// ask the user if this is the record
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			//cin.ignore();
			cin>>choice;
			//			buffer problem here ---> don't use cin.get();
			if (toupper(choice) == 'A')
			{
				//cout<< newResults[i]->getItem();///////////////---------------------------------------------------remove
				return newResults[i];
			}


		}

		if (toupper(choice) != 'A')// outside the forloop we are out of records to check => return to main via NULL
		{	
			cout << "We found no files with the given parameter..." << endl;
			return nullptr;
		}

		break;
	case 'C':// middle name
		
		cout << "Please enter a name" << endl;
		cin.ignore();
		getline(cin, temp);
		
			temp = checkCase(temp);// check the case 
		
		newResults = finalComparison(temp, 2, results);// search via the correct function number 

		for (int i = 0; i < newResults.size(); i++)//  go throught the results and question the user for input
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')// no records so returnj to main 
			{
				return newResults[i];
			}

			 
		}
		// if there are no results return to main 
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		break;
	case 'D':// last name
		cout << "Please enter a name" << endl;
		cin.ignore();
		getline(cin, temp);

		
		temp = checkCase(temp);// check the case of the item 
		
		newResults = finalComparison(temp, 3, results);// call the copmparison using the approperate function number

		for (int i = 0; i < newResults.size(); i++)// ask the user about the results if there are any
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		// else return to main if not found
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		
		
		break;
	case 'E':// company name
		cout << "Please enter a name" << endl;
		cin.ignore();
		getline(cin, temp);

			temp = checkCase(temp);// check the case of the item 

		newResults = finalComparison(temp, 4, results);// search on the approprate filed with final search 

		for (int i = 0; i < newResults.size(); i++)// ask the user for the final comparison 
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		// if not found return nullptr
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		
		break;
	case 'F'://home phone

		cout << "Please enter a number" << endl;
		cin.ignore();
		getline(cin, temp);// get presumable number 
		while (atol(temp.c_str()) == 0 || temp.size()<10 || temp.size()>10)//check number
		{
			cout << "Please enter a VALID phone number, of ten digits, and press enter" << endl;
			getline(cin, temp);
		}
		
		newResults = finalComparison(temp, 5, results);//search for number in given field 

		for (int i = 0; i < newResults.size(); i++)// ask user for final comparison 
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		//if not found by user return to main 
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		break;
	case 'G':// office phone
		cout << "Please enter a number" << endl;
		cin.ignore();
		getline(cin, temp);//gather information 


		while (atol(temp.c_str()) == 0 || temp.size()<10 || temp.size()>10)//check to see that it is a ten digit number
		{
			cout << "Please enter a VALID phone number, of ten digits, and press enter" << endl;
			getline(cin, temp);
		}
		newResults = finalComparison(temp, 6, results);//search on the given field 

		for (int i = 0; i < newResults.size(); i++)//ask user for the final comparison of the whole vector
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		//else return to main wih null
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		cout << "" << endl;
		break;
	case 'H'://email 
		cout << "Please enter a email address" << endl;
		cin.ignore();
		getline(cin, temp);//gather requested information 

		
		newResults = finalComparison(temp, 7, results);//search the given paramenter 

		for (int i = 0; i < newResults.size(); i++)//ask the user for the given parameter
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		//if not found return to the main menu
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		cout << "" << endl;
		break;
	case 'I'://cellPhone
		cout << "Please enter a mobile number" << endl;
		cin.ignore();
		getline(cin, temp);//gather info 


		while (atol(temp.c_str()) == 0 || temp.size()<10 || temp.size()>10)//make sure that it is a number
		{
			cout << "Please enter a VALID phone number, of ten digits, and press enter" << endl;
			getline(cin, temp);
		}

		newResults = finalComparison(temp, 8, results);//search on the given field in final search 

		for (int i = 0; i < newResults.size(); i++)//ask user for given comparison determination 
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		//if not found return to main menu
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		cout << "" << endl;
		break;
	case 'J'://street address
		cout << "Please enter an address" << endl;
		cin.ignore();
		getline(cin, temp);//gather info 

		newResults = finalComparison(temp, 9, results);//search field 

		for (int i = 0; i < newResults.size(); i++)//ask user to confirm result or 
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		//if not found return to main menu with null
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		cout << "" << endl;
		break;
	case 'K'://city
		cout << "Please enter a City" << endl;
		cin.ignore();
		getline(cin, temp);//gather info 
		
			temp = checkCase(temp);//check the case of the first character
		
		
		newResults = finalComparison(temp, 10, results);//search the given field for the item inside the vecor

		for (int i = 0; i < newResults.size(); i++)//ask the user for a confirmation of the item 
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		//if nort found return to main menu
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		break;
	case 'L'://State

		cout << "Please enter a state" << endl;
		cin.ignore();
		getline(cin, temp);//gather info 

			temp = checkCase(temp);// check the case of the item 
		
		newResults = finalComparison(temp, 11, results);//search the vector for the item on the specified field

		for (int i = 0; i < newResults.size(); i++)//ask the user for the comparison 
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		//return if not in the vector 
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		break;

	case 'M'://Zip

		cout << "Please enter a zip" << endl;
		cin.ignore();
		getline(cin, temp);//gather info 

		while (atol(temp.c_str()) == 0 || temp.size()<5 || temp.size()>5)//determine iif it is a legitimate zipcode
		{
			cout << "Please enter a VALID zip code, of 5 digits, and press enter" << endl;
			getline(cin, temp);
		}

		newResults = finalComparison(temp, 12, results);//check for it inside the smaller vector 

		for (int i = 0; i < newResults.size(); i++)//ask the user for the final comparison 
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		//return null if not in the vector
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		break;
	case 'N'://country

		cout << "Please enter a name" << endl;
		cin.ignore();
		getline(cin, temp);//gather information 

		
		newResults = finalComparison(temp, 13, results);//search on the given parameter

		for (int i = 0; i < newResults.size(); i++)//ask the user to make a comparison of results
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		// if item isn't in the vector return to main menu()
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		break;

	case 'O'://Affiliate's first name
		cout << "Please enter a name" << endl;
		cin.ignore();
		getline(cin, temp);//gather info 


		temp = checkCase(temp);// check the case of the item 

		newResults = finalComparison(temp, 14, results);//make comparison of affiliates firstname

		for (int i = 0; i < newResults.size(); i++)//ask the user for a comparison 
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		//if not in the vector return to main() menu
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		break;

		break;
	case 'P'://Affiliate's phone number
		cout << "Please enter a number" << endl;
		cin.ignore();
		getline(cin, temp);//gather infomation 

		while (atol(temp.c_str()) == 0 || temp.size()<10 || temp.size()>10) //check for accurate format
		{
			cout << "Please enter a VALID phone number, of ten digits, and press enter" << endl;
			getline(cin, temp);
		}

		newResults = finalComparison(temp, 15, results);//search the given field 

		for (int i = 0; i < newResults.size(); i++)//ask user to verify result or discard 
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		//if not in vecotr return to main menu()
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		break;

		break;
	case 'Q'://Affiliate's Email
		cout << "Please enter a email" << endl;
		cin.ignore();
		getline(cin, temp);//gather information 

		newResults = finalComparison(temp, 16, results);//search on the given parameter

		for (int i = 0; i < newResults.size(); i++)//ask the user to find the given item in results from the search 
		{
			cout << newResults[i]->getItem();
			cout << endl << "Is this the File?" << endl;
			cout << "A: Yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				return newResults[i];
			}


		}
		//if not in the file then we go back to main function 
		cout << "We found no files with the given parameter..." << endl;
		return nullptr;
		break;

		break;
	case 'X'://EXIT the second search function 
		return nullptr;
		break;
	default:
		// error please try again 
		cout << endl << "\t\tPlease enter a VALID selection" << endl;

		break;
	}

	return nullptr;
}
// this is used to write the given tree to the file. we will probably use this as a save option and a exit option. 



///////////////////////////////////////////////////////////////
// input: a pointer of Node<Data> type, a string containing the filename 
// description: 
// this function take the filename and opens the file and then calls a special 
// traversal function inside the BST.h traversal that streams all of the file 
// to the filename that was given.
// output: unfortunately nothing 
///////////////////////////////////////////////////////////////

void Database::saveFile(BST<Data>* dataPtr, string filename)
{
	fstream file;// placeholder for the file 
	if (filename == "")// if the choice is the default filename we use database.txt
	{
		file.open("database.txt", ios::out);

		dataPtr->printPostOrder(dataPtr->rootPtr(), file);// stream to the file

		file.close();//close the file 
	}
	else
	{
		file.open(filename, ios::out);//open the given filename 

		dataPtr->printPostOrder(dataPtr->rootPtr(), file);//stream the file to the given file

		file.close();//close the file
	}
}

///////////////////////////////////////////////////////////////
// input: a pointer of Node<Data> type, a vector of node<Data> type 
// by reference, and a int for a function number
// description: 
// this function is used to determine if a selected field contains a 
// given string.
// 
// output: unfortunately nothing 
///////////////////////////////////////////////////////////////

void Database::contains(BST<Data>* dataPtr, int functionNumber, vector<Node<Data>*>& results)////////////////////read specificaltions for this function 
{

	string temp;//placeholder for the input from the user 
	char choice = ' ';// menu chocie 
	cout << "Please enter a general item to search the database for:" << endl;
	cin.ignore();
	getline(cin, temp);
	cout << "Which field would you like to search for this item on??" << endl;
	cout << "A: ID Number" << endl;
	cout << "B: First Name" << endl;
	cout << "C: Middle Name" << endl;
	cout << "D: Last Name" << endl;
	cout << "E: Company name" << endl;
	cout << "F: Home Phone" << endl;
	cout << "G: Office Phone" << endl;
	cout << "H: Email" << endl;
	cout << "I: Mobile Number" << endl;
	cout << "J: Address" << endl;
	cout << "K: City" << endl;
	cout << "L: State" << endl;
	cout << "M: Zip" << endl;
	cout << "N: Country" << endl;

	
	
	
	cin >> choice;

	switch (toupper(choice))//main switch for the compare menu 
	{
	case 'A'://employee number

		dataPtr->contains(dataPtr->rootPtr(), temp, 0, results);// call the specific contains function woth the given parameter 
		
		for (int  i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}

		if (results.size() == 0)//else the item wasn't found
		{
			cout <<endl<<endl<< "\t\tWe didn't find the item in question" <<endl<< endl;
		}
		break;

	case 'B'://search by first name
		dataPtr->contains(dataPtr->rootPtr(), temp, 1, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'C':// middle name
		dataPtr->contains(dataPtr->rootPtr(), temp, 2, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'D':// last name
		dataPtr->contains(dataPtr->rootPtr(), temp, 3, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
			
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'E':// company name
		dataPtr->contains(dataPtr->rootPtr(), temp, 4, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'F'://home phone
		dataPtr->contains(dataPtr->rootPtr(), temp, 5, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'G':// office phone
		dataPtr->contains(dataPtr->rootPtr(), temp, 6, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'H'://email 
		dataPtr->contains(dataPtr->rootPtr(), temp, 7, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'I'://cellPhone
		dataPtr->contains(dataPtr->rootPtr(), temp, 8, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'J'://street address 
		dataPtr->contains(dataPtr->rootPtr(), temp, 9, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'K'://city
		dataPtr->contains(dataPtr->rootPtr(), temp, 10, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'L'://State
		dataPtr->contains(dataPtr->rootPtr(), temp, 11, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'M'://zip
		dataPtr->contains(dataPtr->rootPtr(), temp, 12, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'N'://country 
		dataPtr->contains(dataPtr->rootPtr(), temp, 13, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case 'O'://country 
		dataPtr->contains(dataPtr->rootPtr(), temp, 14, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'P'://country 
		dataPtr->contains(dataPtr->rootPtr(), temp, 15, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;
	case 'Q'://country 
		dataPtr->contains(dataPtr->rootPtr(), temp, 16, results);// call the specific contains function woth the given parameter 

		for (int i = 0; i < results.size(); i++)// print out the item if it was found 
		{
			cout << results[i]->getItem();
		}
		if (results.size() == 0)//else the item wasn't found
		{
			cout << endl << endl << "\t\tWe didn't find the item in question" << endl << endl;
		}
		break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
	default:

		break;
	}


}


///////////////////////////////////////////////////////////////
// input: a pointer of Node<Data> type, a string containing the string being searched for
// and the vector of initial results
// description: 
// this function take the filename and opens the file and then calls a special 
// traversal function inside the BST.h traversal that streams all of the file 
// to the filename that was given.
// output: unfortunately nothing 
///////////////////////////////////////////////////////////////
vector<Node<Data>*> Database::finalComparison(string temp, int functionNumber, vector<Node<Data>*> results)
{
	vector<Node<Data>*> newResults;// vector for the final results to be returned to calling function 
	
	switch (functionNumber)//switch based on the function number from the initial search function
	{
	case 0://employee number
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getEmployeeNumber())//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;
		break;
	case 1://search by first name
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getFirstName())//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;
		break;
	case 2:// middle name	
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getMiddleName())//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;
		break;
	case 3:// last name
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getLastName())//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;
		break;
	case 4:// company name
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getCompanyName())//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;


		break;
	case 5://home phone
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getHomePhone())//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;
		break;

	case 6:// office phone
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getWorkPhone())//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;

		break;
	case 7://email 
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getEmail())//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;

		break;
	case 8://cellPhone
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getCellPhone())//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;

		break;
	case 9://street address
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getHomeAddress())//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;

		break;
	case 10://city
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getCity())//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;

		break;
	case 11://State
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getState());//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;

		break;
	case 12://zip
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getZip());//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;

		break;
	case 13://country
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			if (temp == results[i]->getItem().getCountry());//compare and if they are a match push into vector 
			{
				newResults.push_back(results[i]);
			}
		}
		return newResults;

		break;
	case 14://affiliate firstname
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			for (int i = 0; i < results[i]->getItem().getNumberOfAffiliates(); i++)
			{
				if (temp == results[i]->getItem().getAffiliates(i, 0));//compare and if they are a match push into vector 
				{
					newResults.push_back(results[i]);
				}
			}
		}
		return newResults;
	case 15://affiliate phone 
		break;
		//					case 11://State
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			for (int i = 0; i < results[i]->getItem().getNumberOfAffiliates(); i++)
			{
				if (temp == results[i]->getItem().getAffiliates(i, 1));//compare and if they are a match push into vector 
				{

					newResults.push_back(results[i]);
				}
			}
		}
		return newResults;
	case 16: //affiliate email
		break;
		//					case 11://State
		for (int i = 0; i < results.size(); i++)// iterator to directly compare through each item in vector
		{
			for (int i = 0; i < results[i]->getItem().getNumberOfAffiliates(); i++)
			{
				if (temp == results[i]->getItem().getAffiliates(i, 2));//compare and if they are a match push into vector 
				{
					newResults.push_back(results[i]);
				}
			}
		}
		return newResults;

		break;
		//					
	}
}


///////////////////////////////////////////////////////////////
// input: a string 
// description: 
// this function determines if the first characetr in the string 
// is upppercase and if not asks the user for clarification 
// output: the string either corrected or not
///////////////////////////////////////////////////////////////

string Database::checkCase(string temp)
{
	string temp1;
	char choice = ' ';
	if (temp[0] >= 97 && temp[0] <= 122)// && functionNumber > 0 && functionNumber < 4 || functionNumber > 9 && functionNumber < 12)
	{
		temp1 = temp;
		temp1[0] = static_cast<int>(temp[0]) - 32;
		cout << endl << endl << "\tDid you mean " << temp1 << "??" << endl;
		cout << "A: Yes" << endl;
		cout << "B: No" << endl;
		cin >> choice;

		if (toupper(choice) == 'A')// swap strings
		{
			temp = temp1;
		}
		else
		{
			cout << "searching for " << temp << endl << endl;;
		}
		//error with end result of the name
	}


	return temp;// return either srting that the user has selected

}


///////////////////////////////////////////////////////////////
// input: a vector of nodePtrs of data type 
// description: 
// this function destructs the vectors that have been used in the program
// output: unfortunately nothing 
///////////////////////////////////////////////////////////////
void Database::cleanMemory(vector<Node<Data>*>& item)
{
	item.clear();
}

///////////////////////////////////////////////////////////////
// input: a vector of nodePtrs of data type by reference and a interger representing the 
// field to sort on
// description: 
// this function sorts the given vector based on the function number that 
// was passed into it.
//							//**************NOTE**************//
// direct comparison bubble sort based on the code learned from Tony Gladdis' "Starting Out With c++ 8th edition"

// output: unfortunately nothing 
///////////////////////////////////////////////////////////////
void Database::sort(vector<Node<Data>*>& container, int functionNumber)
{
	Node<Data>* temp;
	bool swapage = true;

	switch (functionNumber)// switch based on the number that was passed into the function (I am tired)
	{
	case 1://employee number


		//bubble sort of field based on switch
		while (swapage)
		{
		swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getEmployeeNumber() > container[i + 1]->getItem().getEmployeeNumber())
				{
		   			temp = container[i];
		   			container[i] = container[i + 1];
		   			container[i + 1] = temp;
		   			swapage = true;
				}
			}
		}

		break;

	case 2://search by first name
		   //bubble sort of field based on switch

		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getFirstName() > container[i + 1]->getItem().getFirstName())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 3:// middle name
		   //bubble sort of field based on switch

		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getMiddleName() > container[i + 1]->getItem().getMiddleName())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 4:// last name
		   //bubble sort of field based on switch

		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getMiddleName() > container[i + 1]->getItem().getMiddleName())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 5:// company name
		   //bubble sort of field based on switch

		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getCompanyName() > container[i + 1]->getItem().getCompanyName())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 6://home phone
		   //bubble sort of field based on switch

		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getHomePhone() > container[i + 1]->getItem().getHomePhone())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 7:// office phone
		   //bubble sort of field based on switch
		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getWorkPhone() > container[i + 1]->getItem().getWorkPhone())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 8://email //bubble sort of field based on switch
		
		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getEmail() > container[i + 1]->getItem().getEmail())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 9://cellPhone//bubble sort of field based on switch
		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getCellPhone() > container[i + 1]->getItem().getCellPhone())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 10://street address 
			//bubble sort of field based on switch
		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getHomeAddress() > container[i + 1]->getItem().getHomeAddress())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 11://city
			//bubble sort of field based on switch
		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getCity() > container[i + 1]->getItem().getCity())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 12://State
			//bubble sort of field based on switch
		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getState() > container[i + 1]->getItem().getState())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 13://zip
			//bubble sort of field based on switch
		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getEmployeeNumber() > container[i + 1]->getItem().getEmployeeNumber())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	case 14://country 
			//bubble sort of field based on switch
		while (swapage)
		{
			swapage = false;
			for (int i = 0; i < container.size() - 1; i++)
			{
				if (container[i]->getItem().getCountry() > container[i + 1]->getItem().getCountry())
				{
					temp = container[i];
					container[i] = container[i + 1];
					container[i + 1] = temp;
					swapage = true;
				}
			}
		}
		break;
	
	default:

		break;
	}
}


///////////////////////////////////////////////////////////////
// input: a pointer of BST<Data> type, 
// description: 
// This function is used to edit one contacts specific field based on
// the user input. we use a switch to determine what field needs editing.
// output: unfortunately nothing 
///////////////////////////////////////////////////////////////

void Database::edit(BST<Data>* dataPtr)
{
	vector<Affiliate> temporary;
	Data item;
	Node<Data>* tempPtr = nullptr;
	Node<Data>* placeholderPtr = nullptr;
	char choice = ' ';
	string temp;
	int affiliateNumber = 0;
	Affiliate push;

	tempPtr = searchContact(dataPtr);// search for the contact to edit and obtain the node if applicable 

	if (tempPtr != nullptr)// gather the item from the pointer if applicable
	{
		item = tempPtr->getItem();
	}
	else if (tempPtr == nullptr)// otherwise ERROR nad return to mainmenu()
	{
		cout << endl << endl<< "\t\tWe cannot edit the unknown contact" << endl;
		cout << "\t\tPlease try again" <<endl<< endl;
		return;
	}

	// gather the user input of what to edit
	cout << endl << endl << "What would you like to edit for this contact" << endl<<endl;
	cout << "A: ID Number" << endl;
	cout << "B: First Name" << endl;
	cout << "C: Middle Name" << endl;
	cout << "D: Last Name" << endl;
	cout << "E: Company name" << endl;
	cout << "F: Home Phone" << endl;
	cout << "G: Office Phone" << endl;
	cout << "H: Email" << endl;
	cout << "I: Mobile Number" << endl;
	cout << "J: Address" << endl;
	cout << "K: City" << endl;
	cout << "L: State" << endl;
	cout << "M: Zip" << endl;
	cout << "N: Country" << endl;
	cout << "O: Affiliate information " << endl;




	cin >> choice;

	//
	//for each field of the switch we are ataking the item of Data type, editing the specified field 
	//putting it into the placeholder's new Node<Data> ptr and then deleting the old pointer and adding this new pointer.
	//
	//Please note that if there is a better way to do this I am all ears. a most anoying prospect
	//

	switch (toupper(choice))// based on user choice of what to edit 
	{
	case 'A'://employee number
		cout << "Please enter a new employee Id number" << endl;

		cin.ignore();
		getline(cin, temp);

		while (atol(temp.c_str()) == 0 || temp.size() < 9 || temp.size() > 9 || dataPtr->searchBST(dataPtr->rootPtr(), temp) != nullptr)
		{
			if (dataPtr->searchBST(dataPtr->rootPtr(), temp))
			{
				cout << endl << "\tThis Number is already being used by another person and is unavailable" << endl << endl << endl;
			}
			cout << "Please enter a valid Id Number" << endl;
			getline(cin, temp);
		}
		
		item.setEmployeeNumber(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;


	case 'B'://search by first name
		cout << "Please enter a new first name" << endl;

		cin.ignore();
		getline(cin, temp);
		temp = checkCase(temp);

		item.setFirstName(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'C':// middle name
		cout << "Please enter a new middle name" << endl;

		cin.ignore();
		getline(cin, temp);
		temp = checkCase(temp);
		item.setMiddleName(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'D':// last name
		cout << "Please enter a new last Name" << endl;

		cin.ignore();
		getline(cin, temp);
		temp = checkCase(temp);
		item.setLastName(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'E':// company name
		cout << "Please enter a new company name" << endl;

		cin.ignore();
		getline(cin, temp);
		temp = checkCase(temp);
		item.setCompanyName(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'F'://home phone
		cout << "Please enter a new home phone number" << endl;

		cin.ignore();
		getline(cin, temp);
		item.setHomePhone(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'G':// office phone
		cout << "Please enter a new office phone number " << endl;

		cin.ignore();
		getline(cin, temp);
		item.setWorkPhone(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'H'://email 
		cout << "Please enter a new email address" << endl;

		cin.ignore();
		getline(cin, temp);
		item.setEmail(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'I'://cellPhone
		cout << "Please enter a new mobile phone number" << endl;

		cin.ignore();
		getline(cin, temp);
		item.setCellPhone(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'J'://street address 
		cout << "Please enter a new street address" << endl;

		cin.ignore();
		getline(cin, temp);
		item.setHomeAddress(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'K'://city
		cout << "Please enter a new city " << endl;

		cin.ignore();
		getline(cin, temp);
		temp = checkCase(temp);
		item.setCity(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'L'://State
		cout << "Please enter a new state" << endl;

		cin.ignore();
		getline(cin, temp);
		temp = checkCase(temp);
		item.setState(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'M'://zip
		cout << "Please enter a new zip code" << endl;

		cin.ignore();
		getline(cin, temp);
		item.setZip(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'N'://country
		cout << "Please enter a new country" << endl;

		cin.ignore();
		getline(cin, temp);
		temp = checkCase(temp);
		item.setCountry(temp);
		placeholderPtr = new Node<Data>;
		placeholderPtr->setItem(item);
		dataPtr->deleteNode(tempPtr->getItem());
		dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());
		delete placeholderPtr;
		break;
	case 'O'://Affiliate
		// for the affiliate we must remove the item, edit it and replace it as well as changing the specific item in the
		// affiliate vector
		
		for (int i = 0; i < tempPtr->getItem().getNumberOfAffiliates(); i++)
		{
			cout << "\t\t" << i+1 << ":  ";
			for (int j = 0; j < 3; j++)
			{
				cout<< tempPtr->getItem().getAffiliates(i, j)<<"  ";
			}
			cout << endl;
		}

		if (tempPtr->getItem().getNumberOfAffiliates() == 0)
		{
			cout << "There are no affiliates in this file." << endl;
				affiliateNumber = 0;

				cout << "Would you like to add an affiliate to " << tempPtr->getItem().getEmployeeNumber() << "?" << endl;
				cout << "A: Yes" << endl;
				cout << "B: No" << endl;
				cin >> choice;
				if (toupper(choice) == 'A')
				{
					
						cout << "Please enter a first name for an affiliate" << endl;
						cin.ignore();
						getline(cin, temp);
						push.setFirstName(temp);
						cout << "Please enter a phone number for the affiliate" << endl;
						getline(cin, temp);
						
						while (atol(temp.c_str()) == 0 || temp.size() < 10 || temp.size() > 10)
						{
							cout << "Please enter a VALID home phone number, of ten digits, and press enter" << endl;
							getline(cin, temp);
						}
						push.setHomePhone(temp);
						cout << "Please enter an email address for the affiliate" << endl;
						getline(cin, temp);
						push.setEmail(temp);
						
						temporary.push_back(push);
						item.setVector(temporary);
						dataPtr->deleteNode(tempPtr->getItem());
						dataPtr->addNode(dataPtr->rootPtr(), item);// placeholderPtr->getItem());
						
						return;

				}
				else
				{
					return;

				}

		}
		else
		{
			cout << endl << "Which affiliate would you like to edit" << endl;
			cin >> affiliateNumber;
			affiliateNumber--;// decramented because of the off by one error;
			cout << endl << "What would you like to edit for the affiliate" << endl;
			cout << "A: Name" << endl;
			cout << "B: Phone number" << endl;
			cout << "C: Email" << endl;
			cin >> choice;
		}
		


		switch (toupper(choice))
		{
		case 'A':
			cout << "Please enter a new name" << endl;

			cin.ignore();
			getline(cin, temp);
			temp = checkCase(temp);
			
			temporary = tempPtr->getItem().getVector();
			if (temporary.size() == 0)
			{
				push.setFirstName(temp);
				temporary.push_back(push);

			}
			else if (temporary.size() != 0)
			{
				temporary[affiliateNumber].setFirstName(temp);
			}


			item.setVector(temporary);
			dataPtr->deleteNode(tempPtr->getItem());
			dataPtr->addNode(dataPtr->rootPtr(), item);
			
			break;

		case 'B':
			cout << "Please enter a new phone number" << endl;

			cin.ignore();
			getline(cin, temp);

			temporary = tempPtr->getItem().getVector();
			temporary[affiliateNumber].setHomePhone(temp);
			while (atol(temp.c_str()) == 0 || temp.size() < 10 || temp.size() > 10)
			{
				cout << "Please enter a VALID home phone number, of ten digits, and press enter" << endl;
				getline(cin, temp);
			}

			item.setVector(temporary);
			placeholderPtr = new Node<Data>;
			placeholderPtr->setItem(item);
			dataPtr->deleteNode(tempPtr->getItem());
			dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());

			break;

		case 'C':
			cout << "Please enter a new Email" << endl;

			cin.ignore();
			getline(cin, temp);

			temporary = tempPtr->getItem().getVector();
			temporary[affiliateNumber].setEmail(temp);
			item.setVector(temporary);
			placeholderPtr = new Node<Data>;
			placeholderPtr->setItem(item);
			dataPtr->deleteNode(tempPtr->getItem());
			dataPtr->addNode(dataPtr->rootPtr(), placeholderPtr->getItem());

			break;

		}

		break;
	default:
		cout << endl << "\t\tPLEASE ENTER VALID INPUT" << endl;
		
		break;
	}
}


///////////////////////////////////////////////////////////////
// input: a pointer of BST<Data> type, 
// description: 
// this function goes to the tree, gatherers a 2 dimentional vector(whew) of contact information, 
// gets the users fields that he/she wished to have in the final product, gets the field they wish to sort on
// and then proceeds to go throught the 2d vector sorting and then finally writing to the file. A most 
// ardious and taxing task proposition. Please note that if there is an easier way to do this I am all ears. 
// output: unfortunately nothing 
///////////////////////////////////////////////////////////////
void Database::WriteToFile(BST<Data>* dataPtr)
{

	int num = 0;
	string stuff;
	string check;
	int option = -1;
	char choice = 0;
	vector <char> choices;
	vector <string> currentChoices;
	vector <string> printChoices;
	vector <vector <string> > item;// 2d vector for the tree
	fstream file;
	

	// if the tree is empty then we must either exit  or return to the main menu. I give the user this option
	// here we may gather the 2d vector if applicable
		if (dataPtr->rootPtr() != nullptr)
		{
			item = dataPtr->getVector(dataPtr->rootPtr());
		}
		else
		{
			cout << "There are no files in the system" << endl;
			cout << "Would you like to exit the prgram??" << endl;

			cout << "A: yes" << endl;
			cout << "B: No" << endl;
			cin >> choice;
			if (toupper(choice) == 'A')
			{
				cout << endl << endl << "\t\t GOODBYE" << endl;
				exit(0);
			}
			else 
			{
				return;
			}
		}

		//otherwise, I guess we could let the user write this tree to a file.
		//here we are gathering the fields that the user would like to write to the file
	cout << endl << endl << "What fields would you like to exclude from the written file?" << endl << endl;
	cout << "\tPlease enter selection similar to abcedfghijklmnox ......" << endl << endl;
	cout << "\tEnter 'X' after listing choices...." << endl << endl;

	cout << "*****NOTE*****->the order in which you enter these fields below is the arrangement for which they are put in the file " << endl<<endl;

	cout << "A: ID Number" << endl;
	cout << "B: First Name" << endl;
	cout << "C: Middle Name" << endl;
	cout << "D: Last Name" << endl;
	cout << "E: Company name" << endl;
	cout << "F: Home Phone" << endl;
	cout << "G: Office Phone" << endl;
	cout << "H: Email" << endl;
	cout << "I: Mobile Number" << endl;
	cout << "J: Address" << endl;
	cout << "K: City" << endl;
	cout << "L: State" << endl;
	cout << "M: Zip" << endl;
	cout << "N: Country" << endl;
	cout << "O: Affiliate information " << endl;
	//here i am making a vector of the fields that they may select
	currentChoices.push_back("ID Number");
	currentChoices.push_back("First Name");
	currentChoices.push_back("Middle Name");
	currentChoices.push_back("Last Name");
	currentChoices.push_back("Company name");
	currentChoices.push_back("Home Phone");
	currentChoices.push_back("Office Phone");
	currentChoices.push_back("Email");
	currentChoices.push_back("Mobile Number");
	currentChoices.push_back("Address");
	currentChoices.push_back("City");
	currentChoices.push_back("State");
	currentChoices.push_back("Zip");
	currentChoices.push_back("Country");
	currentChoices.push_back("Affiliate information ");
	
	
	

	//gathering the fields
	cout << "Enter choices to include, or X to stop" << endl;
	//while (toupper(cin.peek()) != 'X')
	do {
		cin >> choice;
		choice = toupper(choice);
		//choice = atoi(stuff.c_str());
		if (choice > 64 && choice < 80)
		{
//			enter as choices and subtract 40 off of the toupper static_cast ascii

			choices.push_back(choice);
		}
	} while (toupper(choice) != 'X');

	//displaying the fields that the user choose if any
	
	if (choices.size() > 0)
	{
		cout << "You have chosen to include: " << endl << endl;
	}
	for (int i = 0; i < choices.size(); i++)
	{
		num = (static_cast<int>(choices[i]) - 65);
		cout <<num<<":"<< currentChoices[num] << endl;
	}
	

	while (atoi(check.c_str()) == 0)// while the user has entered the correct information for us to proceed
	{
		cout << "Which field would you like to sort the Written file by??" << endl;
		cout << "1: ID Number" << endl;
		cout << "2: First Name" << endl;
		cout << "3: Middle Name" << endl;
		cout << "4: Last Name" << endl;
		cout << "5: Company name" << endl;
		cout << "6: Home Phone" << endl;
		cout << "7: Office Phone" << endl;
		cout << "8: Email" << endl;
		cout << "9: Mobile Number" << endl;
		cout << "10: Address" << endl;
		cout << "11: City" << endl;
		cout << "12: State" << endl;
		cout << "13: Zip" << endl;
		cout << "14: Country" << endl;
		cout << "15: Affiliate information " << endl;
		cin >> check;

	}
	
	option = atoi(check.c_str());
	finalSort(item, option - 1);// make one last sort of the information on the field chosen 
	//(we have an off by one mismatch between what the user entered and what is available)

	cout << "Would you like to sort the final file on another field?" << endl;
	cout << "A: yes" << endl;
	cout << "B: No" << endl;
	cin >> choice;

	if (toupper(choice) == 'A')
	{
		int option2 = 0;
		check = 'c';
		while (atoi(check.c_str()) == 0)// while the user has entered the correct information for us to proceed
		{
			cout << "Which field would you like to sort the Written file by??" << endl;
			cout << "1: ID Number" << endl;
			cout << "2: First Name" << endl;
			cout << "3: Middle Name" << endl;
			cout << "4: Last Name" << endl;
			cout << "5: Company name" << endl;
			cout << "6: Home Phone" << endl;
			cout << "7: Office Phone" << endl;
			cout << "8: Email" << endl;
			cout << "9: Mobile Number" << endl;
			cout << "10: Address" << endl;
			cout << "11: City" << endl;
			cout << "12: State" << endl;
			cout << "13: Zip" << endl;
			cout << "14: Country" << endl;
			cout << "15: Affiliate information " << endl;
			cin >> check;

		}

		option2 = atoi(check.c_str());
		SecondaryFinalSort(item, option - 1, option2 - 1);
	}



	//open the file 
	file.open("Report.txt", ios::out);
	for (int i = 0; i < item.size(); i++)// writting loop with index baed inside the 2d vector named items for each individual record
	{
		for (int j = 0; j < choices.size(); j++)// writing the specific items chosen froom the user
		{
			num = (static_cast<int>(choices[j]) - 65);// here we delineated, with a switch, the fields chosen by the user 

			switch (num)// switch of the item in question
			{
			case 0:
				file << currentChoices[num] << ": "<< item[i][num] << endl;
				break;
			case 1:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 2:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 3:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 4:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 5:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 6:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 7:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 8:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 9:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 10:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 11:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 12:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 13:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 14:
				file << currentChoices[num] << ": ";
				file << item[i][num] << endl;
				break;
			case 15:
				file << currentChoices[num] << ": \n";
				file << item[i][num] << endl;
				break;

			default:
				break;
			}
			
		}
		file << endl;

	}
	cout << "Your file has been saved to Report.txt" << endl;
	cout << "Press any key to continue" << endl;
	cin.get();
	cin.get();
	
	for (int i = 0; i < item.size(); i++)// clean out the vector
	{
		 item[i].pop_back();
	}

	exit(0);

	//switch or vector of ints for choices of exclusion
}



///////////////////////////////////////////////////////////////
// input: A 2D VECTOR OF STRINGS and a function number for the field to sort on
// description: 
// this functiomn goes through a 2d array and sorts it based on the specific field
// we do this for the write to a file function in this file 
//
// output: unfortunately nothing 
///////////////////////////////////////////////////////////////

void Database::finalSort(vector<vector<string> > & item, int functionNumber)
{
	bool swapage = true;
	vector<vector<string> > temp;
	temp.push_back(vector<string>());
	for (int i = 0; i < 15; i++)// this is a temporary 2d vector slot with 15 fields
	{
		temp[temp.size()-1].push_back("");

	}
	// bubblesort of the applicable field........notice that the functionnumber is what is determining the sorted field
	while (swapage == true)
		{
			swapage = false;
			for (int i = 0; i < item.size() - 1; i++)
			{
				if (item[i][functionNumber] > item[i+1][functionNumber])// use the function number to delineat the sort 
				{
					// swaps vectors
					temp[0] = item[i];
					item[i] = item[i + 1];
					item[i + 1] = temp[0];
					swapage = true;
				}
			}
		}
	temp.clear();
		//viewVector(item);
		

}

///////////////////////////////////////////////////////////////
// input: A 2D VECTOR OF STRINGS 
// description: 
// this function was used for the creation of this branch of the program and was mainly intended for use so that
// I could see what the heck was going on in the program. its main use is to display the entire 2d vector
// output: unfortunately nothing 
///////////////////////////////////////////////////////////////

	void Database::viewVector(vector<vector<string> > item)
	{
	
		
		for (int i = 0; i <item.size(); i++)
		{
			cout << "---------------------------------------------------------" << endl;
			for (int j = 0; j < item[i].size(); j++)
			{
				cout << item[i][j] << endl;
			}

			cout << "---------------------------------------------------------" << endl;
		}

	
	}

	///////////////////////////////////////////////////////////////
	// input: A 2D VECTOR OF STRINGS, and two intergers representing 
	// the prior field that has been sorted on and the current field to be sorted on. 
	// description: 
	// this function is designed to sort the file after an initial final sort has been done, based 
	// on the user's decision. 
	// 
	// output: unfortunately nothing 
	///////////////////////////////////////////////////////////////

	void Database::SecondaryFinalSort(vector<vector<string> >& item, int PriorField, int newField)
	{
	
		bool swapage = true;
		vector<vector<string> > temp;
		temp.push_back(vector<string>());
		for (int i = 0; i < 15; i++)// this is a temporary 2d vector slot with 15 fields
		{
			temp[temp.size() - 1].push_back("");

		}
		// bubblesort of the applicable field........notice that the functionnumber is what is determining the sorted field
		while (swapage == true)
		{
			swapage = false;
			for (int i = 0; i < item.size() - 1; i++)
			{
				// sort on the new field if their is a match for the prior field
				if (item[i][newField] > item[i + 1][newField]&& item[i][PriorField] == item[i + 1][PriorField]) 
				{
					// swaps vectors
					temp[0] = item[i];
					item[i] = item[i + 1];
					item[i + 1] = temp[0];
					swapage = true;
				}
			}
		}
		temp.clear();
	}