#include "tools.h"

int get_git(char *p, const char *path)
{

  char command[200];

  if (p == NULL || path == NULL)
  {
    return 0;
  }

  snprintf(command, sizeof(command), "rm -rf  %s/* %s/.*", path, path);
  system(command);
  snprintf(command, sizeof(command), "mkdir -p %s; git clone %s %s; rm -rf %s/.*", path,p, path,path);

  int result = system(command);

  if (result == 0)
  {
    printf("Repository cloned successfully!\n");
  }
  else
  {
    printf("Error cloning repository.\n");
    return 0;
  }

  return result;
}
