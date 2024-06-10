#include "serve_file.h"

int get_file_len(char *path)
{
  FILE *fd = fopen(path, "rb");
  int end_file = fseek(fd, 0L, SEEK_END);
  int len = ftell(fd);
  rewind(fd);
  return len;
}

void send_header(int socket, int file_len, char *extension){
  char buff[1024];
  char *br = "\r\n";
  char *response_line = "HTTP/1.1 200 OK%s";
  char *response_content = "Content-type : text/%s; charest=utf-8\r\n";
  char *connexion = "Connexion : Keep-Alive%s";
  //char *transfer_encoding = "Transfer-Encoding : chunked%s";
  int offset;

  sprintf(buff, response_line, br);
  sprintf(buff + strlen(buff), response_content, extension);
  sprintf(buff + strlen(buff), connexion, br);
  //sprintf(buff + strlen(buff), transfer_encoding, br);
  sprintf(buff + strlen(buff), "%s", br); // ending the header;
  printf("%s", buff);

  send(socket, buff, strlen(buff), 0);
}

void send_file(int socket, char *path, int file_len)
{
  int size = 1024;
  FILE *stream = fopen(path, "rb");

  printf("path : '%s'\n", path);
  printf("file size : %d\n", file_len);

  if(stream == NULL){
    printf("problem is here couldnt open file\n");
  }

  printf("file openned\n");

  char file_buffer[size];
  int r = fread(file_buffer, 1, size, stream);

  while(r){
    ssize_t sent = send(socket, file_buffer, r, 0);
    printf("data sent ? %ld\n", sent);
    r = fread(file_buffer, 1, size, stream);
  }
}

int file_available(char *target)
{
  const char *path = "./";
  DIR *dir = opendir(path);
  struct dirent *entry;

  printf("file looked for by file_available '%s'\n", target);

  while((entry = readdir(dir)) != NULL){
    int compn = strcmp(entry->d_name, target);
    if(strcmp(entry->d_name, target) == 0){

      return 0;
    }
  }
  return -1;

}

int current()
{
  char current[100];
  getcwd(current, 100);
  if(current == NULL){
    printf("problem getting current dir \n");
    return -1;
  }
  printf("current working dir %s\n", current);
  return 0;
}
