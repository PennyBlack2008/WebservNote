# HTTP 구조 및 핵심 요소
 GET, POST, Request, Response http

## 1. HyperText Transfer Protocol
 TCP/IP 기반.

## 2. HTTP 핵심 요소
### 2-1 HTTP 통신 방식
 (i) Request

 (ii) Response

 특징) Stateless. 상태를 저장하지 않는다. 그래서 여러 요청/응답의 상태를 확인하지 못한다.

 여러 요청과 응답의 진행과정이나 데이터가 필요하면 쿠키와 세션등을 사용한다.

### 2-2 HTTP Request 구조

 - start line
 - headers
 - body

#### 2-2-1. Start line

![](https://media.vlpt.us/images/teddybearjung/post/15d0cc80-18d0-483a-9751-9052afcc1119/A59882AC-BBD9-4DC9-B596-AFEF2C7181C4.jpeg)

예시) GET /search HTTP/1.1

- HTTP Method
	- 해당 request 가 의도한 action 을 정의.
	- HTTP Method 에는 GET, POST, PUT, DELETE, OPTIONS.
	- 주로 GET, POST 가 쓰임

- Request target
	- 해당 request 가 전송되는 목표 uri
	- 예를 들어 /login

- HTTP Version
	- 말 그대로 사용 되는 HTTP 버젼, 1.0, 1.1, 2.0 등이 있다.

#### 2-2-2. Headers

- 해당 request 에 대한 추가 정보를 담고 있는 부분. request 메세지 body 의 총 길이 (Content-Length) 등.

- Key:Value 값으로 되어있다 (: 이 사용됨).
	- key:value
	- Host:google.com => Key = HOST, Value = google.com
	- Header 들도 크게 3부분으로 나뉘지만(general headers, request headers, entity header)

```
Accept: */*
Accept-Encoding: gzip, deflate
Connection: keep-alive
Content-Type: application/json
Content-Length: 257
Host: google.com
User-Agent: HTTPie/0.9.3
```

자주 사용되는 header 정보에는 다음이 있다.

- Host
	- 요청이 전송되는 target 의 host url: 예를 들어, google.com
- User-Agent
	- 요청을 보내는 클라이언트에 대한 정보: 예를 들어, 웹브라우저에 대한 정보.
- Accept
	- 해당 요청이 받을 수 있는 응답(response) 타입
- Connection
	- 해당 요청이 끝난 후에 클라이언트와 서버가 계속해서 네트워크 커넥션을 유지 또는 끊을 것인지 지시하는 부분
- Content-Type
	- 해당 요청이 보내는 메세지 body 의 타입, 예를 들어 JSON 을 보내면 application/json.
- Content-Length
	- 메세지 body 의 길이.

#### 2-2-3. Body

 해당 request 의 실제 메세지/내용.
 
 Body 가 없는 request 도 많다. 예를 들어 GET request 들은 대부분 body 가 없는 경우가 많음.

```
 POST /payment-sync HTTP/1.1

 Accept: application/json
 Accept-Encoding: gzip, deflate
 Connection: keep-alive
 Content-Length: 83
 Content-Type: application/json
 Host: intropython.com
 User-Agent: HTTPie/0.9.3
 {
	"imp_uid": "imp_1234567890",
	"merchant_uid": "order_id_8237352",
	"status": "paid"
 }
```

#### 2-2-4. HTTP Response 구조

Response 도 request 와 마찬가지로 크게 3부분으로 구성되어 있다.
 - Status line
 - Header
 - Body

#### 2-2-5. Status Line

Response 의 상태를 간략하게 나타내주는 부분.

3 부분으로 구성되어 있다.

- HTTP 버전
- Status code : 응답 상태를 나타내는 코드. 숫자로 되어 있는 코드.
- Status text : 응답 상태를 간략하게 설명해주는 부분.

``HTTP/1.1 404 Not Found``

#### 2-2-6. Headers

- Response 의 headers 와 동일하다.
- 다만, response 에서만 사용되는 header 값들이 있다.
- 예를 들어, User-Agent 대신에 Server 헤더가 사용된다.

#### 2-2-7. Body

- Response 의 body 와 일반적으로 동일하다.
- Requset 와 마찬가지로 모든 response 가 body 가 있지는 않다. 데이터를 전송할 필요가 없는 경우 body 가 비어있게 된다.
```
HTTP/1.1 404 Not Found

Connection: close
Content-Length: 1573
Content-Type: text/html; charset=UTF-8
Date: Mon, 20 Aug 2018 07:59:08 GMT

<!DOCTYPE html>
<html lang=en>
	<meta charset=utf-8>
	<meta name=viewport content="initial-scale=1, minimum-scale=1, widht=device-width>
	<title>Error 404 (NotFound)!!1</title>
	<style>
		*{margin:0;padding:0}html,code{font:15px/22px arial, sans-serif}html{background:#fff;color:#222;padding:15px}body{margin:7% auto 0;max-width:390px;min-height:180px;padding:30px 0 15px}* > body{background:url(//www.google.com/images/errors/robot.png) 100% 5px no-repeat;padding-right:205px}p{margin:11px 0 22px;overflow:hidden}ins{color:#777;text-decoration:none}a img{border:0}@media screen and (max-width:772px){body{background:none;margin-top:0;max-width:none;padding-right:0}}#logo{background:url(//www.google.com/images/branding/googlelogo/1x/googlelogo_color_150x54dp.png) no-repeat;margin-left:-5px}@media only screen and (min-resolution:192dpi){#logo{background:url(//www.google.com/images/branding/googlelogo/2x/googlelogo_color_150x54dp.png) no-repeat 0% 0%/100% 100%;-moz-border-image:url(//www.google.com/images/branding/googlelogo/2x/googlelogo_color_150x54dp.png) 0}}@media only screen and (-webkit-min-device-pixel-ratio:2){#logo{background:url(//www.google.com/images/branding/googlelogo/2x/googlelogo_color_150x54dp.png) no-repeat;-webkit-background-size:100% 100%}}#logo{display:inline-block;height:54px;width:150px}
	</style>
	<a href=//www.google.com/><span id=logo aira-label=Google></span></a>
	<p><b>404.</b><ins>That's an error.</ins>
	<p>The requested URL <code>/payment-sync</code> was not found on this server. <ins>That's all we know.</ins>

```

## 3. 자주 쓰이는 HTTP Methods

### 3-1. GET
- 어떤 data 를 서버로부터 받아(GET) 올 때, 사용되는 Method
- 데이터 생성, 수정, 삭제 없이 받아올 때 사용됨.
- 주로 데이터를 받아올 때 사용되기 때문에 request 에 body 를 안 보내는 경우가 많다.

### 3-2. POST
- 데이터를 생성/수정/삭제할 때 주로 사용되는 Method
- 데이터를 생성 및 수정할 때 많이 사용하기 때문에 대부분의 경우 request body 가 포함되서 보내진다.

## 4. 알고 있으면 좋은 HTTP Methods

### OPTIONS
- 주로 요청 uri 에서 사용할 수 있는 Method 를 받아올 때 사용된다.
- 예를 들어, /update uri 에서 어떤 method 를 요청가능한가(GET? POST?) 를 알고 싶으면 먼저 OPTIONS 요청을 사용해서 확인하게 된다.
```
http -v OPTIONS http://example.org

OPTIONS / HTTP/1.1
Accep: */*
Accept-Encoding: gzip, deflate
Connection: keep-alive
Content-Length: 0
Host: example.org
User-Agent: HTTPie/0.9.3

HTTP/1.1 200 OK
Allow: OPTIONS, GET, HEAD, POST
Cache-Control: max-age=604800
Content-Length: 0
Date: Mon, 20 Aug 2018 08:37:45 GMT
Expires: Mon, 27 Aug 2018 08:37:45 GMT
Server: EOS(vny006/0450)
```

### PUT
- POST 와 비슷하다. 데이터를 생성할 때 사용되는 Method
- POST 와 겹치기 때문에 PUT 을 사용하는 곳도 있고 POST 로 통일해서 사용하는 곳도 있는 데, 최근 몇년 사이에 POST 에 밀려서 잘 사용안된다.

### DELETE
- 특정 데이터를 서버에서 삭제 요청을 보낼 때 쓰이는 Method
- PUT 과 마찬가지로 POST 에 밀려서 잘 사용 안되는 추세.

# 5. 자주 쓰이는 HTTP Status Code

## 200 OK
- 가장 자주 보게 되는 status code.
- 문제없이 다 잘 실행되었을 때 보내는 코드.

## 301 Moved Permanetly
- 해당 URI 가 다른 주소로 바뀌었을 때

## 400 Bad Request
- 해당 요청이 잘못된 요청일 때 보내는 코드
- 주로 요청에 포함된 input 값들이 잘못된 값들이 보내졌을 때 사용되는 코드
- 예를 들어, 전화번호를 보내야 되는 데 text 가 보내졌을 때 등등

## 401 Unauthorized
- 유저가 로그인, 회원가입 등등이 필요하다는 것을 나타낼 때

## 403 Forbidden
- 유저가 해당 요청에 대한 권한이 없을 때

## 404 Not Found
- 요청된 uri 가 존재하지 않는다는 뜻

```
http -v google.com/no-such-uri

GET /no-such-uri HTTP/1.1
Accept: */*
Accept-Encoding: gzip, deflate
Connection: keep-alive
Host: google.com
User-Agent: HTTPie/0.9.3

HTTP/1.1 404 Not Found
Content-Length: 1572
Content-Type: text/html; charset=UTF-8
Date: Mon, 20 Aug 2018 08:46:48 GMT
Referrer-Policy: no-referrer
```

## 500 Internal Server Error
- 서버에서 에러가 났을 때 사용되는 코드