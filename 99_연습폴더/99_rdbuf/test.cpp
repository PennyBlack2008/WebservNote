/*
https://www.cplusplus.com/reference/ios/ios/rdbuf/

keyword: redirect

내가 해석한 rdbuf 의 역할은, redirect 이다.
파일 디스크립터로 장난 치는 메소드이다.
streambuf 로 옮겨줌.... rd 의 약자는 무조건 redirect 일 듯
*/

#include <iostream> // std::streambuf, std::cout
#include <fstream> // std::ofstream, ifstream

int main(void)
{
	std::streambuf *psbuf, *backup;
	std::ofstream filestr;
	/* test.txt 의 fd 가 특정되어졌다.*/
	filestr.open("test.txt");

	/* stdout fd 가 backup 으로 백업 되었다. dup 의 과정 */
	backup = std::cout.rdbuf(); // backup cout's streambuf

	/* test.txt 의 fd 가 psbuf 로 백업되었다. dup 의 과정 */
	psbuf = filestr.rdbuf(); // get file's streambuf

	/* dup2(test.txt의fd, stdout의fd) */
	/* 출력 fd 가 test.txt 를 가리킨다 */
	std::cout.rdbuf(psbuf); // assign streambuf to cout

	/* cout 은 test.txt 를 가리킴 */
	std::cout << "This is written to the file";

	/* stdout의fd 를 다시 원래 위치로 */
	/* dup2(backup된 1번 fd, stdout의fd)*/
	std::cout.rdbuf(backup);

	/* test.txt fd 닫기 */
	filestr.close();
	return (0);
}