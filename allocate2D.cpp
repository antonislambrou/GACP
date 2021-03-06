

double **allocate2DArray(int nRows, int nCols)
{
    double **ppi = new double*[nRows];
    double *curPtr = new double [nRows * nCols];

    for( int i = 0; i < nRows; ++i)
    {
        *(ppi + i) = curPtr;
         curPtr += nCols;
    }
    return ppi;
}

void free2DArray(double** Array)
{
    delete [] *Array;
    delete [] Array;
}

char **allocate2Dchar(int nRows, int nCols)
{
    char **ppi = new char*[nRows];
    char *curPtr = new char [nRows * nCols];

    for( int i = 0; i < nRows; ++i)
    {
        *(ppi + i) = curPtr;
         curPtr += nCols;
    }
    return ppi;
}

char free2Dchar(char** Array)
{
    delete [] *Array;
    delete [] Array;
}

int **allocate2Dint(int nRows, int nCols)
{
    int **ppi = new int*[nRows];
    int *curPtr = new int [nRows * nCols];

    for( int i = 0; i < nRows; ++i)
    {
        *(ppi + i) = curPtr;
         curPtr += nCols;
    }
    return ppi;
}

void free2Dint(int** Array)
{
    delete [] *Array;
    delete [] Array;
}
