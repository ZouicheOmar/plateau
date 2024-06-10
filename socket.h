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

#define PORT "8080"
#define BACKLOG 5
#define BUFF_LEN 512

int config_socket();
void socket_accept(int *s);
