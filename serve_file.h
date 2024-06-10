#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE 1024

int get_file_len(char *path);
void send_header(int socket, int file_len, char *extension);
void send_file(int socket, char *path, int file_len);
int file_available();
int current();
