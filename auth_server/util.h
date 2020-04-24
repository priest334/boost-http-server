#pragma once

#include <string>
#include <iostream>

namespace ntq {
	template<class ErrorCode>
	void PrintError(const ErrorCode& ec, const char* what) {
		std::cout << what << ": " << ec.message() << std::endl;
	}
	void ShowTimestamp(const char* what);
}

