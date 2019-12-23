/**
 * \file deces.c lecture d'un fichier de données
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deces.h"


static deces_t *read_line(char *line) {
	deces_t *new = malloc(sizeof(deces_t));
	if (new != NULL) {
		strncpy(new->dateNaissance, line + 81, 8);
		new->dateNaissance[8] = '\0';
		strncpy(new->dateDeces, line + 154, 8);
		new->dateDeces[8] = '\0';
	}

	return new;
}

deces_t *read_data_file(char *filename) {
	
	deces_t *data = NULL;
	deces_t *last = NULL;
	
	FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
               
    stream = fopen(filename, "r");
    if (stream == NULL) {
        perror("fopen");
        return data;
    }
	
	while ((nread = getline(&line, &len, stream)) != -1) {
		if(nread < 176) {
			// line too short
			continue;
		}
        deces_t *newDeces = read_line(line);
        if (data == NULL) {
			data = newDeces;
		} else {
			last->next = newDeces;
		}
	    if (newDeces != NULL) {
		    last = newDeces;
		}
    }

    free(line);
    fclose(stream);

	return data;
}

deces_t *add_data_file(deces_t *data, char *filename) {
	
	deces_t *new = read_data_file(filename);
	
	if (data == NULL) {
		return new;
	}

	deces_t *last = data;
	
	while (last->next != NULL) {
		last = last->next;
	}
	
	last->next = new;
	return data;
}

void free_deces(deces_t *deces) {
	deces_t *current = deces;
	while (current != NULL) {
		deces_t *next = current->next;
		free(current);
		current = next;
	}
}
