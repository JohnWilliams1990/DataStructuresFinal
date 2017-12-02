// John Williams 
// 105201054
// HW9
// 11-02-16

#include "Data.h"
#include"affiliate.h"
#include <string>
#include <vector>
#include "node.h"

	// GGetters for the Data class 

	///////////////////////////////////////////////////////////////
	// input: nothing
	// description: 
	// these functions are the getters for the Data class
	// output: the item specified of type string
	///////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	string Data::getEmployeeNumber() { return employeeNumber; }
	string Data::getFirstName() { return firstName; }
	string Data::getMiddleName()  { return middleName; }
	string Data::getLastName() { return lastName; }
	string Data::getCompanyName() { return companyName; }
	string Data::getHomePhone() { return homePhone; }
	string Data::getCellPhone() { return cellPhone; }
	string Data::getWorkPhone() { return workPhone; } 
	string Data::getEmail() { return email; }
	string Data::getHomeAddress() { return homeAddress; }
	string Data::getCity() { return city; }
	string Data::getState(){ return state; }
	string Data::getZip() { return zip; }
	string Data::getCountry() { return country; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// input: nothing
// description: 
// this function is used to determine the number of affiliates in the specific contact
// output: the number of affiliats in the vector of affiliates for the specified contact
///////////////////////////////////////////////////////////////

	int Data::getNumberOfAffiliates() { return this->affiliates.size(); }

	//// this function returns an item at a position in the affiliate vector
	//// which is dependent on the 'index' variable and it returns a piece of data from 
	//// the Data class structure inside of the vector depending on the 'type' variable
	//// this essentially is a 2d array with one dimention held constant at three. 
	vector<Affiliate> Data::getVector() { return affiliates; }


	///////////////////////////////////////////////////////////////
	// input: a vector of Affiliate type
	// description: 
	// this function is used to set the affiliates in the specific 
	// contact to the vector that is passed into the function
	// output: unfortunately nothing
	///////////////////////////////////////////////////////////////
	void Data::setVector(vector<Affiliate> item) { affiliates = item; }


	///////////////////////////////////////////////////////////////
	// input: nothing
	// description: 
	// this function is used to get the affiliates in the specific 
	// manner for outputting to the console or to the screen
	// output: a string containing the applicable items in the affiliates vector
	///////////////////////////////////////////////////////////////
	string Data::getAffiliatesString()
	{
		// concatonate the string wit the applicable format => return the string
		string temp; 
		for (int i = 0; i < affiliates.size(); i++)
		{
			temp = temp + "\n";
			temp = temp + affiliates[i].getFirstName();
			temp = temp + ", ";

			temp = temp + affiliates[i].getHomePhone();
			temp = temp + ", ";

			temp = temp + affiliates[i].getEmail();
			//if (i != affiliates.size() -1)
			temp = temp + ";";

		}
		temp = temp + "\n";
		return temp;
	}

	///////////////////////////////////////////////////////////////
	// input: a int for the index in the affiliate vector, and an int 
	// to determine what field in the affilaite we need
	// description: 
	// this function is used to uotput a specific part of the affiliated based on what we would put into the parameter list 
	// output: unfortunately nothing
	///////////////////////////////////////////////////////////////
	string Data::getAffiliates(int index, int type) 
	{
		string temp;
		// based ont he user input return the applicable item at the applicable index
		if (type == 0)
		{
			return affiliates[index].getFirstName();

		}
		if (type == 1)
		{
			return affiliates[index].getHomePhone();
		}
		if (type == 2)
		{
			return affiliates[index].getEmail();
		}
	}

	///////////////////////////////////////////////////////////////
	// input: 3 strings to set the items in each field of the affiliate vector. 
	// description: 
	// this function is used to set the affiliates fields as we add an affiliate from a file ect.
	// output: unfortunately nothing
	///////////////////////////////////////////////////////////////
	void Data::setAffiliates(Affiliate item)
	{
		/*Affiliate item;
		item.setFirstName(Fname);
		item.setHomePhone(hPhone);
		item.setEmail(nEmail);*/

		affiliates.push_back(item);
	}
	void Data::clearAffiliates() { affiliates.clear(); }

	// SETTERS FOR THE SPECIFIC CLASS


	///////////////////////////////////////////////////////////////
	// input: a strings to set the items in each field as applicable 
	// description: 
	// these functions are used to set the applicable fields as we add an item from a file ect.
	// output: unfortunately nothing
	///////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Data::setEmployeeNumber(string item) { employeeNumber = item; }
	void Data::setFirstName(string item) { firstName = item; }
	void Data::setMiddleName(string item) { middleName = item; }
	void Data::setLastName(string item) { lastName = item; }
	void Data::setCompanyName(string item) { companyName = item; }
	void Data::setHomePhone(string item) { homePhone = item; }
	void Data::setCellPhone(string item) { cellPhone = item; }
	void Data::setWorkPhone(string item) { workPhone = item; }
	void Data::setEmail(string item) { email = item; }
	void Data::setHomeAddress(string item) { homeAddress = item; }
	void Data::setCity(string item) { city = item; }
	void Data::setState(string item) { state = item; }
	void Data::setZip(string item) { zip = item; }
	void Data::setCountry(string item) { country = item; }
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

