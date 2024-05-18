#include "headers.h"
extern char* user_name;
extern char* system_name;
extern char *relative_path;

void prompt(char* time)
{
   INT display_size = 1000;
   char *display = (char *)calloc(display_size, sizeof(char));
   sprintf(display,"%s<%s@%s:%s%s>\033[0m",KMAG,user_name,system_name,relative_path,time);
   write(1,display,strlen(display));
}
