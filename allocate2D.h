#ifndef ALLOCATE2D_H
#define ALLOCATE2D_H
#include "global.h"
double **allocate2DArray(int nRows, int nCols);
void free2DArray(double** Array);
char **allocate2Dchar(int nRows, int nCols);
char free2Dchar(char** Array);
int **allocate2Dint(int nRows, int nCols);
void free2Dint(int** Array);
#endif
