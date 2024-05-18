#include "headers.h"
INT io_redirect(char *string[], INT num_tokens, INT type_io[2], INT io_index[2], INT num_types)
{
    if (num_types == 2)
    {
        if (type_io[0] == 0)
        {
            if (io_index[0] != num_tokens - 1)
            {
                INT fd = open(string[io_index[0] + 1], O_RDONLY);
                if (fd == -1)
                {
                    perror(NULL);
                    return -1;
                }
                else
                {

                    INT dup_return = dup2(fd, 0);
                    if (dup_return == -1)
                    {
                        perror(NULL);
                        return -1;
                    }
                    close(fd);
                    return 0;
                }
            }
            else
            {
                perror("last token is <,which is not valid");
                return -1;
            }
        }
        else if (type_io[0] == 1)
        {
            if (io_index[0] != num_tokens - 1)
            {
                INT fd = open(string[io_index[0] + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                {
                    perror(NULL);
                    return -1;
                }
                else
                {
                    INT dup_return = dup2(fd, 1);
                    if (dup_return == -1)
                    {
                        perror(NULL);
                        return -1;
                    }
                    close(fd);
                    return 0;
                }
            }
            else
            {
                perror("last token is >,which is not valid");
                return -1;
            }
        }
        else if (type_io[0] == 2)
        {
            if (io_index[0] != num_tokens - 1)
            {
                INT fd = open(string[io_index[0] + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd == -1)
                {
                    perror(NULL);
                    return -1;
                }
                else
                {
                    INT dup_return = dup2(fd, 1);
                    if (dup_return == -1)
                    {
                        perror(NULL);
                        return -1;
                    }
                    close(fd);
                    return 0;
                }
            }
            else
            {
                perror("last token is >>,which is not valid");
                return -1;
            }
        }
        //
        if (type_io[1] == 0)
        {
            if (io_index[1] != num_tokens - 1)
            {
                INT fd = open(string[io_index[1] + 1], O_RDONLY);
                if (fd == -1)
                {
                    perror(NULL);
                    return -1;
                }
                else
                {
                    INT dup_return = dup2(fd, 0);
                    if (dup_return == -1)
                    {
                        perror(NULL);
                        return -1;
                    }
                    close(fd);
                    return 0;
                }
            }
            else
            {
                perror("last token is <,which is not valid");
                return -1;
            }
        }
        else if (type_io[1] == 1)
        {
            if (io_index[1] != num_tokens - 1)
            {
                INT fd = open(string[io_index[1] + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                {
                    perror(NULL);
                    return -1;
                }
                else
                {
                    INT dup_return = dup2(fd, 1);
                    if (dup_return == -1)
                    {
                        perror(NULL);
                        return -1;
                    }
                    close(fd);
                    return 0;
                }
            }
            else
            {
                perror("last token is >,which is not valid");
                return -1;
            }
        }
        else if (type_io[1] == 2)
        {
            if (io_index[1] != num_tokens - 1)
            {
                INT fd = open(string[io_index[1] + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd == -1)
                {
                    perror(NULL);
                    return -1;
                }
                else
                {
                    INT dup_return = dup2(fd, 1);
                    if (dup_return == -1)
                    {
                        perror(NULL);
                        return -1;
                    }
                    close(fd);
                    return 0;
                }
            }
            else
            {
                perror("last token is >>,which is not valid");
                return -1;
            }
        }
    }
    else if (num_types == 1)
    {
        if (type_io[0] == 0)
        {
            if (io_index[0] != num_tokens - 1)
            {
                INT fd = open(string[io_index[0] + 1], O_RDONLY);
                if (fd == -1)
                {
                    perror(NULL);
                    return -1;
                }
                else
                {
                    INT dup_return = dup2(fd, 0);
                    if (dup_return == -1)
                    {
                        perror(NULL);
                        return -1;
                    }
                    close(fd);
                    return 0;
                }
            }
            else
            {
                perror("last token is <,which is not valid");
                return -1;
            }
        }
        else if (type_io[0] == 1)
        {
            if (io_index[0] != num_tokens - 1)
            {
                INT fd = open(string[io_index[0] + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                {
                    perror(NULL);
                    return -1;
                }
                else
                {
                    INT dup_return = dup2(fd, 1);
                    if (dup_return == -1)
                    {
                        perror(NULL);
                        return -1;
                    }
                    close(fd);
                    return 0;
                }
            }
            else
            {
                perror("last token is >,which is not valid");
                return -1;
            }
        }
        else if (type_io[0] == 2)
        {
            if (io_index[0] != num_tokens - 1)
            {
                INT fd = open(string[io_index[0] + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd == -1)
                {
                    close(fd);
                    perror((NULL));
                    return -1;
                }
                else
                {
                    INT dup_return = dup2(fd, 1);
                    if (dup_return == -1)
                    {
                        perror(NULL);
                        return -1;
                    }
                    close(fd);
                    return 0;
                }
            }
            else
            {
                perror("last token is >>,which is not valid");
                return -1;
            }
        }
    }
    return -1;
}
