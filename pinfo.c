#include "headers.h"
void pinfo(char *argument[], INT tokens, char *correct_path)
{
    char *stat_path = (char *)calloc(800, sizeof(char));
    char *exec_path = (char *)calloc(800, sizeof(char));
    strcat(stat_path, "/proc/");
    INT len1 = strlen(stat_path);
    stat_path[len1] = '\0';
    strcat(exec_path, "/proc/");
    INT len2 = strlen(exec_path);
    stat_path[len2] = '\0';
    if (tokens == 0)
    {
        INT pid = getpid();
        char *number_to_string = (char *)calloc(15, sizeof(char));
        sprintf(number_to_string, "%lld", pid);
        INT len = strlen(number_to_string);
        number_to_string[len] = '\0';
        strcat(stat_path, number_to_string);
        len1 = strlen(stat_path);
        stat_path[len1] = '\0';
        strcat(exec_path, number_to_string);
        len2 = strlen(exec_path);
        stat_path[len2] = '\0';
        strcat(stat_path, "/stat");
        strcat(exec_path, "/exe");
        len1 = strlen(stat_path);
        stat_path[len1] = '\0';
        len2 = strlen(exec_path);
        exec_path[len2] = '\0';
        FILE *fp = fopen(stat_path, "r");
        if (fp == NULL)
        {
            perror(NULL);
            return;
        }
        else
        {
            char *line[53];
            for (INT i = 0; i < 53; i++)
            {
                line[i] = (char *)calloc(100, sizeof(char));
            }
            INT index = 0;
            while ((index < 53) && (line[index] != NULL) && (fscanf(fp, "%s", line[index]) != EOF))
            {
                INT length = strlen(line[index]);
                line[index][length] = '\0';
                index++;
            }
            fclose(fp);
            char *process_status = line[2];
            char *memory = line[22];
            char *pgrp = line[4];
            char *tpgid = line[7];
            char *return_exec_path = (char *)calloc(500, sizeof(char));
            INT return_value = readlink(exec_path, return_exec_path, 500);
            if (return_value == -1)
            {
                perror(NULL);
                return;
            }
            printf("pid : %lld\n", pid);
            printf("process status : %s", process_status);
            if (strcmp(pgrp, tpgid) == 0)
            {
                printf("+\n");
            }
            else
            {
                printf("\n");
            }
            printf("memory : %s\n", memory);
            if (strstr(return_exec_path, correct_path))
            {
                INT length = strlen(correct_path);
                printf("executable path : ~%s\n", &return_exec_path[length]);
            }
            else
            {
                printf("executable path : %s\n", &return_exec_path[0]);
            }
        }
    }
    else if (tokens == 1)
    {
        char *ptr;
        if (argument[0] != NULL)
        {
            INT pid = strtol(argument[0], &ptr, 10);
            char *number_to_string = (char *)calloc(15, sizeof(char));
            sprintf(number_to_string, "%lld", pid);
            INT len = strlen(number_to_string);
            number_to_string[len] = '\0';
            strcat(stat_path, number_to_string);
            len1 = strlen(stat_path);
            stat_path[len1] = '\0';
            strcat(exec_path, number_to_string);
            len2 = strlen(exec_path);
            stat_path[len2] = '\0';
            strcat(stat_path, "/stat");
            strcat(exec_path, "/exe");
            len1 = strlen(stat_path);
            stat_path[len1] = '\0';
            len2 = strlen(exec_path);
            exec_path[len2] = '\0';
            FILE *fp = fopen(stat_path, "r");
            if (fp == NULL)
            {
                perror(NULL);
                return ;
            }
            else
            {
                char *line[53];
                for (INT i = 0; i < 53; i++)
                {
                    line[i] = (char *)calloc(100, sizeof(char));
                }
                INT index = 0;
                while ((index < 53) && (line[index] != NULL) && (fscanf(fp, "%s", line[index]) != EOF))
                {
                    INT length = strlen(line[index]);
                    line[index][length] = '\0';
                    index++;
                }
                fclose(fp);
                char *process_status = line[2];
                char *memory = line[22];
                char *pgrp = line[4];
                char *tpgid = line[7];
                char *return_exec_path = (char *)calloc(500, sizeof(char));
                INT return_value = readlink(exec_path, return_exec_path, 500);
                if (return_value == -1)
                {
                    perror(NULL);
                    return;
                }
                printf("pid : %lld\n", pid);
                printf("process status : %s", process_status);
                if (strcmp(pgrp, tpgid) == 0)
                {
                    printf("+\n");
                }
                else
                {
                    printf("\n");
                }
                printf("memory : %s\n", memory);
                if (strstr(return_exec_path, correct_path))
                {
                    INT length = strlen(correct_path);
                    printf("executable path : ~%s\n", &return_exec_path[length]);
                }
                else
                {
                    printf("executable path : %s\n", &return_exec_path[0]);
                }

            }
        }
    }
}
