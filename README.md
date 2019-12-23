# Décès en France

This project contains a program to plot data from the [french file of deceased persons](https://www.data.gouv.fr/fr/datasets/fichier-des-personnes-decedees/#_).

## Requirements

This is a command line program for Linux using the library [PlPlot](http://plplot.sourceforge.net/index.php).
PlPlot must be build with svg support, the graphic output being in this format.

Building the program requires `gcc` and `make`.

## Making new graphics

The graphics are for year 2003. For a different dataset, download a year's file in directory `data` and change the constants in file `plotYearsData.c`.
Then simply type :

    $ make

## Output

![number of death by day](deces_par_jour.svg)

![distribution by age](deces_par_age.svg)

## License

This is free software release under MIT license. Read the file [LICENSE](LICENSE) for more informations.
