#include "historyFuncs.h"
#include "ListFuncs.h"


HistoryList* addToHistory(char* arr[], char* command, int index, HistoryList* lst)
{

	CommandNode* node;
	int i = 0, indexOfHistory;

	if (index < N)
	{
		arr[index] = command;
	}
	else
	{//short history is full
		if (lst->head == NULL) //find the number of the current command;
			indexOfHistory = 1;
		else
			indexOfHistory = (lst->tail->numOfCommand) + 1;

		int length = strlen(command) + 1;

		node = (CommandNode*)malloc(sizeof(CommandNode));
		node->command = (char*)malloc(sizeof(char)*strlen(arr[0]) + 1);
		strcpy(node->command, arr[0]);
		node->command[strlen(arr[0])] = '\0';
		node->numOfCommand = indexOfHistory;
		node->next = NULL;
		insertNodeToEndHistoryList(lst, node);

		for (int i = 0; i < (N - 1); i++)
		{
			arr[i] = arr[i + 1];
		}
		arr[N - 1] = command;
	}

	return lst;
}


void printShortHistory(char* arr[], int index, HistoryList* lst)
{//function gets array of shrot history and index of how many commands was so far
	int num;
	int flag = 1;

	if (index < N)
		num = 1;
	else
		num = (lst->tail->numOfCommand) + 1;

	for (int i = 0; i < N&&arr[i] != NULL; i++)
	{
		printf("%d: %s\n", num, arr[i]);
		num++;
	}
}

void printHistory(char* arr[], int index, HistoryList* lst)
{//function gets array of shrot history and index of how many commands was so far, and list of old history
	CommandNode* temp;
	if (index <= N)
		printShortHistory(arr, index, lst);
	else
	{

		temp = lst->head;
		while (temp != NULL)
		{

			printf("%d: %s\n", (temp->numOfCommand), temp->command);
			temp = temp->next;
		}
		printShortHistory(arr, index, lst);

	}

}

void freeOldHistory(HistoryList* lst)
{
	CommandNode* temp = lst->head;
	CommandNode* temp2;
	while (temp != NULL)
	{
		temp2 = temp;
		free(temp->command);
		temp = temp->next;
		free(temp2);
	}
	free(lst);
}

void freeShortHistory(char* arr[], int size)
{
	if (size > (N - 1))
	{
		for (int i = 0; i < N; i++)
			if (arr[i])
				free(arr[i]);
	}
	else
	{
		for (int i = 0; i < (N - (N - size)); i++)
			free(arr[i]);
	}

}