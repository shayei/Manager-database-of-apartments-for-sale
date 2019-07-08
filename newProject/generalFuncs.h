#include "structs.h"

char * duplicateString(char * str);


BOOL isCaretExist(char * str);

char * findStringOfCommand(CommandNode * node, int num);

char * findCommandInNode(CommandNode * node, int num);

char* replaceStr(char ** st, int indexOfCommand, HistoryList* oldHistory, char ** short_term_history);

char *replaceWord(char *s, char *from, char *to);

int charToNum(char ch);

int lengthOfNumber(int num);
