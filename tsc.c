#include <string.h>
#include <stdlib.h>
#include "tsc.h"

int compile_ts_file(char *path)
{

  char *p = malloc(strlen(path) * sizeof(char));;
  strcpy(p, path);
  char *ext = strchr(p, '.');
  ext[1] = 't';
  ext[2] = 's';

  char cmdbuff[64];
  sprintf(cmdbuff, "tsc %s", path);
  int status = system(cmdbuff);
  if(status == -1){
    return -1;
  }

  return 0;
}
