#ifndef _MYDLL_H
#define _MYDLL_H

typedef struct node* NodePtr ;
typedef NodePtr Position ;

struct node{

	int Element ;
	char* process_name;
	char* full_name;
	int idx;
	Position Next;
    Position Prev;
};

typedef struct my_dll{
struct node* root;
struct node* tail; 
}List;

NodePtr MakeNode(int X,char* process_name,char* full_name,int index); 
int get_size(List* L);
int find(List* L,int x,char* string);
char* find_string(List* L,int x);
char* find_full_name(List* L,int x);
void insert(List* L,int x,char* process_name,char* full_name,int index);
int DELETE(List* L,int index);
int IsEmpty(List* L);
int find_index(List* L);


#endif







