/*
http://cplusplus.com/reference/istream/istream/seekg/?kw=seekg

https://modoocode.com/279

연관된 streambuf 객체의 입력 위치 지정자 값을 설정한다. 
실패 시에 setstate(std::ios_base::failbit) 을 호출한다

처음에 seekg 를 호출하면, eofbit 을 클리어 한다. 그 후에;

입력 위치 지정자 값을 파일의 시작으로부터의 위치인 pos 로 설정한다. 
이는 rdbuf()->pubseeikpos(pos, std::os_base::in) 를 실행한 것과 같다.

입력 위치 지정자를 dir 이 지정한 위치로 부터 off 만큼 떨어진 곳으로 설정한다. 
이는 rdbuf()->pubseekoff(off, dir, std::ios_base::in) 를 실행한 것과 같다.


*/

#include <iostream>
#include <sstream>
#include <string>

int main()
{
	std::string str = "Hello, world";
	std::istringstream in(str);
	std::string word1, word2;

	in >> word1;
	in.seekg(0);
	in >> word2;

	std::cout << "word1 = " << word1 << '\n' << "word2 = " << word2 << '\n';
}