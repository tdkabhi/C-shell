#ifndef __PROCESS_COMMAND_H
#define __PROCESS_COMMAND_H
#include "headers.h"
long long int str_tok_whitespaces(char* string[],char* string1);
long long int process_command(char* string,char* string1,char* string2,char* string3,long long int len,long long int last,List* LIST);

#endif