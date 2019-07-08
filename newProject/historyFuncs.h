#include "structs.h"

HistoryList* addToHistory(char * arr[], char * command, int index, HistoryList * lst);

void printShortHistory(char * arr[], int index, HistoryList * lst);

void printHistory(char * arr[], int index, HistoryList * lst);

void freeOldHistory(HistoryList * lst);

void freeShortHistory(char * arr[], int size);
