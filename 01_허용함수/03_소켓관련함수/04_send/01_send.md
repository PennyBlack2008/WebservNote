#Send

링크 : https://www.joinc.co.kr/w/man/2/send

## 소켓으로 데이터를 전송한다.

```
#include <sys/types.h>
#include <sys/socket.h>
```

``ssize_t send(int sockfd, const void* buf, size_t len, int flags)``

## 매개 변수
- sockfd : 소켓
- buf : 버퍼
- len : 버퍼 크기
- flags : 옵션
	- flag 가 0 이면, write 함수로 대체할 수 있다.
	- MSG_DONTROUTE : gateway를 통하지 않고 직접 상대시스템으로 전송
	- MSG_DONTWAIT : non blocking에서 사용하는 옵션으로 전송이 block되면 EAGIN, EWOULDBLOCK 오류로 바로 return 함.
	- MSG_MORE : 더 전송할 데이터가 있음을 설정함.
	- MSG_OOB : out of band(긴급데이터) 데이터를 읽습니다. 주로 X.25에서 접속이 끊겼을 때에 전송되는 데이터 flags의 값이 0이면 일반 데이터를 전송하며, write(sockfd, buf, len)를 호출한 것과 같습니다.

출처: https://www.it-note.kr/125 [IT 개발자 Note]
MSG_OOB(0x1) : OOB 데이터를 전송한다.
MSG_DONTWAIT(0x80) : 비 봉쇄. 작동하게 하려면 fcntl(2) 로 O_NONBLOCK 설정 필수

man 3 send

## Return
	- 0 이상: 실제로 전송된 데이터 량을 반환한다.
	- -1: 오류가 발생했으며, 상세한 오류 내용은 errno 에 저장된다.

## Errno

```
EACCES : AF_UNIX에서 사용하는 것으로 권한이 없음
EAGAIN or EWOULDBLOCK : time out이 발생하였거나 socket에 non-blocking이 설정된 경우
EBADF : sockfd가 유효하지 않는 descriptor
ECONNRESET : peer(상대) 시스템에서 connection이 reset(close)됨.
EDESTADDRREQ : socket이 connection-based socket이 아님
EFAULT : 읽을 데이터를 저장할 buf가 유효하지 않은 메모리인 경우
EINTR : signal이 발생하여 interrupted 된 경우
EINVAL : 파라미터의 값이 유효하지 않은 경우
ENOMEM : 메모리를 사용할 수 없음.
ENOTCONN : connect(2), accept(2)가 호출되지 않은 상태인 경우
ENOTSOCK : sockfd가 socket descriptor가 아닌 일반 파일인 경우
EOPNOTSUPP : flag값이 유효하지 않음 EPIPE : local socket이 shutdown 됨.
```