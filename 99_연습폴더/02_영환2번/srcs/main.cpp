#include "../base_headers/Socket.hpp"
#include "HttpMessage/HttpMessageRequest.hpp"
#include "HttpMessage/HttpMessageResponse.hpp"

#include <fstream>	//	FIXME	나중에 지우기 테스트용
#include <sstream>	//	FIXME	나중에 지우기 테스트용
#include <string.h>	//	FIXME	나중에 지우기 테스트용

// #define BUFFER_SIZE 65536
#define BUFFER_SIZE 60000

int main()
{
	// Create a socket (IPv4, TCP)
	Socket socket(80, INADDR_ANY); // Listen 작업까지 되어 있는 소켓
	size_t connections;
	// std::string requested_buffer = "";
	std::string requested_buffer = "";
	char* test;

	connections = socket.Accept(connections);

	/* 테스트 진행 */
		//	STUB : Read from the connection
		char buffer[BUFFER_SIZE];	memset(buffer, 0, BUFFER_SIZE);	//	REVIEW : 전체 탐색하는 것들은 성능 개선의 여지가 있음
		// read 에 루프를 걸어준다. while {read != 0 or != -1}
		int bytesRead = read(connections, buffer, BUFFER_SIZE - 1);
		// std::cout << "The message was: " << buffer;

		// requested_buffer = std::string(buffer); // buffer 가 정적해제 되면 안된다.
		// test = (char*)requested_buffer.c_str();
		//	STUB : HttpMessageRequest
		requested_buffer += std::string(buffer);
		// if (requested_buffer.length() != BUFFER_SIZE - 1)
			std::cout << "requested_length : " << requested_buffer.length() << std::endl;
		// HttpMessageRequest	request((char*)requested_buffer.c_str());
		HttpMessageRequest	request((char*)requested_buffer.c_str());
		// std::cout << "BytesRead is : " << bytesRead << " buffer is " << std::string(buffer) << "\n";
		// std::cout << "requested buffer is : " << requested_buffer << "\n";
		request.Parser();

		//	STUB : HttpMessageResponse
		HttpMessageResponse	response(request);
		response.SetMessage();

		//	STUB : Send a message to the connection
		// std::stringstream resp;
		// std::ifstream header("./testcase/header.http");
		// std::ifstream body("./testcase/body.html");

		// resp << header.rdbuf() << "\r\n" << body.rdbuf();

		// std::string response = resp.str();
		int len = response.GetMessage().size();

		// std::cout << "Answer is :\n";
		// std::cout << response << std::endl;

		// 아직 고려안해도된다.
		// std::cout << "Wrote " << len  << " bytes" << '\n';
		int ret = send(connections, response.GetMessage().c_str(), len, 0);
		// std::cout << "Wrote " << len  << " bytes, sent " << ret << '\n';

	// Close the connections
	close(connections);
	close(socket.GetFd());
}
