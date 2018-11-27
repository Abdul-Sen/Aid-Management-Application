// Milestone 5 Perishable class
// File Perishable.cpp
// Date 2018/08/08
// Name: Abdul Rehman Jahangir
// Description
//       This file contains the class implimentation for Perishable class and the helper function implimentations.
/////////////////////////////////////////////////////
#include <iostream>
#include "Perishable.h"
namespace AMA
{

	//Default constructor
	Perishable::Perishable() :Product('P')
	{

	}
	//outputs data of current prodcut
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		Product::store(file, false);

		file << "," << this->exipiry;
		if (newLine)
			file << std::endl;
		return file;
	}
	//insert data to current product
	std::fstream& Perishable::load(std::fstream& file)
	{
		Product::load(file);
		file.ignore(2000, ',');
		this->exipiry.read(file);
		file.ignore();
		return file;
	}

	//displays object
	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		Product::write(os, linear);
		if (this->isClear())//if not in an error, i.e write function worte everything fine
		{
			if (linear)
			{
				this->exipiry.write(os);
			}
		}
		if (!linear)
		{
			os << std::endl;//added
			os<<" Expiry date: ";
			this->exipiry.write(os);
		}
		return os;
	}
	/*	#define NO_ERROR   0
	#define CIN_FAILED 1
	#define YEAR_ERROR 2
	#define MON_ERROR  3
	#define DAY_ERROR  4*/
	//reads to object
	std::istream& Perishable::read(std::istream& is)
	{
		Product::read(is);//this should also check for errors and report back?
		if (!is.fail())//if is did not fail
		{
			Date temp;
			std::cout << " Expiry date (YYYY/MM/DD): ";//COMPLETE
			temp.read(is);//this should retrun is.fail if not in format and
			//is.ignore();

			if (temp.errCode() != 0)
			{
				switch (temp.errCode())
				{
				case (1):
					this->message("Invalid Data Entry");
					break;
				case (2):
					this->message("Invalid Year in Date Entry");
					break;
				case (3):
					this->message("Invalid Month in Date Entry");
					break;
				case (4):
					this->message("Invalid Day in Date Entry");
					break;
				}
				is.setstate(std::ios::failbit);
			}
			if (temp.errCode() == 0)
			{
				exipiry = temp;//TODO: Does this copy object or not?
			}
		}
	//	is.ignore();
		return is;
	}

	const Date& Perishable::expiry() const
	{
		return this->exipiry;
	}
}