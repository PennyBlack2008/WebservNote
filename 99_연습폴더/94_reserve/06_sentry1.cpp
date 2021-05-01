/*
https://modoocode.com/277
*/

#include <iostream>
#include <sstream>

struct Foo
{
	char n[5];	
};

std::istream& operator>>(std::istream& is, Foo& f)
{
	std::istream::sentry s(is);
	if (s)
		is.read(f.n, 5);
	return is;
}

int main()
{
	std::string input = "   abcde";
	std::istringstream stream(input);
	Foo f;
	stream >> f;
	std::cout.write(f.n, 5);
	std::cout << '\n';
}