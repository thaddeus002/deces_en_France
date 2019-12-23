/**
 * \file deces.h lecture d'un fichier de données
 */

#ifndef __DECES_H__
#define __DECES_H__

typedef struct deces_ {
    char nom[80];
    char prenoms[80];
    char dateNaissance[9]; //YYYYMMDD
    char dateDeces[9]; // YYYYMMDD
    struct deces_ *next;
} deces_t;

deces_t *read_data_file(char *filename);
deces_t *add_data_file(deces_t *data, char *filename);

void free_deces(deces_t *deces);

#endif
