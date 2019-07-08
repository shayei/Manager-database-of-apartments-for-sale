#include "structs.h"

char ** readHistoryFromFile(FILE* f, int * size);

long int fileSize(FILE * file);

void orderCommandsInHistory(char ** arr, int *size, char * short_term_history[N], HistoryList * oldHistory);

void putCommandsInShortHistory(char ** arr, int* size, char * short_term_history[N]);

void putCommandsInOldHistory(char ** arr, int* size, HistoryList * lst);

void loadApartmentsFromBinFile(FILE * binaryFile,short int * size, ApartmentList * lst);

short int getRooms(FILE * f, BYTE * result);

Date getEntryDate(FILE * f, BYTE result);

RealTime getEntryToSystemDate(FILE * f);

void writeToBinaryFile(FILE * binaryFile, ApartmentList * lst, int size);

void compRooms(BYTE * res1, short int numRooms);

void compEntryDate(Date entry, BYTE * res1, BYTE * res2, BYTE * res3);

void compEntryToSystemDate(RealTime time, TWOBYTES * res);

HistoryList* loadCommands(FILE * f, HistoryList * oldHistory, char * short_term_history[N], int * indexOfCommand);

void printCommandToTextFile(FILE * f, char * short_term_history[N], HistoryList * oldHistory,int sizeOfCommand);
