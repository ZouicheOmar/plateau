#include "serve_file.h"

int get_file_len(char *path)
{
  FILE *fd = fopen(path, "rb");
  int end_file = fseek(fd, 0L, SEEK_END);
  int len = ftell(fd);
  rewind(fd);
  return len;
}

void send_header(int socket, int file_len){
  char header_buff[1024];
  char *response_line = "HTTP/1.1 200\r\n";
  char *response_content = "Content-type : text/html\r\n";
  char *connexion = "Connexion : close\r\n";
  sprintf(header_buff, "%s", response_line);
  int indicator = strlen(response_line);
  sprintf(header_buff + indicator, "%s", connexion);
  indicator += strlen(connexion);
  sprintf(header_buff + indicator, "%s", response_content);
  indicator += strlen(response_content);
  sprintf(header_buff + indicator, "\r\n");
  send(socket, header_buff, strlen(header_buff), 0);
}

void send_file(int socket, char *path, int file_len)
{
  int size = 1024;
  FILE *stream = fopen(path, "rb");

  char file_buffer[size];

  int r = fread(file_buffer, 1, size, stream);
  printf("from fread %d\n", r);
  while(r){
    ssize_t sent = send(socket, file_buffer, r, 0);
    printf("data sent ? %ld\n", sent);
    r = fread(file_buffer, 1, size, stream);
  }
}
