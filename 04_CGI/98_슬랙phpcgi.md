뇌피셜로 이해한 자투리모음 (not certified)

- php cgi

- php(binary), cgi binary, Apache, cgi wrapper, chroot, setuid

- cgi-bin directory

- 보안 문제 때문에 cgi-bin 으로 interpreter(php binary) 를 옮겨라

- 시스템 파일 엑세스의 url (?) 뒤의 쿼리 정보는 CGI 인터페이스에서 인터프리터에 명령줄 인수로 전달된다.

- interpreter 의 의미?
	- 특징: binary
	- command line 의 첫 번째 인자를 열고 파일을 실행한다.
	- CGI binary 로 호출되면, php 인터프리터는 해석을 거부한다.
	- http://my.host/cgi-bin/php/secret/doc.html 에서 
		- /secret/doc.html 가 CGI 프로그램에서 열고 해석할 파일의 이름이다.
	- Apache:Action(아마도 nginx 설정도 같을 듯?)이 http://my.host/secret/script.php 와 같은 문서에 대한 요청을 PHP 인터프리터로 리디렉션하는 데 사용됨

		- 아마도 이런 식으로?

			Enable PHP

			Uncomment the following lines in configuration file /etc/nginx/sites-available/default

			location ~ \.php$ {
				fastcgi_split_path_info ^(.+\.php)(/.+)$;
				# NOTE: You should have "cgi.fix_pathinfo = 0;" in php.ini

			#   # With php5-cgi alone:
			#   fastcgi_pass 127.0.0.1:9000;
				# With php5-fpm:
				fastcgi_pass unix:/var/run/php5-fpm.sock;
				fastcgi_index index.php;
				include fastcgi_params;
			}

	- /secret/doc.html은 일반적으로 CGI 프로그램에서 열고 해석 할 파일의 이름을 지정하는 데 사용됩니다.
	- 이 설정을 통해 웹 서버는 먼저 / secret 디렉토리에 대한 액세스 권한을 확인한 후 리디렉션 된 요청 http://my.host/cgi-bin/php/secret/script.php를 생성합니다.
	- 불행히도 요청이 원래이 양식으로 제공된 경우 웹 서버에서 /secret/script.php 파일에 대한 액세스 확인을 수행하지 않고 / cgi-bin / php 파일에 대해서만 액세스 확인을 수행합니다.
		- 이렇게하면 / cgi-bin / php에 액세스 할 수있는 모든 사용자가 웹 서버의 보호 된 문서에 액세스 할 수 있습니다.
		- PHP에서 서버 문서 트리에 액세스 제한이있는 디렉토리가있는 경우 런타임 구성 지시문 cgi.force_redirect, doc_root 및 user_dir을 사용하여이 공격을 방지 할 수 있습니다. 다양한 조합에 대한 전체 설명은 아래를 참조하십시오.
			- 그 아래에는 아무것도 없었고..(https://www.php.net/manual/en/security.cgi-bin.attacks.php)