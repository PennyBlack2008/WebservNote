#Send

링크 : https://www.joinc.co.kr/w/man/2/send

소켓으로 데이터를 전송한다.

```
#include <sys/types.h>
#include <sys/socket.h>
```

``ssize_t send(int sockfd, const void* buf, size_t len, int flags)``
매개 변수
- sockfd : 소켓
- buf : 버퍼
- len : 버퍼 크기
- flags : 옵션

MSG_OOB(0x1) : OOB 데이터를 전송한다.
MSG_DONTWAIT(0x80) : 비 봉쇄. 작동하게 하려면 fcntl(2) 로 O_NONBLOCK 설정 필수

man 3 send
