#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <fstream>

using namespace std;

const string ProductFileName = "Products\\Products.txt";
class clsProduct
{



	enum enMode { EmptyMode = 1, UpdateMode = 2, AddNewMode = 3 };
	enMode _Mode;

	string _Code;
	string _Name;
	string _Category;
	string _SupplierName;
	float _PurchasePrice;
	float _SellingPrice;
	int _Quantity;
	int _QuantityWarining;

	bool MarkForDelete = false;


	static clsProduct _ConvertRecordToObject(string Record, string Saparator = "#//#")
	{
		vector <string> SupRecords = clsString::Split(Record, Saparator);

		return clsProduct(enMode::UpdateMode, SupRecords[0], SupRecords[1], SupRecords[2], SupRecords[3], stof(SupRecords[4]), stof(SupRecords[5]), stoi(SupRecords[6]), stoi(SupRecords[7]));
	}

	static string _ConvertObjectToRecord(clsProduct Product, string Saparator = "#//#")
	{
		string Record = "";
		Record += Product.Code() + Saparator;
		Record += Product.Name + Saparator;
		Record += Product.Category + Saparator;
		Record += Product.SupplierName + Saparator;
		Record += to_string(Product.PurchasePrice) + Saparator;
		Record += to_string(Product.SellingPrice) + Saparator;
		Record += to_string(Product.Quantity) + Saparator;
		Record += to_string(Product.QuantityWarining);

		return Record;
	}

	static clsProduct _GetEmptyObjectProduct()
	{
		return clsProduct(enMode::EmptyMode, "", "", "", "", 0, 0, 0, 0);
	}

	static void _SaveProductsToFile(vector <clsProduct> vProducts,string FileName)
	{
		fstream MyFile;

		MyFile.open(FileName,ios::out);

		if (MyFile.is_open())
		{
			for (clsProduct & Product : vProducts)
			{
				if(!Product.MarkForDelete)
					MyFile << _ConvertObjectToRecord(Product) << endl;
			}

			MyFile.close();
		}
	}

	 static vector <clsProduct> _GetAllProduct(string FileName) 
	{
		vector <clsProduct> vProducts;

		fstream MyFile;

		MyFile.open(FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vProducts.push_back(_ConvertRecordToObject(Line));
			}

			MyFile.close();
		}

		return vProducts;
	}

	static void _AddProductToFile(clsProduct Product, string FileName)
	{
		fstream MyFile;

		MyFile.open(FileName, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << _ConvertObjectToRecord(Product) << endl;
			MyFile.close();
		}
	}

	void _AddProduct()
	{
		_AddProductToFile(*this, ProductFileName);
	}

	static void _MoveProductBetweenFiles(clsProduct CurrentProduct, string Path1, string Path2)
	{
		vector <clsProduct> vProductsPath1 = _GetAllProduct(Path1);

		for (clsProduct &Product : vProductsPath1)
		{
			if (CurrentProduct.Code() == Product.Code())
			{
				_AddProductToFile(Product, Path2);
				Product.MarkForDelete = true;
				break;
			}
		}

		_SaveProductsToFile(vProductsPath1, Path1);
	}

	void _UpdateProdcutToFile(string FileName)
	{
		vector <clsProduct> vProducts = _GetAllProduct(FileName);

		for (clsProduct &Product : vProducts)
		{
			if (this->Code() == Product.Code())
			{

				Product = *this;
				break;
			}

		}

		_SaveProductsToFile(vProducts, FileName);
	}

	void _UpdateProdcut(string FileName)
	{
		vector <clsProduct> vProducts = _GetAllProduct(FileName);

		for (clsProduct &Product : vProducts)
		{
			if (this->Code() == Product.Code())
			{


				string Path;

				Path= "Products\\Categories\\" + clsString::UpperFirstLetterOfEachWord(Product.Category) + ".txt";
				_UpdateProdcutToFile(Path);

				Path = "Products\\Suppliers\\" + clsString::UpperFirstLetterOfEachWord(Product.SupplierName) + ".txt";
				_UpdateProdcutToFile(Path);
				
				string Path1, Path2;



				if (clsString::UpperAllString(this->Category) != clsString::UpperAllString(Product.Category))
				{
					Path1 = "Products\\Categories\\" + clsString::UpperFirstLetterOfEachWord(Product.Category) + ".txt";
					Path2 = "Products\\Categories\\" + clsString::UpperFirstLetterOfEachWord(this->Category) + ".txt";

					_MoveProductBetweenFiles(*this,Path1,Path2);
				}



				if (clsString::UpperAllString(this->SupplierName) != clsString::UpperAllString(Product.SupplierName))
				{
					Path1 = "Products\\Suppliers\\" + clsString::UpperFirstLetterOfEachWord(Product.SupplierName) + ".txt";
					Path2 = "Products\\Suppliers\\" + clsString::UpperFirstLetterOfEachWord(this->SupplierName) + ".txt";

					_MoveProductBetweenFiles(*this, Path1, Path2);
				}

				Product = *this;
				break;
			}

		}

		_SaveProductsToFile(vProducts, FileName);
	}


	 void _Update()
	 {
		 _UpdateProdcut(ProductFileName);
	 }

	 bool _DeleteProduct(string FileName) 
	 {
		 vector <clsProduct> vProducts = _GetAllProduct(FileName);

		 for (clsProduct &Product : vProducts)
		 {
			 if (this->Code() == Product.Code())
			 {
				 Product.MarkForDelete = true;
				 _SaveProductsToFile(vProducts,FileName);
				 return true;
			 }
		 }

		 *this = _GetEmptyObjectProduct();

		 return false;
	 }
public:

	clsProduct(enMode Mode, string Code, string Name, string Category, string SupplierName, float PurchasePrice, float SellingPrice, int Quantity, int QuantityWarining)
	{
		_Mode = Mode;
		_Code = Code;
		_Name = Name;
		_Category = Category;
		_SupplierName = SupplierName;
		_PurchasePrice = PurchasePrice;
		_SellingPrice = SellingPrice;
		_Quantity = Quantity;
		_QuantityWarining = QuantityWarining;


	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	string Code()
	{
		return _Code;
	}

	void SetName(string Name)
	{
		_Name = Name;
	}

	string GetName()
	{
		return _Name;
	}

	__declspec(property(get = GetName, put = SetName))string Name;

	void SetCategory(string Category)
	{
		_Category = Category;
	}

	string GetCategory()
	{
		return _Category;
	}

	__declspec(property(get = GetCategory, put = SetCategory))string Category;

	void SetSupplierName(string SupplierName)
	{
		_SupplierName = SupplierName;
	}

	string GetSupplierName()
	{
		return _SupplierName;
	}

	__declspec(property(get = GetSupplierName, put = SetSupplierName))string SupplierName;


	void SetPurchasePrice(float PurchasePrice)
	{
		_PurchasePrice = PurchasePrice;
	}

	float GetPurchasePrice()
	{
		return _PurchasePrice;
	}

	__declspec(property(get = GetPurchasePrice, put = SetPurchasePrice))float PurchasePrice;

	void SetSellingPrice(float SellingPrice)
	{
		_SellingPrice = SellingPrice;
	}

	float GetSellingPrice()
	{
		return _SellingPrice;
	}

	__declspec(property(get = GetSellingPrice, put = SetSellingPrice))float SellingPrice;


	void SetQuantity(int Quantity)
	{
		_Quantity = Quantity;
	}

	int GetQuantity()
	{
		return _Quantity;
	}

	__declspec(property(get = GetQuantity, put = SetQuantity))int  Quantity;


	void SetQuantityWarining(int QuantityWarining)
	{
		_QuantityWarining = QuantityWarining;
	}

	int GetQuantityWarining()
	{
		return _QuantityWarining;
	}

	__declspec(property(get = GetQuantityWarining, put = SetQuantityWarining))int  QuantityWarining;

	static clsProduct Find(string Code)
	{

		fstream MyFile;

		MyFile.open(ProductFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsProduct Product = _ConvertRecordToObject(Line);

				if (Code == Product.Code())
				{
					MyFile.close();

					return Product;
				}
			}

			MyFile.close();
		}

		return _GetEmptyObjectProduct();
	}

	void Print()
	{
		cout << "\n____________________________________________\n\n";
		cout << "               Product Card          \n";
		cout << "\n____________________________________________\n";
		cout << "\nName               : " << Name;
		cout << "\nCode               : " << Code();
		cout << "\nCategory           : " << Category;
		cout << "\nSupplier           : " << SupplierName;
		cout << "\nPurchase Price     : " << PurchasePrice;
		cout << "\nSelling Price      : " << SellingPrice;
		cout << "\nQuantity           : " << Quantity;
		cout << "\nQuantity Warining  : " << QuantityWarining;
		cout << "\n____________________________________________\n";

	}
	
	bool Delete()
	{
		bool isDleleted;

		isDleleted = _DeleteProduct(ProductFileName);
		isDleleted = _DeleteProduct("Products\\Categories\\" + clsString::UpperFirstLetterOfEachWord(Category) + ".txt");
		isDleleted = _DeleteProduct("Products\\Suppliers\\" + clsString::UpperFirstLetterOfEachWord(SupplierName) + ".txt");

		if (isDleleted)
		{
			*this = _GetEmptyObjectProduct();
		}

		return isDleleted;
	}

	enum enSave { svEmptyObject = 1, svSucceeded = 2, svAalreadyExists = 3 };

	enSave SaveResult()
	{
		switch (_Mode) 
		{
		case enMode::EmptyMode:
			{
			return enSave::svEmptyObject;
		}
			
		
		case enMode::AddNewMode:
			{
				bool IsExist = clsProduct::IsExist(Code());

				if (IsExist)
				{
					_Mode = enMode::UpdateMode;
					return enSave::svAalreadyExists;
				}
				else
				{
					string CategoryFileName = "Products\\Categories\\" + clsString::UpperFirstLetterOfEachWord(Category) + ".txt";
					string SupplierFileName = "Products\\Suppliers\\" + clsString::UpperFirstLetterOfEachWord(SupplierName) + ".txt";

					_AddProduct();
					_AddProductToFile(*this, CategoryFileName);
					_AddProductToFile(*this, SupplierFileName);
					_Mode = enMode::UpdateMode;
					return enSave::svSucceeded;
				}

			}

		case enMode::UpdateMode:
			{

				_Update();

				return enSave::svSucceeded;
			}
		
		}
	}

	static bool IsExist(string Code) 
	{
		clsProduct Product = clsProduct::Find(Code);

		return !(Product.IsEmpty());
	}

	static clsProduct GetAddObjectProduct(string Code) 
	{

		return clsProduct(enMode::AddNewMode, Code, "", "", "", 0, 0, 0, 0);
	}

	static vector <clsProduct> GetProductList() 
	{
		return _GetAllProduct(ProductFileName);
	}
};

