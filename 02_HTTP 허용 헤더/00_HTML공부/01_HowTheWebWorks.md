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
 - 503 Service unavailable