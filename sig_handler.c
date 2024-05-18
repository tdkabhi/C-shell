#include "headers.h"
extern List *LIST;
extern INT prompt_wait;
extern char *user_name;
extern char *system_name;
extern char *relative_path;
void interrupt_handler()
{
    int status;
    INT pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
    if (pid > 0)
    {
        if (WIFEXITED(status) || WIFSIGNALED(status))
        {
            INT exit_status = WEXITSTATUS(status);
            if (WIFSIGNALED(status)||WEXITSTATUS(status))
            {
                char *string = (char *)malloc(600 * sizeof(char));
                string = find_string(LIST, pid);
                printf("%s with  pid %lld exited abnormally\n", string, pid);
                DELETE(LIST, find(LIST, pid, string));
                free(string);
                if (prompt_wait)
                {
                    INT display_size = 1000;
                    char *display = (char *)calloc(display_size, sizeof(char));
                    sprintf(display, "%s<%s@%s:%s>\033[0m", KMAG, user_name, system_name, relative_path);
                    write(1, display, strlen(display));
                } 
            }
            else if (!exit_status)
            {
                char *string = (char *)malloc(600 * sizeof(char));
                string = find_string(LIST, pid);
                printf("%s with  pid %lld exited normally\n", string, pid);
                DELETE(LIST, find(LIST, pid, string));
                free(string);
                if (prompt_wait)
                {
                    INT display_size = 1000;
                    char *display = (char *)calloc(display_size, sizeof(char));
                    sprintf(display, "%s<%s@%s:%s>\033[0m", KMAG, user_name, system_name, relative_path);
                    write(1, display, strlen(display));
                }
            }
        }
    }
}