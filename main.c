#include "headers.h"
INT num_bg_processes;
time_t start_seconds;
typedef long long int INT;
List *LIST;
char *correct_path;
char *previous_path;
char *relative_path;
char *absolute_path;
char *user_name;
char *system_name;
char *H[20];
char *history_path;
INT total_commands = 0;
#define NAME_MAX1 300
INT prompt_wait;
void die(const char *s)
{
    perror(s);
    exit(1);
}
struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

int main(int argc, char *argv[])
{
    absolute_path = (char *)calloc(300, sizeof(char));
    relative_path = (char *)calloc(300, sizeof(char));
    previous_path = (char *)calloc(300, sizeof(char));
    correct_path = (char *)calloc(300, sizeof(char));
    user_name = (char *)calloc(200, sizeof(char));
    system_name = (char *)calloc(200, sizeof(char));
    char *Time = (char *)calloc(300, sizeof(char));
    history_path = (char *)calloc(625, sizeof(char));
    Time[0] = '\0';
    LIST = (List *)malloc(sizeof(List));
    LIST->root = NULL;
    LIST->tail = NULL;
    previous_path[0] = '#';
    previous_path[1] = '\0';
    for (INT i = 0; i < 20; i++)
    {
        H[i] = (char *)calloc(NAME_MAX1, sizeof(char));
    }
    getcwd(absolute_path, 300);
    getcwd(correct_path, 300);
    user_name = getlogin();
    gethostname(system_name, 200);
    relative_path[0] = '~';
    relative_path[1] = '\0';
    char *input = (char *)calloc(1000, sizeof(char));
    char *ptr = input;
    num_bg_processes = 0;
    strcat(history_path, correct_path);
    strcat(history_path, "/history.txt");
    INT D = strlen(history_path);
    history_path[D] = '\0';
    total_commands = readfromhistory();
    prompt_wait = 0;
    char *inp = malloc(sizeof(char) * 1000);
    char c;
    while (1)
    {
        setbuf(stdout, NULL);
        enableRawMode();
        memset(inp, '\0', 1000);
        int pt = 0;
        size_t size = 100;
        prompt(Time);
        char *tokens[1000];
        signal(SIGINT, ctrlc);
        signal(SIGTSTP, ctrlz);
        prompt_wait = 1;
        INT return_value = 0;

        /**********************************************/

        while (read(STDIN_FILENO, &c, 1) == 1)
        {
            INT inp_len = strlen(inp);
            INT start_index = 0;
            INT end_index = 0;
            INT space_flag = 1;
            for (INT i = 0; i < inp_len; i++)
            {
                if (inp[i] == ' ')
                {
                    space_flag = 1;
                }
                else
                {
                    if (space_flag)
                    {
                        start_index = i;
                        end_index = i;
                        space_flag = 0;
                    }
                    else
                    {
                        end_index++;
                    }
                }
            }
            INT slash_index = start_index - 1;
            INT empty_index = -1;
            INT slash_flag = 0;
            for (INT u = end_index; u >= start_index; u--)
            {
                if (inp[u] == '/')
                {
                    slash_flag = 1;
                    slash_index = u;
                    break;
                }
            }
            if (iscntrl(c))
            {
                if (c == 10)
                {
                    printf("\n");
                    break;
                }
                else if (c == 27)
                {
                    char buf[3];
                    buf[2] = 0;
                    if (read(STDIN_FILENO, buf, 2) == 2)
                    { // length of escape code
                        printf("\rarrow key: %s", buf);
                    }
                }
                else if (c == 127)
                { // backspace
                    if (pt > 0)
                    {
                        if (inp[pt - 1] == 9)
                        {
                            for (int i = 0; i < 7; i++)
                            {
                                printf("\b");
                            }
                        }
                        inp[--pt] = '\0';
                        printf("\b \b");
                    }
                }
                else if (c == 9)
                { // TAB character
                    if (slash_flag)
                    {
                        INT tab_dir_length = 0;
                        char *tab_dir_string = (char *)calloc(1000, sizeof(char));
                        for (INT l = start_index; l <= slash_index; l++)
                        {
                            tab_dir_string[tab_dir_length] = inp[l];
                            tab_dir_length++;
                        }
                        tab_dir_string[tab_dir_length] = '\0';
                        INT find_length = 0;
                        char *find_string = (char *)calloc(1000, sizeof(char));
                        for (INT l = slash_index + 1; l <= end_index; l++)
                        {
                            find_string[find_length] = inp[l];
                            find_length++;
                        }
                        find_string[find_length] = '\0';
                        if (tab_dir_string[0] == '~')
                        {
                            char *final_tab_dir_string = (char *)calloc(1100, sizeof(char));
                            strcat(final_tab_dir_string, correct_path);
                            INT final_length = strlen(final_tab_dir_string);
                            final_tab_dir_string[final_length] = '\0';
                            strcat(final_tab_dir_string, &tab_dir_string[1]);
                            return_value = autocomplete(final_tab_dir_string, find_string, inp, slash_index, end_index);
                            if (return_value == -2)
                            {
                                break;
                            }
                            pt = strlen(inp);
                        }
                        else
                        {
                            return_value = autocomplete(tab_dir_string, find_string, inp, slash_index, end_index);
                            if (return_value == -2)
                            {
                                break;
                            }
                            pt = strlen(inp);
                        }
                    }
                    else
                    {
                        INT find_length = 0;
                        char *find_string = (char *)calloc(1000, sizeof(char));
                        for (INT l = slash_index + 1; l <= end_index; l++)
                        {
                            find_string[find_length] = inp[l];
                            find_length++;
                        }
                        //  printf("start_index is %lld slash_index is %lld  and end_index is %lld\n", start_index, slash_index, end_index);
                        find_string[find_length] = '\0';
                        //  printf("find_string is %s\n", find_string);
                        char *dir = (char *)calloc(2, sizeof(char));
                        dir[0] = '.';
                        dir[1] = '\0';
                        return_value = autocomplete(dir, find_string, inp, slash_index, end_index);
                        if (return_value == -2)
                        {
                            break;
                        }
                        pt = strlen(inp);
                    }
                }
                else if (c == 4)
                {
                    printf("\n");
                    exit(0);
                }
                else
                {
                    printf("%d\n", c);
                }
            }
            else
            {
                inp[pt++] = c;
                printf("%c", c);
            }
        }
        if (return_value == -2)
        {
            return_value = 0;
            continue;
        }
        disableRawMode();

        /*************************************************/
        strcpy(input, inp);
        INT Y = strlen(input);
        prompt_wait = 0;
        time(&start_seconds);
        input[Y] = '\0';
        INT flag6 = 1;
        INT flag7 = 0;
        for (INT i = 0; i < Y; i++)
        {
            for (INT j = i + 1; j < Y; j++)
            {
                if ((input[i] == ';') && (input[j] == ';'))
                {
                    flag7 = 1;
                    for (INT k = i + 1; k < j; k++)
                    {
                        if ((input[k] != '\t') && (input[k] != ' ') && (input[k] != '\n'))
                        {
                            flag6 = 0;
                            break;
                        }
                    }
                    if (!flag6)
                    {
                        break;
                    }
                }
                else if ((input[i] == ';') && (input[j] == '&'))
                {
                    flag7 = 1;
                    for (INT k = i + 1; k < j; k++)
                    {
                        if ((input[k] != '\t') && (input[k] != ' ') && (input[k] != '\n'))
                        {
                            flag6 = 0;
                            break;
                        }
                    }
                    if (!flag6)
                    {
                        break;
                    }
                }
                else if ((input[i] == '&') && (input[j] == ';'))
                {
                    flag7 = 1;
                    for (INT k = i + 1; k < j; k++)
                    {
                        if ((input[k] != '\t') && (input[k] != ' ') && (input[k] != '\n'))
                        {
                            flag6 = 0;
                            break;
                        }
                    }
                    if (!flag6)
                    {
                        break;
                    }
                }
                else if ((input[i] == '&') && (input[j] == '&'))
                {
                    flag7 = 1;
                    for (INT k = i + 1; k < j; k++)
                    {
                        if ((input[k] != '\t') && (input[k] != ' ') && (input[k] != '\n'))
                        {
                            flag6 = 0;
                            break;
                        }
                    }
                    if (!flag6)
                    {
                        break;
                    }
                }
            }
            if (!flag6)
            {
                break;
            }
        }
        writetohistory(&H[0], input);
        INT token_count = 0;
        if (flag6 && flag7)
        {
            perror("invalid syntax given as input");
            continue;
        }
        char *p = strstr(input, ";;");
        if (p)
        {
            perror("syntax error near unexpected token `;;'");
            continue;
        }
        else
        {
            tokens[token_count] = strtok(input, ";");
            INT length = strlen(input);
            while (tokens[token_count] != NULL)
            {
                token_count++;
                tokens[token_count] = strtok(NULL, ";");
            }
            for (INT i = 0; i < token_count; i++)
            {
                str_tok_and(tokens[i], relative_path, correct_path, previous_path, length, LIST);
            }
        }
        prompt_wait = 1;
        num_bg_processes = 0;
        time_t end_time;
        time(&end_time);
        long int U = end_time - start_seconds;
        if (U >= 1)
        {
            Time[0] = '\0';
            sprintf(Time, "took %lds", U);
        }
        else
        {
            Time[0] = '\0';
        }
    }
    free(absolute_path);
    free(relative_path);
    free(history_path);
    free(user_name);
    free(previous_path);
    free(correct_path);
    free(system_name);
    free(Time);
}