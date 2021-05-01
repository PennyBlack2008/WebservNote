// string::reserve
/*
문자열을 넣기 전에 미리 "곧 n만큼의 크기의 스트링이 들어올거니까 그에 맞는 capacity를 할당해 달라"는 함수 입니다
(출처: https://blockdmask.tistory.com/338 [개발자 지망생])
*/

#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::string str;

	std::ifstream file("test.txt", std::ios::in|std::ios::ate);
	if (file)
	{
		std::ifstream::streampos filesize = file.tellg();
		str.reserve(filesize);

		file.seekg(0);
		while (!file.eof())
			str += file.get();
		std::cout << str;
	}
	return (0);
}