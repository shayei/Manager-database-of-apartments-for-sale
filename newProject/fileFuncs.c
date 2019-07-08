#include "fileFuncs.h"
#include "ListFuncs.h"

HistoryList* loadCommands(FILE* f, HistoryList* oldHistory, char* short_term_history[N], int* indexOfCommand)
{
	char** res = readHistoryFromFile(f, indexOfCommand);
	orderCommandsInHistory(res, indexOfCommand, short_term_history, oldHistory);
	return oldHistory;
}

void printCommandToTextFile(FILE* f, char* short_term_history[N], HistoryList* oldHistory, int sizeOfCommand)
{
	if (sizeOfCommand <= N)
	{
		for (int i = sizeOfCommand - 1; i >= 0; i--)
		{
			fprintf(f, "%s\n", short_term_history[i]);
		}
	}
	else
	{
		for (int i = N - 1; i >= 0; i--)
		{
			fprintf(f, "%s\n", short_term_history[i]);
		}
	}

	reverse(&oldHistory->head);
	CommandNode*first = oldHistory->head;

	while (first != NULL)
	{
		fprintf(f, "%s\n", first->command);
		first = first->next;
	}

}

char** readHistoryFromFile(FILE* f, int* size)
{
	/* This function restores the history of commands from a text file.
	The function returns a dynamic array of pointers, each cell is a command.
	The first cell is the last command*/
	int logStrSize = 0, physStrSize = 1;
	int logArrSize = 0, physArrSize = 1;
	char** res = (char**)malloc(sizeof(char*)*physArrSize);

	int i = 0;
	char let;
	long int fSize = fileSize(f);


	while (ftell(f) < fSize)
	{
		fread(&let, sizeof(char), 1, f);
		if (logArrSize == physArrSize)
		{
			physArrSize *= 2;
			res = (char**)realloc(res, sizeof(char*)*(physArrSize));
		}
		res[logArrSize] = (char*)malloc(sizeof(char)*(physStrSize));
		while (let != '\n')
		{
			if (logStrSize == physStrSize)
			{
				physStrSize *= 2;
				res[logArrSize] = (char*)realloc(res[logArrSize], sizeof(char)*(physStrSize));
			}

			res[logArrSize][logStrSize] = let;
			logStrSize++;
			fread(&let, sizeof(char), 1, f);

		}
		if (let == '\n')
		{
			res[logArrSize] = (char*)realloc(res[logArrSize], sizeof(char)*(logStrSize + 1));
			res[logArrSize][logStrSize] = '\0';
			logArrSize++;
			logStrSize = 0;
			physStrSize = 1;
		}

	}

	res = (char**)realloc(res, sizeof(char*)*logArrSize);
	(*size) = logArrSize; //number of the commands.
	return res;

}

long int fileSize(FILE* file)
{//Returns how many characters the file contains.
	long int res;

	fseek(file, 0, SEEK_END);
	res = ftell(file);
	fseek(file, 0, SEEK_SET);

	return res;
}

void orderCommandsInHistory(char** arr, int* size, char *short_term_history[N], HistoryList* oldHistory)
{
	int j = 0;
	if (*size <= 7) /*If there were less than 7 commands, we would only use the array*/
	{
		for (int i = (*size - 1); i >= 0; i--)
		{
			short_term_history[i] = arr[j];
			j++;
		}
	}
	else
	{
		putCommandsInShortHistory(arr, size, short_term_history);
		for (int i = 0; i < *size - 7; i++)
		{
			putCommandsInOldHistory(arr, size, oldHistory);
		}

	}
	free(arr);
}

void putCommandsInShortHistory(char** arr, int* size, char *short_term_history[N])
{
	int j = 0;
	for (int i = (N - 1); i >= 0; i--)
	{
		short_term_history[i] = arr[j];
		j++;
	}
}


void putCommandsInOldHistory(char** arr, int* size, HistoryList* lst)
{
	CommandNode* node;
	int indexOfHistory;
	if (lst->head == NULL) //find the number of the current command;
		indexOfHistory = 1;
	else
		indexOfHistory = (lst->tail->numOfCommand) + 1;


	node = (CommandNode*)malloc(sizeof(CommandNode));
	node->command = arr[*size - indexOfHistory];
	node->numOfCommand = indexOfHistory;
	node->next = NULL;
	insertNodeToEndHistoryList(lst, node);
}



void loadApartmentsFromBinFile(FILE* binaryFile, short int* size, ApartmentList *lst)
{
	short	int countApt = 0;
	long int fSize = fileSize(binaryFile);
	ApartmentNode* node;
	short int lengthAddress;
	int lastCodeApartment;
	BYTE bits;

	while (ftell(binaryFile) < fSize)
	{
		countApt++;
		node = (ApartmentNode*)malloc(sizeof(ApartmentNode));
		fread(&(node->codeApartment), sizeof(short int), 1, binaryFile);
		fread(&lengthAddress, sizeof(short int), 1, binaryFile);
		node->address = (char*)malloc(sizeof(char)*(lengthAddress + 1));
		fread(node->address, sizeof(char), lengthAddress, binaryFile);
		node->address[lengthAddress] = '\0';
		fread(&(node->price), sizeof(int), 1, binaryFile);

		node->numOfRooms = getRooms(binaryFile, &bits);
		node->entryDay = getEntryDate(binaryFile, bits);
		node->currentTime = getEntryToSystemDate(binaryFile);
		node->next = NULL;
		insertNodeToEndList(lst, node);

		lastCodeApartment = node->codeApartment;
	}
	*size = lastCodeApartment;
}

short int getRooms(FILE*f, BYTE* result)
{
	short int res;
	BYTE bits;
	fread(&bits, sizeof(BYTE), 1, f);
	BYTE mask = 0xF0;////1111 0000
	res = bits&mask;
	res = res >> 4;
	*result = bits;
	return res;

}


Date getEntryDate(FILE*f, BYTE result)
{
	Date res;
	BYTE next;

	BYTE mask = 0x0F;//0000 1111
	res.day = result&mask;
	res.day = res.day << 1;
	fread(&next, sizeof(BYTE), 1, f);
	mask = next >> 7;
	res.day |= mask;
	mask = 0x78; //0111 1000
	res.month = mask&next;
	res.month >>= 3;
	mask = 0x07; //0000 0111
	res.year = mask&next;
	res.year <<= 4;
	fread(&next, sizeof(BYTE), 1, f);
	mask = next >> 4;
	res.year |= mask;
	return res;
}

RealTime getEntryToSystemDate(FILE* f)
{
	TWOBYTES next, temp;
	RealTime res;

	fread(&next, sizeof(TWOBYTES), 1, f);
	temp = 31;
	temp <<= 11;
	temp &= next;
	temp >>= 11;
	res.day = temp;
	temp = 15;
	temp <<= 7;
	temp &= next;
	temp >>= 7;
	res.month = temp;
	temp = 127;
	res.year = temp&next;

	return res;

}

void writeToBinaryFile(FILE* binaryFile, ApartmentList*lst, int size)
{
	ApartmentNode*node = lst->head;
	short int lengthAddress;
	BYTE res1, res2, res3;
	TWOBYTES res;
	while (node)
	{
		fwrite(&(node->codeApartment), sizeof(short int), 1, binaryFile);
		lengthAddress = (short int)strlen(node->address);
		fwrite(&lengthAddress, sizeof(short int), 1, binaryFile);
		fwrite(node->address, sizeof(char), lengthAddress, binaryFile);

		fwrite(&(node->price), sizeof(int), 1, binaryFile);
		compRooms(&res1, node->numOfRooms);
		compEntryDate(node->entryDay, &res1, &res2, &res3);
		compEntryToSystemDate(node->currentTime, &res);
		fwrite(&res1, sizeof(BYTE), 1, binaryFile);
		fwrite(&res2, sizeof(BYTE), 1, binaryFile);
		fwrite(&res3, sizeof(BYTE), 1, binaryFile);
		fwrite(&res, sizeof(TWOBYTES), 1, binaryFile);
		node = node->next;

	}

}
void compRooms(BYTE* res1, short int numRooms)
{

	BYTE res;
	res = numRooms;  //insert first number
	res = res << 4; //shift number to left half

	(*res1) = res;
}

void compEntryDate(Date entry, BYTE *res1, BYTE* res2, BYTE* res3)
{
	BYTE temp1 = entry.day;
	BYTE temp2 = entry.day;
	temp1 >>= 1; //0000 0XXX
	*res1 = *res1 | temp1;
	temp2 <<= 7; //X000 0000

	temp1 = entry.month;
	temp1 <<= 3; //0XXX X000

	*res2 = temp2 | temp1;
	temp1 = temp2 = entry.year;
	temp1 >>= 4; // 0000 0XXX
	temp2 <<= 4; //XXXX 0000
	*res2 |= temp1;

	*res3 = temp2;

}


void compEntryToSystemDate(RealTime time, TWOBYTES* res)
{
	TWOBYTES temp1, temp2;
	temp1 = time.day;
	temp1 <<= 11;
	temp2 = time.month;
	temp2 <<= 7;
	temp1 = temp1 | temp2;
	temp2 = (time.year - 2000);
	temp1 = temp1 | temp2;

	*res = temp1;
}