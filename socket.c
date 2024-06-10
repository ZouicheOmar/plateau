#include "socket.h"

#include "parse_req_line.h"
#include "serve_file.h"

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
  printf("Listenning on port %s\n", PORT);

  return s;
}

void socket_accept(int *s)
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
    char *reqmethod, *reqfile, *reqext;
    parse_req_line(request_line, &reqmethod, &reqfile, &reqext);
    int avail = file_available(reqfile);
    if(avail == 0){
      int file_len = get_file_len(reqfile);
      send_header(subs, file_len, reqext);
      send_file(subs, reqfile, file_len);
    }
    if(avail == -1){
      printf("sorry file not available \n");
      //TODO implement HTPP Error response
      //status : 404 ??
    }

    if(message_status == -1){
      printf("ERROR GETTING HTTP REQUEST\n");
      exit(1);
    }

    close(subs);
  }
}

