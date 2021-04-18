# URL, URI 차이점
링크 (https://velog.io/@syoung125/%EA%B0%9C%EB%85%90%EA%B3%B5%EB%B6%80-URI%EB%8A%94-%EB%AC%B4%EC%97%87%EC%9D%B4%EA%B3%A0-URL%EC%9D%80-%EB%AC%B4%EC%97%87%EC%9D%BC%EA%B9%8C)

## URI 란?

서버 리소스 이름(식별자)을 uniform resource identifier(통합 자원 식별자).

## URL 란?

URL 은 리소스의 가장 흔한 형태로, 특정 서버의 한 리소스에 대한 구체적인 위치를 서술한다.

(오늘날 대부분의 uri 는 url 이다.)

### URL 표준 포맷

대부분의 url 스킴의 문법은 일반적으로 9개 부분으로 나뉜다.

``<스킴>://<사용자 이름>:<비밀번호>@<호스트>:<포트>/<경로>;<파라미터>?<질의>#<프레그먼트>``

하지만, 이 중 url 의 가장 중요한 컴포넌트는 스킴, 호스트, 경로이다.

예시) http://www.google.com/images/logo.gif
- ``http://`` : 스킴, 리소스에 접근하기 위해 사용되는 프로토콜(웹 클라이언트가 리소스에

어떻게 접근하는 지 알려줌) (보통 HTTP)

	- 대표적인 스킴 종류/: ftp(file transfer protocol), rtsp(real time streaming protocol, 비디오 서버), smtp(메일) 등

	- ``www.google.com``: 서버의 인터넷 주소(리소스가 어디에 호스팅 되었는 지)
		- => 호스트

	- ``/images/logo.gif``: 웹서버의 리소스(리소스 경로)
		- => 경로