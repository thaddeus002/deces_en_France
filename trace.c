/**
 * \file trace.c
 */

#include <stdlib.h>
#include "plplot.h"
#include "trace.h"

typedef enum {
    CURVE,
    HISTOGRAM,
    CURVE_ZERO,
    HISTOGRAM_ZERO
} tr_type_t;

static int is_from_zero(tr_type_t type) {
    return type == CURVE_ZERO || type == HISTOGRAM_ZERO;
}

/**
 * \param nb number of data, strictly positive
 */
static double *get_boundaries(int nb, double data[]) {
    double *boundaries = malloc(sizeof(double) * 2);
    boundaries[0] = data[0];
    boundaries[1] = data[0];
    int i;
    for (i=1; i<nb; i++) {
        if (data[i] < boundaries[0]) {
            boundaries[0] = data[i];
        }
        if (data[i] > boundaries[1]) {
            boundaries[1] = data[i];
        }
    }

    return boundaries;
}


static int tr_plot_with_type(char *filename, int nb, double x[], double y[], char *title, char *xlab, char *ylab, tr_type_t type) {

    plsdev("svg");
    plsfnam(filename);

    // change colors
    plscolbg(255, 255, 255);
    plscol0(15, 0, 0, 0);

    // Initialize plplot
    plinit();

    double *xb = get_boundaries(nb, x);
    double *yb = get_boundaries(nb, y);
    if (is_from_zero(type)) {
        yb[0] = 0;
    }
    // Create a labelled box to hold the plot.
    //pltimefmt("%b");
    plcol0(15); // black
    plenv(xb[0], xb[1], yb[0], yb[1], 0, 0);
    free(xb);
    free(yb);

    pllab(xlab, ylab, title);

    // Plot the data that was prepared above.
    plcol0(9); // blue
    switch(type) {
    case CURVE:
    case CURVE_ZERO:
        plline(nb, x, y);
        break;
    case HISTOGRAM:
    case HISTOGRAM_ZERO:
        plbin(nb, x, y, PL_BIN_DEFAULT);
    }

    // Close PLplot library
    plend();

    return(0);
}


int tr_plot(char *filename, int nb, double x[], double y[], char *title, char *xlab, char *ylab) {
    return tr_plot_with_type(filename, nb, x, y, title, xlab, ylab, CURVE);
}

int tr_histo(char *filename, int nb, double x[], double y[], char *title, char *xlab, char *ylab) {
    return tr_plot_with_type(filename, nb, x, y, title, xlab, ylab, HISTOGRAM);
}

int tr_plot_from_zero(char *filename, int nb, double x[], double y[], char *title, char *xlab, char *ylab) {
    return tr_plot_with_type(filename, nb, x, y, title, xlab, ylab, CURVE_ZERO);
}

int tr_histo_from_zero(char *filename, int nb, double x[], double y[], char *title, char *xlab, char *ylab) {
    return tr_plot_with_type(filename, nb, x, y, title, xlab, ylab, HISTOGRAM_ZERO);
}
