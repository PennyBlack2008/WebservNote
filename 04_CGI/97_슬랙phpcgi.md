## 왜 PHP 가 cgi 역할을 하게 되는 가?

98_슬랙phpcgi.md 에서 두개의 포인트가 있다.

- command line 의 첫 번째 인자를 열고 파일을 실행한다.
	- 이건 사실이다. 이게 shebangs 가 작동하는 방식이다.
		- shebangs 이 뭐냐면, ``a file script.sh beginning with #!/bin/sh is magically transformed to ["/bin/sh", "script.sh"]``
		- 뒤에 더 보안 상 좋다고 말하는 것같음.
	- PHP 인터프리터를 웹 서버의 문서 루트 아래에 놓은 다음에 이를 사용하여 최종 사용자가 지정한 PATH_INFO 환경 변수를 사용하여 PHP 스크립트를 로드하면 PHP 가 모든 문서를 충실하게 제공한다.
	- 이해하지 못한다면 (저도 마찬가지 임) 일부 시스템 관리자가 정직하게 다음 URL이 작동하기를 원한다는 의미입니다.
		- ``http://yourhost/cgi-bin/php-cgi/var/www/yourhost-root/scripts/mything.php``
		- / var / www / cgi-bin에 셸을 넣은 다음 브라우저 (최종 사용자가 원하는대로 할 수 있음)에 URL의 일부로 셸 스크립트에 대한 경로를 전달하도록 요청하는 것은 유사합니다.