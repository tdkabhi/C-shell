#include "headers.h"
int compare1(const void *arg1, const void *arg2)
{
    return (strcmp((*((struct node **)arg1))->process_name, (*((struct node **)arg2))->process_name));
}
INT jobs(char *string[], INT num_tokens, List *LIST)
{
    INT running = 0;
    INT stopped = 0;
    if (num_tokens == 0)
    {
        running = 1;
        stopped = 1;
    }
    else if (num_tokens == 1)
    {
        if (strcmp(string[0], "-r") == 0)
        {
            running = 1;
            // printf("running\n");
        }
        else if (strcmp(string[0], "-s") == 0)
        {
            stopped = 1;
            //  printf("stopped\n");
        }
        else
        {
            perror("Invalid syntax to command job");
            return -1;
        }
    }
    INT list_size = get_size(LIST);
    if (list_size > 0)
    {
        struct node *nodeptr_array[list_size];
        struct node *head = LIST->root;
        for (INT i = 0; i < list_size; i++)
        {
            if (head == NULL)
            {
                perror("error in liked list");
                return -1;
            }
            nodeptr_array[i] = head;
            head = head->Next;
        }
        qsort(nodeptr_array, list_size, sizeof(nodeptr_array[0]), compare1);
        char *stat_path = (char *)calloc(800, sizeof(char));
        strcat(stat_path, "/proc/");
        INT len1 = strlen(stat_path);
        stat_path[len1] = '\0';
        if (running && stopped)
        {
            INT pid;
            char *number_to_string = (char *)calloc(15, sizeof(char));
            for (INT i = 0; i < list_size; i++)
            {
                stat_path[len1] = '\0';
                pid = nodeptr_array[i]->Element;
                sprintf(number_to_string, "%lld", pid);
                INT len = strlen(number_to_string);
                number_to_string[len] = '\0';
                strcat(stat_path, number_to_string);
                INT len2 = strlen(stat_path);
                stat_path[len2] = '\0';
                strcat(stat_path, "/stat");
                len2 = strlen(stat_path);
                stat_path[len2] = '\0';
                FILE *fp = fopen(stat_path, "r");
                if (fp == NULL)
                {
                    perror("problem in fp");
                    return -1;
                }
                else
                {
                    char *line[4];
                    for (INT i = 0; i < 4; i++)
                    {
                        line[i] = (char *)calloc(100, sizeof(char));
                    }
                    INT index = 0;
                    while ((index < 4) && (line[index] != NULL) && (fscanf(fp, "%s", line[index]) != EOF))
                    {
                        INT length = strlen(line[index]);
                        line[index][length] = '\0';
                        index++;
                    }
                    fclose(fp);
                    char *process_status = line[2];
                    char *print_process_status = (char *)calloc(15, sizeof(char));
                    print_process_status[0] = '\0';
                    if (strcmp(process_status, "T") == 0)
                    {
                        strcat(print_process_status, "Stopped");
                        INT len3 = strlen(print_process_status);
                        print_process_status[len3] = '\0';
                    }
                    else
                    {
                        strcat(print_process_status, "Running");
                        INT len3 = strlen(print_process_status);
                        print_process_status[len3] = '\0';
                    }
                    printf("[%d] %s %s [%d]\n", nodeptr_array[i]->idx, print_process_status, nodeptr_array[i]->full_name, nodeptr_array[i]->Element);
                }
            }
        }
        else if (running)
        {
            INT pid;
            char *number_to_string = (char *)calloc(15, sizeof(char));
            for (INT i = 0; i < list_size; i++)
            {
                stat_path[len1] = '\0';
                pid = nodeptr_array[i]->Element;
                sprintf(number_to_string, "%lld", pid);
                INT len = strlen(number_to_string);
                number_to_string[len] = '\0';
                strcat(stat_path, number_to_string);
                INT len2 = strlen(stat_path);
                stat_path[len2] = '\0';
                strcat(stat_path, "/stat");
                len2 = strlen(stat_path);
                stat_path[len2] = '\0';
                FILE *fp = fopen(stat_path, "r");
                if (fp == NULL)
                {
                    perror(NULL);
                    return -1;
                }
                else
                {
                    char *line[4];
                    for (INT i = 0; i < 4; i++)
                    {
                        line[i] = (char *)calloc(100, sizeof(char));
                    }
                    INT index = 0;
                    while ((index < 4) && (line[index] != NULL) && (fscanf(fp, "%s", line[index]) != EOF))
                    {
                        INT length = strlen(line[index]);
                        line[index][length] = '\0';
                        index++;
                    }
                    fclose(fp);
                    char *process_status = line[2];
                    char *print_process_status = (char *)calloc(15, sizeof(char));
                    print_process_status[0] = '\0';
                    if (strcmp(process_status, "T") != 0)
                    {
                        strcat(print_process_status, "Running");
                        INT len3 = strlen(print_process_status);
                        print_process_status[len3] = '\0';
                    }
                    else
                    {
                        continue;
                    }
                    printf("[%d] %s %s [%d]\n", nodeptr_array[i]->idx, print_process_status, nodeptr_array[i]->full_name, nodeptr_array[i]->Element);
                }
            }
        }
        else if (stopped)
        {
            INT pid;
            char *number_to_string = (char *)calloc(15, sizeof(char));
            for (INT i = 0; i < list_size; i++)
            {
                stat_path[len1] = '\0';
                pid = nodeptr_array[i]->Element;
                sprintf(number_to_string, "%lld", pid);
                INT len = strlen(number_to_string);
                number_to_string[len] = '\0';
                strcat(stat_path, number_to_string);
                INT len2 = strlen(stat_path);
                stat_path[len2] = '\0';
                strcat(stat_path, "/stat");
                len2 = strlen(stat_path);
                stat_path[len2] = '\0';
                FILE *fp = fopen(stat_path, "r");
                if (fp == NULL)
                {
                    perror(NULL);
                    return -1;
                }
                else
                {
                    char *line[4];
                    for (INT i = 0; i < 4; i++)
                    {
                        line[i] = (char *)calloc(100, sizeof(char));
                    }
                    INT index = 0;
                    while ((index < 4) && (line[index] != NULL) && (fscanf(fp, "%s", line[index]) != EOF))
                    {
                        INT length = strlen(line[index]);
                        line[index][length] = '\0';
                        index++;
                    }
                    fclose(fp);
                    char *process_status = line[2];
                    char *print_process_status = (char *)calloc(15, sizeof(char));
                    print_process_status[0] = '\0';
                    if (strcmp(process_status, "T") == 0)
                    {
                        strcat(print_process_status, "Stopped");
                        INT len3 = strlen(print_process_status);
                        print_process_status[len3] = '\0';
                    }
                    else
                    {
                        continue;
                    }
                    printf("[%d] %s %s [%d]\n", nodeptr_array[i]->idx, print_process_status, nodeptr_array[i]->full_name, nodeptr_array[i]->Element);
                }
            }
        }
    }
    return -1;
}