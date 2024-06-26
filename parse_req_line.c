#include "parse_req_line.h"
#include "tsc.h"

int parse_req_line(char *reqline, char **method, char **file, char **extension)
{
  char *oc1 = strchr(reqline, ' ');
  int methodlen = oc1 - reqline;
  *method = calloc( methodlen + 1, sizeof(char));
  strncpy(*method, reqline, methodlen);

  oc1++;
  char *oc2 = strchr(oc1, ' ');
  int filelen = oc2 - oc1;
  if(filelen == 1){
    *file = "index.html";
    *extension = "html";
    return 0;
  }

  oc1++;
  *file = calloc(filelen, sizeof(char));
  strncpy(*file, oc1, filelen - 1);

  char *oc3 = strchr(*file, '.');
  oc3++;
  *extension = calloc(strlen(oc3), sizeof(char));
  strncpy(*extension, oc3, strlen(oc3));
  
  if(strcmp(*extension, "js") == 0){
    //if not already compiled ??..
    //maybe i should compile all files first !!!
    int compiled = compile_ts_file(*file);
    if(compiled == -1){
      printf("ERROR COMPILING FILE\n");
    }
    printf("After compilation in parse req line\n");
    //call the compile function from here
    //is it going to be synchronous ?}

  }

  return 0;
}


char *get_request_line(char *request)
{
  char *first_line_break = strchr(request, '\n');
  int request_line_len = first_line_break - request;
  char *request_line = malloc(request_line_len * sizeof(char));
  strncpy(request_line, request, request_line_len);
  return request_line;
}

//int main(){
//  char *reqline = "GET /hello.js HTTP/1.1";
//  char *method, *file, *ext;
//  parse_req_line(reqline, &method, &file, &ext);
//}
