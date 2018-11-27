// Milestone 2 - Errorstate Class
// File ErrorState.h
// Date 2018/07/18
// Name: Abdul Rehman Jahangir
// Description
//       This file contains the class definition for ErrorState class and the helper function declaration.
/////////////////////////////////////////////////////
#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H
#include <iostream>

namespace AMA {

	class ErrorState {
		char* error_message_adr;
	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& em) = delete;
		ErrorState& operator=(const ErrorState& em) = delete;
		virtual ~ErrorState();

		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message()const;
	};

	//helper functions
	std::ostream& operator<<(std::ostream&, const ErrorState&);
}

#endif // !AMA_ERRORSTATE_H
