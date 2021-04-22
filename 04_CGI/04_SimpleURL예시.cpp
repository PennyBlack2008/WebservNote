/*
- cgicc::Cgicc
	- cgicc 라이브러리의 기본 클래스입니다.
	- 업로드된 파일에서 HTML 양식 요소에 대한 정보를 검색
	- CGI 환경에 대한 정보를 저장, 복원, 검색

- cgicc::CgiEnvironment
	- HTTP 서버에서 CGI 응용 프로그램으로 전달 된 데이터를 캡슐화합니다.
	- CGI 표준에 지정된 HTTP 서버에서 설정한 모든 환경변수가 포함됩니다.

- cigcc::FormEntry
	- HTML 양식 요소(text field, radio button, checkbox)과 같은
	- HTML 양식 요소의 단일 사용자 항목을 나타내는 변경 불가능한 클래스이다.
	- FormEntry 는 기본적으로 이름 / 쌍 값이다.
		- 이름은 HTML 양식 요소의 이름
		- FormEntry 는 문자열, 정수 또는 double 로 값에 액세스할 수 있는 메서드를 제공.

- cgicc::FormFile
	- HTTP 파일 업로드 메커니즘을 통해 업로드된 파일을 내나태는 변경 불가능한 클래스
	- FormFile 은 FormEntry 와 매우 유사하지만
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "./cgicc/CgiDefs.h"
#include "./cgicc/Cgicc.h"
#include "./cgicc/HTTPHTMLHeader.h"
#include "./cgicc/HTMLClasses.h"

using namespace std;
using namespace cgicc;

int main () {
   Cgicc formData;

   cout << "Content-type:text/html\r\n\r\n";
   cout << "<html>\n";
   cout << "<head>\n";
   cout << "<title>Using GET and POST Methods</title>\n";
   cout << "</head>\n";
   cout << "<body>\n";

   form_iterator fi = formData.getElement("first_name");
   if( !fi->isEmpty() && fi != (*formData).end()) {
      cout << "First name: " << **fi << endl;
   } else {
      cout << "No text entered for first name" << endl;
   }

   cout << "<br/>\n";
   fi = formData.getElement("last_name");
   if( !fi->isEmpty() &&fi != (*formData).end()) {
      cout << "Last name: " << **fi << endl;
   } else {
      cout << "No text entered for last name" << endl;
   }

   cout << "<br/>\n";
   cout << "</body>\n";
   cout << "</html>\n";

   return 0;
}