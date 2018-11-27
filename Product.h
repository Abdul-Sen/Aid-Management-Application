// Milestone 3 - Product Class
// File Prodcut.h
// Date 2018/07/18
// Name: Abdul Rehman Jahangir
// Description
//       This file contains the class definition for Prodcut class and the helper function declaration.
/////////////////////////////////////////////////////
#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#include "ErrorState.h"
#include "iProduct.h"

namespace AMA {

	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double CURR_TAX_RATE = 0.13;//or 0.13?

	class Product :public iProduct {
		char product_type;//tells product type
		char product_sku[max_sku_length];
		char product_unit[max_unit_length];
		char* p_name;//stores product name in dynamic mem
		int quantity_available;
		int quantity_needed;
		double product_price;//holds price of 1 unit
		bool tax_status;// true if product is taxable
		ErrorState product_error;//Is this correct?

	protected:
		void name(const char*); //takes name of the product and sets it up dynamically
		const char* name() const; // returns address of name string
		const char* sku() const; //returns address of sku string
		const char* unit() const; // returns address of unit string
		bool taxed() const; //returns tax status
		double price() const; // return cost of 1 item
		double cost() const; // return cost of 1 item + tax
		void message(const char*); // takes message and add it to error state of the class
		bool isClear() const; //checks if errorstate is clear
	public:
		//default constructor
		Product(char = 'N');//default constructor
		Product(const char* ui_sku, const char* ui_p_name, const char* ui_unit, int ui_qty_available= 0,bool ui_tax_status = true, double ui_price = 0,int ui_qty_needed = 0);
		Product(const Product&);//build = operator first
		Product& operator=(const Product&);//copy assignment operator
		~Product();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		//OVERLOADS
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int); //changes quntity avail to whatever you input 
		bool isEmpty() const; //checks if obj is in safe empty state
		int qtyNeeded() const;
		int quantity() const;//
		bool operator>(const char*) const;
		bool operator>(const iProduct&) const;
		int operator+=(int);//adds that much amount to quantity

	};

	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);
	double operator+=(double&, const iProduct&);
}

#endif // !AMA_PRODUCT_H
