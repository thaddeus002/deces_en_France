/**
 * \file trace.h
 */

#ifndef __TRACE_H__
#define __TRACE_H__

int tr_plot(char *filename, int nb, double x[], double y[], char *title, char *xlab, char *ylab);

int tr_histo(char *filename, int nb, double x[], double y[], char *title, char *xlab, char *ylab);

int tr_plot_from_zero(char *filename, int nb, double x[], double y[], char *title, char *xlab, char *ylab);

int tr_histo_from_zero(char *filename, int nb, double x[], double y[], char *title, char *xlab, char *ylab);


#endif
