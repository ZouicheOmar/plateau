#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024

int get_file_len(char *path);
void send_header(int socket, int file_len);
void send_file(int socket, char *path, int file_len);
