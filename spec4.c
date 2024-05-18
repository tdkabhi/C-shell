#include "headers.h"
extern INT num_bg_processes;
extern time_t start_seconds;
void bg_func(char *string[], char *correct_path, List *LIST, INT num_tokens,char* full_name)
{
    INT forkReturn = fork();
    if (forkReturn == -1)
    {
        perror(NULL);
        return;
    }
    else
    {

        if (forkReturn == 0)
        {
            setpgid(0, 0);
            char *modify[num_tokens + 1];
            for (INT i = 0; i < num_tokens; i++)
            {
                modify[i] = (char *)calloc(600, sizeof(char));
            }
            modify[num_tokens] = NULL;
            for (INT i = 0; i < num_tokens; i++)
            {
                if (string[i][0] == '~')
                {
                    strcat(modify[i], correct_path);
                    INT len = strlen(modify[i]);
                    modify[i][len] = '\0';
                    strcat(modify[i], &string[i][1]);
                    len = strlen(modify[i]);
                    modify[i][len] = '\0';
                }
                else
                {
                    strcpy(modify[i], string[i]);
                    INT len = strlen(modify[i]);
                    modify[i][len] = '\0';
                }
            }
            INT exec_return = execvp(modify[0], modify);
            if (exec_return == -1)
            {
                perror(NULL);
                exit(1);
            }
            for (INT i = 0; i < num_tokens; i++)
            {
                free(modify[i]);
            }
        }
        else
        {
            printf("[%d] %lld\n", find_index(LIST), forkReturn);
            insert(LIST, forkReturn, string[0],full_name,find_index(LIST));
            signal(SIGCHLD, interrupt_handler);
        }
    }
}
void fg_func(char *string[], char *correct_path, INT num_tokens, List *LIST,char* full_name)
{
    pid_t forkReturn = fork();
    if (forkReturn == -1)
    {
        perror(NULL);
        return;
    }
    else
    {
        if (forkReturn == 0)
        {
            char *modify[num_tokens + 1];
            for (INT i = 0; i < num_tokens; i++)
            {
                modify[i] = (char *)calloc(600, sizeof(char));
            }
            modify[num_tokens] = NULL;
            for (INT i = 0; i < num_tokens; i++)
            {
                if (string[i][0] == '~')
                {
                    strcat(modify[i], correct_path);
                    INT len = strlen(modify[i]);
                    modify[i][len] = '\0';
                    strcat(modify[i], &string[i][1]);
                    len = strlen(modify[i]);
                    modify[i][len] = '\0';
                }
                else
                {
                    strcpy(modify[i], string[i]);
                    INT len = strlen(modify[i]);
                    modify[i][len] = '\0';
                }
            }
            INT exec_return = execvp(modify[0], modify);
            if (exec_return == -1)
            {
                perror(NULL);
                exit(0);
            }
            for (INT i = 0; i < num_tokens; i++)
            {
                free(modify[i]);
            }
        }
        else
        {
            signal(SIGTSTP,ctrlz);
            num_tokens = 1;
            char *modify[num_tokens];
            for (INT i = 0; i < num_tokens; i++)
            {
                modify[i] = (char *)calloc(600, sizeof(char));
            }
            for (INT i = 0; i < num_tokens; i++)
            {
                if (string[i][0] == '~')
                {
                    strcat(modify[i], correct_path);
                    INT len = strlen(modify[i]);
                    modify[i][len] = '\0';
                    strcat(modify[i], &string[i][1]);
                    len = strlen(modify[i]);
                    modify[i][len] = '\0';
                }
                else
                {
                    strcpy(modify[i], string[i]);
                    INT len = strlen(modify[i]);
                    modify[i][len] = '\0';
                }
            }
            int status;
            pid_t wpid;
            insert(LIST, forkReturn, modify[0],full_name,find_index(LIST));
            wpid = waitpid(forkReturn, &status, WSTOPPED);
            if (!WIFSTOPPED(status))
            {
                char *string = (char *)malloc(600 * sizeof(char));
                string = find_string(LIST, forkReturn);
                DELETE(LIST, find(LIST, forkReturn, string));
            }
            for (INT i = 0; i < num_tokens; i++)
            {
                free(modify[i]);
            }
        }
    }
}

void spec4_func(char *string[], char *correct, long long int last, List *LIST, INT num_tokens,char* full_name)
{
    if (last)
    {
        fg_func(string, correct, num_tokens,LIST,full_name);
    }
    else
    {
        bg_func(string, correct, LIST, num_tokens,full_name);
    }
}
