# WebservNote
This is Webserv note. Who cares..

## 보는 순서

### 1. 01_허용함수/02_파일디스크립터관련함수/02_socket/01_소켓프로그래밍
-> 어느정도 이해되었음.
### 2. 01_허용함수/02_파일디스크립터관련함수/01_select/02_MultipleSocket
-> 아직 이해안됬고, practice로 타이핑하면서 이해하려고 하는 데 아직 이거 이해할 능력안되는 듯
### 3. 01_허용함수/05_바이트정렬(호스트와네트워크)/03_htonl과ntohl.c
-> 코드는 어느정도 이해되는 데, 실행을 어떻게 하는 건지 모르겠음.

## 공부해야할 것들 목록
1. 소켓 기본 개념 관련 https://dbehdrhs.tistory.com/83
2. send 함수에서 채팅 & 계산기 C/S 프로그램

## 약간의 팁
1. sockaddr_in 구조체에서 sin_ 이라는 prefix 는 말 그대로 sockaddr_in 의 약어이다.

## 이해 안되는 것
1. server_addr.sin_family = AF_INET // IPv4 <-- 이거는 htons 안 먹이네.. 왜지? 이론상으로는 그렇게 배웠는 데
