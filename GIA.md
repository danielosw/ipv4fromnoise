The way I generally tried to use it is to ask for help for specific parts, not to do the whole thing.
The reason for this is I find it tends to struggle more when you give it large chunks of code it needs to juggle in its context window.
So here is a list of times I uses AI.


I used Gemini 3.6 flash on 9/7/26
I used it to get the forumale for getting the decimal value of the ip
address I asked:  "how do you get the 32 bit decimal of an ip address"
and it responded that we should concatinate the bits and then convert to decimal.
This makes sense to me, as we are basicly converting 4 8 bit numbers into one 32 bit number and 8*4=32.



I used Gemini 3.6 flash on 9/7/26
I prompted "how can I concat four 8 sized arrays to one 32 size array
c++, prefer simplicity to verbosity" and it gave three answers, the one I used was

If you are working with plain C-style arrays (int a1[8]), std::memcpy offers
the cleanest and fastest approach: #include <cstring>
int a1[8] = {}, a2[8] = {}, a3[8] = {}, a4[8] = {};
int result[32];
std::memcpy(result,      a1, sizeof(a1));
std::memcpy(result + 8,  a2, sizeof(a2));
std::memcpy(result + 16, a3, sizeof(a3));
std::memcpy(result + 24, a4, sizeof(a4));

which I modified to my existing variables to
"
	std::memcpy(finalbinanry, binarya, sizeof(binarya));
	std::memcpy(finalbinanry + 8, binaryb, sizeof(binaryb));
	std::memcpy(finalbinanry + 16, binaryc, sizeof(binaryc));
	std::memcpy(finalbinanry + 24, binaryd, sizeof(binaryd));

"
what its doing is copying the bytes from the array dirrectly into the final array

I used Gemini 3.6 flash on 9/7/26
prompt: "how do I get user input with spaces in c++"
it told me:
"
	std::string fullName;

	std::cout << "Enter your full name: ";
	std::getline(std::cin, fullName);

	std::cout << "Hello, " << fullName << "!\n";
"
which I adopted into:
"
		std::cout << "Enter a string (or 'END' to quit): ";
		string holding;
		std::getline(std::cin, holding);
		cout << "\n" << endl;

"