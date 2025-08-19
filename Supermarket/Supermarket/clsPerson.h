#pragma once

#include <iostream>
#include <string>

using namespace std;

class clsPerson
{
private:

	string _FirstName;
	string _LastName;
	string _Phone;
	string _Address;
public:

	clsPerson(string FirstName, string LastName, string Phone, string Address)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Phone = Phone;
		_Address = Address;
	}

	void SetFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}

	string GetFirstName() 
	{
		return _FirstName;
	}
	__declspec(property (get = GetFirstName, put = SetFirstName))string FirstName;



	void SetLastName(string LastName)
	{
		_LastName = LastName;
	}

	string GetLastName() 
	{
		return _LastName;
	}
	__declspec(property (get = GetLastName, put = SetLastName))string LastName;



	void SetPhone(string Phone)
	{
		_Phone = Phone;
	}

	string GetPhone()
	{
		return _Phone;
	}
	__declspec(property (get = GetPhone, put = SetPhone))string Phone;


	void SetAddress(string Address)
	{
		_Address = Address;
	}

	string GetAddress()
	{
		return _Address;
	}
	__declspec(property (get = GetAddress, put = SetAddress))string Address;

	string FullName() 
	{
		return FirstName + " " + LastName;
	}
};

