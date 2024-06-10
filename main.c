#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "socket.h"

char *get_request_line(char *request);

int main(int argc, char *argv[])
{

  int s = config_socket();
  socket_accept(&s);

  return 0;
}

