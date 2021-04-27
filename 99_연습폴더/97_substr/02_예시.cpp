#include <iostream>
#include <string>
#include <cstddef>

int main(void)
{
	std::string str = "We think in generalities, but we live in details.";
	std::string str2 = str.substr(3, 5); // "think"
	std::size_t pos = str.find("live"); // live 가 있는 포지션
	std::string str3 = str.substr(pos); // 포지션 부터 string을 substr 으로 가져온다.
	std::cout << str2 << ' ' << str3 << '\n';

	std::string str4 = "abcdef.ghijk";
	str4 = str4.substr(str4.rfind(".") + 1, str4.size() - str4.rfind("."));
	std::cout << str4 <<'\n';

	return 0;
}