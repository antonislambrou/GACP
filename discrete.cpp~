#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "global.h"
#include "allocate2D.h"

using namespace std;

void discrete()
{

	ifstream file1;
	ifstream file2;  
    
    file1.open("data/means1.txt", ios::in);
	file2.open("data/widths1.txt", ios::in);
    
    if (!file1 || !file2)
    {
		throw "File2 not opened";
    }
    
    means = allocate2DArray(fuzzysets,attributes);
    widths = allocate2DArray(fuzzysets*2,attributes);
    
    for(int x=0;x<fuzzysets;x++)
    {
    	for(int y=0;y<attributes;y++)
    	{
    		file1 >> means[x][y];
    	}
    }
    
    for(int x=0;x<fuzzysets*2;x++)
    {
    	for(int y=0;y<attributes;y++)
    	{
    		file1 >> widths[x][y];
    	}
    }
}
