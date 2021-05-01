/*
http://cplusplus.com/reference/istream/istream/tellg/?kw=tellg
*/

#include <iostream>
#include <fstream>
// tellg : 입력 위치 지정자의 현재 위치를 리턴한다.
int main()
{
	std::ifstream is("test.txt", std::ifstream::binary);
	if (is)
	{
		//get length of file:
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		//allocate memory:
		char* buffer = new char[length];

		// read data as a block:
		is.read(buffer, length);

		is.close();

		//print content:
		std::cout.write(buffer, length);

		delete[] buffer;
	}
	return (0);
}