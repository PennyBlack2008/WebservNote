/*
https://www.cplusplus.com/reference/string/string/c_str/

Get C string equivalent

Returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string)
 representing the current value of the string object.

This array includes the same sequence of characters that make up the value of the string object
plus an additional terminating null-character ('\0') at the end.

*/

#include <iostream>
#include <cstring>
#include <string>

int main()
{
	std::string str("Please split this sentence into tokens");

	char* cstr = new char[str.length() + 1];
	std::strcpy(cstr, str.c_str()); // str 객체에 c_str 메소드를 먹이는 순간, str.c_str() 은 문자열을 가리키는 char* 가 된다.
	// 완벽 1 대 1 대응이기 때문에, 문자열의 마지막 문자가 NUL 이므로 C 함수인 strcpy 에 넣어도 된다.

	// cstr now contains a c-string copy of str
	char* p = std::strtok(cstr, " ");
	while (p != 0)
	{
		std::cout << p << std::endl;
		p = std::strtok(NULL, " ");
	}
	delete[] cstr;
	return 0;
}