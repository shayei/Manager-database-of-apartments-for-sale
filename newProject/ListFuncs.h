#include "structs.h"


void reverse(CommandNode ** head);

void makeEmptyList(ApartmentList * l);

void makeEmptyHistoryList(HistoryList * l);

void insertNodeToEndHistoryList(HistoryList * lst, CommandNode * tail);

void insertNodeToEndList(ApartmentList * lst, ApartmentNode * tail);

void freeNode(ApartmentNode * lst);
