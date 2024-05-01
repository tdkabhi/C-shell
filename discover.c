#include "headers.h"
char *current_directory; // ~
INT tilder = 0;
INT first_dir = 1;
void dfs(char *dir_path, char *find_path, int directory, int file, int len)
{
    struct dirent *dirnt;
    DIR *dr = opendir(dir_path);
    if (dr == NULL)
    {
        perror(NULL);
        return;
    }
    if ((find_path == NULL) && (directory))
    {
        if (first_dir)
        {
            if (tilder)
            {
                INT X = strlen(current_directory);
                printf("~%s\n", &dir_path[X]);
            }
            else
            {
                printf("%s\n", dir_path);
            }
            first_dir = 0;
        }
    }
    struct stat fs;
    char *string4 = (char *)calloc(800, sizeof(char));
    string4[0] = '\0';
    char *string2 = (char *)calloc(600, sizeof(char));
    string2[0] = '\0';
    while ((dirnt = readdir(dr)) != NULL)
    {
        strcat(string4, dir_path);
        if (strcmp(string4, "/") != 0)
        {
            strcat(string4, "/");
        }
        strcat(string4, dirnt->d_name);
        INT R = stat(string4, &fs);
        if (R == -1)
        {
            perror(NULL);
            return;
        }
        INT J = S_ISDIR(fs.st_mode);
        if (J)
        {
            if (find_path == NULL)
            {
                if (directory)
                {
                    if ((strcmp(dirnt->d_name, ".") != 0) && (strcmp(dirnt->d_name, "..") != 0))
                    {
                        strcat(string2, dir_path);
                        if (strcmp(string2, "/") != 0)
                        {
                            strcat(string2, "/");
                        }
                        strcat(string2, dirnt->d_name);
                        if (tilder && strstr(string2, current_directory))
                        {
                            INT length5 = strlen(current_directory);
                            printf("~%s\n", &string2[length5]);
                        }
                        else
                        {
                            printf("%s\n", string2);
                        }
                    }
                }
            }
            else
            {
                if (directory)
                {
                    if (strcmp(dirnt->d_name, find_path) == 0)
                    {
                        strcat(string2, dir_path);
                        if (strcmp(string2, "/") != 0)
                        {
                            strcat(string2, "/");
                        }
                        strcat(string2, dirnt->d_name);
                        if (tilder && strstr(string2, current_directory))
                        {
                            INT length5 = strlen(current_directory);
                            printf("~%s\n", &string2[length5]);
                        }
                        else
                        {
                            printf("%s\n", string2);
                        }
                    }
                }
            }
            /********/
            if ((strcmp(dirnt->d_name, ".") != 0) && (strcmp(dirnt->d_name, "..") != 0))
            {
                int len = strlen(dir_path);
                if (strcmp(dir_path, "/") != 0)
                {
                    strcat(dir_path, "/");
                }
                strcat(dir_path, dirnt->d_name);
                dfs(dir_path, find_path, directory, file, strlen(dir_path));
                dir_path[len] = '\0';
            }
        }
        else
        {
            if (S_ISREG(fs.st_mode))
            {
                if (find_path != NULL)
                {
                    if (file)
                    {
                        if (strcmp(dirnt->d_name, find_path) == 0)
                        {
                            char *string1 = (char *)calloc(600, sizeof(char));
                            strcat(string1, dir_path);
                            if (strcmp(string1, "/") != 0)
                            {
                                strcat(string1, "/");
                            }
                            strcat(string1, dirnt->d_name);
                            if (tilder && (strstr(string1, current_directory)))
                            {
                                INT length5 = strlen(current_directory);
                                printf("~%s\n", &string1[length5]);
                            }
                            else
                            {
                                printf("%s\n", string1);
                            }
                            free(string1);
                        }
                    }
                }
                else if (file)
                {
                    char *string1 = (char *)calloc(600, sizeof(char));
                    strcat(string1, dir_path);
                    if (strcmp(string1, "/") != 0)
                    {
                        strcat(string1, "/");
                    }
                    strcat(string1, dirnt->d_name);
                    if (tilder && (strstr(string1, current_directory)))
                    {
                        INT length5 = strlen(current_directory);
                        printf("~%s\n", &string1[length5]);
                    }
                    else
                    {
                        printf("%s\n", string1);
                    }
                    free(string1);
                }
            }
        }
        string4[0] = '\0';
        string2[0] = '\0';
    }
    free(string4);
    free(string2);
}
void discover_func(char *string[], char *correct_path, long long int num_tokens)
{
    INT directory = 0;
    INT file = 0;
    INT num_commands = 0;
    INT total_commands = 0;
    current_directory = (char *)calloc(800, sizeof(char));
    strcpy(current_directory, correct_path);
    current_directory[strlen(correct_path)] = '\0';
    INT quotes = 0;
    for (INT i = 0; i < num_tokens; i++)
    {
        if (string[i][0] == '-')
        {
            total_commands++;

            if (strcmp(string[i], "-d") == 0)
            {
                directory = 1;
            }
            else if ((strcmp(string[i], "-f") == 0))
            {
                file = 1;
            }
            else
            {
                perror("Incorrect argument supplied to command discover");
                return;
            }
        }
        else
        {
            num_commands++;
            total_commands++;
        }
    }
    for(INT i=0;i<num_tokens;i++)
    {
        for(INT j=0;j<strlen(string[i]);j++)
        {
            if(string[i][j]=='"')
            {
                quotes++;
            }
        }
    }
    if (num_commands > 2)
    {
        perror("Too many arguments to command discover");
        return;
    }
    if ((quotes != 0) && (quotes != 2))
    {
        perror("find_argument can either be NULL or of the form <filename> inside double quotes");
        return;
    }
    num_tokens = num_commands;
    if (file)
    {
        num_tokens++;
    }
    if (directory)
    {
        num_tokens++;
    }
    INT find_input = 0;
    char *given_find = (char *)calloc(600, sizeof(char));
    given_find[0] = '\0';
    for (INT i = 0; i < num_tokens; i++)
    {
        if (string[i][0] == '"')
        {
            INT length5 = strlen(string[i]);
            strcat(given_find, &string[i][1]);
            given_find[length5 - 2] = '\0';
            find_input = 1;
            break;
        }
    }
    if (find_input)
    {
        if (num_tokens == 1) // discover "find"
        {
            char *string3 = (char *)calloc(800, sizeof(char));
            string3[0] = '.';
            string3[1] = '\0';
            char *s2 = (char *)calloc(600, sizeof(char));
            s2[0] = '\0';
            strcpy(s2, &given_find[0]);
            INT len = strlen(string3);
            dfs(string3, s2, 1, 1, len);
            free(string3);
            free(s2);
        }
        else if (num_tokens == 2) // discover  -d/-f find or discover folder "find"
        {

            if (file) // discover -f find
            {
                char *string3 = (char *)calloc(800, sizeof(char));
                string3[0] = '.';
                string3[1] = '\0';
                INT len = strlen(string3);
                dfs(string3, given_find, 0, 1, len);
                free(string3);
            }
            else if (directory) // discover -d find
            {
                char *string3 = (char *)calloc(800, sizeof(char));
                string3[0] = '.';
                string3[1] = '\0';
                INT len = strlen(string3);
                dfs(string3, given_find, 1, 0, len);
                free(string3);
            }
            else // dicover folder "find" - find all such "find" whether it is folder/file type
            {
                char *s1 = (char *)calloc(600, sizeof(char));
                s1[0] = '\0';
                if (string[0][0] == '~')
                {
                    strcat(s1, correct_path);
                    strcat(s1, &string[0][1]);
                    tilder = 1;
                }
                else
                {
                    tilder = 0;
                    strcpy(s1, string[0]);
                }
                char *s2 = (char *)calloc(600, sizeof(char));
                s2[0] = '\0';
                strcpy(s2, &given_find[0]);
                INT len = strlen(s1);
                if (len != 1)
                {
                    if (s1[len - 1] == '/')
                    {
                        s1[len - 1] = '\0';
                        len--;
                    }
                }
                dfs(s1, s2, 1, 1, len);
                tilder = 0;
                free(s1);
                free(s2);
            }
        }
        else if (num_tokens == 3)
        {
            if (file && directory) // discover -d -f "find"
            {
                char *string3 = (char *)calloc(800, sizeof(char));
                string3[0] = '.';
                string3[1] = '\0';
                INT len = strlen(string3);
                dfs(string3, given_find, 1, 1, len);
                free(string3);
            }
            else if (file) // discover folder -f "find"
            {
                char *s1 = (char *)calloc(600, sizeof(char));
                s1[0] = '\0';
                if (string[0][0] == '~')
                {
                    strcat(s1, correct_path);
                    strcat(s1, &string[0][1]);
                    tilder = 1;
                }
                else
                {
                    strcpy(s1, string[0]);
                    tilder = 0;
                }
                char *s2 = (char *)calloc(600, sizeof(char));
                s2[0] = '\0';
                strcpy(s2, &given_find[0]);
                INT len = strlen(s1);
                if (len != 1)
                {
                    if (s1[len - 1] == '/')
                    {
                        s1[len - 1] = '\0';
                        len--;
                    }
                }
                dfs(s1, s2, 0, 1, len);
                free(s1);
                free(s2);
            }
            else if (directory) // discover folder -d "find"
            {
                char *s1 = (char *)calloc(600, sizeof(char));
                s1[0] = '\0';
                if (string[0][0] == '~')
                {
                    strcat(s1, correct_path);
                    strcat(s1, &string[0][1]);
                    tilder = 1;
                }
                else
                {
                    strcpy(s1, string[0]);
                    tilder = 0;
                }
                char *s2 = (char *)calloc(600, sizeof(char));
                s2[0] = '\0';
                strcpy(s2, &given_find[0]);
                INT len = strlen(s1);
                if (len != 1)
                {
                    if (s1[len - 1] == '/')
                    {
                        s1[len - 1] = '\0';
                        len--;
                    }
                }
                dfs(s1, s2, 1, 0, len);
                free(s1);
                free(s2);
            }
            else
            {
                perror("Incorrect format of arguments supplied");
                return;
            }
        }
        else if (num_tokens == 4)
        {
            if (file && directory)
            {
                char *s1 = (char *)calloc(600, sizeof(char));
                s1[0] = '\0';
                if (string[0][0] == '~')
                {
                    strcat(s1, correct_path);
                    strcat(s1, &string[0][1]);
                    tilder = 1;
                }
                else
                {
                    strcpy(s1, string[0]);
                    tilder = 0;
                }
                INT len = strlen(s1);
                if (len != 1)
                {
                    if (s1[len - 1] == '/')
                    {
                        s1[len - 1] = '\0';
                        len--;
                    }
                }
                dfs(s1, given_find, 1, 1, strlen(s1));
                free(s1);
            }
            else
            {
                perror("Incorrect format of arguments supplied");
                return;
            }
        }
    }
    else
    {
        if (num_tokens == 0) // discover
        {
            char *string3 = (char *)calloc(800, sizeof(char));
            string3[0] = '.';
            string3[1] = '\0';
            INT len = strlen(string3);
            dfs(string3, NULL, 1, 1, len);
            free(string3);
        }
        else if (num_tokens == 1) // discovery -f or discovery -d or discovery folder
        {
            char *string3 = (char *)calloc(800, sizeof(char));
            string3[0] = '.';
            string3[1] = '\0';
            INT len = strlen(string3);
            if (directory)
            {
                dfs(string3, NULL, 1, 0, len);
            }
            else if (file)
            {
                dfs(string3, NULL, 0, 1, len);
            }
            else
            {
                char *s1 = (char *)calloc(600, sizeof(char));
                s1[0] = '\0';
                if (string[0][0] == '~')
                {
                    strcat(s1, correct_path);
                    strcat(s1, &string[0][1]);
                    tilder = 1;
                }
                else
                {
                    tilder = 0;
                    strcpy(s1, string[0]);
                }
                INT len4 = strlen(s1);
                if (len4 != 1)
                {
                    if (s1[len4 - 1] == '/')
                    {
                        s1[len4 - 1] = '\0';
                        len4--;
                    }
                }
                dfs(s1, NULL, 1, 1, len4);
            }
        }
        else if (num_tokens == 2) // discover folder -f , discover folder -d ,disscover -d -f
        {
            if (file && directory)
            {
                char *string3 = (char *)calloc(800, sizeof(char));
                string3[0] = '.';
                string3[1] = '\0';
                INT len = strlen(string3);
                dfs(string3, NULL, 1, 1, len);
                free(string3);
            }
            else if (file)
            {
                char *s1 = (char *)calloc(600, sizeof(char));
                s1[0] = '\0';
                if (string[0][0] == '~')
                {
                    strcat(s1, correct_path);
                    strcat(s1, &string[0][1]);
                    tilder = 1;
                }
                else
                {
                    tilder = 0;
                    strcpy(s1, string[0]);
                }
                INT len = strlen(s1);
                if (len != 1)
                {
                    if (s1[len - 1] == '/')
                    {
                        s1[len - 1] = '\0';
                        len--;
                    }
                }
                dfs(s1, NULL, 0, 1, strlen(s1));
            }
            else if (directory)
            {
                char *s1 = (char *)calloc(600, sizeof(char));
                s1[0] = '\0';
                if (string[0][0] == '~')
                {
                    tilder = 1;
                    strcat(s1, correct_path);
                    strcat(s1, &string[0][1]);
                }
                else
                {
                    tilder = 0;
                    strcpy(s1, string[0]);
                }
                INT len = strlen(s1);
                if (len != 1)
                {
                    if (s1[len - 1] == '/')
                    {
                        s1[len - 1] = '\0';
                        len--;
                    }
                }
                dfs(s1, NULL, 1, 0, strlen(s1));
            }
            else
            {
                perror("Incorrect format of arguments supplied");
                return;
            }
        }
        else if (num_tokens == 3) // discover folder -d -f
        {
            char *s1 = (char *)calloc(600, sizeof(char));
            s1[0] = '\0';
            if (string[0][0] == '~')
            {
                tilder = 1;
                strcat(s1, correct_path);
                strcat(s1, &string[0][1]);
            }
            else
            {
                tilder = 0;
                strcpy(s1, string[0]);
            }
            INT len = strlen(s1);
            if (len != 1)
            {
                if (s1[len - 1] == '/')
                {
                    s1[len - 1] = '\0';
                    len--;
                }
            }
            dfs(s1, NULL, 1, 1, strlen(s1));
        }
    }
    tilder = 0;
    first_dir = 1;
}
