#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse_req_line(char *request_line, char **method, char **file, char **ext);
char *get_request_line(char *request);
