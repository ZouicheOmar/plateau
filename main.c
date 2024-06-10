#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* is superset of <netinet/in.h> */
#include <netdb.h> /* defines types like in_addr_t */
#include <arpa/inet.h> /* for htonl and other network byte stream conversion func */
#include <ctype.h> /* char related types and funcs/macros eg : _toupper(int) */
#include <unistd.h> /* defines different types and funcs like size_t type, ssize_t, uid_t etc.. */
#include "parse_req_line.h"
#include "serve_file.h"

#define PORT "8080"
#define BACKLOG 5
#define BUFF_LEN 512

int config_socket();
void socket_listen(int *s);
char *get_request_line(char *request);

int main(int argc, char *argv[])
{

  int s = config_socket();
  socket_listen(&s);

  return 0;
}

int config_socket()
{
  int status;
  struct addrinfo hints;
  struct addrinfo *servinfo;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if((status = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
    printf("getaddrinfo ERROR\n");
    exit(1);
  }

  int s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  int sb = bind(s, servinfo->ai_addr, servinfo->ai_addrlen);
  if(sb == -1){
    printf("socket bind ERROR\n");
    exit(1);
  }

  int sl = listen(s, BACKLOG);
  if(sl == -1){
    printf("socket listen ERROR\n");
    exit(1);
  }

  return s;
}

void socket_listen(int *s)
{
  for(;;){
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int subs;

    addr_size = sizeof(their_addr);
    subs = accept(*s, (struct sockaddr *) &their_addr, &addr_size);

    if(subs == -1){
      printf("ACCEPT CONNEXION ERROR\n");
      exit(1);
    }
    printf("connected\n");

    char buff[BUFF_LEN];
    int message_status = recv(subs, buff, BUFF_LEN, 0);
    char *request_line = get_request_line(buff);
    char *request_file = parse_req_line(request_line);
    if(strcmp(request_file, "/") == 0){
      request_file = "cv.html";
      int file_len = get_file_len(request_file);
      printf("file length %d\n", file_len);
      send_header(subs, file_len);
      send_file(subs, request_file, file_len);
    }


    if(message_status == -1){
      printf("ERROR GETTING HTTP REQUEST\n");
      exit(1);
    }

    close(subs);
  }
}

char *get_request_line(char *request)
{
  char *first_line_break = strchr(request, '\n');
  int request_line_len = first_line_break - request;
  char *request_line = malloc(request_line_len * sizeof(char));
  strncpy(request_line, request, request_line_len);
  return request_line;
}
