/*
https://stackoverflow.com/questions/20572829/c-webvserver-stdin-sockets-and-cgi-piping
*/

if (pipe(cgiPipe))
{
  perror("pipe");
}

cgiPid = fork();

if (cgiPid == 0)
{

  /* child */

  /* piping the POST content... */

  /* first, send the truncated part of the POST string contained within the request string... */
  /*
  보시다시피, CGI 프로그램을 실행하기 전에 전체 POST 문자열이 클라이언트로부터 수신되고 파이프됩니다 
  (먼저 요청 문자열 내에 포함 된 잘린 부분 (일반적으로 몇 바이트), 그리고 나머지 부분). 그러면 CGI 프로그램이 실행됩니다.
  */
  if (nPOSTLength && (nSentChrs = write(cgiPipe[1], sPOSTSegment, 
      nReqLen + requestString - sPOSTSegment)) > 0)
  {
    nPOSTLength -= nSentChrs;

    /* after, read and send the rest of the POST string not received yet... */
    while (nPOSTLength > 0 && (nReadChrs = read(nRemote, reservedBuffer, 
        BUFFER_SIZE_PER_USER)) > 0 && (nSentChrs = write(cgiPipe[1], reservedBuffer, 
        nReadChrs)) > 0 && nReadChrs == nSentChrs)
    {
      nPOSTLength -= nReadChrs;
    }

    if (nReadChrs < 0)
    {
      printf("Error reading POST string.\n");
      goto closeThread;
    }
    if (nSentChrs < 0)
    {
      printf("Error sending POST string.\n");
      goto closeThread;
    }
  }
  else
  {
    write(cgiPipe[1], "(null)", 6);
  }

  close(cgiPipe[1]);

  /* redirecting the output of the pipe to the STDIN of the child process */
  dup2(cgiPipe[0], STDIN_FILENO);
  /* redirecting STDOUT of the child process to the remote client */
  dup2(nRemote, STDOUT_FILENO);
  setuid(nUserID);

  if (execve(sLocalPath, NULL, aCGIEnv))
  {
    /* unable to execute CGI... */
    perror("execve");
    sendString(nRemote,
        "HTTP/1.1 200 OK\r\n"
        "Content-length: 97\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<!doctype html><html><head><title>CGI Error</title></head><body><h1>CGI Error.</h1></body></html>\r\n"
    );
  }

  goto closeThread;

}
else if (cgiPid > 0)
{

  /* parent */

  close(cgiPipe[0]);

  /* wait for child process. */
  if (waitpid(cgiPid, NULL, 0) == -1)
  {
    perror("wait");
  }

  goto closeThread;

}
else
{

  /* parent */

  perror("fork");

  /* let's try to send it as normal file, if the user has the right permissions... */

}

/*

여러 MB의 파일을 업로드하려고하면 CGI 호출 전에 여러 MB가 파이프됩니다. 이전에 읽지 않기 위해 소켓을 새 프로세스의 STDIN으로 직접 리디렉션 할 수있는 방법이 있습니까?

  그러나 확실히, 전에 POST 문자열의 잘린 부분을 읽어야합니다. 따라서 다음과 같이하고 싶은 작업을 도식화 할 수 있습니다.

1. 문자열 (몇 바이트)을 STDIN에 파이프 한 다음

2. 소켓 (클라이언트)을 STDIN으로 리디렉션 한 다음

3. 외부 프로세스 실행 (CGI 프로그램)

*/