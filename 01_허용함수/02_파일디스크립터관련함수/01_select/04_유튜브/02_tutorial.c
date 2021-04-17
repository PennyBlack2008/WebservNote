/*
select 함수가 필요할 때
fds 가 가리키는 파일이 바뀌는 것을 감지해서 그 때마다 코드가 실행된다.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
	int fd = 0;
	char buf[11];
	int ret, sret;

	fd_set readfds;
	struct timeval timeout;
	while (1)
	{
		FD_ZERO(&readfds); // bzero
		FD_SET(fd, &readfds); // fd set

		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		sret = select(8, &readfds, NULL, NULL, &timeout);

		if (sret == 0)
		{
			printf("sret = %d\n", sret);
			printf("  timeout\n");
		}
		else
		{
			memset((void*)buf, 0, 11);
			ret = read(fd, (void*)buf, 10);
			printf("ret = %d\n", ret);

			if (ret != -1)
			{
				printf(" buf = %s\n", buf);
			}
		}
	}
	return (0);
}