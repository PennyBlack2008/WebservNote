# fd_set, FD_SET, FD_ZERO 에 대하여
링크 (http://blog.naver.com/PostView.nhn?blogId=tipsware&logNo=220810795410)

fd_set

## 1. FD
 파일 디스크립터, 4 bytes. FD 1024 개 -> 4Kbytes

## 2. FD 효과적으로 저장
 0 번 파일 디스크립터 저장할 때는, 마지막 bit 를 1로 바꿔주고
 1 번 파일 디스크립터 저장할 때는 마지막에서 첫번째 bit 를 1로 바꿔준다.
 int data[2] 의 크기에서 해당 bit 를 1로 만들어주는 방식으로 저장.

 32 bit computer 는 fd 를 int data[2]; 로 저장 (Mac은 4바이트)
  -> fds_bits 의 크기(128 bytes)

 ## 3. fd_set
 - __FD_SETSIZE
 	- 상수 : 1024

 - __fd_mask
	- 4 bytes 의 type

 - __NFDBITS
	- __fd_mask 가 8 개. 32 bytes.

## 4. FD_ZERO
 fd_set 으로 선언된 변수를 초기화할 때 사용

## 5. FD_SET
 파일 디스크립터를 세팅해주는 방식은 비트 "|" 연산을 통해 해당 bit 의 값을 1로 바꿔준다.

## 6. FD_CLR
 해당 파일 디스크립터를 "&= ~(1 << (d%32))" 연산을 통해 해당 bit 의 값을 0으로 바꿔준다.

## 7. FD_ISSET
 fd_set 안에서 해당 파일 디스크립터가 1인지 확인해주고 1이면 1을 반환, 아니면 0