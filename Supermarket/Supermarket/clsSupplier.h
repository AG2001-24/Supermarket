#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include <fstream>
#include "clsString.h"
#include <vector>
using namespace std;

string FileNameSuppliers = "Suppliers\\Suppliers.txt";

class clsSupplier : public clsPerson
{

	
	enum enMode { EmptyMode = 1, UpdateMode = 2, AddNewMode = 3 };
	 enMode _Mode;

	bool _MarkForDelete = false;

	string _ID;

	static clsSupplier _GetEmptySupplierObject()
	{
		return clsSupplier(enMode::EmptyMode, "", "", "", "", "");
	}

	static clsSupplier _ConvertRecordToObject(string Record, string Saparator = "#//#")
	{
		vector <string> SubRecords = clsString::Split(Record, Saparator);

		return clsSupplier(enMode::UpdateMode, SubRecords[0], SubRecords[1], SubRecords[2], SubRecords[3], SubRecords[4]);
	}

	static string _ConvertObjectToRecord(clsSupplier Object, string Saparator = "#//#")
	{
		string Record = "";
		Record += Object.ID() + Saparator;
		Record += Object.FirstName + Saparator;
		Record += Object.LastName + Saparator;
		Record += Object.Phone + Saparator;
		Record += Object.Address;

		return Record;
	}

	static vector<clsSupplier> _GetSuppliersList()
	{
		fstream MyFile;
		vector <clsSupplier> vSuppliersList;

		MyFile.open(FileNameSuppliers, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vSuppliersList.push_back(_ConvertRecordToObject(Line));
			}

			MyFile.close();
		}

		return vSuppliersList;
	}

	static void _SaveSuppliersToFile(vector <clsSupplier> vSuppliersList)
	{
		fstream MyFile;

		MyFile.open(FileNameSuppliers, ios::out);

		if (MyFile.is_open())
		{
			for (clsSupplier &Supplier : vSuppliersList)
			{
				if (!Supplier._MarkForDelete)
					MyFile << _ConvertObjectToRecord(Supplier) << endl;
			}

			MyFile.close();
		}


	}

	void _AddSupplierToFile(clsSupplier Supplier)
	{
		fstream MyFile;

		MyFile.open(FileNameSuppliers, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << _ConvertObjectToRecord(Supplier) << endl;
			MyFile.close();
		}
	}

	void _AddSupplier()
	{
		_AddSupplierToFile(*this);
	}

	void _UpdateSupplier()
	{

		vector <clsSupplier> vSupplierList = _GetSuppliersList();

		for (clsSupplier &Supplier : vSupplierList)
		{
			if (ID() == Supplier.ID())
			{
				Supplier = *this;
				break;
			}
		}

		_SaveSuppliersToFile(vSupplierList);
	}




public:

	clsSupplier(enMode Mode, string ID, string FirstName, string LastName, string Phone, string Address) : clsPerson(FirstName, LastName, Phone, Address)
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

	enum enSave {svEmptyObject = 1, svSucceeded = 2, svAlreadyExists = 3};

	enSave SaveResult() 
	{
		switch (_Mode) 
		{
		case enMode::EmptyMode:

			return enSave::svEmptyObject;

		case enMode::UpdateMode:

			_UpdateSupplier();
			return enSave::svSucceeded;

		case enMode::AddNewMode:

			bool IsSupplierExist = clsSupplier::IsExist(ID());

			if (IsSupplierExist)
			{
				_Mode = enMode::UpdateMode;
				return enSave::svAlreadyExists;
			}
			else
			{
				_AddSupplier();
				_Mode = enMode::UpdateMode;

				return enSave::svSucceeded;
			}

		}
	}

	bool Delete() 
	{
		vector <clsSupplier> vSuppliersList = _GetSuppliersList();

		for (clsSupplier &Supplier : vSuppliersList)
		{
			if (ID() == Supplier.ID())
			{
				Supplier._MarkForDelete = true;
				_SaveSuppliersToFile(vSuppliersList);
				*this = _GetEmptySupplierObject();
				return true;
				
			}
		}

		return false;
	}

	static clsSupplier Find(string ID ) 
	{
		fstream MyFile;

		MyFile.open(FileNameSuppliers,ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsSupplier Supplier = _ConvertRecordToObject(Line);

				if (ID == Supplier.ID())
				{
					MyFile.close();
					return Supplier;
				}
			}

			MyFile.close();
		}

		return _GetEmptySupplierObject();
	}

	void Print() 
	{
		
		cout << "\n____________________________\n\n";
		cout << "      Supplier Card         \n";
		cout << "____________________________\n";
		cout << "\nFirst Name : " << FirstName;
		cout << "\nLast Name  : " << LastName;
		cout << "\n Full Name : " << FullName();
		cout << "\nID         : " << ID();
		cout << "\nPhone      : " << Phone;
		cout << "\nAddress    : " << Address;
		cout << "\n____________________________\n\n";

	}

	static bool IsExist(string ID) 
	{
		clsSupplier Supplier = clsSupplier::Find(ID);

		return !Supplier.IsEmpty();
	}

	static clsSupplier GetAddSupplierObject(string ID) 
	{
		return clsSupplier(enMode::AddNewMode, ID, "", "", "", "");
	}

	static vector<clsSupplier> GetSuppliersList() 
	{
		return _GetSuppliersList();
	}

};

