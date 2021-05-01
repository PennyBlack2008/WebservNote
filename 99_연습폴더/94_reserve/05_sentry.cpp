/*
http://cplusplus.com/reference/istream/istream/sentry/
*/

// istream::sentry example
#include <iostream> // std::istream, std::cout
#include <string> // std::string
#include <sstream> // std::stringstream
#include <locale> // std::isspace, std::isdigit

struct Phone
{
	std::string digits;
};

// custom extractor for objects of type Phone
std::istream& operator>>(std::istream& is, Phone& tel)
{
	std::istream::sentry s(is);
	if (s) while (is.good())
	{
		char c = is.get();
		if (std::isspace(c, is.getloc())) break ;
		if (std::isdigit(c, is.getloc())) tel.digits+=c;
	}
	return is;
}

int main()
{
	/* 첫 space 는 넘어가지만, space 아닌 문자 사이에 space 가 있다면 거기까지 끊어진다. */
	std::stringstream parseme("   (%555)2326");
	// std::stringstream parseme("   ( %555)2326");
	Phone myphone;
	parseme >> myphone;
	std::cout << "digits parsed: " << myphone.digits << '\n';
	return (0);
}