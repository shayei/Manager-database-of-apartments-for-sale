#include "dateFuncs.h"
#include "getAnAptFuncs.h"
#include "ListFuncs.h"
#include "historyFuncs.h"
#include "generalFuncs.h"
#include "apartmentFuncs.h"
#include "fileFuncs.h"

void main()
{

	ApartmentList* apartmentList = (ApartmentList*)malloc(sizeof(ApartmentList));
	HistoryList *oldHistory = (HistoryList*)malloc(sizeof(HistoryList));
	makeEmptyHistoryList(oldHistory);
	makeEmptyList(apartmentList);
	char *short_term_history[N] = { NULL };
	char* st, *actToDo = NULL, *content = NULL;
	char*actToDoTemp = NULL, *contentTemp = NULL;
	char* actionSaver = NULL;
	int num,code=0;
	int indexOfCommand = 0;
	short int indexOfApartment = 0;
	printf("Please enter one of the following commands:\nadd-an-apt, get-an-apt, buy-an-apt or delete-an-apt:\n");
	printf("For reconstruction commands, please enter:\n!!, !num, history, short_history or !num^str1^str2\nTo exit, enter exit.\n");
	FILE* textFile = fopen("command.txt", "rt");
	FILE* binaryFile = fopen("command.bin", "rb");

	if (textFile)
	{
		oldHistory = loadCommands(textFile, oldHistory, short_term_history, &indexOfCommand);
		fclose(textFile);
	}
	if (binaryFile)
	{

		loadApartmentsFromBinFile(binaryFile, &indexOfApartment, apartmentList);
		fclose(binaryFile);
	}




	st = getInput();
	char *temp = duplicateString(st);
	while (strcmp(st, "exit") != 0)
	{

		getAction(st, &actToDo, &content);

		//in case we have !! we check 2 options 
		if ((strcmp(actToDo, "!!") == 0))
		{
			if (indexOfCommand <= 7) //in case the short term array is not full
			{
				getAction(short_term_history[indexOfCommand - 1], &actToDoTemp, &contentTemp);
				doAction(actToDoTemp, contentTemp, apartmentList, &indexOfApartment);
				char* str = duplicateString(short_term_history[num - 1]);
				oldHistory = addToHistory(short_term_history, str, indexOfCommand, oldHistory);
			}
			else//if the short term array is full
			{
				getAction(short_term_history[N - 1], &actToDoTemp, &contentTemp);
				doAction(actToDoTemp, contentTemp, apartmentList, &indexOfApartment);
				char* str = duplicateString(short_term_history[N - 1]);
				oldHistory = addToHistory(short_term_history, str, indexOfCommand, oldHistory);

			}
		}

		//in case we have ! we check 2 options 
		else if (st[0] == '!')
		{
			//option 1- !num^num^num
			if (isCaretExist(st) == 1)
			{
				char*str = replaceStr(&st, indexOfCommand, oldHistory, short_term_history);
				getAction(str, &actToDoTemp, &contentTemp);
				doAction(actToDoTemp, contentTemp, apartmentList, &indexOfApartment);
				oldHistory = addToHistory(short_term_history, str, indexOfCommand, oldHistory);
			}
			//option 2 - !num
			else
			{
				num = atoi(st + 1);
				if (indexOfCommand > 7)
					code = oldHistory->tail->numOfCommand;
				if (indexOfCommand - num >= 7)
				{
					actionSaver = duplicateString(findCommandInNode(oldHistory->head, num));// the command is in the old history list
					getAction(actionSaver, &actToDoTemp, &contentTemp);
					doAction(actToDoTemp, contentTemp, apartmentList, &indexOfApartment);
					oldHistory = addToHistory(short_term_history, actionSaver, indexOfCommand, oldHistory);

				}
				else
				{
					getAction(short_term_history[num-code - 1], &actToDoTemp, &contentTemp);
					doAction(actToDoTemp, contentTemp, apartmentList, &indexOfApartment);// the command is in the short history array
					char* str = duplicateString(short_term_history[num-code - 1]);
					oldHistory = addToHistory(short_term_history, str, indexOfCommand, oldHistory);
				}

			}


		}

		////in case we get history command 
		else if ((strcmp(actToDo, "history") == 0))
		{
			printHistory(short_term_history, indexOfCommand, oldHistory);
			indexOfCommand--;
		}

		////in case we get history command 
		else if ((strcmp(actToDo, "short_history") == 0))
		{
			printShortHistory(short_term_history, indexOfCommand, oldHistory);
			indexOfCommand--;
		}

		//if is not of the above it's one of the 4 action that we need to do and save to history
		else
		{

			doAction(actToDo, content, apartmentList, &indexOfApartment);

			oldHistory = addToHistory(short_term_history, temp, indexOfCommand, oldHistory);//save the command in the history
		}

		st = getInput();
		temp = duplicateString(st);
		indexOfCommand++;
	}

	textFile = fopen("command.txt", "w+");
	printCommandToTextFile(textFile, short_term_history, oldHistory, indexOfCommand);
	fclose(textFile);
	binaryFile = fopen("command.bin", "w+b");
	writeToBinaryFile(binaryFile, apartmentList, indexOfApartment);
	fclose(binaryFile);
	freeShortHistory(short_term_history, indexOfCommand);
	freeOldHistory(oldHistory);
	freeApartments(apartmentList);
	printf("Good Bye!\n");

}