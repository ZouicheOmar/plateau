/*
 * format an http reponse header
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int simple();
void *format();

void *format()
{
  char buff[512];
  int size = 5120;
  char *br = "\r\n";
  char *line = "HTTP/1.1 200 OK%s";
  char *server = "Server : Plateau%s";
  char *content_size = "Content-size : %d%s";

  int offset;

  sprintf(buff, line, br);
  sprintf(buff + strlen(line), server, br);
  offset = strlen(line) + strlen(server);
  sprintf(buff + offset, content_size, size, br);

  printf("%s", buff);
}

int simple(char **target)
{
  *target = "GET";
  return 0;
}
