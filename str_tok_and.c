#include "headers.h"
void str_tok_and(char *string, char *relative, char *correct, char *previous, INT len,List* LIST)
{
    char *tokens[1000];
    INT token_count = 0;
    char *final_string = (char *)calloc(600, sizeof(char));
    strcpy(final_string, string);
    INT final_length = strlen(final_string);
    final_string[final_length] = ' ';
    final_string[final_length + 1] = '\0';
    tokens[token_count] = strtok(final_string, "&");
    while (tokens[token_count] != NULL)
    {
        token_count++;
        tokens[token_count] = strtok(NULL, "&");
    }
    for (INT i = 0; i < token_count - 1; i++)
    {
        pipe_to_process_command(tokens[i], relative, correct, previous, len, 0,LIST);
    }
    pipe_to_process_command(tokens[token_count - 1], relative, correct, previous, len, 1,LIST);
}
