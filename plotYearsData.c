/**
 * \file plotYearsData.c
 * \brief Program to plot data of a given year.
 */

#include <stdlib.h>
#include <stdio.h>
#include "trace.h"
#include "deces.h"
#include "dates.h"
#define NSIZE 365
#define NAGE 120
#define THEYEAR 2003
#define DATAFILEFMT "data/deces-%d.txt.gz"
#define TITLENFMT "Décès en France en %d"
#define TITLEAGEFMT "Décès en France en %d par classe d'age"

int main( int argc, char *argv[] ) {
    double date[NSIZE], nb[NSIZE];
    double age[NAGE] , nbAge[NAGE];

    char datafilename[23];
    sprintf(datafilename, DATAFILEFMT, THEYEAR);
    deces_t *deces = read_data_file(datafilename);
    // Some data from december of a given year are in the datafile of the next year
    sprintf(datafilename, DATAFILEFMT, THEYEAR + 1);
    deces = add_data_file(deces, datafilename);

    int i;
    for (i=0; i<NSIZE; i++) {
        date[i] = i+1;
        nb[i] = 0;
    }
    for (i=0; i<NAGE; i++) {
        age[i] = i;
        nbAge[i] = 0;
    }

    deces_t *current = deces;
    char firstDay[9];
    sprintf(firstDay, "%04d0101", THEYEAR);
    date_t *begin = read_date(firstDay);
    while (current != NULL) {
        date_t *dateDeces = read_date(current->dateDeces);
        date_t *birth = read_date(current->dateNaissance);
        int day = -1;
        if (dateDeces != NULL) {
            day = difference_dates(begin, dateDeces);
            if (birth != NULL && dateDeces->year == THEYEAR) {
                int ageold = process_age(birth, dateDeces);
                if (ageold >= 0 && ageold < NAGE) {
                    nbAge[ageold] = nbAge[ageold] + 1;
                }
            }
            destroy_date(dateDeces);
        }
        if (birth != NULL) {
            destroy_date(birth);
        }
        if(day >= 0 && day < NSIZE) {
            nb[day] = nb[day] + 1;
        }
        current = current->next;
    }
    destroy_date(begin);
    free_deces(deces);

    char graphTitle[50];
    sprintf(graphTitle, TITLENFMT, THEYEAR);
    tr_plot_from_zero("deces_par_jour.svg", NSIZE, date, nb, graphTitle, "jour de l'année", "nombre de décès par jour");
    sprintf(graphTitle, TITLEAGEFMT, THEYEAR);
    tr_histo_from_zero("deces_par_age.svg", NAGE, age, nbAge, graphTitle, "age", "nombre de décès");

    exit(EXIT_SUCCESS);
}
