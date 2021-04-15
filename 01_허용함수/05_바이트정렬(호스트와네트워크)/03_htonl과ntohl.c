/*
바이트 정렬
링크 : https://www.joinc.co.kr/w/man/3/htons
*/
/*
목적: Client 에서 데이터를 보내고 읽어보자.
TIP: read, write 함수 내부에서 엔디안 처리를 따로 알아서 해준다. 그래서 포트번호와 IP 주소만 처리해주면 된다.
*/

#include <netinet/in.h> // htons, htonl, ntohl
#include <unistd.h>
#include <sys/socket.h> // sockaddr_in
#include <stdio.h> // perror
#include <string.h>
#include <stdlib.h> // exit
#include <arpa/inet.h> // inet_addr

int main(int argc, char* argv[])
{
	/* 3. data 만들기 */
	int data = 65;
	
	/* 4. 클라이언트 소켓 만들기 */
	/* IPv4 TCP client socket 완성*/
	int client_sockfd; client_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* 5. 클라이언트 소켓 세팅 */
	struct sockaddr_in clientaddr;
	clientaddr.sin_family = AF_INET; // IPv4
	/* IP, port# 가 domain */
	clientaddr.sin_addr.s_addr = inet_addr("192.168.100.190"); // 주소 inet_addr 이 빅엔디안으로 변환시켜준다.
	clientaddr.sin_port = htons(atoi(argv[1])); // 포트 번호
	int client_len = sizeof(clientaddr);
	
	/* 6. listen, accept 없이 곧 바로 연결! */
	if (connect(client_sockfd, (struct sockaddr*)&clientaddr, client_len) < 0)
	{
		perror("Connect error: ");
		exit(0);
	}

	/* 1. 클라이언트 소켓에 데이터 적기 */
	data = htonl(data); // little -> big endian
	write(client_sockfd, (void*)&data, sizeof(int)); // write 함수 내부에서 엔디안 처리됨

	/* 2. 다시 소켓으로 부터 데이터 받아 읽기 */
	read(client_sockfd, (void*)&data, sizeof(int)); // write 함수 내부에서 엔디안 처리됨
	data = ntohl(data);
	close(client_sockfd);
}