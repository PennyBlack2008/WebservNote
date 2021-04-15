# Accept

##### 헷갈렸지만 해결된 레퍼런스 문구

 Accept를 설명할 때, accept의 첫 인수를 listen socket이라 부르고, accept가 반환하는 값을 연결 socket이라 부른다. 이 두 socket을 구별하는 것 이 중요하다. Server가 평생을 같이 할 하나의 listen socket만을 만드는 것이 정상이다. 그러면 커 널은 accept된 client 연결마다 하나의 연결 socket을 생성한다. Server가 어떤 client에 대한 서비 스를 끝내면 연결 socket은 닫히게 된다.