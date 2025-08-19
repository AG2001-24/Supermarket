// Supermarket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "clsSupplier.h"
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;


void ReadSupplier(clsSupplier &Supplier) 
{
	cout << "Please Enter First Name : ";
	Supplier.FirstName = clsInputValidate::ReadString();

	cout << "Please Enter Last Name : ";
	Supplier.LastName = clsInputValidate::ReadString();

	cout << "Please Enter Phone : ";
	Supplier.Phone = clsInputValidate::ReadString();

	cout << "Please Enter Address : ";
	Supplier.Address = clsInputValidate::ReadString();

}

void AddSupplier()
{
	cout << "Please Enter ID : ";
	string ID = clsInputValidate::ReadString();

	while (clsSupplier::IsExist(ID))
	{
		cout << "This ID already exists., Please enter another one : ";
		ID = clsInputValidate::ReadString();
	}

	clsSupplier Supplier = clsSupplier::GetAddSupplierObject(ID);

	ReadSupplier(Supplier);

	clsSupplier::enSave SaveResult = Supplier.SaveResult();

	switch (SaveResult) 
	{
	case clsSupplier::enSave::svEmptyObject:
		cout << "\nThe supplier was not added because the data is empty.\n";
		break;

	case clsSupplier::enSave::svAlreadyExists:
		cout << "\nThe supplier was not added because it already exists.\n";
		break;

	case clsSupplier::enSave::svSucceeded:
		cout << "\nThe supplier has been added successfully.\n";
		Supplier.Print();
		break;
	}
}

void UpdateSupplier()
{
	cout << "Please Enter ID : ";
	string ID = clsInputValidate::ReadString();

	while (!clsSupplier::IsExist(ID))
	{
		cout << "This ID is not found., Please enter another one : ";
		ID = clsInputValidate::ReadString();
	}

	clsSupplier Supplier = clsSupplier::Find(ID);

	Supplier.Print();

	ReadSupplier(Supplier);

	char answer = 'n';
	
	cout << "\nAre your sure you want to update date this supplier? Y/N : ";
	cin >> answer;

	if (answer == 'Y' || answer == 'y')
	{
		clsSupplier::enSave SaveResult = Supplier.SaveResult();

		switch (SaveResult)
		{
		case clsSupplier::enSave::svEmptyObject:
			cout << "\nThe supplier was not updated because the data is empty.\n";
			break;

		case clsSupplier::enSave::svSucceeded:
			cout << "\nThe supplier has been updated successfully.\n";
			Supplier.Print();
			break;
		}
	}

}

void DeleteSupplier() 
{
	cout << "Please Enter ID : ";
	string ID = clsInputValidate::ReadString();

	while (!clsSupplier::IsExist(ID))
	{
		cout << "This ID is not found., Please enter another one : ";
		ID = clsInputValidate::ReadString();
	}

	clsSupplier Supplier = clsSupplier::Find(ID);

	Supplier.Print();

	char answer = 'n';

	cout << "\nAre you sure you want to delete this supplier? Y/N : ";
	cin >> answer;

	if (toupper(answer) == 'Y')
	{
		bool IsDelete = Supplier.Delete();

		if (IsDelete)
		{
			cout << "\nThe supplier has been deleted successfully.\n";

		}
		else
		{
			cout << "\nThe supplier was not deleted because the data is empty.\n";
		}

		Supplier.Print();
	}
}

void PrintRecord(clsSupplier Supplier)
{
	cout << "| " << left << setw(40) << Supplier.FullName();
	cout << "| " << left << setw(10) << Supplier.ID();
	cout << "| " << left << setw(13) <<  Supplier.Phone;
	cout << "| " << left << setw(20) << Supplier.Address;
	cout << endl;
}

void ShowSuppliersList()
{
	vector <clsSupplier> SuppliersList = clsSupplier::GetSuppliersList();

	cout << "\n"<<left << setw(30) << "" << "Suppliers List (" << SuppliersList.size() << ") Supplier(s).";
	cout << "\n______________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(10) << "ID";
	cout << "| " << left << setw(13) << "Phone";
	cout << "| " << left << setw(20) << "Address";
	cout << "\n______________________________________________________________________________________________\n";

	for (clsSupplier &Supplier : SuppliersList)
	{
		PrintRecord(Supplier);
	}
	cout << "______________________________________________________________________________________________\n";
}

void FindSupplier() 
{
	cout << "Please Enter ID : ";
	string ID = clsInputValidate::ReadString();

	while (!clsSupplier::IsExist(ID))
	{
		cout << "This ID is not found., Please enter another one : ";
		ID = clsInputValidate::ReadString();
	}

	clsSupplier Supplier = clsSupplier::Find(ID);

	Supplier.Print();
}


int main()
{

	ShowSuppliersList();
    return 0;
}

