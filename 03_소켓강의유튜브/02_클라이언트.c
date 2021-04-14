#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int sockfd;
	int len;
	struct sockaddr_un address; // <sys/un.h>
	int result;
	char ch = 'A';

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	address.sun_family = AF_UNIX; /* local to host (pipes) */
	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr*)&address, len);

	if (result == -1)
	{
		perror("oops: client1");
		exit(1);
	}
	write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf("char from server = %c\n", ch);
	close(sockfd);
	exit(0);
}