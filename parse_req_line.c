#include "parse_req_line.h"

char *parse_req_line(char *src)
{
  char *file;
  char *method;
  char reqlen = strlen(src);

  char *ws1 = strchr(src, ' ');
  char *ws2 = strchr(ws1+1, ' ');

  int len1 = ws1 - src;
  int len2 = ws2 - (ws1+1);

  method = malloc(len1 * sizeof(char));
  char *p = src;
  for(int i = 0; i < len1; i++){
    method[i] = *p;
    p++;
  }
  method[len1] = '\0';

  file = malloc(len2 * sizeof(char));
  char *q = ws1 + 1;
  for(int i = 0; i < len2; i++){
    file[i] = *q;
    q++;
  }
  file[len2] = '\0';

  if(strcmp(method, "GET") > 0){
    return NULL;
  }
  return file;

}
