#include "headers.h"
int compare(const void *arg1, const void *arg2)
{
    return (strcasecmp((*((struct dirent **)arg1))->d_name, (*((struct dirent **)arg2))->d_name));
}
void print_ls(char *string, char *correct_path, INT type, INT num_args)
{
    char *string1 = (char *)calloc(1000, sizeof(char));
    char *path = (char *)calloc(600, sizeof(char));
    if (string[0] == '~')
    {
        strcpy(string1, correct_path);
        strcat(string1, &string[1]);
    }
    else
    {
        strcpy(string1, string);
    }
    strcpy(path, string1);
    strcat(path, "/");
    INT len = strlen(path);
    /**/
    struct dirent **name_list;
    if (type == 0) // no l & a
    {
        INT files = 0;
        INT num_directory_entries = scandir(string1, &name_list, NULL, alphasort);
        if (num_directory_entries == -1)
        {
            if (errno == ENOTDIR)
            {
                files = 1;
            }
            else
            {
                perror(NULL);
                return;
            }
        }
        if (num_args >= 2 && files != 1)
        {
            printf("%s:\n", string1);
        }
        if (!files)
        {
            qsort(name_list, num_directory_entries, sizeof(name_list[0]), compare);
            for (INT i = 0; i < num_directory_entries; i++)
            {
                char *ptr = name_list[i]->d_name;
                char ch = ptr[0];
                if (ch != '.')
                {
                    struct stat fs;
                    strcat(path, name_list[i]->d_name);
                    INT R = lstat(path, &fs);
                    if (R == -1)
                    {
                        perror(NULL);
                        return;
                    }
                    INT J = S_ISDIR(fs.st_mode);
                    INT G = fs.st_mode & S_IXUSR;
                    if (S_ISLNK(fs.st_mode))
                    {
                        printf("%s%s\033[0m\n",KRED,name_list[i]->d_name);
                    }
                    else if (J)
                    {
                        printf("%s%s\033[0m\n", KBLU, name_list[i]->d_name);
                    }
                    else
                    {
                        if (S_ISREG(fs.st_mode))
                        {
                            if (G)
                            {
                                printf("%s%s\033[0m\n", KGRN, name_list[i]->d_name);
                            }
                            else
                            {
                                printf("%s%s\033[0m\n", KWHT, name_list[i]->d_name);
                            }
                        }
                        else
                        {
                            printf("%s%s\033[0m\n", KYEL, name_list[i]->d_name);
                        }
                    }
                    path[len] = '\0';
                }
                free(name_list[i]);
            }
            free(name_list);
        }
        else
        {
            INT R = 0;
            struct stat fs;
            R = lstat(string1, &fs);
            if (R == -1)
            {
                perror(NULL);
                return;
            }
            INT G = fs.st_mode & S_IXUSR;
            if (S_ISLNK(fs.st_mode))
            {
                printf("%s%s\033[0m\n", KRED, string1);
            }
            else if (S_ISREG(fs.st_mode))
            {
                if (G)
                {
                    printf("%s%s\033[0m\n", KGRN, string1);
                }
                else
                {
                    printf("%s%s\033[0m\n", KWHT, string1);
                }
            }
            else
            {
                printf("%s%s\033[0m\n", KYEL, string1);
            }
        }
    }
    else if (type == 1) // no l but a is there
    {
        INT files = 0;
        INT num_directory_entries = scandir(string1, &name_list, NULL, alphasort);
        if (num_directory_entries == -1)
        {
            if (errno == ENOTDIR)
            {
                files = 1;
            }
            else
            {
                perror(NULL);
                return;
            }
        }
        if (num_args >= 2 && files != 1)
        {
            printf("%s:\n", string1);
        }
        if (!files)
        {
            qsort(name_list, num_directory_entries, sizeof(name_list[0]), compare);
            for (INT i = 0; i < num_directory_entries; i++)
            {
                struct stat fs;
                strcat(path, name_list[i]->d_name);
                INT R = lstat(path, &fs);
                if (R == -1)
                {
                    perror(NULL);
                    return;
                }
                INT J = S_ISDIR(fs.st_mode);
                INT G = fs.st_mode & S_IXUSR;
                if (S_ISLNK(fs.st_mode))
                {
                    printf("%s%s\033[0m\n", KRED, name_list[i]->d_name);
                }
                else if (J)
                {
                    printf("%s%s\033[0m\n", KBLU, name_list[i]->d_name);
                }
                else
                {
                    if (S_ISREG(fs.st_mode))
                    {
                        if (G)
                        {
                            printf("%s%s\033[0m\n", KGRN, name_list[i]->d_name);
                        }
                        else
                        {
                            printf("%s%s\033[0m\n", KWHT, name_list[i]->d_name);
                        }
                    }
                    else
                    {
                        printf("%s%s\033[0m\n", KYEL, name_list[i]->d_name);
                    }
                }
                path[len] = '\0';
                free(name_list[i]);
            }
            free(name_list);
        }
        else
        {
            INT R = 0;
            struct stat fs;
            R = lstat(string1, &fs);
            if (R == -1)
            {
                perror(NULL);
                return;
            }
            INT G = fs.st_mode & S_IXUSR;
            if (S_ISLNK(fs.st_mode))
            {
                printf("%s%s\033[0m\n", KRED, string1);
            }
            else if (S_ISREG(fs.st_mode))
            {
                if (G)
                {
                    printf("%s%s\033[0m\n", KGRN, string1);
                }
                else
                {
                    printf("%s%s\033[0m\n", KWHT, string1);
                }
            }
            else
            {
                printf("%s%s\033[0m\n", KYEL, string1);
            }
        }
    }
    else if (type == 2) // no a ,only l
    {
        INT files = 0;
        INT num_directory_entries = scandir(string1, &name_list, NULL, alphasort);
        if (num_directory_entries == -1)
        {
            if (errno == ENOTDIR)
            {
                files = 1;
            }
            else
            {
                perror(NULL);
                return;
            }
        }

        if (num_args >= 2 && files != 1)
        {
            printf("%s:\n", string1);
        }
        struct stat fs;
        INT R = 0;
        if (!files)
        {
            qsort(name_list, num_directory_entries, sizeof(name_list[0]), compare);
            INT total = 0;
            for (INT i = 0; i < num_directory_entries; i++)
            {
                char *ptr = name_list[i]->d_name;
                char ch = ptr[0];
                if ((ch != '.'))
                {
                    strcat(path, name_list[i]->d_name);
                    R = lstat(path, &fs);
                    if (R == -1)
                    {
                        perror(NULL);
                        return;
                    }
                    total += fs.st_blocks;
                    path[len] = '\0';
                }
            }
            printf("total %lld\n", total / 2);
            for (INT i = 0; i < num_directory_entries; i++)
            {
                char *ptr = name_list[i]->d_name;
                char ch = ptr[0];
                if ((ch != '.'))
                {
                    strcat(path, name_list[i]->d_name);
                    R = lstat(path, &fs);
                    if (R == -1)
                    {
                        perror(NULL);
                        return;
                    }
                    INT E;
                    INT J = S_ISDIR(fs.st_mode);
                    INT G = fs.st_mode & S_IXUSR;
                    if (S_ISLNK(fs.st_mode))
                    {
                        printf("l");
                    }
                    else
                    {
                        E = S_ISDIR(fs.st_mode) ? printf("d") : printf("-");
                    }
                    E = (fs.st_mode & S_IRUSR) ? printf("r") : printf("-");
                    E = (fs.st_mode & S_IWUSR) ? printf("w") : printf("-");
                    E = (fs.st_mode & S_IXUSR) ? printf("x") : printf("-");
                    E = (fs.st_mode & S_IRGRP) ? printf("r") : printf("-");
                    E = (fs.st_mode & S_IWGRP) ? printf("w") : printf("-");
                    E = (fs.st_mode & S_IXGRP) ? printf("x") : printf("-");
                    E = (fs.st_mode & S_IROTH) ? printf("r") : printf("-");
                    E = (fs.st_mode & S_IWOTH) ? printf("w") : printf("-");
                    E = (fs.st_mode & S_IXOTH) ? printf("x") : printf("-");
                    printf("%4ld ", fs.st_nlink);
                    uid_t user_id = fs.st_uid;
                    if (getpwuid(user_id) != NULL)
                    {
                        printf("%15s ", getpwuid(user_id)->pw_name);
                    }
                    else
                    {
                        perror("error in getpwuid");
                        return;
                    }
                    gid_t group_id = fs.st_gid;
                    if (getgrgid(group_id) != NULL)
                    {
                        printf("%15s ", getgrgid(group_id)->gr_name);
                    }
                    else
                    {
                        perror("error in getgrgid");
                        return;
                    }
                    off_t file_size = fs.st_size;
                    printf("%8ld ", file_size);
                    char buff[35];
                    struct tm *timeinfo;
                    timeinfo = localtime(&(fs.st_mtim.tv_sec));
                    INT last_modified_time = fs.st_mtim.tv_sec;
                    INT current_time = time(NULL);
                    INT six_months = 15780000;
                    INT diff = current_time - last_modified_time - six_months;
                    if (diff <= 0)
                    {
                        strftime(buff, sizeof(buff), "%b %d %H:%M", timeinfo);
                        printf("%s ", buff);
                    }
                    else
                    {
                        strftime(buff, sizeof(buff), "%b %d  %Y", timeinfo);
                        printf("%s ", buff);
                    }
                    if (S_ISLNK(fs.st_mode))
                    {
                        printf("%s%20s\033[0m\n",KRED,name_list[i]->d_name);
                    }
                    else if (J)
                    {
                        printf("%s%20s\033[0m\n", KBLU, name_list[i]->d_name);
                    }
                    else
                    {
                        if (S_ISREG(fs.st_mode))
                        {
                            if (G)
                            {
                                printf("%s%20s\033[0m\n", KGRN, name_list[i]->d_name);
                            }
                            else
                            {
                                printf("%s%20s\033[0m\n", KWHT, name_list[i]->d_name);
                            }
                        }
                        else
                        {
                            printf("%s%20s\033[0m\n", KYEL, name_list[i]->d_name);
                        }
                    }
                    free(name_list[i]);
                    path[len] = '\0';
                }
            }
            free(name_list);
        }
        else
        {
            INT R = 0;
            struct stat fs;
            R = lstat(string1, &fs);
            if (R == -1)
            {
                perror(NULL);
                return;
            }
            INT E;
            INT G = fs.st_mode & S_IXUSR;
            if (S_ISLNK(fs.st_mode))
            {
                printf("l");
            }
            else
            {
                E = S_ISDIR(fs.st_mode) ? printf("d") : printf("-");
            }
            E = (fs.st_mode & S_IRUSR) ? printf("r") : printf("-");
            E = (fs.st_mode & S_IWUSR) ? printf("w") : printf("-");
            E = (fs.st_mode & S_IXUSR) ? printf("x") : printf("-");
            E = (fs.st_mode & S_IRGRP) ? printf("r") : printf("-");
            E = (fs.st_mode & S_IWGRP) ? printf("w") : printf("-");
            E = (fs.st_mode & S_IXGRP) ? printf("x") : printf("-");
            E = (fs.st_mode & S_IROTH) ? printf("r") : printf("-");
            E = (fs.st_mode & S_IWOTH) ? printf("w") : printf("-");
            E = (fs.st_mode & S_IXOTH) ? printf("x") : printf("-");
            printf("%4ld ", fs.st_nlink);
            uid_t user_id = fs.st_uid;
            if (getpwuid(user_id) != NULL)
            {
                printf("%15s ", getpwuid(user_id)->pw_name);
            }
            else
            {
                perror("error in getpwuid");
                return;
            }
            gid_t group_id = fs.st_gid;
            if (getgrgid(group_id) != NULL)
            {
                printf("%15s ", getgrgid(group_id)->gr_name);
            }
            else
            {
                perror("error in getgrgid");
                return;
            }
            off_t file_size = fs.st_size;
            printf("%8ld ", file_size);
            char buff[35];
            struct tm *timeinfo;
            timeinfo = localtime(&(fs.st_mtim.tv_sec));
            INT last_modified_time = fs.st_mtim.tv_sec;
            INT current_time = time(NULL);
            INT six_months = 15780000;
            INT diff = current_time - last_modified_time - six_months;
            if (diff <= 0)
            {
                strftime(buff, sizeof(buff), "%b %d %H:%M", timeinfo);
                printf("%s ", buff);
            }
            else
            {
                strftime(buff, sizeof(buff), "%b %d  %Y", timeinfo);
                printf("%s ", buff);
            }
            if (S_ISLNK(fs.st_mode))
            {
                printf("%s%20s\033[0m\n", KRED, string1);
            }
            else if (S_ISREG(fs.st_mode))
            {
                if (G)
                {
                    printf("%s%20s\033[0m\n", KGRN, string1);
                }
                else
                {
                    printf("%s%20s\033[0m\n", KWHT, string1);
                }
            }
            else
            {
                printf("%s%20s\033[0m\n", KYEL, string1);
            }
        }
    }

    else if (type == 3) // both a and l
    {
        INT files = 0;
        INT num_directory_entries = scandir(string1, &name_list, NULL, alphasort);
        if (num_directory_entries == -1)
        {
            if (errno == ENOTDIR)
            {
                files = 1;
            }
            else
            {
                perror(NULL);
                return;
            }
        }

        if (num_args >= 2 && files != 1)
        {
            printf("%s:\n", string1);
        }

        struct stat fs;
        INT R = 0;
        if (!files)
        {
            qsort(name_list, num_directory_entries, sizeof(name_list[0]), compare);
            INT total = 0;
            for (INT i = 0; i < num_directory_entries; i++)
            {
                strcat(path, name_list[i]->d_name);
                R = lstat(path, &fs);
                if (R == -1)
                {
                    perror(NULL);
                    return;
                }
                total += fs.st_blocks;
                path[len] = '\0';
            }
            printf("total %lld\n", total / 2);
            for (INT i = 0; i < num_directory_entries; i++)
            {
                if (1)
                {
                    strcat(path, name_list[i]->d_name);
                    R = lstat(path, &fs);
                    if (R == -1)
                    {
                        perror(NULL);
                        return;
                    }
                    INT E;
                    INT J = S_ISDIR(fs.st_mode);
                    INT G = fs.st_mode & S_IXUSR;
                    if (S_ISLNK(fs.st_mode))
                    {
                        printf("l");
                    }
                    else
                    {
                        E = S_ISDIR(fs.st_mode) ? printf("d") : printf("-");
                    }
                    E = (fs.st_mode & S_IRUSR) ? printf("r") : printf("-");
                    E = (fs.st_mode & S_IWUSR) ? printf("w") : printf("-");
                    E = (fs.st_mode & S_IXUSR) ? printf("x") : printf("-");
                    E = (fs.st_mode & S_IRGRP) ? printf("r") : printf("-");
                    E = (fs.st_mode & S_IWGRP) ? printf("w") : printf("-");
                    E = (fs.st_mode & S_IXGRP) ? printf("x") : printf("-");
                    E = (fs.st_mode & S_IROTH) ? printf("r") : printf("-");
                    E = (fs.st_mode & S_IWOTH) ? printf("w") : printf("-");
                    E = (fs.st_mode & S_IXOTH) ? printf("x") : printf("-");
                    printf("%4ld ", fs.st_nlink);
                    uid_t user_id = fs.st_uid;
                    if (getpwuid(user_id) != NULL)
                    {
                        printf("%15s ", getpwuid(user_id)->pw_name);
                    }
                    else
                    {
                        perror("error in getpwuid");
                        return;
                    }
                    gid_t group_id = fs.st_gid;
                    if (getgrgid(group_id) != NULL)
                    {
                        printf("%15s ", getgrgid(group_id)->gr_name);
                    }
                    else
                    {
                        perror("error in getgrgid");
                        return;
                    }
                    off_t file_size = fs.st_size;
                    printf("%8ld ", file_size);
                    char buff[35];
                    struct tm *timeinfo;
                    timeinfo = localtime(&(fs.st_mtim.tv_sec));
                    INT last_modified_time = fs.st_mtim.tv_sec;
                    INT current_time = time(NULL);
                    INT six_months = 15780000;
                    INT diff = current_time - last_modified_time - six_months;
                    if (diff <= 0)
                    {
                        strftime(buff, sizeof(buff), "%b %d %H:%M", timeinfo);
                        printf("%s ", buff);
                    }
                    else
                    {
                        strftime(buff, sizeof(buff), "%b %d  %Y", timeinfo);
                        printf("%s ", buff);
                    }
                    if (S_ISLNK(fs.st_mode))
                    {
                        printf("%s%20s\033[0m\n", KRED, name_list[i]->d_name);
                    }
                    else if (J)
                    {
                        printf("%s%20s\033[0m\n", KBLU, name_list[i]->d_name);
                    }
                    else
                    {
                        if (S_ISREG(fs.st_mode))
                        {
                            if (G)
                            {
                                printf("%s%20s\033[0m\n", KGRN, name_list[i]->d_name);
                            }
                            else
                            {
                                printf("%s%20s\033[0m\n", KWHT, name_list[i]->d_name);
                            }
                        }
                        else
                        {
                            printf("%s%20s\033[0m\n", KYEL, name_list[i]->d_name);
                        }
                    }

                    free(name_list[i]);
                    path[len] = '\0';
                }
                else
                {
                    perror("Error in print_ls function");
                    return;
                }
            }
            free(name_list);
        }
        else
        {
            INT R = 0;
            struct stat fs;
            R = lstat(string1, &fs);
            if (R == -1)
            {
                perror(NULL);
                return;
            }
            INT E;
            INT G = fs.st_mode & S_IXUSR;
            if (S_ISLNK(fs.st_mode))
            {
                printf("l");
            }
            else
            {
                E = S_ISDIR(fs.st_mode) ? printf("d") : printf("-");
            }
            E = (fs.st_mode & S_IRUSR) ? printf("r") : printf("-");
            E = (fs.st_mode & S_IWUSR) ? printf("w") : printf("-");
            E = (fs.st_mode & S_IXUSR) ? printf("x") : printf("-");
            E = (fs.st_mode & S_IRGRP) ? printf("r") : printf("-");
            E = (fs.st_mode & S_IWGRP) ? printf("w") : printf("-");
            E = (fs.st_mode & S_IXGRP) ? printf("x") : printf("-");
            E = (fs.st_mode & S_IROTH) ? printf("r") : printf("-");
            E = (fs.st_mode & S_IWOTH) ? printf("w") : printf("-");
            E = (fs.st_mode & S_IXOTH) ? printf("x") : printf("-");
            printf("%4ld ", fs.st_nlink);
            uid_t user_id = fs.st_uid;
            if (getpwuid(user_id) != NULL)
            {
                printf("%15s ", getpwuid(user_id)->pw_name);
            }
            else
            {
                perror("error in getpwuid");
                return;
            }
            gid_t group_id = fs.st_gid;
            if (getgrgid(group_id) != NULL)
            {
                printf("%15s ", getgrgid(group_id)->gr_name);
            }
            else
            {
                perror("error in getgrgid");
                return;
            }
            off_t file_size = fs.st_size;
            printf("%8ld ", file_size);
            char buff[35];
            struct tm *timeinfo;
            timeinfo = localtime(&(fs.st_mtim.tv_sec));
            INT last_modified_time = fs.st_mtim.tv_sec;
            INT current_time = time(NULL);
            INT six_months = 15780000;
            INT diff = current_time - last_modified_time - six_months;
            if (diff <= 0)
            {
                strftime(buff, sizeof(buff), "%b %d %H:%M", timeinfo);
                printf("%s ", buff);
            }
            else
            {
                strftime(buff, sizeof(buff), "%b %d  %Y", timeinfo);
                printf("%s ", buff);
            }
            if (S_ISLNK(fs.st_mode))
            {
                printf("%s%20s\033[0m\n", KRED, string1);
            }
            else if (S_ISREG(fs.st_mode))
            {
                if (G)
                {
                    printf("%s%20s\033[0m\n", KGRN, string1);
                }
                else
                {
                    printf("%s%20s\033[0m\n", KWHT, string1);
                }
            }
            else
            {
                printf("%s%20s\033[0m\n", KYEL, string1);
            }
        }
    }
}

void ls_func(char *string[], char *correct_path, long long int num_tokens)
{
    INT extra_info = 0;
    INT hidden = 0;
    INT num_commands = 0;
    INT total_commands = 0;
    for (INT i = 0; i < num_tokens; i++)
    {
        if (string[i][0] == '-')
        {
            total_commands++;

            if (strcmp(string[i], "-l") == 0)
            {
                extra_info = 1;
            }
            else if ((strcmp(string[i], "-a") == 0))
            {
                hidden = 1;
            }
            else if ((strcmp(string[i], "-la") == 0))
            {
                extra_info = 1;
                hidden = 1;
            }
            else if ((strcmp(string[i], "-al") == 0))
            {
                extra_info = 1;
                hidden = 1;
            }
            else
            {
                perror("Incorrect argument supplied to command ls");
                return;
            }
        }
        else
        {
            num_commands++;
            total_commands++;
        }
    }
    if (extra_info)
    {
        if (hidden)
        {
            if (num_commands == 0)
            {
                print_ls(".", correct_path, 3, 0);
            }
            else
            {
                for (INT i = 0; i < num_tokens; i++)
                {
                    if (string[i][0] != '-')
                    {
                        print_ls(string[i], correct_path, 3, num_commands);
                    }
                }
            }
        }
        else
        {
            if (num_commands == 0)
            {
                print_ls(".", correct_path, 2, 0);
            }
            else
            {
                for (INT i = 0; i < num_tokens; i++)
                {
                    if (string[i][0] != '-')
                    {
                        print_ls(string[i], correct_path, 2, num_commands);
                    }
                }
            }
        }
    }
    else
    {
        if (hidden)
        {
            if (num_commands == 0)
            {
                print_ls(".", correct_path, 1, 0);
            }
            else
            {
                for (INT i = 0; i < num_tokens; i++)
                {
                    if (string[i][0] != '-')
                    {
                        print_ls(string[i], correct_path, 1, num_commands);
                    }
                }
            }
        }
        else
        {
            if (num_commands == 0)
            {
                print_ls(".", correct_path, 0, 0);
            }
            else
            {
                for (INT i = 0; i < num_tokens; i++)
                {
                    if (string[i][0] != '-')
                    {
                        print_ls(string[i], correct_path, 0, num_commands);
                    }
                }
            }
        }
    }
}
