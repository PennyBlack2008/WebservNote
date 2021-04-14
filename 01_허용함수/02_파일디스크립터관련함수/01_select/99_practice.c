#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#define TRUE 1
#define FALSE 0
#define PORT 8888

int main(int argc, char* argv[])
{
	int opt = TRUE; // 이것이 무슨 의미냐?
	int master_socket, addrlen, new_socket, client_socket[30],
		max_clients = 30, activity, i, valread, sd;
	int max_sd;
	struct sockaddr_in address;

	char buffer[1025];

	// set of socket descriptors
	fd_set readfds;

	char *message = "Hello world! \r\n";

	for (i = 0; i < max_clients; i++)
		client_socket[i] = 0;

	if ((master_socket) = socket(AF_INET, SOCK_STREAM, 0) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	// type(sockaddr_in) of socket created
	address.sin_family = AF_INET; // 이게 아마 0이라고 했던 것같아. 아무대나 연결하겠다 라는 뜻으로 배웠던 것같음.
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT ); // 8888

	// bind 를 할 건데 목적: 서버에서 새로 만들어준 socket 과 addr 를 묶어줌.
	// 첫번째는 소켓의 fd 이고, 두 번째에는 addr 이고, 세 번째는 addr 의 사이즈(IPv4 or IPv6 이냐 인것 같음.)
	if (bind(master_socket, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	printf("Listener on port %d \n", PORT);

	// try to specify maximum of 3 pending connections for the master socket
	if (listen(master_socket, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	// accept the incoming connection
	addrlen = sizeof(address);
	puts("Waiting for connections ....");

	while (TRUE)
	{
		// clear the socket set
		FD_ZERO(&readfds);

		// add master socket to set
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;

		// add child sockets to set
		for (i = 0; i < max_clients; i++)
		{
			// socket descriptor
			sd = client_socket[i];

			// if valid socket descriptor then add to read list
			if (sd > 0)
				FD_SET(sd, &readfds);
		}
	}
}