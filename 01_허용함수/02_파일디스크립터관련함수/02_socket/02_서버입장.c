#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1; // opt 1 이 의미하는 것은 뭘 까?
	int addrlen = sizeof(address); // address 는 몇 바이트일까?
	char buffer[1024] = {0}; // 무엇을 위한 buffer 인가?
	char *hello = "Hello from server";
	
	/* 1. 서버 소켓 만들기 */
	/* IPv4 의 TCP 소켓을 만들어준다 */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	/* 2. 서버 소켓 옵션선택 */
	/* 재사용할 목적을 지닌 소켓으로 서버 소켓을 세팅해준다 */
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												  &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	/* 주소 체계로서 IPv4 를 사용하는 인터넷망에 접속 */
	address.sin_family = AF_INET;
	/* 서버의 IP주소를 자동으로 찾아서 대입해주는 상수 값 0 이다. */
	address.sin_addr.s_addr = INADDR_ANY;
	/* htons 로 IP 주소와 PORT 번호를 big endian 으로 바꿔줘야한다. */
	address.sin_port = htons( PORT );

	/* 3. 서버 소켓과 주소 바인딩 */
	if (bind(server_fd, (struct sockaddr *)&address, 
								 sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	/* 4. 서버 소켓 queue 에 대기시키는 중 */
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	/* 5. 연결용 소켓 만들고 그 소켓 fd 반환 */
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					   (socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

	/* 요건 뭔지 모르겠다 */
	valread = read( new_socket , buffer, 1024);
	printf("%s\n",buffer );
	send(new_socket , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");
	return 0;
}