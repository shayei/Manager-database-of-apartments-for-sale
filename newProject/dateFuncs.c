#include "dateFuncs.h"


RealTime currentTime()
{//this node save the current time of the apartment
	RealTime node;
	time_t now;
	struct tm nowLocal;
	now = time(NULL); //gets the time from the OS
	nowLocal = *localtime(&now);
	node.day = nowLocal.tm_mday;
	node.month = nowLocal.tm_mon + 1;
	node.year = nowLocal.tm_year + 1900;
	return node;
}

int compareTime(RealTime dateOfApt, RealTime check)
{// if 'dateOfApt' is closer then 'check' return 1, else 0.
	int res = 0;
	if (dateOfApt.year > check.year-2000)
		res = 1;
	else if ((dateOfApt.month > check.month) && (dateOfApt.year == check.year-2000))
		res = 1;
	if ((dateOfApt.day >= check.day) && (dateOfApt.month == check.month) && (dateOfApt.year == check.year-2000))
		res = 1;
	return res;
}


RealTime findDateBack(RealTime date, int x)
{
	RealTime res;
	res.day = date.day;
	res.month = date.month;
	res.year = date.year;

	if (x < res.day)//if reduce days will stay in the same 
	{
		x--;
		res.day -= x;
	}
	else
	{
		while (x > 1)
		{
			if (res.day == 1 && res.month == 1) //for example 1.1.18
			{
				res.month = 12;
				res.day = howManyDaysInMonth(res.month);
				res.year--;
				x--;
			}
			else if (res.day == 1) //for example 1.4.18
			{
				res.month--;
				res.day = howManyDaysInMonth(res.month);
				x--;
			}
			else
			{
				x--;
				res.day--;
			}

		}
	}

	return res;
}

int howManyDaysInMonth(int month)
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		return 31;
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;

	return 28; //february
}