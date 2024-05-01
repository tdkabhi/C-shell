#include "headers.h"
extern INT prompt_wait;
extern char *user_name;
extern char *system_name;
extern char *relative_path;
void ctrlz()
{
    if (prompt_wait)
    {
        INT display_size = 1000;
        char *display = (char *)calloc(display_size, sizeof(char));
        printf("^Z");
        sprintf(display, "\n%s<%s@%s:%s>\033[0m", KMAG, user_name, system_name, relative_path);
        write(1, display, strlen(display));
        fflush(stdout);
    }
}