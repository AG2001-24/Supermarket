#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include <fstream>
#include "clsString.h"
#include <vector>
using namespace std;

string FileNameCustomers = "Customers\\Customers.txt";

class clsCustomer : public clsPerson
{


	enum enMode { EmptyMode = 1, UpdateMode = 2, AddNewMode = 3 };
	enMode _Mode;

	bool _MarkForDelete = false;

	string _ID;

	static clsCustomer _GetEmptyCustomerObject()
	{
		return clsCustomer(enMode::EmptyMode, "", "", "", "", "");
	}

	static clsCustomer _ConvertRecordToObject(string Record, string Saparator = "#//#")
	{
		vector <string> SubRecords = clsString::Split(Record, Saparator);

		return clsCustomer(enMode::UpdateMode, SubRecords[0], SubRecords[1], SubRecords[2], SubRecords[3], SubRecords[4]);
	}

	static string _ConvertObjectToRecord(clsCustomer Object, string Saparator = "#//#")
	{
		string Record = "";
		Record += Object.ID() + Saparator;
		Record += Object.FirstName + Saparator;
		Record += Object.LastName + Saparator;
		Record += Object.Phone + Saparator;
		Record += Object.Address;

		return Record;
	}

	static vector<clsCustomer> _GetCustomersList()
	{
		fstream MyFile;
		vector <clsCustomer> vCustomersList;

		MyFile.open(FileNameCustomers, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vCustomersList.push_back(_ConvertRecordToObject(Line));
			}

			MyFile.close();
		}

		return vCustomersList;
	}

	static void _SaveCustomersToFile(vector <clsCustomer> vCustomersList)
	{
		fstream MyFile;

		MyFile.open(FileNameCustomers, ios::out);

		if (MyFile.is_open())
		{
			for (clsCustomer &Customer : vCustomersList)
			{
				if (!Customer._MarkForDelete)
					MyFile << _ConvertObjectToRecord(Customer) << endl;
			}

			MyFile.close();
		}


	}

	void _AddCustomerToFile(clsCustomer Customer)
	{
		fstream MyFile;

		MyFile.open(FileNameCustomers, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << _ConvertObjectToRecord(Customer) << endl;
			MyFile.close();
		}
	}

	void _AddCustomer()
	{
		_AddCustomerToFile(*this);
	}

	void _UpdateCustomer()
	{

		vector <clsCustomer> vCustomerList = _GetCustomersList();

		for (clsCustomer &Customer : vCustomerList)
		{
			if (ID() == Customer.ID())
			{
				Customer = *this;
				break;
			}
		}

		_SaveCustomersToFile(vCustomerList);
	}




public:

	clsCustomer(enMode Mode, string ID, string FirstName, string LastName, string Phone, string Address) : clsPerson(FirstName, LastName, Phone, Address)
	{
		_Mode = Mode;
		_ID = ID;
	}

	string ID()
	{
		return _ID;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	enum enSave { svEmptyObject = 1, svSucceeded = 2, svAlreadyExists = 3 };

	enSave SaveResult()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:

			return enSave::svEmptyObject;

		case enMode::UpdateMode:

			_UpdateCustomer();
			return enSave::svSucceeded;

		case enMode::AddNewMode:

			bool IsCustomerExist = clsCustomer::IsExist(ID());

			if (IsCustomerExist)
			{
				_Mode = enMode::UpdateMode;
				return enSave::svAlreadyExists;
			}
			else
			{
				_AddCustomer();
				_Mode = enMode::UpdateMode;

				return enSave::svSucceeded;
			}

		}
	}

	bool Delete()
	{
		vector <clsCustomer> vCustomersList = _GetCustomersList();

		for (clsCustomer &Customer : vCustomersList)
		{
			if (ID() == Customer.ID())
			{
				Customer._MarkForDelete = true;
				_SaveCustomersToFile(vCustomersList);
				*this = _GetEmptyCustomerObject();
				return true;

			}
		}

		return false;
	}

	static clsCustomer Find(string ID)
	{
		fstream MyFile;

		MyFile.open(FileNameCustomers, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCustomer Customer = _ConvertRecordToObject(Line);

				if (ID == Customer.ID())
				{
					MyFile.close();
					return Customer;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCustomerObject();
	}

	void Print()
	{

		cout << "\n____________________________\n\n";
		cout << "      Customer Card         \n";
		cout << "____________________________\n";
		cout << "\nFirst Name : " << FirstName;
		cout << "\nLast Name  : " << LastName;
		cout << "\nFull Name  : " << FullName();
		cout << "\nID         : " << ID();
		cout << "\nPhone      : " << Phone;
		cout << "\nAddress    : " << Address;
		cout << "\n____________________________\n\n";

	}

	static bool IsExist(string ID)
	{
		clsCustomer Customer = clsCustomer::Find(ID);

		return !Customer.IsEmpty();
	}

	static clsCustomer GetAddCustomerObject(string ID)
	{
		return clsCustomer(enMode::AddNewMode, ID, "", "", "", "");
	}

	static vector<clsCustomer> GetCustomersList()
	{
		return _GetCustomersList();
	}


};

