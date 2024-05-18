#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main(void)
{
   
    List *LIST;
    LIST = (List *)malloc(sizeof(List));
    LIST->root = NULL;
    LIST->tail = NULL;
    char ch[15];

    while (1)
    {
        scanf("%s", ch);
        if (strcmp(ch,"insert") == 0)
        {
            int x;
            scanf("%d", &x); 
            insert(LIST, x);
        }
        else if (strcmp(ch,"insert_at") == 0)
        {
            int x,y;
            scanf("%d",&x);
            scanf("%d",&y);
           insert_at(LIST,x,y);
        }
        else if (strcmp(ch,"prune")==0)
        {
            prune(LIST);
        }
        else if (strcmp(ch,"print")==0)
        {
            print(LIST);
        }
        else if (strcmp(ch,"print_reverse")==0)
        {
            print_reverse(LIST);
        }
        else if(strcmp(ch,"get_size")==0)
        {
            printf("%d\n",get_size(LIST));
        }
        else if(strcmp(ch,"delete")==0)
        {
            int x;
            scanf("%d",&x);
            delete(LIST,x);
        }
    }
    return 0;
}