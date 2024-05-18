#include "headers.h"
long long int sig_func(char *string[], long long int num_tokens, List *LIST)
{
    if (num_tokens == 2)
    {
        char *ptr1;
        INT job_number = strtol(string[0], &ptr1, 10);
        char *ptr2;
        INT signal_number = strtol(string[1], &ptr2, 10);
        struct node *head = LIST->root;
        while (head != NULL)
        {
            if(head->idx==job_number)
            {
                INT pid=head->Element;
                INT return_kill=kill(pid,signal_number);
                if(return_kill==-1)
                {
                    perror(NULL);
                    return -1;
                }
                return 0;
            }
            head=head->Next;
        }
        perror("Job with given job number is not found");
        return -1;
    }
    return -1;
}