// Supermarket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "clsSupplier.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsProduct.h"
#include <string>
#include "clsCustomer.h"
using namespace std;


// --------- Suppliers Management ------------//
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
	cout << "| " << left << setw(13) << Supplier.Phone;
	cout << "| " << left << setw(20) << Supplier.Address;
	cout << endl;
}

void ShowSuppliersList()
{
	vector <clsSupplier> SuppliersList = clsSupplier::GetSuppliersList();

	cout << "\n" << left << setw(30) << "" << "Suppliers List (" << SuppliersList.size() << ") Supplier(s).";
	cout << "\n______________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(10) << "ID";
	cout << "| " << left << setw(13) << "Phone";
	cout << "| " << left << setw(20) << "Address";
	cout << "\n______________________________________________________________________________________________\n\n";


	for (clsSupplier &Supplier : SuppliersList)
	{
		PrintRecord(Supplier);
		cout << "______________________________________________________________________________________________\n\n";
	}

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
// --------- End Suppliers Management -------------//

// --------- Customers Management ------------//
void ReadCustomer(clsCustomer &Customer) 
{
	cout << "Please Enter First Name : ";
	Customer.FirstName = clsInputValidate::ReadString();

	cout << "Please Enter Last Name : ";
	Customer.LastName = clsInputValidate::ReadString();

	cout << "Please Enter Phone : ";
	Customer.Phone = clsInputValidate::ReadString();

	cout << "Please Enter Address : ";
	Customer.Address = clsInputValidate::ReadString();

}

void AddCustomer()
{
	cout << "Please Enter ID : ";
	string ID = clsInputValidate::ReadString();

	while (clsCustomer::IsExist(ID))
	{
		cout << "This ID already exists., Please enter another one : ";
		ID = clsInputValidate::ReadString();
	}

	clsCustomer Customer = clsCustomer::GetAddCustomerObject(ID);

	ReadCustomer(Customer);

	clsCustomer::enSave SaveResult = Customer.SaveResult();

	switch (SaveResult) 
	{
	case clsCustomer::enSave::svEmptyObject:
		cout << "\nThe Customer was not added because the data is empty.\n";
		break;

	case clsCustomer::enSave::svAlreadyExists:
		cout << "\nThe Customer was not added because it already exists.\n";
		break;

	case clsCustomer::enSave::svSucceeded:
		cout << "\nThe Customer has been added successfully.\n";
		Customer.Print();
		break;
	}
}

void UpdateCustomer()
{
	cout << "Please Enter ID : ";
	string ID = clsInputValidate::ReadString();

	while (!clsCustomer::IsExist(ID))
	{
		cout << "This ID is not found., Please enter another one : ";
		ID = clsInputValidate::ReadString();
	}

	clsCustomer Customer = clsCustomer::Find(ID);

	Customer.Print();

	ReadCustomer(Customer);

	char answer = 'n';
	
	cout << "\nAre your sure you want to update date this Customer? Y/N : ";
	cin >> answer;

	if (answer == 'Y' || answer == 'y')
	{
		clsCustomer::enSave SaveResult = Customer.SaveResult();

		switch (SaveResult)
		{
		case clsCustomer::enSave::svEmptyObject:
			cout << "\nThe Customer was not updated because the data is empty.\n";
			break;

		case clsCustomer::enSave::svSucceeded:
			cout << "\nThe Customer has been updated successfully.\n";
			Customer.Print();
			break;
		}
	}

}

void DeleteCustomer() 
{
	cout << "Please Enter ID : ";
	string ID = clsInputValidate::ReadString();

	while (!clsCustomer::IsExist(ID))
	{
		cout << "This ID is not found., Please enter another one : ";
		ID = clsInputValidate::ReadString();
	}

	clsCustomer Customer = clsCustomer::Find(ID);

	Customer.Print();

	char answer = 'n';

	cout << "\nAre you sure you want to delete this Customer? Y/N : ";
	cin >> answer;

	if (toupper(answer) == 'Y')
	{
		bool IsDelete = Customer.Delete();

		if (IsDelete)
		{
			cout << "\nThe Customer has been deleted successfully.\n";

		}
		else
		{
			cout << "\nThe Customer was not deleted because the data is empty.\n";
		}

		Customer.Print();
	}
}

void PrintRecord(clsCustomer Customer)
{
	cout << "| " << left << setw(40) << Customer.FullName();
	cout << "| " << left << setw(10) << Customer.ID();
	cout << "| " << left << setw(13) <<  Customer.Phone;
	cout << "| " << left << setw(20) << Customer.Address;
	cout << endl;
}

void ShowCustomersList()
{
	vector <clsCustomer> CustomersList = clsCustomer::GetCustomersList();

	cout << "\n"<<left << setw(30) << "" << "Customers List (" << CustomersList.size() << ") Customer(s).";
	cout << "\n______________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(10) << "ID";
	cout << "| " << left << setw(13) << "Phone";
	cout << "| " << left << setw(20) << "Address";
	cout << "\n______________________________________________________________________________________________\n\n";


	for (clsCustomer &Customer : CustomersList)
	{
		PrintRecord(Customer);	
		cout << "______________________________________________________________________________________________\n\n";
	}

}

void FindCustomer() 
{
	cout << "Please Enter ID : ";
	string ID = clsInputValidate::ReadString();

	while (!clsCustomer::IsExist(ID))
	{
		cout << "This ID is not found., Please enter another one : ";
		ID = clsInputValidate::ReadString();
	}

	clsCustomer Customer = clsCustomer::Find(ID);

	Customer.Print();
}
// --------- End Customers Management -------------//


// --------- Product Management -----------//
void ReadProduct(clsProduct &Product)
{
	cout << "Please Enter Product Name : ";
	Product.Name = clsInputValidate::ReadString();


	char answer;

	cout << "Do you want to add the product to the default category? Y/N : ";
	cin >> answer;

	if (toupper(answer) == 'Y')
	{
		Product.Category = "Default Category";
	}
	else
	{
		cout << "Please Enter Category : ";
		Product.Category = clsInputValidate::ReadString();
	}


	cout << "Is the supplier the default supplier? Y/N : ";
	cin >> answer;

	if (toupper(answer) == 'Y')
	{
		Product.SupplierName = "Default Supplier";
	}
	else
	{
		cout << "Please Enter ID Supplier : ";
		string ID = clsInputValidate::ReadString();

		while (!clsSupplier::IsExist(ID))
		{
			cout << "This ID is not found , Please enter another one : ";
			ID = clsInputValidate::ReadString();
		}

		clsSupplier Supplier = clsSupplier::Find(ID);

		Product.SupplierName = Supplier.FullName();


	}


	cout << "Please Enter Purchase Price : ";
	Product.PurchasePrice = clsInputValidate::ReadDblNumber();


	cout << "Please Enter Selling Price : ";
	Product.SellingPrice = clsInputValidate::ReadDblNumber();


	cout << "Please Enter Quantity : ";
	Product.Quantity = clsInputValidate::ReadIntPositiveNumber();


	cout << "Please Enter Quantity Warining : ";
	Product.QuantityWarining = clsInputValidate::ReadIntPositiveNumber();


}

void PrintRecordProduct(clsProduct &Prodcut)
{
	cout << "| " << left << setw(25) << Prodcut.Name;
	cout << "| " << left << setw(6) << Prodcut.Code();
	cout << "| " << left << setw(8) << Prodcut.PurchasePrice;
	cout << "| " << left << setw(8) << Prodcut.SellingPrice;
	cout << "| " << left << setw(10) << Prodcut.Quantity;
	cout << "| " << left << setw(12) << Prodcut.QuantityWarining;
	cout << "| " << left << setw(25) << Prodcut.Category;
	cout << "| " << left << setw(25) << Prodcut.SupplierName;
	cout << endl;
}

void ShowProductList()
{
	vector <clsProduct> vProductList = clsProduct::GetProductList();

	cout << "\n" << left << setw(50) << "" << "Product List (" << vProductList.size() << ") Product(s).\n";
	cout << "\n________________________________________________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(25) << "Name";
	cout << "| " << left << setw(6) << "Code";
	cout << "| " << left << setw(8) << "P Price";
	cout << "| " << left << setw(8) << "S Price";
	cout << "| " << left << setw(10) << "Quantity";
	cout << "| " << left << setw(12) << "QtyWarning";
	cout << "| " << left << setw(25) << "Category";
	cout << "| " << left << setw(25) << "Supplier";
	cout << "\n________________________________________________________________________________________________________________________________________\n\n";

	if (vProductList.size() == 0)
	{
		cout << "\nThe product list is empty.There are no products available at this time.\n";
	}
	else
	{
		for (clsProduct &Product : vProductList)
		{
			PrintRecordProduct(Product);

			cout << "________________________________________________________________________________________________________________________________________\n\n";
		}
	}

}

void AddProduct()
{
	cout << "Please enter code : ";
	string Code = clsInputValidate::ReadString();

	while (clsProduct::IsExist(Code))
	{
		cout << "This Product exists, Please enter another one : ";
		Code = clsInputValidate::ReadString();
	}

	clsProduct Product = clsProduct::GetAddObjectProduct(Code);

	ReadProduct(Product);

	clsProduct::enSave SaveResult = Product.SaveResult();

	switch (SaveResult)
	{
	case clsProduct::enSave::svEmptyObject:
		cout << "\nThe product was not added because it is empty.\n";
		break;
	case clsProduct::enSave::svAalreadyExists:
		cout << "\nThe product has not been added because it already exists.\n";
		break;
	case clsProduct::enSave::svSucceeded:
		cout << "\nThe product has been added successfully.\n";
		Product.Print();
		break;
	}
}

void UpdateProduct()
{
	cout << "Please enter code : ";
	string Code = clsInputValidate::ReadString();

	while (!clsProduct::IsExist(Code))
	{
		cout << "This Product is not found, Please enter another one : ";
		Code = clsInputValidate::ReadString();
	}

	clsProduct Product = clsProduct::Find(Code);

	Product.Print();

	ReadProduct(Product);

	cout << "Are you sure you want to update this product? Y/N : ";
	char answer;
	cin >> answer;

	if (toupper(answer) == 'Y')
	{
		clsProduct::enSave SaveResult = Product.SaveResult();

		switch (SaveResult)
		{
		case clsProduct::enSave::svEmptyObject:
			cout << "\nThe product was not updated because it is empty.\n";
			break;
		case clsProduct::enSave::svSucceeded:
			cout << "\nThe product has been updated successfully.\n";
			Product.Print();
			break;
		}
	}

}

void DeleteProduct()
{
	cout << "Please enter code : ";
	string Code = clsInputValidate::ReadString();

	while (!clsProduct::IsExist(Code))
	{
		cout << "This Product is not found, Please enter another one : ";
		Code = clsInputValidate::ReadString();
	}

	clsProduct Product = clsProduct::Find(Code);

	Product.Print();

	char answer = 'n';

	cout << "\nAre you sure you want to delete this product? Y/N : ";
	cin >> answer;

	if (answer == 'Y' || answer == 'y')
	{
		bool isDeleted = Product.Delete();


		if (isDeleted)
		{
			cout << "\nThe product has been successfully deleted.\n";
		}
		else
		{
			cout << "\nThe product was not deleted because it is empty.\n";
		}

		Product.Print();
	}
}

void FindProduct()
{
	cout << "Please enter code : ";
	string Code = clsInputValidate::ReadString();

	while (!clsProduct::IsExist(Code))
	{
		cout << "This Product is not found, Please enter another one : ";
		Code = clsInputValidate::ReadString();
	}

	clsProduct Product = clsProduct::Find(Code);

	Product.Print();
}

// --------- End Product Management ---------//





int main()
{

	ShowCustomersList();

    return 0;
}

