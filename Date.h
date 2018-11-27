// Final Project Milestone 1
// Date.h
// Version 1.0
// Date 2018/7/13
// Author Abdul Rehman Jahangir
// Description
// Date.h header file that contains Date calss definition and helper function declarations
//=========================================================================================
#ifndef AMA_DATE_H
#define AMA_DATE_H

namespace AMA {
#include <iostream>
	const int min_year = 2000;
	const int max_year = 2030;

	//macros
	#define NO_ERROR   0
	#define CIN_FAILED 1
	#define YEAR_ERROR 2
	#define MON_ERROR  3
	#define DAY_ERROR  4

  class Date {
	  int year;
	  int month;
	  int dayofMonth;
	  int comparitor;//is used to compare date of our obj with another obj
	  int err_state;

	  //private memeber functions
     int mdays(int, int	)const;
	 void errCode(int errorCode);
 
  public:
	  Date();
	  Date(int, int, int);
	  bool isEmpty() const;//checks if obj is in safe state

	  
	  //operators
	  bool operator==(const Date&) const;
	  bool operator!=(const Date& rhs) const;
	  bool operator<(const Date& rhs) const;
	  bool operator>(const Date& rhs) const;
	  bool operator<=(const Date& rhs) const;
	  bool operator>=(const Date& rhs) const;
	//  Date& operator=(Date&&); //leaving this here because I need it for future reference
	 // Date& operator=(Date&);

	  //queries
	  int errCode() const;
	  bool bad() const;
	  std::istream& read(std::istream& istr);
	  std::ostream& write(std::ostream& ostr) const;
  };

  //helper operators
  std::istream& operator>>(std::istream& is, Date& s);
  std::ostream& operator<<(std::ostream& os, const Date& s);
}
#endif