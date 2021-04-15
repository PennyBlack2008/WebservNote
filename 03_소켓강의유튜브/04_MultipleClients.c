#include <stdio.h>

while (1)
{
	char ch;

	printf("server waiting\n");
	client_len = sizeof(client_address);
	client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address
	, &client_len);

	if (fork() == 0)
	{
		read(client_sockfd, &ch, 1);
		sleep(5);
		ch++;
		write(client_sockfd, &ch, 1);
		close(client_sockfd);
		exit(0);
	}
	else
		close(client_sockfd);
}