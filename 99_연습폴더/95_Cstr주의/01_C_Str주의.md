# C_str 을 string class 로, 또 그것을 C_str 로 바꿀 때 생긴 문제점

webserver 소켓 문제를 해결하려다가 알 수 없는 난관에 부딛혔고 정상작동과 비정상작동을 비교하다가

결국 C 문자열을 string 으로 바꾸고 그것을 다시 C 문자열로 바꾸는 방법이 잘 못되었다는 것을 파악했다.

**코 드**
```
int bytesRead = read(connections, buffer, BUFFER_SIZE - 1);
// std::cout << "The message was: " << buffer;

requested_buffer += std::string(buffer);
//	STUB : HttpMessageRequest
HttpMessageRequest	request((char*)(requested_buffer.c_str()));
request.Parser();

//	STUB : HttpMessageResponse
HttpMessageResponse	response(request);
```

https://jayy-h.tistory.com/5 <----- 별 도움 안됨. 예시가 틀렸음.
