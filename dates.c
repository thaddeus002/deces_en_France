/**
 * \file dates.c
 * \brief utilitary functions to handle dates.
 */

#include <stdlib.h>
#include <string.h>
#include "dates.h"


/**
 * Convert a date to day number.
 * The day number is only used for internal calculation.
 */
static int day_number(date_t *d);

/**
 * \brief Create a date structur.
 */
static date_t *create_date(int year, int month, int day);


date_t *read_date(const char *date){
	int year, month, day;
	char tempo[5];
	if(date == NULL) return(NULL);
	if(strlen(date)!=8) return(NULL);

	strncpy(tempo, date+6, 2);
	tempo[2]='\0';
	day=atoi(tempo);

	strncpy(tempo, date+4, 2);
	tempo[2]='\0';
	month=atoi(tempo);

	strncpy(tempo, date, 4);
	tempo[4]='\0';
	year=atoi(tempo);

	return(create_date(year, month, day));
}



/**
 * \brief Free memory.
 */
void destroy_date(date_t *d){
	if(d!=NULL) free(d);
}


/**
 * \return the number of days between two dates
 */
int difference_dates(date_t *before, date_t *after){
	int dBefore, dAfter;
	dBefore = day_number(before);
	dAfter = day_number(after);
	return dAfter - dBefore;
}


/**
 * Calculate the number on entire years between two dates.
 */
int process_age(date_t *begin, date_t *end) {
	int n1 = begin->year * 10000 + begin->month * 100 + begin->day;
	int n2 = end->year * 10000 + end->month * 100 + end->day;
	return (n2 - n1) / 10000;
}

/********** INTERNAL FUNCTONS ******************/

/**
 * Convert a date to day number.
 * The day number is only used for internal calculation. Is the number of
 * days since march the first of year zero.
 */
static int day_number(date_t *d) {
	int a, m, j;
	a=d->year;
	m=d->month;
	j=d->day;
	if (m < 3) { a-=1; m+=12; } /* offsetting to the first day of march */
	return(a*365 + a/4 - a/100 + a/400 + (m+1)*153/5-123 + j);
}

/**
 * \brief Say if a given year is a leap year.
 * 
 * A year is a leap year if it is multiple of four, except for the years
 * multiple of 100 but not of 400.
 * \param y a year number
 * \return 1 if the year is a leap year, 0 otherwise
 */
static int is_leap(int y) {
	return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

/**
 * \brief Create a date structur.
 * \return the newly created date or NULL if the parameters are wrong
 */
static date_t *create_date(int year, int month, int day){
	date_t *newDate;
	short daysInMonth[] = { 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 };

	if((month < 1)||(month > 12)) return(NULL);
	if(is_leap(year)) daysInMonth[1]++;

	if((day < 1)||(day > daysInMonth[month-1])) return(NULL);

	newDate=malloc(sizeof(date_t));
	newDate->year=year;
	newDate->month=month;
	newDate->day=day;
	return(newDate);
}
