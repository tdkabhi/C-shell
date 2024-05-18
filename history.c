#include "headers.h"
extern char *history_path;
extern char *H[20];
extern INT total_commands;

void print_history()
{
    if (total_commands <= 10)
    {
        for (INT i = 0; i < total_commands; i++)
        {
            printf("%s\n", H[i]);
        }
    }
    else
    {
        for (INT i = total_commands - 10; i < total_commands; i++)
        {
            printf("%s\n", H[i]);
        }
    }
}
INT readfromhistory()
{
    FILE *fp;
    INT index = 0;
    fp = fopen(history_path, "r");
    if (fp == NULL)
    {
        perror(NULL);
        return -1;
    }
    while ((H[index] != NULL) && (fscanf(fp, "%[^\n]s", H[index]) != EOF))
    {
        fgetc(fp);
        INT length = strlen(H[index]);
        H[index][length] = '\0';
        index++;
    }
    if (index <= 20)
    {
        fclose(fp);
        return index;
    }
    else
    {
        fclose(fp);
        perror("Too many arguments in history.txt");
        return -1;
    }
}
INT writetohistory(char *Hist[], char *string)
{
    if (string != NULL && strlen(string)!=0)
    {
        FILE *fp;
        fp = fopen(history_path, "w");
        if (fp == NULL)
        {
            perror(NULL);
            return -1;
        }
        if (total_commands < 20)
        {
            if (total_commands != 0)
            {
                if (strcmp(Hist[total_commands - 1], string) != 0)
                {
                    strcpy(Hist[total_commands], string);
                    INT length = strlen(Hist[total_commands]);
                    Hist[total_commands][length] = '\0';
                    for (INT i = 0; i < total_commands; i++)
                    {
                        INT len = strlen(Hist[i]);
                        Hist[i][len] = '\0';
                        fprintf(fp, "%s\n", Hist[i]);
                    }
                    fprintf(fp, "%s\n", Hist[total_commands]);
                    total_commands++;
                    fclose(fp);
                }
            }
            else
            {
                strcpy(Hist[total_commands], string);
                INT length = strlen(Hist[total_commands]);
                Hist[total_commands][length] = '\0';
                for (INT i = 0; i < total_commands; i++)
                {
                    INT len = strlen(Hist[i]);
                    Hist[i][len] = '\0';
                    fprintf(fp, "%s\n", Hist[i]);
                }
                fprintf(fp, "%s\n", Hist[total_commands]);
                total_commands++;
                fclose(fp);
            }
        }
        else
        {

            if (total_commands == 20)
            {
                if (strcmp(Hist[19], string) != 0)
                {
                    for (INT i = 1; i < 20; i++)
                    {
                        INT len = strlen(H[i]);
                        Hist[i][len] = '\0';
                    }
                    free(Hist[0]);
                    for (INT i = 0; i < 19; i++)
                    {
                        Hist[i] = Hist[i + 1];
                    }
                    Hist[19] = (char *)calloc(400, sizeof(char));
                    strcpy(Hist[19], string);
                    INT len1 = strlen(Hist[19]);
                    Hist[19][len1] = '\0';
                    for (INT i = 0; i < 20; i++)
                    {
                        INT len = strlen(Hist[i]);
                        Hist[i][len] = '\0';
                        fprintf(fp, "%s\n", Hist[i]);
                    }
                    fclose(fp);
                }
            }
            else if (total_commands > 20)
            {
                fclose(fp);
                perror("total commands is greater than 20");
                return -1;
            }

            return 2;
        }
        return -1;
    }
    return 0;
}
