// John Williams 
// 105201054
// HW9
// 11-02-16
#ifndef AFFILIATE_H
#define AFFILIATE_H
#include <string>
using namespace std;

class Affiliate
{

private:
	string firstName;// variable for first Name
	string homePhone;// variable for Home telephone number 
	string email;// variable for email address 
public:
	string getFirstName() const { return firstName; }
	string getHomePhone() const { return homePhone; }
	string getEmail() const { return email; }
	void setFirstName(string item) { firstName = item; }
	void setHomePhone(string item) { homePhone = item; }
	void setEmail(string item) { email = item; }
};

#endif