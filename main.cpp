#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Return true if char is one of the following
// 0-9, :, or .
// Written by hand
bool validChar(char c)
{
	if (isdigit(c))
	{
		return true;
	}
	switch (c)
	{
	case '.':
		return true;
	case ':':
		return true;
	default:
		return false;
	}
}

// Return the equivelent num to a char
// accepts 0-9
// returns -1 if invalid
// Written by hand
int charToInt(char i)
{
	switch (i)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	default:
		return -1;
	}
}
/*Using Gemini 3.6 flash on 9/16/2026
promt:
 how can I optimise this conversion between decimal to binary, its currently
very slow, explain your code, avoid bit operations:    for (size_t i = 0; i <
outAddress; i++) {           flip(binary, 31);       } 

 void flip(int binary[], int i) { 
     // basicly we swap the 0 ->1 and 1->0, but 1->0 makes us swap the 
     // next one as well 
     if (binary[i] == 1) { 
         binary[i] = 0; 
         flip(binary, i - 1); 
     } else { 
         binary[i] = 1; 
     } 
 }"
result:
void decimalToBinary(size_t value, int binary[32]) {
	// 1. Initialize all bits to 0
	for (int i = 0; i < 32; i++) {
		binary[i] = 0;
	}

	// 2. Extract binary digits from right to left using division and modulo
	int index = 31;
	while (value > 0 && index >= 0) {
		binary[index] = value % 2;  // Remainder gives the current binary digit
(0 or 1) value = value / 2;          // Integer division drops the lowest digit
		index--;
	}
}
	which I adopted by making it more generic and passing in the binary array;
*/
void decimalToBinary(unsigned long value, int index, int *binary)
{
	while (value > 0 && index >= 0)
	{
		binary[index] = value % 2;
		value = value / 2;
		index--;
	}
}
unsigned long binaryToDecimal(int *binary, int length)
{
	unsigned long a = 0;
	int count = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		if (binary[i] == 0)
		{
			count += 1;
			continue;
		}
		else
		{
			a += pow(2, count);
			count += 1;
			continue;
		}
	}
	return a;
}
void accumilate(int &a, int &b, int &c, int &d, int colonCount, int &port,
				char num, int numCount, int dotCount)
{
	int realnum = charToInt(num);
	switch (dotCount)
	{
		// the mess is that we are essentually going in reverse so we need to
		// multiply the existing by ten then add the new one to it
		// ie
		// for 192, 1, 1*10+9=19, 19*10+2=192
	case (0):
		a *= 10;
		a += realnum;
		break;
	case (1):
		b *= 10;
		b += realnum;
		break;

	case (2):
		c *= 10;
		c += realnum;
		break;

	case (3):
		if (colonCount == 0)
		{
			d *= 10;
			d += realnum;
			break;
		}
		else
		{
			port *= 10;
			port += realnum;
			break;
		}
	}
}
void flip(int binary[], int i)
{
	// basicly we swap the 0 ->1 and 1->0, but 1->0 makes us swap the
	// next one as well
	if (binary[i] == 1)
	{
		binary[i] = 0;
		flip(binary, i - 1);
	}
	else
	{
		binary[i] = 1;
	}
}
// I had issues with this until I relised I was casting an unsigned long to an
// int
unsigned long calcDecimal(int a, int b, int c, int d)
{
	// While this is hand coded the logic is not mine
	// I used Gemini 3.6 flash on 9/7/26
	// I used it to get the forumale for getting the decimal value of the ip
	// address I asked:  "how do you get the 32 bit decimal of an ip
	// address" and it responded that we should concatinate the bits and
	// then convert to decimal

	// This makes sense to me as what we are doing is converting a from 4
	// bytes, 4*8=32, to raw 32 bits as a result the amount of information
	// when combineing them already will add up to 32 bits so we need to
	// convert a b c and d to binary, concatant, then convert to decimal
	int binarya[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int binaryb[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int binaryc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int binaryd[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	decimalToBinary(a, 7, binarya);
	decimalToBinary(b, 7, binaryb);
	decimalToBinary(c, 7, binaryc);
	decimalToBinary(d, 7, binaryd);
	// now we need to concat that to eachother
	int finalbinanry[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	// I used Gemini 3.6 flash on 9/7/26
	// I prompted "how can I concat four 8 sized arrays to one 32 size array
	// c++, prefer simplicity to verbosity" and it gave three answers, the one I
	// used was
	/*
	If you are working with plain C-style arrays (int a1[8]), std::memcpy offers
	the cleanest and fastest approach: #include <cstring>

	int a1[8] = {}, a2[8] = {}, a3[8] = {}, a4[8] = {};
	int result[32];

	std::memcpy(result,      a1, sizeof(a1));
	std::memcpy(result + 8,  a2, sizeof(a2));
	std::memcpy(result + 16, a3, sizeof(a3));
	std::memcpy(result + 24, a4, sizeof(a4));
	*/
	// whicch I modified to my existing variables
	// what its doing is copying the bytes from the array dirrectly into the
	// final array
	std::memcpy(finalbinanry, binarya, sizeof(binarya));
	std::memcpy(finalbinanry + 8, binaryb, sizeof(binaryb));
	std::memcpy(finalbinanry + 16, binaryc, sizeof(binaryc));
	std::memcpy(finalbinanry + 24, binaryd, sizeof(binaryd));

	return binaryToDecimal(finalbinanry, 32);
}
// Returns true if a valid address was found, false otherwise.
// On success: outAddress holds the 32-bit value,
// and outPort holds the port number, or -1 if no port was present.
// On failure: outAddress is set to 0 and outPort is set to -1.
bool extractIPv4(const std::string &str, unsigned long &outAddress,
				 int &outPort)
{
	// starting at each point in the string, try to parse an IPv4 address

	for (size_t i = 0; i < str.length(); ++i)
	{
		if (!validChar(str[i]))
		{
			continue;
		}
		// otherwise try to parse
		// we are basiccly matching by hand
		// [0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}(:[0-9]{1,5})?
		// their is probably a better way to to do this but this techinally
		// works
		// one rule is that if the previues one is valid start, this one cannot
		// be
		if (i != 0 && isdigit(str[i]) && validChar(str[i - 1]))
		{
			continue;
		}
		// it can only be a valid start if it is a digit
		if (!isdigit(str[i]))
		{
			continue;
		}
		// store current number of numbers
		int numCount = 0;
		// store current number of dots
		int dotCount = 0;
		// store current number of colons
		int colonCount = 0;
		int a = 0;
		int b = 0;
		int c = 0;
		int d = 0;
		int port = 0;
		bool portexists = false;
		// store if we have the correct one or not
		bool correct = false;

		for (size_t j = i; j < str.length(); ++j)
		{

			// if its a number
			if (isdigit(str[j]))
			{
				// if we have three numbers AND are not in the port secton
				// break, if we have 4 numbers already and are in the port
				// section break
				if ((numCount > 2 && colonCount == 0) ||
					(numCount > 4 && colonCount == 1))
				{
					break;
				}
				// this is sepret just due to complexity
				// basiclly this is our leading zero detection
				// IF its zero AND numCount == 0 AND str[j] is a number then
				// break
				else if (charToInt(str[j]) == 0 && j != str.length() - 1 &&
						 numCount == 0 && isdigit(str[j + 1]))
				{
					break;
				}
				else if (dotCount == 3)
				{
					// essentually we want to check if thier is a colon or
					// dot if thier is a dot then break if colon then
					// continue otherwise return true

					// check if we are at the end of the string
					if (j == str.length() - 1 || !validChar(str[j + 1]))
					{
						correct = true;
						numCount += 1;
						accumilate(a, b, c, d, colonCount, port, str[j],
								   numCount, dotCount);
						break;
					}
					else if (str[j + 1] == '.')
					{
						// its invalid
						break;
					}
					else
					{
						// accumilate
						numCount += 1;

						accumilate(a, b, c, d, colonCount, port, str[j],
								   numCount, dotCount);
						continue;
					}
				}

				else
				{
					// increment the numCount and continue
					numCount += 1;
					accumilate(a, b, c, d, colonCount, port, str[j], numCount,
							   dotCount);
					continue;
				}
				// if its a dot
			}
			else if (str[j] == '.')
			{
				// if we have no numbers proceding, already have three dots,
				// or already are in the port parsing part then break
				if (numCount == 0 || dotCount > 2 || colonCount > 0)
				{
					break;
				}
				else
				{
					// reset numCount and increment dotCount
					numCount = 0;
					dotCount += 1;
				}
			}
			// this must be a colon
			else if (str[j] == ':')
			{
				// if we already have a colon or dont have at least 3 dots
				// or dont have at least 1 number, break
				if (colonCount > 0 || dotCount < 3 || numCount == 0)
				{
					break;
				}
				else
				{
					portexists = true;
					numCount = 0;
					colonCount += 1;
					continue;
				}
			}
			else
			{
				break;
			}
		}
		// if its correct

		if (correct)
		{
			// make sure a b c and d are all in the range 0-255
			// we need to do this now because at the next step we assume that
			// values are in these ranges so if we don't reject them we will
			// have out of bounds issues
			if (a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 ||
				d < 0 || d > 255 || port < 0 || port > 65535)
			{
				// oops its actually wrong
				continue;
			}
			outAddress = calcDecimal(a, b, c, d);

			if (portexists)
			{
				outPort = port;
			}
			else
			{
				outPort = -1;
			}
			return true;
		}
	}
	outPort = -1;
	outAddress = 0;
	return false;
};

void printIp(unsigned long outAddress, int outPort)
{
	// we are basiclly reversing calc decimal
	// so first decimal -> binary
	int binary[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int index = 31;
	unsigned long value = outAddress;
	decimalToBinary(value, index, binary);
	// then split into a b c and d.
	int binarya[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	int binaryb[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int binaryc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int binaryd[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	std::memcpy(binarya, binary, sizeof(binarya));
	std::memcpy(binaryb, binary + 8, sizeof(binaryb));
	std::memcpy(binaryc, binary + 16, sizeof(binaryc));
	std::memcpy(binaryd, binary + 24, sizeof(binaryd));
	int a = binaryToDecimal(binarya, 8);
	int b = binaryToDecimal(binaryb, 8);
	int c = binaryToDecimal(binaryc, 8);
	int d = binaryToDecimal(binaryd, 8);
	cout << "Extracted IPv4 address:" << a << '.' << b << '.' << c << '.' << d
		 << " (decimal value:" << outAddress << ", port: ";
	if (outPort != -1)
	{
		cout << outPort;
	}
	else
	{
		cout << "none";
	}
	cout << ")\n"
		 << endl;
}

int main()
{
	// I used Gemini 3.6 flash on 9/7/26
	// prompt: "how do I get user input with spaces in c++"
	// it have me:
	/*
	std::string fullName;

	std::cout << "Enter your full name: ";
	std::getline(std::cin, fullName);

	std::cout << "Hello, " << fullName << "!\n";
	*/
	// which I adopted by using the right promt and variable names
	while (true)
	{
		std::cout << "Enter a string (or 'END' to quit): ";
		string holding;
		std::getline(std::cin, holding);
		cout << "\n"
			 << endl;
		if (holding == "END")
		{
			cout << "Program terminated." << endl;
			return 0;
		}
		unsigned long outAddress = 0;
		int outPort = 0;
		if (extractIPv4(holding, outAddress, outPort))
		{

			printIp(outAddress, outPort);
		}
		else
		{
			cout << "Invalid input: no valid IPv4 address found" << "\n"
				 << endl;
		}
	}
}
