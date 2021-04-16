/*
select 함수가 필요할 때
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd = 0;
	char buf[11];
	int ret;

	fd = 0;
	while (1)
	{
		memset((void*)buf, 0, 11);
		ret = read(fd, (void*)buf, 10);
		printf("ret = %d\n", ret);

		if (ret != -1)
		{
			printf(" buf = %s\n", buf);
		}
	}
	return (0);
}