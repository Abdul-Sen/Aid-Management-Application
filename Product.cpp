// MILESTONE 3 - Derived Classes
// File Product.cpp
// Date 2018/07/29
// Name: Abdul Rehman Jahangir
// Description
//       This file contains the class implimentation for Product class and the helper function implimentations.
/////////////////////////////////////////////////////
#include <iostream>
#include <cstring>
#include "Product.h"
namespace AMA {

	//sets the name of the product, or removes current name
	void Product::name(const char* outside) //CHANGED
	{
		if (outside == nullptr || outside == '\0')
		{
			p_name = nullptr;//CHANGED
		}
		else
		{
			this->p_name = new char[max_name_length];
			strncpy(p_name, outside, max_name_length);
			p_name[max_name_length - 1] = '\0';
		}

		/*//First implimentation
		//dealloc previous data
		if (outside == nullptr)
		delete[] p_name;
		p_name = nullptr;

		//int length = strlen(outside)+1;
		p_name = new char[max_name_length];
		strncpy(p_name, outside, max_name_length);
		p_name[max_name_length-1] = '\0';
		*/
	}

	//returns p_name adr
	const char* Product::name() const
	{
		if (p_name == nullptr)
			return nullptr;
		return p_name;
	}

	//returns products sku
	const char* Product::sku() const
	{
		return product_sku;
	}

	//returns product unit
	const char* Product::unit() const
	{
		return product_unit;
	}

	//returns product tax status
	bool Product::taxed() const
	{
		return tax_status;
	}

	//return product price (without taxes)
	double Product::price() const
	{
		return product_price;
	}

	//return final cost of a single item (i.e price + taxes if any)
	double Product::cost() const
	{
		if (taxed())
			return (price()*(CURR_TAX_RATE + 1));
		return price();
	}

	//stores an error message
	void Product::message(const char* outside)
	{
		product_error.message(outside);
	}

	//checks error message status
	bool Product::isClear() const
	{
		return product_error.isClear();
	}

	/*******************************Public memeber functions************************************/


	// 0-1 arg constructor
	Product::Product(char type)
	{
		product_type = type;//Default 'N'
		product_sku[0] = '\0';
		product_unit[0] = '\0';
		p_name = nullptr;
		quantity_available = 0;
		quantity_needed = 0;
		product_price = 0.0;
		tax_status = false;//should this be true?
		message("\0");//ADDED
	}

	//7-arg constructor
	Product::Product(const char* ui_sku, const char* ui_p_name, const char* ui_unit, int ui_qty_available, bool ui_tax_status, double ui_price, int ui_qty_needed)
	{
		this->product_type = 'N';

		strncpy(this->product_sku, ui_sku, max_sku_length);
		this->name(ui_p_name);
		//this->message(ui_p_name);
		strncpy(this->product_unit, ui_unit, max_unit_length);
		this->quantity_available = ui_qty_available;
		this->tax_status = ui_tax_status;
		this->product_price = ui_price;
		this->quantity_needed = ui_qty_needed;
		this->message("\0");//ADDED
							//checking some things

	}

	//copy assignment operator
	Product& Product::operator=(const Product& source) //TODO: Use 7 arg consturcotr to copy shallow? somehow?
	{

		if (this != &source) {  // check for self-assignment by comparing addresses
								//shallow copy
			int size = strlen(source.product_sku) + 1;
			strncpy(this->product_sku, source.product_sku, size);
			size = 0;
			size = strlen(source.product_unit) + 1;
			strncpy(this->product_unit, source.product_unit, size);
			this->quantity_available = source.quantity_available;
			this->tax_status = source.tax_status;
			this->product_price = source.product_price;
			this->quantity_needed = source.quantity_needed;

			this->name(source.p_name);//CHANGED

		}
		return *this;
	}

	//copy constructor

	//NOTE: Might have to manually copy everythign from rhs to this
	Product::Product(const Product& rhs)//CHANGED
	{
		*this = Product();
		*this = rhs;
	}

	Product::~Product()
	{
		delete[] p_name;
		p_name = nullptr;//ADDED
	}

	//puts values of current object to file object
	std::fstream & Product::store(std::fstream & file, bool newLine) const
	{
		file << this->product_type << "," << this->sku() << "," << this->name() << "," << this->unit() << "," << this->taxed();
		file << "," << price() << "," << quantity_available << "," << quantity_needed;
		if (newLine == true)
			file << "\n";
		return file;
	}


	//extracts data from incoming file
	std::fstream & Product::load(std::fstream & file)
	{
		char fsku[max_sku_length];
		char funit[max_unit_length];
		char fname_adder[max_name_length];//stores product name in dynamic mem
										  //CHANGED
		int fqty_avail;
		int fqty_needed;
		double fprice;//holds price of 1 unit
		bool ftaxed;// true if product is taxable

		file.getline(fsku, max_sku_length, ',');
		file.getline(fname_adder, max_name_length,',');
		//file.ignore(',');//ADDED

		//CHANGED
		file.getline(funit, max_unit_length, ',');
		file >> ftaxed;
		file.ignore(2000,',');
		file >> fprice;
		file.ignore(2000, ',');
		file >> fqty_avail;
		file.ignore(2000, ',');
		file >> fqty_needed;
		Product temp(fsku, fname_adder, funit, fqty_avail, ftaxed, fprice, fqty_needed);
		//if(!temp.isEmpty())//ADDED
		*this = temp;
		return file;
	}

	//writes to an ostream object i.e reads from an object
	std::ostream& Product::write(std::ostream& os, bool linear) const
	{
		os.fill(' ');
		if (this->isClear())
		{
			if (linear)
			{
				os.setf(std::ios::left);
				os.width(max_sku_length);
				os << this->sku() << '|';
				os.width(20);
				os << this->name() << '|';
				os.width(7);
				os.unsetf(std::ios::left);
				os.setf(std::ios::fixed);
				os.precision(2);
				os << this->cost() << '|';
				os.width(4);
				os << this->quantity_available << '|';
				os.width(10);
				os.setf(std::ios::left);
				os << this->unit() << '|';
				os.width(4);
				os.unsetf(std::ios::left);
				os << this->quantity_needed << '|';
			}

			if (!linear)
			{
				os << " Sku: " << this->sku() << std::endl;
				os << " Name (no spaces): " << this->name() << std::endl;
				os << " Price: " << this->price() << std::endl;
				os << " Price after tax: ";
				if (this->price() == this->cost())
					os << "N/A" <<std::endl;
				else
					os << this->cost() << std::endl;
				os << " Quantity on Hand: " << this->quantity_available << " " <<product_unit<< std::endl;
				os << " Quantity needed: " << this->quantity_needed;
				
			}
		}
		else
			os << this->product_error;
		return os;
	}

	//writes to istream obj i.e writes to a product object
	std::istream& Product::read(std::istream& is)
	{
		char temp[max_name_length];
		std::cout << " Sku: ";
		is.getline(this->product_sku, max_sku_length, '\n');//sku
		std::cout << " Name (no spaces): ";
		is.getline(temp, max_name_length);//name
		this->name(temp);
		std::cout << " Unit: ";
		is.getline(this->product_unit, max_unit_length); //unit
		std::cout << " Taxed? (y/n): ";
		char s;
		is.get(s);
		if (s == 'Y' || s == 'y')
			this->tax_status = true;
		if (s == 'N' || s == 'n')
			tax_status = false;
		//NEW
		if (s != 'y' && s != 'Y' && s != 'N' && s != 'n')
		{
			is.setstate(std::ios::failbit);
			this->message("Only (Y)es or (N)o are acceptable");
		}
		if (!is.fail())
		{
			std::cout << " Price: ";
			is >> this->product_price;
			if (is.fail())
			{
				this->message("Invalid Price Entry");
			}
			if (!is.fail())
			{
			std::cout << " Quantity on hand: ";
			is >> this->quantity_available;
			if (is.fail())
			{
				this->message("Invalid Quantity Entry");
			}
			if (!is.fail())
			{
				std::cout << " Quantity needed: ";
				is >> this->quantity_needed;
				if (is.fail())
				{
					this->message("Invalid Quantity Needed Entry");
				}
			}
			}
		}
		if (!is.fail())
			this->message("");
		is.ignore();//ADDED
		return is;
	}

	//COMPARISON OPERATOR
	bool Product::operator==(const char* RHS_UNIT) const// check if UNITS ARE EQUAL
	{

		if (strncmp(this->sku(), RHS_UNIT, max_sku_length) == 0)//if equal
			return true;
		return false;
	}


	//return total cost of all units including taxes
	double Product::total_cost() const
	{
		return this->quantity_available * this->cost();
	}

	//change quantity avail to this
	void Product::quantity(int new_quantity)
	{
		this->quantity_available = 0;
		this->quantity_available = new_quantity;
	}

	bool Product::isEmpty() const
	{
		if (product_sku[0] == '\0' && product_unit[0] == '\0' && p_name == nullptr && quantity_available == 0 && quantity_needed == 0 && product_price == 0.0 && this->product_error.message() == '\0') //ADDED
			return true;
		return false;
	}

	int Product::qtyNeeded() const
	{
		return this->quantity_needed;
	}

	int Product::quantity() const
	{
		return this->quantity_available;
	}

	//if lhs sku> rhs sku
	bool Product::operator>(const char* rhs) const
	{
		int result = strncmp(this->sku(), rhs, max_sku_length);//  0 if equal, <0 if rhs is bigger, >0 if lhs is bigger
		if (result > 0)
			return true;
		return false;
	}

	bool Product::operator>(const iProduct& rhs) const //TODO: CHANGE THIS AND OTHER STR COMPARE FUNCTIONS! They mean compare ASCII values!
	{
		int str1 = strlen(this->name());
		int str2 = strlen(rhs.name());
		int size = 0;
		if (str1 > str2)
			size = str1;
		else
			size = str2;
		return strncmp(this->name(), rhs.name(), size);//this is wrong
	}

	//adds that much amount to quantity
	int Product::operator+=(int No_units)
	{
		if (No_units > 0)
		{
			this->quantity_available += No_units;
		}
		return this->quantity();
	}

	//inserts Product to ostream
	std::ostream& operator<<(std::ostream& os, const iProduct& rhs)
	{
		return rhs.write(os, true);//or false?
	}

	//read overlaod
	std::istream& operator>>(std::istream& is, iProduct& lhs)
	{
		lhs.read(is);
		return is;
	}

	//adds product cost to double dcost
	double operator+=(double& dcost, const iProduct& myProduct)
	{
		dcost += myProduct.total_cost();
		return dcost;
	}
}