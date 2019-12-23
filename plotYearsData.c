/**
 * \file plotYearsData.c
 * Program to plot data of a given year.
 */

#include <stdlib.h>
#include "trace.h"
#include "deces.h"
#include "dates.h"
#define NSIZE 365
#define NAGE 120
#define DATAFILE "data/deces-2003.txt"
// Some data from december of a given year are in the datafile of the next year
#define NEXTDATAFILE "data/deces-2004.txt"


int main( int argc, char *argv[] ) {
    double date[NSIZE], nb[NSIZE];
    double age[NAGE] , nbAge[NAGE];

    deces_t *deces = read_data_file(DATAFILE);
    deces = add_data_file(deces, NEXTDATAFILE);

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
    date_t *begin = read_date("20030101");
    while (current != NULL) {
		date_t *dateDeces = read_date(current->dateDeces);
		date_t *birth = read_date(current->dateNaissance);
		int day = -1;
		if (dateDeces != NULL) {
			day = difference_dates(begin, dateDeces);
			if (birth != NULL && dateDeces->year == 2003) {
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

    tr_plot_from_zero("deces_par_jour.svg", NSIZE, date, nb, "Décès en France en 2003", "jour de l'année", "nombre de décès par jour");
    tr_histo_from_zero("deces_par_age.svg", NAGE, age, nbAge, "Décès en France en 2003 par classe d'age", "age", "nombre de décès");

    exit(EXIT_SUCCESS);
}
