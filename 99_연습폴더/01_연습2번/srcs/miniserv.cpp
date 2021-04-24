#include "miniserv.hpp"
#include <arpa/inet.h>

int		setup_server(void)
{
	int					server_fd;
	struct sockaddr_in	address;

	ft_memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(8079);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1; // 소켓을 재사용하려면 희한하게도 1로 설정해야한다. 
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
		printf(" error binding ");
	listen(server_fd, 10);
	return (server_fd);
}

void	accept_request(int server_fd)
{
	int					socket_fd;
	struct sockaddr_in	address;
	unsigned int		addrlen;
	char				buffer[50000];

	socket_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
	ft_memset(buffer, 0, 50000);
	recv(socket_fd, buffer, 50000, 0); // read(socket_fd, buffer, 50000);
	make_header(buffer, "index.html");
	printf("Sending index.html...\n"); // 브라우저로 접속 시 반복해서 실행된다.
	send(socket_fd, buffer, 50000, 0); // write(socket_fd, buffer, 7);
	close(socket_fd);
}

int		main(void)
{
	int		server_fd;

	server_fd = setup_server();
	while (1)
		accept_request(server_fd);

	return (0);
}
