// MILESTONE 5 - ANA Final application: Perishable class
// File Perishable.h
// Date 2018/08/08
// Name: Abdul Rehman Jahangir
// Seneca ID: 149019176
// Description
//       This file contains the class definition for Perishable Product class and the helper function definitions.
/////////////////////////////////////////////////////
#ifndef PERISHABLE_H_AMA
#define PERISHABLE_H_AMA
#include <iostream>
#include "Product.h"
#include "Date.h"
namespace AMA {

	class Perishable :public Product
	{
		Date exipiry;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};

}

#endif // !PERISHABLE_H_AMA
