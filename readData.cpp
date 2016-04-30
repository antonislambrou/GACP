#include "global.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "allocate2D.h"

using namespace std;
void readData(int fold)
{	
	ifstream file;  
    file.open(filename, ios::in);

    if (!file)
    {
		throw "File not opened";
    }
    
    file >> examples;
    file >> attributes;
    file >> label;

    int ten_fold = examples / FOLDS;
	int remainder = examples % FOLDS;
	int z = 0;
	int x;
	if(fold+1 == FOLDS)
	{
		z=remainder;
	}

	train_set = allocate2DArray(examples - ten_fold + 1 - z,attributes + label);
	test_set = allocate2DArray(ten_fold+z,attributes + label);

	for(x=trainx=testx=0; x < examples; x++)
    {
		if(x >= (fold * ten_fold) && x < ((fold * ten_fold) + ten_fold + z))
		{
			for (int j = 0; j < attributes + label; j++)
			{
				file >> test_set[testx][j];
			}
			
			testx++;
		}
		else
		{
			for (int j = 0; j < attributes + label; j++)
			{
	    		file >> train_set[trainx][j];
			}
			trainx++;
		}
    }
}
