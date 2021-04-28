#include "Socket.hpp"
#include "HttpMessage/HttpMessageRequest.hpp"
#include "HttpMessage/HttpMessageResponse.hpp"

#include <string.h>	//	FIXME	나중에 지우기 테스트용 for memset

// #define BUFFER_SIZE 65536
#define BUFFER_SIZE 100
int main()
{
	// Create a socket (IPv4, TCP)
	Socket socket(80, INADDR_ANY); // Listen 작업까지 되어 있는 소켓
	size_t connections;
	int bytesRead = BUFFER_SIZE - 1;
	char buffer[BUFFER_SIZE];
	std::string requested_buff = "";
	while (1)
	{
		bytesRead = BUFFER_SIZE - 1;
		connections = socket.Accept(connections);

		/* 테스트 진행 */
		//	STUB : Read from the connection
		while (bytesRead == BUFFER_SIZE - 1)
		{
			memset(buffer, 0, BUFFER_SIZE);	//	REVIEW : 전체 탐색하는 것들은 성능 개선의 여지가 있음
			bytesRead = read(connections, buffer, BUFFER_SIZE - 1);
			if (bytesRead == -1)
				std::cerr << "Could not read request." << std::endl;
			std::cout << "BytesRead is : " << bytesRead << " buffer is " << std::string(buffer) << "\n";
			requested_buff += std::string(buffer);
		}
		if (bytesRead != -1)
		{
			std::cout << "hello\n";
			//	STUB : HttpMessageRequest
			// test = requested_buffer.c_str();
			HttpMessageRequest	request((char*)requested_buff.c_str());
			request.Parser();
			//	STUB : HttpMessageResponse
			HttpMessageResponse	response(request);
			response.SetMessage();

			int len = response.GetMessage().size();
			int ret = send(connections, response.GetMessage().c_str(), len, 0);
			std::cerr << "read message\n";
		}
		close(connections);
	}
	close(socket.GetFd());
}
