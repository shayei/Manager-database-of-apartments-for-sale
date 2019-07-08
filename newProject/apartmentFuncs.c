#include "apartmentFuncs.h"
#include "dateFuncs.h" 
#include "ListFuncs.h"
#include "generalFuncs.h"
#include "getAnAptFuncs.h"



char* getInput()
{//get the input from the user
	int logSize = 0, phySize = 1;
	char ch;
	char* st = (char*)malloc(phySize * sizeof(char));

	ch = getchar();
	while (ch != '\n')
	{
		st[logSize] = ch;
		logSize++;
		ch = getchar();
		if (logSize == phySize)
		{
			phySize *= 2;
			st = (char*)realloc(st, sizeof(char)*phySize);
		}
	}
	st = (char*)realloc(st, sizeof(char)*(logSize + 1));
	st[logSize] = '\0';
	return st;
}

void getAction(char* st, char** actToDo, char** content)
{
	char *temp = duplicateString(st);
	*actToDo = strtok(temp, " ");
	*content = strtok(NULL, "\n");

}


void doAction(char* actToDo, char* content, ApartmentList* l, short int* countApt)
{

	if (strcmp(actToDo, "get-an-apt") == 0)
	{
		getAnApt(content, l);
	}
	else if (strcmp(actToDo, "add-an-apt") == 0)
	{
		(*countApt)++;
		addAnApt(content, l, *countApt);
	}
	else if ((strcmp(actToDo, "delete-an-apt") == 0))
	{
		deleteAnApt(content, l);
	}
	else if (strcmp(actToDo, "buy-an-apt") == 0)
	{
		buyAnApt(content, l);
	}

}



void addAnApt(char* comm2, ApartmentList *l, short int codeApt)
{
	ApartmentNode* ln = (ApartmentNode*)malloc(sizeof(ApartmentNode));

	time_t now;
	struct tm nowLocal;
	now = time(NULL); //gets the time from the OS
	nowLocal = *localtime(&now);
	comm2++; // for the first- "
	char* add = strtok(comm2, "\"");
	int lengthAddress = strlen(add);
	char* price = strtok(NULL, " ");
	char* rooms = strtok(NULL, " ");
	char* day = strtok(NULL, " ");
	char* month = strtok(NULL, " ");
	char* year = strtok(NULL, "\n");

	ln->codeApartment = codeApt;
	ln->address = (char*)malloc(sizeof(char)*(lengthAddress + 1));
	strcpy(ln->address, add);
	ln->address[lengthAddress] = '\0';
	
	


	ln->price = atoi(price);
	ln->numOfRooms = atoi(rooms);
	ln->entryDay.day = atoi(day);
	ln->entryDay.month = atoi(month);
	ln->entryDay.year = atoi(year);
	ln->next = NULL;
	ln->currentTime = currentTime();
	insertNodeToEndList(l, ln);
}

void deleteAnApt(char* str, ApartmentList* l)
{
	ApartmentNode* temp1, *temp2;
	RealTime current;
	char* command;
	temp1 = l->head;
	temp2 = l->head;
	str = strtok(str, " "); //the string was: "–Enter <x>"
	command = strtok(NULL, "\n"); //string just of a number

	int numOfDays;
	numOfDays = atoi(command);

	current = currentTime(); //find the current time
	current = findDateBack(current, numOfDays);

	while (temp1 != NULL)
	{
		if (compareTime(temp1->currentTime, current))
		{
			if (temp2 == temp1)
			{
				l->head = temp1->next;
				freeNode(temp1);
				temp1 = l->head;
				temp2 = l->head;
				if (!l->head)
					l->tail = NULL;
			}
			else
			{
				if (temp1->next == NULL)//update the new tail
					l->tail = temp2;
				temp2->next = temp1->next;
				freeNode(temp1);
				temp1 = temp2->next;

			}
		}
		else
		{

			temp2 = temp1;
			if (temp1->next == NULL)//update the new tail
				l->tail = temp1;

			temp1 = temp1->next;
		}

	}


}


void buyAnApt(char* comm2, ApartmentList* lst)
{
	ApartmentNode* temp1, *temp2;
	int numOfApt = atoi(comm2);
	int flag = 1;
	temp1 = lst->head;
	temp2 = lst->head;
	while (flag == 1 && temp1 != NULL)
	{
		if ((temp1->codeApartment) == numOfApt)
		{
			flag = 0;
			if (temp2 == temp1)
			{
				lst->head = temp1->next;
			}
			else
			{
				temp2->next = temp1->next;
			}
			freeNode(temp1);
		}
		else {
			temp2 = temp1;
			temp1 = temp1->next;
		}
	}
}


void printApartment(ApartmentNode* node)
{
	printf("Apt details:\n");
	printf("Code:%u\n", node->codeApartment);
	printf("Address: %s\n", node->address);
	printf("Number of rooms: %hu\n", node->numOfRooms);
	printf("Price: %d\n", node->price);
	printf("Entry date: %hu.%hu.%hu\n", node->entryDay.day, node->entryDay.month, node->entryDay.year);
	printf("Database entry date: %hu.%hu.%hu\n", node->currentTime.day, node->currentTime.month, node->currentTime.year);

}

void freeApartments(ApartmentList* lst)
{
	ApartmentNode* temp = lst->head;
	ApartmentNode* temp2;
	while (temp != NULL)
	{
		temp2 = temp;
		free(temp->address);
		temp = temp->next;
		free(temp2);
	}
	free(lst);
}

