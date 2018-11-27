// Milestone 2 Errorstate class
// File ErrorState.cpp
// Date 2018/07/18
// Name: Abdul Rehman Jahangir
// Description
//       This file contains the class implimentation for ErrorState class and the helper function implimentation.
/////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include "ErrorState.h"

namespace AMA {

	// 0 and 1 arg constructor that stores the error message
	ErrorState::ErrorState(const char* errorMessage)
	{
		if (errorMessage != nullptr)
		{
			//finding size of msg.
			int size = strlen(errorMessage);
			//alloc mem to copy msg.
			error_message_adr = new char[size + 1];//alloc dynamic mem of that size

			for (int i = 0; i < size; i++)
			{
				strncpy(this->error_message_adr, errorMessage, size);
			}
			this->error_message_adr[size] = '\0';
		}
		else
			this->error_message_adr = nullptr;
	}

	//destructor for ErrorState class
	ErrorState::~ErrorState()
	{
		delete[]error_message_adr;
		error_message_adr = nullptr;
	}

	//clears an object and set it to safe state
	void ErrorState::clear()
	{
		this->~ErrorState();
	}

	//checks if obj is in safe state
	bool ErrorState::isClear() const
	{
		if (this->error_message_adr == nullptr)
			return true;
		return false;
	}

	//stores whatever string you input inside the object
	void ErrorState::message(const char* str)
	{
		if (str[0] == '\0' || str == nullptr)
		{
			delete[] error_message_adr;
			error_message_adr = nullptr;
		}
		else
		{
			if (this->error_message_adr != nullptr)
				delete[] this->error_message_adr;
			int size = strlen(str) + 1;
			error_message_adr = new char[size];
			strncpy(this->error_message_adr, str, size);
			error_message_adr[size - 1] = '\0';
		}

	}

	//returns address of the ptr
	const char* ErrorState::message() const
	{
		return error_message_adr;
	}

	//output operator(Not in class)
	std::ostream& operator<<(std::ostream& os, const ErrorState& es)
	{
		if (!es.isClear())
		{
			os << es.message();
		}
		return os;
	}

}