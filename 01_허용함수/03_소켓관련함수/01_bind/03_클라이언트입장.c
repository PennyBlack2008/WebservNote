#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> // sockaddr_in
#include <string.h>
#include <stdio.h>

#define BUFF_SIZE 1024

int main(int argc, char* argv[])
{
	/* 2. client 소켓 만들기 */
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);

	/* 3. binding 작업을 하자 */
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (-1 == connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
	{
		printf("접속 실패\n");
		exit(1);
	}

	/* 1. 우리는 write, read 를 하기 위해서 클라이언트 c 파일을 짠다. */
	char buff[BUFF_SIZE + 5];
	write(client_socket, argv[1], strlen(argv[1]) + 1); // nul 문자 포함 전송 중요!!
	read(client_socket, buff, BUFF_SIZE);
	printf("%s\n", buff);
	close(client_socket);

	return (0);
}