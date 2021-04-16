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

## 4. fd_zero
