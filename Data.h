// John Williams 
// 105201054
// HW9
// 11-02-16
#ifndef DATA_H
#define DATA_H
#include"affiliate.h"
#include <string>
#include <vector>
#include "node.h"
using namespace std;

class Data
{
private:
	string employeeNumber;// variable for the employee Id Number
	string firstName;// variable for first Name
	string middleName;// variable for middle Name
	string lastName;// variable for Last name 
	string companyName;// variable for Company name 
	string homePhone;// variable for Home telephone number 
	string cellPhone;// variable for mobile telephone number 
	string workPhone;// variable for work telephone number 
	string email;// variable for email address 
	string homeAddress;// variable for Physical address-> assumed to bbe home adress but I doubt the user will notice a difference
	string city;// variable for City 
	string state;// variable for State 
	string zip;// variable for Zip
	string country;// variable for Country 
	vector<Affiliate> affiliates;// Vector of Data Type reusing three of the Data fields -> I MAY SWAP THIS OUT WITH A DIFFERENT CLASS AFFILIATE 
public:
	// GGetters for the Data class 
	string getEmployeeNumber();
	string getFirstName();
	string getMiddleName();
	string getLastName();
	string getCompanyName();
	string getHomePhone();
	string getCellPhone();
	string getWorkPhone();
	string getEmail();
	string getHomeAddress();
	string getCity();
	string getState();
	string getZip();
	string getCountry();
	void clearAffiliates();
	int getNumberOfAffiliates();

	void setVector(vector<Affiliate> item);
	vector<Affiliate> getVector();
	string getAffiliatesString();
	// this function returns an item at a position in the affiliate vector
	// which is dependent on the 'index' variable and it returns a piece of data from 
	// the Data class structure inside of the vector depending on the 'type' variable
	// this essentially is a 2d array with one dimention held constant at three. 
	string getAffiliates(int index, int type); // const

	//void setAffiliates(string Fname, string hPhone, string nEmail);
	void setAffiliates(Affiliate item);
	// SETTERS FOR THE SPECIFIC CLASS
	void setEmployeeNumber(string item);
	void setFirstName(string item);
	void setMiddleName(string item);
	void setLastName(string item);
	void setCompanyName(string item);
	void setHomePhone(string item);
	void setCellPhone(string item);
	void setWorkPhone(string item);
	void setEmail(string item);
	void setHomeAddress(string item);
	void setCity(string item);
	void setState(string item);
	void setZip(string item);
	void setCountry(string item);

	~Data() { affiliates.clear(); }
	// BOOLEAN OPERATORS THAT ARE OVERLOADED TO allow for a comparison in the tree. 
	bool operator > (const Node<Data>* Ptr) const
	{

		return (this->employeeNumber > (Ptr->getItem()).getEmployeeNumber());

	}
	bool operator < (const Node<Data>* Ptr) const
	{

		return (this->employeeNumber < (Ptr->getItem()).getEmployeeNumber());

	}

	friend ostream& operator<< (ostream& out, Data item)
	{


		out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		//cout << node->getItem();
		out << "Employee ID: " << item.getEmployeeNumber() << endl;
		out << "Name: " << item.getFirstName() << " ";
		out << item.getMiddleName() << " ";
		out << item.getLastName() << endl;
		out << "Company Name: " << item.getCompanyName() << endl;
		out << "Home Phone: " << item.getHomePhone() << endl;
		out << "Office Phone: " << item.getWorkPhone() << endl;
		out << "Email: " << item.getEmail() << endl;
		out << "Mobile Number: " << item.getCellPhone() << endl;
		out << "Address: " << item.getHomeAddress() << endl;
		out << "City: " << item.getCity() << endl;
		out << "State: " << item.getState() << endl;
		out << "Zip: " << item.getZip() << endl;
		out << "Country: " << item.getCountry() << endl;
		out << "Affiliates: " << endl << endl;
		for (int i = 0; i < item.getNumberOfAffiliates(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (j == 0)
				{
					out << "\tName: ";
				}
				if (j == 1)
				{
					out << "\tPhone: ";
				}
				if (j == 2)
				{
					out << "\tEmail: ";
				}
				out << item.getAffiliates(i, j) << endl;
			}
			out << endl;
		}
		out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		return out;
	}


	friend ostream& operator<< (ostream& out, Node<Data>* object)
		{
			
				out << object->getItem().getEmployeeNumber() << endl;
				out << object->getItem().getFirstName() << endl;
				out << object->getItem().getMiddleName() << endl;
				out << object->getItem().getLastName() << endl;
				out << object->getItem().getCompanyName() << endl;
				out << object->getItem().getHomePhone() << endl;
				out << object->getItem().getWorkPhone() << endl;
				out << object->getItem().getEmail() << endl;
				out << object->getItem().getCellPhone() << endl;
				out << object->getItem().getHomeAddress() << endl;
				out << object->getItem().getCity() << endl;
				out << object->getItem().getState() << endl;
				out << object->getItem().getZip() << endl;
				out << object->getItem().getCountry() << endl;
				for (int j = 0; j < object->getItem().getNumberOfAffiliates(); j++)
				{
					for (int k = 0; k < 3; k++)
					{
						out << object->getItem().getAffiliates(j, k);
						if (k < 2)
						{
							out << ",";
						}
						else
							out << ";";
					}
					 out<<endl;
				}
				out << "|"<< endl;

			return out;
		}

};


#endif