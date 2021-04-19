# How the web works: HTTP and CGI explained
링크 : https://www.garshol.priv.no/download/text/http-tut.html

## Introduction

 웹 페이지를 송수신하는 데 사용되는 HTTP 프로토콜과 일부 서버 작업 및 스크립팅 기술을 다룹니다.

## Some background

 문서를 읽을 수 있으려면, 문서가 포함된 컴퓨터에서 웹 서버를 실행해야한다. 웹 서버는 브라우저의 요청을 수신한 다음 실행하는 컴퓨터 프로그램입니다.

 그 다음은 브라우저가 서버에 접속하여 서버가 문서를 전달하도록 요청하는 것입니다. 서버는 문서가 포함 된 응답을 제공하고, 브라우저는 이를 사용자에게 표시한다. 서버는 이것이 어떤 종류의 문서인지(HTML, PDF, ZIP 등) 브라우저에 알려주고, 브라우저는 이러한 종류의 문서에 사용하도록 구성된 프로그램과 함께 문서를 표시한다.

 브라우저는 HTML 문서를 직접 표시하고 이미지, Java application, 사운드, 클립 등에 대한 참조가 있고 이를 표시하도록 브라우저가 설정된 경우 해당 문서가 상주하는 서버에서도 이를 요청한다.

## 링크를 클릭하면 일어나는 일

### Step1: URL parsing
 Url 을 파싱해라.
### Step2: Sending the request
 HTTP 를 통해 문서를 검색하기 위해 브라우저는 "GET/request-URI HTTP/version" 요청을 서버에 전송합니다.

 서버는 요청을 수행하고 결과를 반환합니다.

### Step3: The server response
 서버가 HTTP 요청을 받으면 적절한 문서를 찾아서 반환합니다. 특정 형식을 가지려면 HTTP 응답이 필요합니다.

```
HTTP/[VER] [CODE] [TEXT]
Field1: Value1
Field2: Value2

...Document content here...
```
 일반적으로 코드는 다음과 같습니다.

```
HTTP/1.0 200 OK // <-- 1. 이것을 받으면 요청 성공
Server: Netscape-Communications/1.1 // <-- 2. 이것은 선택사항이다. 서버가 Netscape 웹 서버 버전 1.1을 실행한다는 의미
Date: Tuesday, 25-Nov-97 01:22:04 GMT // <-- 3. 서버가 현재 날짜
Last-modified: Thursday, 20-Nov-97 10:44:53 GMT // <-- 4. 문서가 마지막으로 수정된 시기
Content-length: 6372 // <-- 5. 바이트 단위의 문서 크기
Content-type: text/html // <-- 6. 문서의 필드(content type)

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
<HTML>
...followed by document content...
```
다음은 위의 주석 번호에 상응함.

6. content-type 필드는 수신한 문서의 형식을 알리기위해 브라우저에서 사용됨.

HTML 은 "text/html" 로 식별되고 일반 텍스트 "text/plain" 으로 식별되며 GIF 는 "image/gif" 로 식별된다.

여기서 중요한 개념은 브라우저에서 서버가 블랙박스 처럼 작동한다는 것. 즉, 브라우저가 특정 문서를 요청하고 문서를 반환하거나 오류 메시지를 반환한다.

### 서버가 하는 일
 서버가 설정되면 디스크의 어딘가에 루트디렉토리로 각 디렉토리에 대한 기본 파일 이름(예: index.html) 이 있도록 구성한다.

 즉, http://www.doamin.tld/ 를 입력하면 서버루트 바로 아래의 디렉토리에서 .html 파일을 얻을 수 있다.

 RFC 2068은 여러 영역에서 HTTP / 1.0을 확장하고 개선하는 HTTP / 1.1을 설명합니다. 이를 지원하는 브라우저는 거의 없지만 (MSIE 4.0은 작성자에게 알려진 유일한 브라우저 임) 서버는이를 지원하기 시작했습니다.

 주요 차이점은 HTTP를 통해 온라인으로 문서를 작성하기위한 HTTP / 1.1의 일부 확장과 클라이언트가 다음 요청을 위해 다시 설정할 필요가 없도록 요청 후 연결을 열어 두도록 요청하는 기능입니다. 이렇게하면 여러 요청을 빠르게 발행해야하는 경우 대기 및 서버로드를 줄일 수 있습니다.

## 클라이언트가 보낸 request

### request 폼
폼
```
[METH] [REQUEST-URI] HTTP/[VER]
[fieldname1]: [field-value1]
[fieldname2]: [field-value2]

[request body, if any]

```
실제 예시
```
GET / HTTP/1.0
User-Agent: Mozilla/3.0 (compatible; Opera/3.0; Windows 95/NT4)
Accept: */*
Host: birk105.studby.uio.no:81
```

첫 번째) ``METH``

 가장 일반적인 유형은 GET. "이 문서 보내기" 를 의미한다. GET document_path HTTP/version 과 같음.

 예를 들어, http://www.yahoo.com/ 의 경우 document path 는 "/" 이고, "http://wwww.w3.org/Talks/General.html" 의 경우 "/Talks/General.html" 입니다.

 GET 과 함께 쓸 수 있는 헤더의 fields 는

 - User-Agent
	- 사용자 에이전트의 응용 프로그램, 운영 체제, 공급 업체 및 / 또는 버전을 식별 할 수 있도록하는 특성 문자열입니다.
 - Referer
	- 사용자가 어디에서 왔는지 서버에 알려주며, 이는 누가 페이지에 링크했는지 기록하고 추적하는 데 매우 유용합니다.
 - If-Modified-Since
	- 지정된 날짜 이후에 수정 된 경우에만 200 상태로 요청 된 리소스를 다시 보낸다. 그렇지 않을 경우 304 코드.
 - From
	- User-Agent 를 제어하는 관리자의 인터넷 이메일 주소가 포함됨.
 - Authorization
	- HTTP Authorization 요청 헤더에는 User-Agent 를 인증하기 위한 자격증명이 포함되어 있음.

이다.

### HEAD: checking documents

 실제로 문서를 다운로드 하지 않고 특정 문서에 대해 서버에서 반환된 헤더를 보고 싶을 때, HEAD 를 사용한다.

 HEAD 는 GET 과 똑같이 작동하는 것처럼 보이지만, 서버가 문서 내용이 아닌 헤더만 반환한다.

### Playing web browser

 실제로 웹 브라우저를 직접 재생하고 웹 서버에 직접 HTTP 요청 작성할 수 있다. 다음과 같이 포트 80으로 텔넷하고 요청을 작성하고 Enter 키를 두번 눌러라.

```
larsga - tyrfing>telnet www.w3.org 80
Trying 18.23.0.23...
Connected to www.w3.org.
Escape character is '^]'.
HEAD / HTTP/1.0

HTTP/1.1 200 OK
Date: Tue, 17 Feb 1998 22:24:53 GMT
Server: Apache/1.2.5
Last-Modified: Wed, 11 Feb 1998 18:22:22 GMT
ETag: "2c3136-23c1-34e1ec5e"
Content-Length: 9153
Accept-Ranges: bytes
Connection: close
Content-Type: text/html; charset=ISO-8859-1

Connection closed by foreign host.
larsga - tyrfing>
```

### 서버로 부터 response 를 받으면

#### Outline

```
HTTP/1.0 code text
Field1: Value1
Field2: Value2
```

#### The status codes

##### 1xx: Informational

 1xx 는 정해진 것이 없다. 사용자가 특정 목적을 위해 정의하면 된다.

##### 2xx: Successful

 - 200 OK
	- 클라이언트가 원하는 데로 서버가 request 를 성공했다는 의미
 - Others
	- 나머지 2xx 상태 코드는 주로 스크립트 처리를위한 것이며 자주 사용되지 않습니다.

##### 3xx: Redirection

 - 301 Moved permanetly
	- 클라이언트가 요청한 리소스는 다른 곳에 있으며 클라이언트가 리소스를 가져와야합니다.
 - 302 Moved temporarily
	- 301 과 같음. 하지만 url 로 일시적으로 이동했음을 나타낸다.
 - 304 Not modified
	- 요청 된 리소스를 다시 전송할 필요가 없음을 나타낸다.
	- GET 또는 HEAD 요청과 같이 요청 메서드가 안전할 때
	- If-None-Match 또는 If-Modified-Since 헤더를 사용하는 경우

##### 4xx: Client error

 클라이언트가 잘못했을 때의 에러이다. 주로 요청하면 안되는 것을 요청했을 때 난다.
 - 400 Bad request
	- 클라이언트의 요청이 syntax
 - 401 Unauthorized
	- 클라이언트가 리소스에 액세스 할 수 없음을 의미합니다.
	- 클라이언트가 인증 헤더로 재시도하면 변경될 수 있습니다.
 - 403 Forbidden
	- 서버가 요청을 이해했지만, 승인을 거부했음을 나타낸다.
	- 401 과 비슷하지만 권한을 재 인증해도 액세스는 영구적으로 금지된다.
 - 404 Not found
	- 서버가 요청된 리소스를 찾을 수 없음
	- 이 코드는 리소스가 일시적 또는 영구적으로 누락되었는 지 알려주지 않음.
	- 리소스가 영구적으로 제거되면 404 대신 410을 사용해야한다.

##### 5xx: Server error

 - 500 Internal server error
	- 서버에서 뭔가 잘못되었을 때
 - 501 Not implemented
	- 서버가 요청을 수행하는 데 필요한 기능을 지원하지 않음
	- 이 상태는 Retry-After 헤더를 전송하여 요청자에게 언제 기능이 지원되는 지 다시 확인할 시기를 알려준다.
 - 503 Service unavailable
	- 서버가 요청을 처리할 준비가 되지 않았을 때
	- 서버 다운, 서버 과부화
	- Retry-After 헤더는 가능하면 서비스 복구에 대한 예상 시간을 포함해야한다.

#### Response header fields

 - Location
	- 위치 응답 헤더는 페이지를 리디렉션할 url 을 나타낸다. 3xx(리디렉션) 또는 201(생성됨) 상태 응답으로 제공되는 경우에만 의미제공
	- ex) Location: /index.html
 - Server
	- 서버 헤더는 요청을 처리한 원본 서버, 즉 응답을 생성한 서버에서 사용하는 소프트웨어를 설명한다.
	- ex) Server: Apache/2.4.1 (Unix)
 - Content-Length
	- 리소스의 크기(byte)를 제공합니다.
 - Content-type
	- 리소스의 파일 형식을 설명한다.
 - Content-encoding
	- 리소스가 어떤 방식으로든 코딩되었으며 사용하기 전에 디코딩해야함을 의미한다.
 - Expires
	- 이 필드는 알려진 시간에 업데이트 되는 데이터에 대해 설정할 수 있다.
	- 브라우저가 지정된 날짜 이후에 리소스를 캐싱하지 못하도록 방지하는 데 사용된다.
 - Last-modified
	- 리소스가 마지막으로 수정된 시기를 브라우저에게 알려준다.

### Caching: 서버와 클라이언트 사이의 에이전트

 캐싱의 의미는 어떤 것을 나중에 유용하게 사용하기위해 저장한다는 뜻(원격으로 서버에 요청하지 않고 하드디스크에서 파일을 검색)

#### The browser cache

 새 페이지를 방문하면 캐시에 저장되고 캐시가 가득차면 브라우저가 곧 다시 방문할 가능성이 없다고 간주하는 일부 문서는

 공간을 확보하기 위해 삭제된다. 정확히 캐시가 작동하는 방식은 브라우저마다 다르다.

#### Proxy cahces

 다수의 사용자가 서버에 접속했을 때, 클라이언트와 서버의 중간 매개자인 프록시가 서버로부터 리소스를 가져오지 않고 프록시가 가지고 있는 캐시를 이용해 클라이언트에게 뿌리는 방식.

 네트워크 트래픽을 상당히 줄일 수 있다.

### 서버측의 프로그래밍

#### 이건 무엇이고 왜 하지?

 당신이 웹 페이지의 링크를 클릭하면 당신의 웹 브라우저는 HTTP request 를 목적 서버에 전달한다.

 웹 서버는 클라이언트 요청이 오길 기다리고, 요청이 도착하면 작업을 진행하여 웹 브라우저에 HTTP 응답 메시지를 보냅니다.

 그 응답은 요청이 성공 또는 실패를 지시하는 상태라인을 포함한다.(ex. HTTP/1.1 200 OK)

##### 정적 웹사이트

![](https://media.prod.mdn.mozit.cloud/attachments/2016/09/04/13841/3320b8e8984e7ab1fa72124df678693c/Basic%20Static%20App%20Server.png)

사용자가 페이지를 탐색하거나 브라우저가 지정된 URL 에 HTTP "GET" 요청을 보낼 때 서버는 파일 시스템에서 요청한 문서를 검색하고 문서와  success status(보통 200 OK) 를 포함한 HTTP 응답을 반환한다. 만약 어떠한 이유 때문에 파일을 검색하면 error status 가 반환됩니다.

##### 동적 웹사이트

![](https://media.prod.mdn.mozit.cloud/attachments/2016/09/04/13839/887e50af70deb1a23a9047c9b7b050e3/Web%20Application%20with%20HTML%20and%20Steps.png)

브라우저에서 실행되는 코드는 client-side code 라고 한다.

- Client-side code
	- 랜더링 된 웹페이지의 모양과 행동을 개선
	- UI 구성 요소 선택 및 스타일 지정, 레이아웃 만들기, 탐색, 양식 유효성 검사
	- HTML, CSS, JavaScript

- Server-side code
	- 브라우저의 요청에 대한 응답으로 어떤 컨텐츠를 반환하는 지 선택하는 것을 포함.
	- 제출 된 데이터 및 요청의 유효성 검사, 데이터 저장 및 검색을 위한 데이터베이스 사용, 올바른 데이터 전송
	- PHP, Python, Ruby, C#

### CGI

 Common Gateway Interface 는 웹서버와 서버 측 프로그램이 상호 작용하는 방법입니다.

### Other techniques

C/C++ 로 API 자체를 프로그래밍하면 프로그래밍 오류가 전체 서버를 충돌시킬 수 있다. 서버 API 프로그래밍의 주요 장점은 요청이 도착하면 프로그램이 필요한 데이터와 함께 이미 메모리에 로드되기 때문에 훨씬 빠르다. 일부 서버는 충돌 방지언어로 스크립팅을 허용한다.
또한, 다양한 웹 서버를 위한 스크립팅 언어 기술로는 ASP, MetaHTML, PHP3 이 있다.

### Submitting forms

 폼이란 사용자의 데이터를 서버에 전송하는 방법. 일반적으로 아래와 같은 작업을 하기 위해서는 폼을 이용한다.
 서버 측 프로그램이 웹 서버와 통신하는 가장 일반적인 방법은 HTML 이다. 사용자가 양식을 작성하고 제출 버튼을 누르면 데이터가 서버에 제출된다.
 - 로그인을 위해서 아이디/비밀번호를 입력할 때
 - 회원가입을 하기위해서 개인정보를 입력할 때
 - 블로그나 게시판에 글을 작성하거나 파일을 전송할 때

### GET 과 POST 의 차이점

(i) GET

- url 에 정보가 담겨서 전송한다.
- 전송할 수 있는 정보의 길이가 제한되어 있다.
- 퍼머링크로 사용될 수 있다. -> 정보를 식별하는 고유한 식별자(고유한 주소체계)

![](https://t1.daumcdn.net/cfile/tistory/241EDE34549590E915)

- url 상에 파라미터를 표현할 때는 '?' 앞뒤로 구분하여 앞에 것은 url 뒤의 것은 파라미터이다.
- 각각의 파라미터는 '&'로 구분하여 nickname 과 job 이라는 두개의 파라미터가 온 것을 알 수 있다.
- '=' 을 이용하여 파라미터와 파라미터의 값을 구분한다.

![](https://t1.daumcdn.net/cfile/tistory/226276385495911106)


(ii) POST

![](https://t1.daumcdn.net/cfile/tistory/237C653A5495913A2B)

- header 의 body 에 담겨서 전송된다.
- URL 상에 전달한 정보가 표시되지 않는다.
- 전송할 수 있는 데이터의 길이 제한이 없다.
- 퍼머링크로 사용할 수 없다.
- 서버 쪽에 어떤 작업을 명령할 때 사용한다.(데이터의 기록, 삭제, 수정 등)

## More details

### Content negotiation
 잘 모르겠음. 요약 불가.

### Cookies
 잘 모르겠음. 요약 불가.

### Server logs
 잘 모르겠음. 요약 불가.

### A sample HTTP client
 클라이언트.c 에서 많이 연습했던 코드가 나온다.

### Authentication
 사용자가 자신의 신원을 확인할 수 없는 경우 특정 url 에 대한 액세스를 허용하지 않도록 서버를 설정할 수 있습니다.

### Server-side HTML extensions

 Roxen 및 Meta HTML 서버와 같은 일부 서버에서는 사용자가 HTML 파일에 비 HTML 명령을 포함할 수 있습니다. 이러한 명령은 파일이 요청될 대 처리되고 클라이언트에 전송되는 HTML 을 생성합니다. 이것은 페이지 내용을 조정하거나 그것으로부터 내용을 전달하기위해 데이터 베이스에 접근하는 데 사용될 수 있습니다.

### Authoring/maintainance: HTTP extensions for this

 무엇을 말하려고 하는 지 모르겟음. 그런데 PUT, DELETE 에 대해서 말하려고 하는 것같음.

PUT
 - PUT 은 주어진 url 아래의 서버에 새 리소스를 업로드합니다. 정확히 서버에서 일어나는 일은 HTTP/1.1 사야에 정의되어 있지 않지만, Netscape composer 와 같은 저작 프로그램은 PUT 을 사용하여 파일을 웹서버에 업로드하고 거기에 저장합니다. PUT 요청은 캐시되지 않아야합니다.

DELETE
 - DELETE 메서드는 url 로 식별된 리소스를 삭제하도록 서버에 요청합니다. UNIX 시스템에서는 서버가 파일 시스템에서 파일을 삭제할 수 없는 경우 실패 할 수 있습니다.

### META HTTP-EQUIV

 Expires 헤더 필드 또는 특정 파일에 대해 설정할 수 있는 다른 헤더 필드가 있습니다. 그 문제를 해결할 방법이 HTML 에는 HTTP 헤더 필드를 설정하는 데 사용할 수 있는 META 라는 요소가 있습니다.

``<META HTTP-EQUIV="header field name" CONTENT="field value">``

### The Host header field
 무슨 말인지 해석이 안됨. 그런데, 여기서 말하는 웹 호텔의 개념이

 "하나의 물리적 시스템이 여러 다른 서버처럼 보이게 제공하는 것" 이다.

 예를 들어, ``http://www.foo.com``, ``http://www.bar.com`` 및

 ``http://www.baz.com`` 은 모두 동일한 웹 서버에서 제공될 수 있다.

 그래도 사용자는 각각의 다른 url 로 이동하여 다른 페이지를 보게 됩니다.

 이 웹 호텔을 가능하게 하려면, 사용자가 http://www.bar.com 을 요청하면,

 웹 서버는 "호스트: www.bar.com" 으로 설정된 헤더를 수신하므로 어떤 톱 페이지를

 전달할 지 알 수 있습니다. 일반적으로 서로 다른 가상 서버에 대해 별도의 로그를 생성합니다.

## 자주있는 공통된 질문들

### Can I prevent people from seeing my HTML source?

아니다.

### Can I prevent people from stealing my images?

 아니다.

### Files in format X are not displayed correctly, why not?

 일부 형식의 경우 다소 일반적인 문제입니다.

### How can i pass a parameter to a web page?

 웹 페이지가 일반 HTML 파일인 경우 잊어버립시오. HTML 파일이 표시되고 더 이상 작업이 수행되지 않으므로 매개 변수 개념이 적용되지 않습니다. 할 수 있는 일은 문서의 다른 부분에서 설명하는 방식으로 서버 측 스크립팅을 사용하는 것입니다.

## How can i prevent browsers from caching my page/script

 Expiration 헤더가 과거의 날짜/시간으로 설정된 경우, 요청의 출력이 캐시되지 않습니다.
 (HTTP 는 브라우저가 브라우저 기록에 결과를 유지하도록 요구하므로 캐시되지 않은 페이지로 돌아가도
 새로운 요청이 발생하지 않습니다.)

 만료 시간은 서버 스크립트를 사용하거나 서버를 올바르게 구성하여 설정할 수 있다.

## Should I include a slash (/) at the end of my URLs?
 뭘 말하려는 지 모르겠다.