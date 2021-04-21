/*
I just had to put the sending process inside the parent rather than the child. In this way the CGI is executed immediately:

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

  /* first, send the truncated part of the POST string contained within the request string... */
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