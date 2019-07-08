#include "ListFuncs.h"


void reverse(CommandNode** head)
{
	CommandNode* prev = NULL;
	CommandNode* current = *head;
	CommandNode* next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}







void makeEmptyList(ApartmentList* l)
{
	l->head = l->tail = NULL;
}

void makeEmptyHistoryList(HistoryList* l)
{
	l->head = l->tail = NULL;
}


void insertNodeToEndHistoryList(HistoryList *lst, CommandNode *tail)
{
	if (lst->head == NULL)
	{
		lst->head = tail;
		lst->tail = tail;
	}
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
}


void insertNodeToEndList(ApartmentList *lst, ApartmentNode *tail)
{
	if (lst->head == NULL)
	{
		lst->head = tail;
		lst->tail = tail;
	}
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
}

void freeNode(ApartmentNode* lst)
{
	free(lst->address);
	free(lst);
}