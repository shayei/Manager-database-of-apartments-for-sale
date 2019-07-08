#include "structs.h"


void getAnApt(char * str, ApartmentList * lst);

ApartmentNode ** deleteNodeFromArray(ApartmentNode ** arr, int * size);



void swap(ApartmentNode ** xp, ApartmentNode ** yp);


void printAptLast_X_days(int numOfDays, ApartmentList * lst);

void sortedArr(ApartmentNode** arr, int size);

BOOL checkEvacuationDate(Date apt, int day, int month, int year);

ApartmentNode** buildArrayOfNodes(ApartmentList* originalLst, int*size);

void getAnAptCheckString(char * str, BOOL * maxPrice, int * numMaxPrice, BOOL * minRooms, short int * numMinRooms, BOOL * maxRooms, short int * numMaxRooms, BOOL * date, char ** numDate, BOOL * enter, int * numEnter, BOOL * s, BOOL * sr);
