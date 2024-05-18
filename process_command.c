#include "headers.h"
INT str_tok_whitespaces(char *tokens[], char *input)
{
    long long int Token_count = 0;
    tokens[Token_count] = strtok(input, " \t");
    while (tokens[Token_count] != NULL)
    {
        Token_count++;
        tokens[Token_count] = strtok(NULL, " \t");
    }
    return Token_count;
}
long long int process_command(char *string, char *relative, char *correct, char *previous, INT len, INT last, List *LIST)
{
    char *token[1000];
    char *reuse_string = (char *)calloc(1000, sizeof(char));
    strcpy(reuse_string, string);
    INT reuse_len = strlen(reuse_string);
    reuse_string[reuse_len] = '\0';
    INT num_tokens = str_tok_whitespaces(token, string);
    if ((token[0] != NULL) || (len == 0))
    {
        INT io_index[2]; // storing index
        io_index[0] = -1;
        io_index[1] = -1;
        INT type_io[2]; // storing type of io as number
        type_io[0] = -1;
        type_io[1] = -1;
        INT num_io_type = 0;
        INT io_flag = 0;
        INT less_than = 0;
        INT greater_than = 0;
        INT double_greater_than = 0;
        for (INT i = 0; i < num_tokens; i++)
        {
            if (strcmp(token[i], "<") == 0)
            {
                if (num_io_type > 1)
                {
                    perror("Too many i/o redirection arguments in one token of command");
                    return -1;
                }
                if (less_than)
                {
                    perror("multiple instances of < are not allowed in a single command");
                    return -1;
                }
                less_than = 1;
                if (i != num_tokens - 1)
                {
                    io_flag = 1;
                    io_index[num_io_type] = i;
                    type_io[num_io_type] = 0;
                    num_io_type++;
                }
                else
                {
                    perror("last token is <,which is not valid");
                    return -1;
                }
            }
            else if (strcmp(token[i], ">") == 0)
            {
                if (num_io_type > 1)
                {
                    perror("Too many i/o redirection arguments in one token of command");
                    return -1;
                }
                if (greater_than)
                {
                    perror("multiple instances of > are not allowed in a single command");
                    return -1;
                }
                greater_than = 1;
                if (i != num_tokens - 1)
                {
                    io_flag = 1;
                    io_index[num_io_type] = i;
                    type_io[num_io_type] = 1;
                    num_io_type++;
                }
                else
                {
                    perror("last token is >,which is not valid");
                    return -1;
                }
            }
            else if (strcmp(token[i], ">>") == 0)
            {
                if (num_io_type > 1)
                {
                    perror("Too many i/o redirection arguments in one token of command");
                    return -1;
                }
                if (double_greater_than)
                {
                    perror("multiple instances of >> are not allowed in a single command");
                    return -1;
                }
                double_greater_than = 1;
                if (i != num_tokens - 1)
                {
                    io_flag = 1;
                    io_index[num_io_type] = i;
                    type_io[num_io_type] = 2;
                    num_io_type++;
                }
                else
                {
                    perror("last token is >>,which is not valid");
                    return -1;
                }
            }
        }
        if (io_flag)
        {
            INT std_out = dup(1);
            INT std_in = dup(0);
            INT io_return = io_redirect(&token[0], num_tokens, type_io, io_index, num_io_type);
            if (io_return == -1)
            {
                INT dup_return;
                dup_return = dup2(std_in, 0);
                if (dup_return == -1)
                {
                    perror(NULL);
                    return -1;
                }
                dup_return = dup2(std_out, 1);
                if (dup_return == -1)
                {
                    perror(NULL);
                    return -1;
                }
                return -1;
            }
            else if (io_return == 0)
            {
                INT num_new_tokens = 0;
                char *tokens_new[num_tokens];
                for (INT i = 0; i < num_tokens; i++)
                {
                    if ((strcmp(token[i], "<") == 0) || (strcmp(token[i], ">") == 0) || (strcmp(token[i], ">>") == 0))
                    {
                        i++;
                    }
                    else
                    {
                        tokens_new[num_new_tokens] = token[i];
                        num_new_tokens++;
                    }
                }
                //
                if (strcmp(tokens_new[0], "cd") == 0)
                {
                    if (&tokens_new[1] != NULL)
                    {
                        cd_func(&tokens_new[1], num_new_tokens - 1, relative, correct, previous);
                        INT len = strlen(previous);
                        previous[len] = '\0';
                    }
                    else
                    {
                        perror("syntax error");
                        return -1;
                    }
                }
                else if (strcmp(tokens_new[0], "pwd") == 0)
                {
                    pwd_func(num_new_tokens - 1);
                }
                else if (strcmp(tokens_new[0], "echo") == 0)
                {
                    echo_func(&tokens_new[1], num_new_tokens - 1);
                }
                else if (strcmp(tokens_new[0], "ls") == 0)
                {
                    ls_func(&tokens_new[1], correct, num_new_tokens - 1);
                }
                else if (strcmp(tokens_new[0], "history") == 0)
                {
                    if (num_new_tokens == 1)
                    {
                        print_history();
                    }
                    else
                    {
                        perror("Too many arguments for history");
                        return -1;
                    }
                }
                else if (strcmp(tokens_new[0], "discover") == 0)
                {

                    discover_func(&tokens_new[1], correct, num_new_tokens - 1);
                }
                else if (strcmp(tokens_new[0], "pinfo") == 0)
                {
                    if (num_new_tokens <= 2)
                    {
                        pinfo(&tokens_new[1], num_new_tokens - 1, correct);
                    }
                    else
                    {
                        perror("Too many arguments for command pinfo");
                        return -1;
                    }
                }
                else if (strcmp(tokens_new[0], "jobs") == 0)
                {
                    if (num_new_tokens <= 2)
                    {
                        jobs(&tokens_new[1], num_new_tokens - 1, LIST);
                    }
                    else
                    {
                        perror("Too many arguments for command jobs");
                        return -1;
                    }
                }
                else if (strcmp(tokens_new[0], "sig") == 0)
                {
                    if (num_new_tokens == 3)
                    {
                        sig_func(&tokens_new[1], num_new_tokens - 1, LIST);
                    }
                    else
                    {
                        perror("Too many arguments for command sig");
                        return -1;
                    }
                }
                else if (strcmp(tokens_new[0], "fg") == 0)
                {
                    if (num_new_tokens == 2)
                    {
                        FG(&tokens_new[1], num_new_tokens - 1, LIST);
                    }
                    else
                    {
                        perror("Too many arguments for command fg");
                        return -1;
                    }
                }
                else if (strcmp(tokens_new[0], "bg") == 0)
                {
                    if (num_new_tokens == 2)
                    {
                        BG(&tokens_new[1], num_new_tokens - 1, LIST);
                    }
                    else
                    {
                        perror("Too many arguments for command bg");
                        return -1;
                    }
                }
                else
                {
                    if ((strlen(tokens_new[0]) != 0))
                    {
                        spec4_func(&tokens_new[0], correct, last, LIST, num_new_tokens, reuse_string);
                    }
                    else
                    {
                        perror("syntax error");
                        return -1;
                    }
                }
                fflush(stdout);
                INT dup_return = dup2(std_in, 0);
                if (dup_return == -1)
                {
                    perror(NULL);
                    return -1;
                }
                dup_return = dup2(std_out, 1);
                if (dup_return == -1)
                {
                    perror(NULL);
                    return -1;
                }
                close(std_in);
                close(std_out);
            }
        }
        else
        {
            // builtin commands no io
            if (strcmp(token[0], "cd") == 0)
            {
                if (&token[1] != NULL)
                {
                    cd_func(&token[1], num_tokens - 1, relative, correct, previous);
                    INT len = strlen(previous);
                    previous[len] = '\0';
                }
                else
                {
                    perror("syntax error");
                    return -1;
                }
            }
            else if (strcmp(token[0], "pwd") == 0)
            {
                pwd_func(num_tokens - 1);
            }
            else if (strcmp(token[0], "echo") == 0)
            {
                echo_func(&token[1], num_tokens - 1);
            }
            else if (strcmp(token[0], "ls") == 0)
            {
                ls_func(&token[1], correct, num_tokens - 1);
            }
            else if (strcmp(token[0], "history") == 0)
            {
                if (num_tokens == 1)
                {
                    print_history();
                }
                else
                {
                    perror("Too many arguments for history");
                    return -1;
                }
            }
            else if (strcmp(token[0], "discover") == 0)
            {

                discover_func(&token[1], correct, num_tokens - 1);
            }
            else if (strcmp(token[0], "pinfo") == 0)
            {
                if (num_tokens <= 2)
                {
                    pinfo(&token[1], num_tokens - 1, correct);
                }
                else
                {
                    perror("Too many arguments for command pinfo");
                    return -1;
                }
            }
            else if (strcmp(token[0], "jobs") == 0)
            {
                if (num_tokens <= 2)
                {
                    jobs(&token[1], num_tokens - 1, LIST);
                }
                else
                {
                    perror("Too many arguments for command jobs");
                    return -1;
                }
            }
            else if (strcmp(token[0], "sig") == 0)
            {
                if (num_tokens == 3)
                {
                    sig_func(&token[1], num_tokens - 1, LIST);
                }
                else
                {
                    perror("Too many arguments for command sig");
                    return -1;
                }
            }
            else if (strcmp(token[0], "fg") == 0)
            {
                if (num_tokens == 2)
                {
                    FG(&token[1], num_tokens - 1, LIST);
                }
                else
                {
                    perror("Too many arguments for command fg");
                    return -1;
                }
            }
            else if (strcmp(token[0], "bg") == 0)
            {
                if (num_tokens == 2)
                {
                    BG(&token[1], num_tokens - 1, LIST);
                }
                else
                {
                    perror("Too many arguments for command bg");
                    return -1;
                }
            }
            else
            {
                if ((strlen(token[0]) != 0))
                {
                    spec4_func(&token[0], correct, last, LIST, num_tokens, reuse_string);
                }
                else
                {
                    perror("syntax error");
                    return -1;
                }
            }
        }
    }
    return -1;
}
