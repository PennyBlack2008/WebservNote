# bind 소켓에 IP 주소와 포트 번호 지정
 링크 (http://forum.falinux.com/zbxe/index.php?document_srl=430926&mid=C_LIB)

#### bind 는 소켓에 IP 와 포트 번호를 지정해준다.

헤더 : <sys/types.h>, <sys/socket.h>

``int bind(int sockfd, struct sockaddr* myaddr, socklen_t addrlen);``

##### sockfd: 소켓
##### myaddr: AF_INET(IPv4), struct sockaddr_in 으로 사용
##### addrlen: myaddr 의 길이

## 전체적인 개요 : 서버와 클라이언트
![](http://forum.falinux.com/_lectimages/054%20tcp_prog/tcp_prog_000.gif)

### 서버의 개요
![](http://forum.falinux.com/_lectimages/054%20tcp_prog/tcp_prog_001.gif)

#### 첫 번째) 소켓을 만든다.

**<span style="color:#33FF52"> 두 번째) bind 로 socket 주소와 port 를 할당 </span>**

sockaddr_in 구조체 이용하여 socket 에 주소와 port 를 할당
```
struct sockaddr_in server_addr;
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET // IPv4 <-- 이거는 htons 안 먹이네.. 왜지? 이론상으로는 그렇게 배웠는 데
server_addr.sin_port = htons(4000); // 사용할 port 4000
server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 32bit IPv4 주소

if (-1 == bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
{
	printf("bind() 실행 에러\n");
	exit(1);
}
```
htonl(INADDR_ANY) 는 아무 주소나 자동으로 할당되게끔함. 상수 0과 동일

#### 세 번째) litsen() 함수로 클라이언트 접속 요청을 확인한다.

```
if (-1 == listen(server_socket, 5))
{
	printf("대기 상태 모드 설정 실패\n");
	exit(1);
}
```

#### 네 번째) 서버가 클라이언트 접속 요청을 허락함(accept)

1. accept 후, 서버의 커널이 자동으로 client 소켓 생성
2. client socket 정보를 구하기 위해 변수 선언.

```
int client_addr_size;
client_addr_size = sizeof(client_addr);
```
3. accept 후, 에러 없으면 커널이 생성한 client socket 을 반환
```
client_socket = accpet(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
if (-1 == client_socket)
{
	printf("클라이언트 연결 수락 실패\n");
	exit(1);
}
```

3.5 이제 client socket 설정 완료하여 이 socket 으로 read, write 함수를 사용하여 자료를 송수신할 수 있다.

#### 다섯 번째) read & write

##### 전송되는 자료 읽기
```
read(client_socket, buff_rcv, BUFF_SIZE);
- 클라이언트에서 전송된 자료를 읽는다.
- 소켓에 자료가 없으면 있을 때까지 대기한다.
```
##### 클라언트로 전송하기

1. 수신된 데이터의 길이를 구하여 전송 데이터를 준비
```
sprint(buff_snd, "%d : %s", strlen(buff_rcv), buff_rcv);
```
2. write 를 이용하여 client 로 자료를 송신
```
write(client_socket, buff_snd, strlen(buff_snd) + 1); // +1 은 nul 문자
```
3. 작업 후 close 로 client socket 소멸
```
close(client_socket);
```

### 클라이언트 개요
![](http://forum.falinux.com/_lectimages/054%20tcp_prog/tcp_prog_002.gif)

#### 첫 번째) 소켓을 만든다.
```
int client_socket = socket(AF_INET,SOCK_STREAM, 0);
if (-1 == client_socket)
{
	printf("socket 생성 실패\n");
	exit(1);
}
```

#### 두 번째) connet 을 이용하여 서버로 접속을 시도합니다.
1. 주소 정보에 서버의 주소와 포트번호를 지정한다.
2. 서버와의 연결을 시도한다.
3. 주소는 localhost 로 사용했습니다.
```
struct sockaddr_in server_addr;
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(4000); // little endian -> big endian
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 서버의 주소
if (-1 == connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
{
	printf("접속 실패\n");
	exit(1);
}
```
4. 접속에 성공하면 데이터를 전송합니다.
``write(client_socket, argv[1], strlen(argv[1]) + 1); // +1 : NULL 까지 포함해서 전송``

5. 자료를 수신하고 화면에 출력
``read(client_socket, buff, BUFF_SIZE); printf("%s\n", buff); ``

6. socket 을 소멸하여 통신 작업을 완료합니다.
``close(client_socket);``