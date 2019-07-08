 #include "structs.h"





char * getInput();

void getAction(char * st, char ** actToDo, char ** content);



void doAction(char* actToDo, char* content, ApartmentList * l,short int * countApt);

void addAnApt(char * comm2, ApartmentList * l, short int codeApt);

void deleteAnApt(char * str, ApartmentList * l);

void buyAnApt(char * comm2, ApartmentList * lst);

void printApartment(ApartmentNode * node);

void freeApartments(ApartmentList * lst);
