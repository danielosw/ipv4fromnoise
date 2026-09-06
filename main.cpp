#include <cctype>
#include <iostream>

int main() {
	std::cout << "Hello, CMake!" << std::endl;
	return 0;
}
// Returns true if a valid address was found, false otherwise.
// On success: outAddress holds the 32-bit value,
// and outPort holds the port number, or -1 if no port was present.
// On failure: outAddress is set to 0 and outPort is set to -1.
bool extractIPv4(const std::string &str, unsigned long &outAddress,
				 int &outPort) {
	return false;
};

// Return true if char is one of the following
// 0-9, :, or .
// Written by hand
bool validChar(char c) {
	if (isdigit(c)) {
		return true;
	}
	switch (c) {
	case '.':
		return true;
	case ':':
		return true;
	default:
		return false;
	}
}
