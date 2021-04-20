# TCP 3 Way-Handshake & 4 Way-Handshake

(https://mindnet.tistory.com/entry/%EB%84%A4%ED%8A%B8%EC%9B%8C%ED%81%AC-%EC%89%BD%EA%B2%8C-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0-22%ED%8E%B8-TCP-3-WayHandshake-4-WayHandshake)

TCP 는 장치들 사이에 논리적인 접속을 성립하기 위해서 three-way handshake 를 사용한다.
세 가지 악수
(i) Client > Server : TCP SYN
(ii) Server > Client : TCP SYN ACK
(iii) Client > Server : TCP ACK

SYN 은 Synchronized sequence numbers 의 약자. ACK 는 Acknowledgement 의 약자.

## TCP 3 way Handshake 의 역할

![](https://t1.daumcdn.net/cfile/tistory/225A964D52F1BB6917)

### 첫 번째: A 클라이언트가 SYN 을 보내고 SYN/ACK 응답을 기다리는 SYN_SENT 상태
A 클라이언트는 B 서버에 접속을 요청하는 SYN 패킷을 보낸다.

### 두 번째
B 서버는 SYN 요청을 받고 A 클라이언트에게 요청을 수락한다는 ACK 와 SYN flag 가 설정된 패킷을 발송. 다시 클라이언트 A가

ACK 로 응답하기를 기다림. B 서버는 SYN_RECEIVED 상태

### 세 번째
A 클라이언트가 ACK 로 응답을 하고 B 서버는 ESTABLISHED 상태가 된다.

이 때, listen 의 두개의 큐가 있는 대기하는 데, 위의 두 번째 상태에 있는 소켓들의 queue 와 세 번째 상태에 있는 소켓들의 queue 로 이루어져있다.

![](https://www.ibm.com/support/pages/system/files/support/isg/isgtech.nsf/0/821df190232c8ede852580440069c8a5/Content/1.3448.jpg)

## 이 때! backlog 는 이 두 가지 상태에 놓여있는 두 queue 의 합에 대한 최대값을 규정한다.

역사적으로, sample code에서 backlog는 항상 5였다. Busy server도 하루에 몇 백 건의 연결 만 처리했던 1980년대에는 이 값이 적절했다. 그러나 웹의 팽창으로 Busy server는 하루에 수백만 건의 연결을 처리하게 되었기에 이 작은 값은 쓸모가 없어졌다. busy HTTP server는 엄청나게 큰 backlog를 규정해야 하므로 새로운 커널은 이를 지원해야 한다. 요즘 많은 시스 템에서 관리자가 backlog를 위한 최대 값을 수정할 수 있도록 한다.

backlog 설정 시 table 을 보면 된다.