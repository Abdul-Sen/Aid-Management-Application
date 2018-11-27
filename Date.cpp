// Final Project Milestone 1
//
// Version 1.0
// Date 2018 07 13
// Author Abdul Rehman Jahangir
// Description
// Date.cpp implimentation file that include all the overloaded operators, i and ostream helper functions,
// 
//======================================================================================================
#include <iostream>
#include "Date.h"

namespace AMA {

	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	//sets error state to one of the following
	void Date::errCode(int errorCode)
	{
		switch (errorCode)
		{
		case(0):
			err_state = NO_ERROR;
			break;
		case(1):
			err_state = CIN_FAILED;
			break;
		case(2):
			err_state = YEAR_ERROR;
			break;
		case(3):
			err_state = MON_ERROR;
			break;
		case(4):
			err_state = DAY_ERROR;
			break;
		}

	}

	//Default constructor
	Date::Date()
	{
		err_state = NO_ERROR;
		year = 0000;
		month = 00;
		dayofMonth = 00;
		comparitor = 0;
	}

	//3-Arg constructor
	Date::Date(int ui_year, int ui_month, int ui_day)
	{
		this->errCode(NO_ERROR);
		//validating year
		if (ui_year >= min_year && ui_year <= max_year)
		{
			this->year = ui_year;
		}
		else
			this->errCode(YEAR_ERROR);
		if (err_state == NO_ERROR && ui_month >= 1 && ui_month <= 12)
		{
			this->month = ui_month;
		}
		else
			this->errCode(MON_ERROR);
		//validating day
		if (err_state == NO_ERROR)
		{
			int validDay = this->mdays(ui_month, ui_year);
			if (ui_day <= validDay)
				this->dayofMonth = ui_day;
			else
				this->errCode(4);
		}
		if (this->err_state != NO_ERROR)
		{
			*this = Date();
		}
			//*this = Date(); //THIS DID NOT WORK SO NOW IM SETTING IT MAUALLY

		else
			this->comparitor = year * 372 + month * 13 + dayofMonth;
	}

	//checks if instance of the obj is in safe state. returns true if empty
	bool Date::isEmpty() const
	{
		if (this->year == 0000 && this->month == 00 && this->dayofMonth == 00 && this->comparitor == 0 && this->err_state == NO_ERROR)
			return true;
		return false;
	}

	//uses comparator to check if both obj dates are same
	bool Date::operator==(const Date& outside) const
	{
		if (this->isEmpty() || outside.isEmpty())
			return false;//if does not hold any data
		else if (this->comparitor == outside.comparitor)
			return true;//if both comparators are same
		return false;  //if both have comparators but different values
	}

	//checks if both obj are not the same
	bool Date::operator!=(const Date& outside) const
	{
		if (*this == outside)//if both are same, return false (== will also check to see if obj is empty or not
			return false;
		return true;//if both are not same
	}

	//checks if current date comparator is less than other date comparatorr after checking if both dates have data
	bool Date::operator<(const Date& outside) const
	{
		if (this->isEmpty() || outside.isEmpty())
			return false;
		if (this->comparitor < outside.comparitor)
			return true;
		return false;
	}

	//checks if this>outside value
	bool Date::operator>(const Date& outside) const
	{
		if (*this < outside)
			return false;
		else
			return true;
	}

	bool Date::operator<=(const Date& rhs) const
	{
		if (this->isEmpty() || rhs.isEmpty())
			return false;
		if (this->comparitor <= rhs.comparitor)
			return true;
		return false;
	}

	bool Date::operator>=(const Date& rhs) const
	{
		if (*this == rhs) //in case they are equal
			return true;
		if (*this <= rhs) //if this is less than rhs
			return false;
		else
			return true;
	}

	//returns error code number
	int Date::errCode() const
	{
		int temp = this->err_state;
		return temp;
	}

	//if NO_ERROR, return true, else false
	bool Date::bad() const
	{
		if (this->err_state == NO_ERROR)
			return true;
		return false;
	}

	//reads into an object if values input are correct
	std::istream& Date::read(std::istream& istr)
	{
		int ui_year=0000, ui_month=00, ui_day=00;

		istr >> ui_year;
		istr.ignore();
		istr >> ui_month;
		istr.ignore();
		istr >> ui_day;
		if (istr.fail() == true)
		{
			this->errCode(CIN_FAILED);
		}

		if (this->err_state == NO_ERROR)
		{
			if (ui_year >= 2000 && ui_year <= 2030)
			{
				this->year = ui_year;
			}
			else
				this->errCode(YEAR_ERROR);
			if (this->err_state == NO_ERROR)
			{
				if (ui_month >= 1 && ui_month <= 12)
				{
					this->month = ui_month;
				}
				else
					this->errCode(MON_ERROR);
			}

			if (this->err_state == NO_ERROR)
			{
				int temp = this->mdays(this->month, this->year);
				if (ui_day <= temp)
					this->dayofMonth = ui_day;
				else
					this->errCode(DAY_ERROR);
			}
		}
		if (this->err_state != NO_ERROR)
		{
			int temp = this->err_state;
			*this = Date();
			this->errCode(temp);
		}
		//istr.ignore();
		return istr;

	}

	//reads from an obj
	std::ostream& Date::write(std::ostream& ostr) const //is this correct?
	{
		//does commented code below do the same thing?
		//ostr << this->year << this->month << this->dayofMonth;
		ostr << this->year;
		ostr << "/";
		if (this->month < 10)//if not 2 digit
		{
			ostr.width(2);
			ostr.fill('0');
		}
		ostr << this->month;
		ostr << "/";
		if (this->dayofMonth < 10)//if not 2 digit
		{
			ostr.width(2);
			ostr.fill('0');
		}

		ostr << this->dayofMonth;
		return ostr;
	}

	//overloaded << operator that writes to date obj
	std::ostream& operator<<(std::ostream& os, const Date& s) {
		s.write(os);
		return os;
	}
	//overloaded >> operator that reads from date obj
	std::istream& operator>>(std::istream& is, Date& s) {
		s.read(is);
		return is;
	}

	//This function was suppose to let us do *this = Date(); because for some reason my = function was deleted.

/*
	Date& Date::operator=(Date& rhs)
	{
		this->year = rhs.year;
		this->month = rhs.month;
		this->dayofMonth = rhs.dayofMonth;
		this->comparitor = rhs.comparitor;
		this->err_state = rhs.err_state;
		return *this;
	}
	*/ 

}

/*
Date& Date::operator=(Date&& rhs) //first add it to temp vars to make sure they are OK.
{
this->year = rhs.year;
this->month = rhs.month;
this->dayofMonth = rhs.dayofMonth;
return *this;
}
*/
