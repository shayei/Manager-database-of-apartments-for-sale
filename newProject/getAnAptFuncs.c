#include "dateFuncs.h"
#include "getAnAptFuncs.h"
#include "ListFuncs.h"
#include "apartmentFuncs.h"
#include "dateFuncs.h"
#include "generalFuncs.h"


void getAnApt(char* str, ApartmentList* lst)
{
	BOOL maxPrice = 0;
	short int numMinRooms = 0, numMaxRooms = 0;
	int numMaxPrice = 0, numEnter = 0;
	BOOL minRooms = 0;
	BOOL maxRooms = 0;
	BOOL date = 0;
	char* numDate;
	BOOL enter = 0;
	BOOL s = 0;
	BOOL sr = 0;
	ApartmentNode** arr;
	int sizeOfArray;
	short int day, month, year;
	arr = buildArrayOfNodes(lst, &sizeOfArray);

	getAnAptCheckString(str, &maxPrice, &numMaxPrice, &minRooms, &numMinRooms, &maxRooms, &numMaxRooms,
		&date, &numDate, &enter, &numEnter, &s, &sr);

	if (enter == 1)
	{
		printAptLast_X_days(numEnter, lst);
	}

	if (maxPrice == 1)
	{
		for (int i = 0; i < sizeOfArray; i++)
		{
			if ((arr[i]->price) > numMaxPrice)
				arr[i] = NULL;
		}
		arr = deleteNodeFromArray(arr, &sizeOfArray);

	}
	if (minRooms == 1)
	{
		for (int i = 0; i < sizeOfArray; i++)
		{
			if (arr[i]->numOfRooms < numMinRooms)
				arr[i] = NULL;
		}
		arr = deleteNodeFromArray(arr, &sizeOfArray);
	}
	if (maxRooms == 1)
	{
		for (int i = 0; i < sizeOfArray; i++)
		{
			if (arr[i]->numOfRooms > numMaxRooms)
				arr[i] = NULL;
		}
		arr = deleteNodeFromArray(arr, &sizeOfArray);
	}
	if (date == 1)
	{//Read the date from a string, for example '01052017'
		day = charToNum(numDate[0]);
		if (day == 0)
			day = charToNum(numDate[1]);
		else
			day = day * 10 + charToNum(numDate[1]);

		month = charToNum(numDate[2]);
		if (month == 0)
			month = charToNum(numDate[3]);
		else
			month = month * 10 + charToNum(numDate[3]);
		year = charToNum(numDate[6])*10+charToNum(numDate[7]);
		//After reading the date we will filter out irrelevant apartments
		for (int i = 0; i < sizeOfArray; i++)
		{
			if (checkEvacuationDate(arr[i]->entryDay, day, month, year) == 0)
			{//If the date is later then the entry date, than the apartment is irrelevant.
				arr[i] = NULL;
			}
		}
		arr = deleteNodeFromArray(arr, &sizeOfArray);

	}
	if (enter == 0)
	{
		if (s == 1)
		{
			sortedArr(arr, sizeOfArray);
			for (int i = 0; i < sizeOfArray; i++)
				printApartment(arr[i]);

		}
		else if (sr == 1)
		{
			sortedArr(arr, sizeOfArray);
			for (int i = sizeOfArray - 1; i >= 0; i--)
				printApartment(arr[i]);

		}
		else
			for (int i = 0; i < sizeOfArray; i++)
				printApartment(arr[i]);
	}
	free(arr);
}

ApartmentNode** deleteNodeFromArray(ApartmentNode**arr, int* size)
{//Delete cells that do not have a pointer and reduce the array
	ApartmentNode** res;
	int logSize = 0;
	res = (ApartmentNode**)malloc(sizeof(ApartmentNode*)*(*size));

	for (int i = 0; i < *size; i++)
	{
		if (arr[i] != NULL)
		{
			res[logSize] = arr[i];
			logSize++;
		}
	}

	*size = logSize; //the new size of the array
	res = (ApartmentNode**)realloc(res, sizeof(ApartmentNode*)*logSize);
	free(arr);

	return res;
}

void sortedArr(ApartmentNode** arr, int size)
{

	int i, j;
	for (i = 0; i < size - 1; i++)

		for (j = 0; j < size - i - 1; j++)
			if (arr[j]->price > arr[j + 1]->price)
				swap(&arr[j], &arr[j + 1]);

}

void swap(ApartmentNode **xp, ApartmentNode **yp)
{
	ApartmentNode* temp = *xp;
	*xp = *yp;
	*yp = temp;
}

BOOL checkEvacuationDate(Date apt, int day, int month, int year)
{//If the apartment is will be available until the date return 1

	BOOL res = 0;
	if (apt.year < year)
		res = 1;
	if (apt.month < month && apt.year == year)
		res = 1;
	if (apt.day <= day && apt.month == month && apt.year == year)
		res = 1;
	return res;

}
ApartmentNode** buildArrayOfNodes(ApartmentList* originalLst, int*size)
{
	ApartmentNode** arr;
	ApartmentNode* temp = originalLst->head;
	int logSize = 0, phySize = 1;
	arr = (ApartmentNode**)malloc(sizeof(ApartmentNode*)*phySize);

	while (temp != NULL)
	{

		if (logSize == phySize)
		{
			phySize *= 2;
			arr = (ApartmentNode**)realloc(arr, sizeof(ApartmentNode*)*phySize);
		}
		arr[logSize] = temp;
		temp = temp->next;
		logSize++;
	}

	arr = (ApartmentNode**)realloc(arr, sizeof(ApartmentNode*)*logSize);
	*size = logSize;
	return arr;

}

void getAnAptCheckString(char* str, BOOL* maxPrice, int* numMaxPrice, BOOL* minRooms, short int* numMinRooms, BOOL* maxRooms, short int* numMaxRooms,
	BOOL* date, char** numDate, BOOL* enter, int* numEnter, BOOL* s, BOOL* sr)
{
	char* curr;
	int temp;
	char*place=strtok(str, " ");
	while (place != '\0')
	{
		
		 if (strcmp(place, "-Enter") == 0)
		{
			*enter = 1;
			curr = strtok(NULL, " ");
			temp = atoi(curr);
			*numEnter = temp;
			place = strtok(NULL, " ");
		}
		else if (strcmp(place, "-MaximumPrice") == 0)
		{
			*maxPrice = 1;
			curr = strtok(NULL, " ");
			temp = atoi(curr);
			*numMaxPrice = temp;
			place = strtok(NULL, " "); //Skip the number that should follow the phrase
		}
		
		else if (strcmp(place, "-MinimumNumRooms") == 0)
		{
			*minRooms = 1;
			curr = strtok(NULL, " ");
			temp = atoi(curr);
			*numMinRooms = temp;
			place = strtok(NULL, " "); //Skip the number that should follow the phrase
		}
		else if (strcmp(place, "-MaximumNumRooms") == 0)
		{
			*maxRooms = 1;
			curr = strtok(NULL, " ");
			temp = atoi(curr);
			*numMaxRooms = temp;
			place = strtok(NULL, " "); //Skip the number that should follow the phrase
		}
		else if (strcmp(place, "-Date") == 0)
		{
			*date = 1;
			curr = strtok(NULL, " ");
			*numDate = curr; //return a string of date (for example '01032018')
			place = strtok(NULL, " "); //Skip the number that should follow the phrase
		}
		else if (strcmp(place, "-s") == 0)
		{
			*s = 1;
			place = strtok(NULL, "\n");
		}
		else if (strcmp(place, "-sr") == 0)
		{
			*sr = 1;
			place = strtok(NULL, "\n");
		}


	}

}

void printAptLast_X_days(int numOfDays, ApartmentList* lst)
{
	ApartmentNode* temp;
	RealTime current;
	temp = lst->head;

	if (numOfDays == 0)
		return;
	numOfDays--;
	current = currentTime(); //find the current time
	current = findDateBack(current, numOfDays);

	while (temp->next != NULL)
	{
		if (compareTime(temp->currentTime, current))
			printf("%d ", temp->codeApartment);

		temp = temp->next;
	}
}
