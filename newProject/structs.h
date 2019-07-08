#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef ABC
#define ABC

unsigned char typedef BYTE;
unsigned short typedef TWOBYTES;

typedef struct date {
	short int day;
	short int month;
	short int year;
} Date;
typedef struct realTime {
	short int day;
	short int month;
	short int year;
} RealTime;

typedef struct apartmentNode {
	short int codeApartment;
	char* address;
	int price;
	short int numOfRooms;
	Date entryDay;
	RealTime currentTime;
	struct apartmentNode* next;
} ApartmentNode;

typedef struct apartmentList {
	ApartmentNode* head;
	ApartmentNode* tail;
} ApartmentList;

typedef struct commandNode {
	char* command;
	int numOfCommand;
	struct CommandNode* next;
} CommandNode;

typedef struct historyList {
	CommandNode* head;
	CommandNode* tail;
} HistoryList;


#define N 7
typedef int BOOL;

#endif
