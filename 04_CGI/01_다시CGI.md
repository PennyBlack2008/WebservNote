# CGI

>클라이언트의 요청을 받은 웹서버는 파일 시스템에서 파일 정보를 읽어서 클라이언트에 전송한다. 혹은 외부의 다른 프로그램을 실행해서 그 결과를 클라이언트에 전송하기도 한다. 외부 프로그램으로의 정보 입출력은 CGI 규격을 사용한다.(https://github.com/l-yohai/webserv#readme)

## CGI 는 무엇인가

- 웹서버와 스크립터 사이의 정보교환 인터페이스
- Common Gateway Interface
	- 왜 이렇게 부르는 지는 모르겠다.
		- Gateway 는 서로 다른 네트워크를 통신하게 해주는 것이라고 애매하게 알고 있는 데,
			서버 내부에서 이 과정이 이루어지는 게 아닌가?

## Web Browsing

CGI의 개념을 이해하기 위해 특정 웹 페이지 또는 URL을 탐색하기 위해 하이퍼 링크를 클릭하면 어떤 일이 발생하는지 살펴 보겠습니다.

- 1. 브라우저가 HTTP 웹서버에 연결하여 URL 요구한다. ex) file name
- 2. 웹서버는 URL 을 구문 분석하고, 파일이름을 찾는다.
- 3. 웹서버는 찾은 파일을 브라우저로 다시보낸다.
- 4. 웹브라우저는 웹서버에서 응답을 받아 수신 된 응답에 따라 수신 된 파일을 표시한다.

여기서, 특정 디렉토리에 있는 파일을 요청받을 때 해당 파일을 바로 전송되지 않고, 프로그램으로 실행하여 프로그램에서 생성 된 출력을 브라우저로 표시할 수 있다.

CGI 는 응용프로그램이 웹 서버 및 클라이언트와 상호작용할 수 있도록 하는 표준 프로토콜입니다. 이러한 CGI 프로그램은 Python, PERL, Shell, C, C++ 로 작성될 수 있다.

## CGI Architecture Diagram

![](https://www.tutorialspoint.com/cplusplus/images/cgiarch.gif)

## Web Server Configuration

CGI 를 웹서버에 적용하려면 웹 서버 config 를 설정해줘야한다. HTTP 서버에 의해 실행되는 모든 CGI 프로그램은 미리 구성된 디렉토리가 있다.

이 디렉토리를 CGI 디렉토리라고하며 /var/www/cgi-bin 으로 되어있다. 관례상 CGI 파일은 C++ 실행 가능하지만, 확장자는 .cgi 로한다.

기본적으로 Apache Web Server 는 /var/www/cgi-bin 에서 CGI 프로그램을 실행하도록 구성된다. CGI 스크립트를 실행하기 위해 다른 디렉토리를 지정하려면 httpd.conf 파일에서 다음 섹션을 수정할 수 있습니다.

```
<Directory "/var/www/cgi-bin">
   AllowOverride None
   Options ExecCGI
   Order allow,deny
   Allow from all
</Directory>
 
<Directory "/var/www/cgi-bin">
   Options All
</Directory>
```

여기에서는 Web Server가 성공적으로 실행되고 있으며 Perl 또는 Shell 등과 같은 다른 CGI 프로그램을 실행할 수 있다고 가정합니다.

## First CGI 프로그램

```
#include <iostream>
using namespace std;

int main () {
   cout << "Content-type:text/html\r\n\r\n";
   cout << "<html>\n";
   cout << "<head>\n";
   cout << "<title>Hello World - First CGI Program</title>\n";
   cout << "</head>\n";
   cout << "<body>\n";
   cout << "<h2>Hello World! This is my first CGI program</h2>\n";
   cout << "</body>\n";
   cout << "</html>\n";
   
   return 0;
}
```
다음을 컴파일해서 cplusplus.cgi 로 만드세요. 이 파일은 /var/www/cgi-bin 경로에 두면되고, CGI 프로그램을 실행하기 전에 chmod 755 cplusplus.cgi 를 하세요.

## HTTP header

**Content-type:text/html\r\n\r\n** 줄은 콘텐츠를 이해하기 위해 브라우저로 전송되는 HTTP 헤더이다. 

```
HTTP Field Name: Field Content
 
For Example
Content-type: text/html\r\n\r\n
```
다음은 CGI 에서 자주 사용되는 HTTP header 입니다.

**HTTP Header**

| Sr.No | Header & Description |
| -------- | -------- |
| 1     | Content-type     |
| 2     | Expires: Date     |
| 3     | Location: URL     |
| 4     | Last-modified: Date     |
| 5     | Content-length: N     |
| 6     | Set-Cookie: string     |

## CGI Environment Variables

이 환경변수들은 CGI 프로그램에서 중요합니다.

**CGI Environment Variables**

| Sr.No | Variable Name & Description |
| -------- | -------- |
| 1     | CONTENT_TYPE     |
| 2     | CONTENT_LENGTH     |
| 3(참고용)     | HTTP_COOKIE     |
| 4(참고용)     | HTTP_USER_AGENT     |
| 5     | PATH_INFO     |
| 6     | GATEWAY_INTERFACE     |
| 7     | PATH_TRANSLATED     |
| 8     | QUERY_STRING     |
| 9     | REMOTE_ADDR     |
| 10     | REMOTE_IDENT     |
| 11     | REMOTE_USER     |
| 12     | REQUEST_METHOD     |
| 13     | REQUEST_URI     |
| 14     | SCRIPT_NAME     |
| 15     | SERVER_PORT     |
| 16     | SERVER_PROTOCOL     |
| 17     | SERVER_SOFTWARE     |


- ``1.`` CONTENT_TYPE
	- 콘텐츠의 데이터 유형
- ``2.`` CONTENT_LENGTH
	- POST 요청에만 사용할 수 있는 query 정보의 길이
		- (https://knight76.tistory.com/entry/30021323262)
			- HTTP 1.0 은 길이 제한이 있고 HTTP 1.1 은 길이 제한이 없다.
			- HTTP 1.0 에서 CONTENT_LENGTH 가 없으면, user agent 가 의도와 다르게 처리할 수도 있다.
		- 브라우저에 따라 query 길이를 제한하기도 한다.
			- (https://codezip.tistory.com/741)
- ``3.`` HTTP_COOKIE(참고용)
	- 설정된 쿠키를 key & value 의 쌍으로 반환합니다.
	- 환경 변수가 반환값을 도출해내는 것이 가능한지 모르겠다.
		- (https://tapito.tistory.com/604)
			- 이 환경변수를 사용한 예제들이 있는 데, 이것을 어떻게 만들까?
				- (http://www.deadfire.net/cgic/cgic25.html)
	- 대충 이런 식으로 동작하는 것같다. 내 수준으로 설명하자면 한 줄로 쫘악하고 세미콜론으로 분류. 직접 사용할 땐 ft_split 으로 한방에 해결되는 스트링인 듯
	
	- 예제

		**코드**
		
		```
		char* str;
		str = getenv("HTTP_COOKIE");
		```
	
		**결과**

		```
		Cookie: CUSTOMER=WILE_E_COYOOTE;PART_NUMBER=ROCKET_LAUNCHER_0001
		```

- ``4.`` HTTP_USER_AGENT(참고용)
	- 웹 브라우저의 이름이 될 수도 있고 기기 OS 의 이름이 될 수도 있는 것같다.
		- 환경변수 HTTP_USER_AGENT 를 사용하여 스마트 기기 분류하기
			- (https://roadrunner.tistory.com/174)
	- 환경변수 getenv() 함수로 HTTP_USER_AGENT 환경 변수 사용 예시
		- (https://roadrunner.tistory.com/174)
		
		코드

		```
		$browser_info = getenv(HTTP_USER_AGENT);
		echo("접속자 브라우저 정보 : $browser_info");
		```

		결과

		``접속자 브라우저 정보 : Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1``

	- 접속자 브라우저 정보를 갖고 오는 함수가 있어서 이게 가능한 건가?
- ``5.`` PATH_INFO
	- url 에서 어떤 부분이 PATH_INFO 에 들어오는 지 알 수 있다.
		- (https://blog.daum.net/jchern/13756884)
			- 여기에 PATH_INFO 를 파싱하는 코드가 들어있다. url 로 부터 파싱하는 거 말하는 건지 정확히는 모르겠지만.

- ``6.`` GATEWAY_INTERFACE
	- 서버의 CGI 타입과 버전
		- 예) CGI/revision

- ``7.`` PATH_TRANSLATED
	- PATH_INFO 에 나타난 가상 경로(path) 를 실제의 물리적인 경로로 바뀐 값.


- ``8.`` QUERY_STRING
	- URL 뒤에 추가된 데이터
		- ex) ``http://some.machine/cgi-bin/name.pl?forune
			- 첫 번째 ? 뒤의 모든 데이터를 query string 이라고 한다.
			- CGI 프로그램은 QUERY_STRING 환경변수로 query string 을 얻는다.
	- (http://math.ewha.ac.kr/~jylee/CompMath.html/html.changwon/home5200.html)

- ``9.`` REMOTE_ADDR
	- 클라이언트의 IP 주소

- ``10.`` REMOTE_IDENT
	- 서버가 RFC931 사용자 확인을 지원한다면 서버로부터 발췌된 사용자 이름이 이 환경변수에 저장된다. 이 변수 의 용도는 로그인에만 한정됩니다.

- ``11.``REMOTE_USER
	- 클라이언트의 HOST 이름

- ``12.``REQUEST_METHOD
	- HTML 폼이 사용하는 METHOD, 보통 GET 이나 POST

- ``13.``REQUEST_URI

- ``14.``SCRIPT_NAME

- ``15.``SERVER_PORT
	- 클라이언트 요청을 보내는 포트 번호

- ``16.``SERVER_PROTOCOL
	- 클라이언트 요청이 사용하는 프로토콜. 보통 HTTP 1.0, 1.1
	
- ``17.``SERVER_SOFTWARE





## Encoding & Decoding

- (https://slidesplayer.org/slide/14083569/)
	- 예시 코드 있는 것같다.

## CGI 참고

- (http://dpnm.postech.ac.kr/cs103/lab-material/11/cse103-1120-CGI.html)