/**
 * \file dates.h
 * \brief utilitary functions to handle dates.
 */

#ifndef DATES_H_
#define DATES_H_ 1

typedef struct date_t_ {
    int day; /* 1..31 */
    int month; /* 1..12 */
    int year; /* ..2003.. */
} date_t;


/**
 * Init a date from a string.
 * \param date a date formatted as "YYYYMMDD"
 * \return a new date or NULL if the parameter is malformatted
 */
date_t *read_date(const char *date);

/**
 * \brief Free memory.
 */
void destroy_date(date_t *d);

/**
 * \return the number of days between two dates
 */
int difference_dates(date_t *before, date_t *after);

/**
 * Calculate the number on entire years between two dates.
 */
int process_age(date_t *begin, date_t *end);

#endif
