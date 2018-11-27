// MILESTONE 4 - abstract class
// File iProduct.h
// Date 2018/08/03
// Name: Abdul Rehman Jahangir
// Description
//       This file contains the iProcduct interface class
/////////////////////////////////////////////////////
#ifndef IPRODCUT_H_AMA
#define IPRODCUT_H_AMA
#include <iostream>
#include <fstream>

namespace AMA {

	class iProduct {
	public:
		virtual std::fstream& store(std::fstream& file, bool newLine = true) const = 0;
		virtual std::fstream& load(std::fstream& file) = 0;
		virtual std::ostream& write(std::ostream& os, bool linear) const = 0;
		virtual std::istream& read(std::istream& is) = 0;
		virtual bool operator==(const char*) const = 0;
		virtual double total_cost() const = 0;
		virtual const char* name() const = 0;
		virtual void quantity(int) = 0;
		virtual int qtyNeeded() const = 0;
		virtual int quantity() const = 0;
		virtual int operator+=(int) = 0;
		virtual bool operator>(const iProduct&) const = 0;
		virtual ~iProduct()
		{

		}
	};

	


	iProduct* CreateProduct();
	iProduct* CreatePerishable();
	std::ostream& operator<<(std::ostream& os, const iProduct& ip);
	std::istream& operator>>(std::istream& is, iProduct& ip);
	double operator+=(double& cost, const iProduct& ip);

}
#endif // !IPRODCUT_H_AMA

