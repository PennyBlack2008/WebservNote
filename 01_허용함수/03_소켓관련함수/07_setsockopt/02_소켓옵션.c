/*
setsockopt 사용해보기

!! 주의 할점. 웹사이트에서는 4배 사이즈로 증가한다고 하는 데, 실제 돌려보면 2배 사이즈로 증가됨 커널의 차이점인 듯 !!
목적 : 소켓의 전송 버퍼를 IPv4 사이즈의 4배 사이즈로 조작해보자.


시나리오.
- 4바이트 소켓을 getsockopt 로 4바이트인 지 확인한다.
- 버퍼 크기를 수동으로 2배로 늘려준다.
- setsocketopt 로 이 늘어난 버퍼크기를 적용시켜준다.
- 커널에서 두배로 늘린 버퍼크기 와 수동으로 두배로 늘려준 버퍼크기로 4배 커진 소켓의 크기를 확인해준다.

Tip : sizeof(IPv4) == sizeof(int) == 4 bytes
*/

#include <sys/socket.h> // socket, setsockopt
#include <stdio.h> // printf

// #include <sys/types.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/stat.h>

int main(int argc, char *argv[])
{
	/* 2. IPv4(4바이트, AF_INET 옵션) 만큼의 소켓을 만든다. */
	int s; s = socket(AF_INET, SOCK_STREAM, 0);

	/* 3. int 사이즈를 상수로 직접 넣어줘도 되지만, 일단 변수에 넣자 */
	int rn = sizeof(int);

	/* 4. 소켓의 버퍼를 확인해보자. + rn 으로 소켓 주소 받기 */
	int bsize = 0; // 주소 초기화
	getsockopt(s, SOL_SOCKET, SO_SNDBUF, &bsize, (socklen_t*)&rn);
	printf("Send buf size : %d\n", bsize);

	/* 5. 버퍼 수동으로 강제로 늘리기 */
	bsize = bsize * 2;

	/* 1. 먼저 이 옵션을 써주고 이 역할은 강제로 늘린 버퍼를 socket 에 적용 */
	setsockopt(s, SOL_SOCKET, SO_SNDBUF, &bsize, (socklen_t)rn);

	/* 
	------------ 커널 조작중 ------------
	6. 커널이 자동으로 버퍼크기를 2배로 늘린다. 
	*/
	
	/* 7. 소켓의 버퍼 사이즈 확인해보기 */
	getsockopt(s, SOL_SOCKET, SO_SNDBUF, &bsize, (socklen_t*)&rn);
	printf("Send buf size : %d\n", bsize);

}

/*
아직 확실히 확인되지 못한 것들.
 소켓의 버퍼를 늘려주면 bandwidth 가 커진다. 이건 확실한 사실이지만, 이 예제가
 그 주제와 매칭이되는 건지는 모르겠다.
*/