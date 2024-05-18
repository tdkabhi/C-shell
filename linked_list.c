#include "headers.h"

int IsEmpty(List *L)
{
	return (L->root == NULL && L->tail == NULL);
}
int get_size(List *L)
{

	NodePtr P = L->root;
	int ans = 1;
	int x = IsEmpty(L);
	if (x == 1)
	{
		return 0;
	}
	while (P->Next != NULL)
	{
		ans++;
		P = P->Next;
	}
	return ans;
}
NodePtr MakeNode(int X, char *string,char* full_process_name,int index)
{
	NodePtr P = (NodePtr)malloc(sizeof(struct node));
	assert(P != NULL);
	P->Element = X;
	P->process_name = (char *)malloc(600 * sizeof(char));
	P->full_name=(char*)malloc(700*sizeof(char));
	strcpy(P->process_name, string);
	strcpy(P->full_name,full_process_name);
	P->idx=index;
	P->Next = NULL;
	P->Prev = NULL;
	return P;
}

int DELETE(List *L, int index)
{
	NodePtr P = L->root;
	int i = 0;

	if (get_size(L) == 1)
	{
		if (index == 0)
		{
			free(P);
			L->root = NULL;
			L->tail = NULL;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		if ((index >= get_size((L)) && (index < 0)))
		{
			return -1;
		}
		else
		{
			while (P != NULL)
			{
				if (i == index)
				{
					if (index == get_size(L) - 1)
					{
						L->tail->Next = NULL;
						L->tail = P->Prev;
						P->Prev->Next = NULL;
						free(P);
						return 1;
					}
					else
					{
						if (index == 0)
						{
							NodePtr X = L->root;
							L->root = L->root->Next;
							L->root->Prev = NULL;
							free(X);
							return 1;
						}
						else
						{
							P->Next->Prev = P->Prev;
							P->Prev->Next = P->Next;
							free(P);
							return 1;
						}
					}

					break;
				}
				P = P->Next;
				i++;
			}
		}
	}
	return -1;
}

void insert(List *L, int x, char *string,char* full_name,int index)
{
	if (IsEmpty(L))
	{
		L->root = MakeNode(x, string,full_name,index);
		L->tail = L->root;
	}
	else
	{
		NodePtr P = L->tail;
		P->Next = MakeNode(x, string,full_name,index);
		P->Next->Prev = P;
		L->tail = P->Next;
	}
}
int find(List *L, int X, char *string)
{
	NodePtr P = L->root;
	int index = 0;
	int ans = -1;
	while (P != NULL)
	{
		if ((P->Element) == X)
		{
			ans = index;
			return ans;
		}
		index++;
		P = P->Next;
	}
	return -1;
}
char *find_string(List *L, int X)
{
	NodePtr P = L->root;
	int index = 0;
	int ans = -1;
	while (P != NULL)
	{
		if ((P->Element) == X)
		{
			char *Y = P->process_name;
			return Y;
		}
		index++;
		P = P->Next;
	}
	return NULL;
}
int find_index(List* L)
{
	if(L!=NULL&&L->root!=NULL&&L->tail!=NULL)
	{
		return L->tail->idx+1;
	}
	return 1;
}
char *find_full_name(List *L, int X)
{
	NodePtr P = L->root;
	int index = 0;
	int ans = -1;
	while (P != NULL)
	{
		if ((P->Element) == X)
		{
			char *Y = P->full_name;
			return Y;
		}
		index++;
		P = P->Next;
	}
	return NULL;
}