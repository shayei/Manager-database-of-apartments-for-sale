#include "generalFuncs.h"
#include "apartmentFuncs.h"
#include "getAnAptFuncs.h"
#include "dateFuncs.h"
#include "historyFuncs.h"




char* duplicateString(char* str)
{
	char* res = NULL;
	int leng = strlen(str);
	res = (char*)malloc(sizeof(char)*(leng + 1));
	strcpy(res, str);
	res[leng] = '\0';

	return res;
}




BOOL isCaretExist(char* str)
{
	BOOL res = 0;
	int i = 0;
	int len = strlen(str);
	while (i < len&&res == 0)
	{
		if (str[i] == '^')
			res = 1;
		i++;
	}
	return res;
}

char* findStringOfCommand(CommandNode *node, int num)
{

	while (node != NULL)
	{
		if (node->numOfCommand == num)
			return node->command;
		else
			node = node->next;
	}
	return NULL;

}


char* findCommandInNode(CommandNode *node, int num)
{
	char*res = NULL;
	while (res == NULL)
	{
		if (node->numOfCommand == num)
			res = node->command;
		else
			node = node->next;
	}
	return res;
}

char* replaceStr(char **st, int indexOfCommand, HistoryList* oldHistory, char** short_term_history)
{

	char *wantedCommand = strtok(*st, "^");
	char *before = strtok(NULL, "^");
	char *after = strtok(NULL, "\n");
	char*comm;
	int num, code=0;
	if (indexOfCommand > 7)
		code = oldHistory->tail->numOfCommand;


	num = atoi(wantedCommand + 1);
	if (indexOfCommand - num >= 7)//in case the command is in the list
	{
		comm = findStringOfCommand(oldHistory->head, num);
		comm = replaceWord(comm, before, after);
		return comm;
	}
	else//in case the command is in the array
	{
		short_term_history[num - code - 1] = replaceWord(short_term_history[num - code - 1], before, after);
		return short_term_history[num - code - 1];
	}

}

// Function to replace a string with another string
char *replaceWord(char *s, char *from, char *to)
{
	char *result;
	int i, cnt = 0;
	int newWlen = strlen(to);
	int oldWlen = strlen(from);

	// Counting the number of times old word
	// occur in the string
	for (i = 0; s[i] != '\0'; i++)
	{
		if (strstr(&s[i], from) == &s[i])
		{
			cnt++;
			// Jumping to index after the old word.
			i += oldWlen - 1;
		}
	}

	// Making new string of enough length
	result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);

	i = 0;
	while (*s)
	{
		// compare the substring with the result
		if (strstr(s, from) == s)
		{
			strcpy(&result[i], to);
			i += newWlen;
			s += oldWlen;
		}
		else
			result[i++] = *s++;
	}

	result[i] = '\0';
	return result;
}

int charToNum(char ch)
{
	return ch - '0';
}

int lengthOfNumber(int num)
{
	int count = 0;
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return count;
}