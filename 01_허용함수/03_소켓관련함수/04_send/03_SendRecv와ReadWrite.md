# Send/Recv, Read/Write 의 차이점

- read/write 가 socket 에 대해서 동작할 때는 마지막에 recv/send 를 호출한다.

- recv/send 는 매 I/O 에 대해서 동작할 때는 마지막에 recvmsg/sendmsg 를 호출한다.
