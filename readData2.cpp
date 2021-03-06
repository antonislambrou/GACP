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

    int ten_fold = floor(double(examples / FOLDS));
	int remainder = examples % FOLDS;

	double origData[examples][attributes+label];
	
	for(int i=0;i<examples;i++)
		for(int j=0;j<examples+label;j++)
			file >> origData[i][j];
	
	if(f+1 <= remainder)
	{
		test_exs = ten_fold + 1;
		train_exs = examples - test_exs;

		train_set = allocate2DArray(train_exs + 1,attributes + label);
		test_set = allocate2DArray(test_exs,attributes + label);
		
		for(int i=0;i< ((f)*(ten_fold + 1)); i++)
		{
			train_set[i] = origData[i];
		}
		for(int i=(f)*(ten_fold+1);i<examples-test_exs;i++)
		{
			train_set[i] = origData[i+test_exs];
		}
		for(int i=0;i<test_exs;i++)
		{
			test_set[i]=origData[i + ((f)*(ten_fold + 1))];
		}
	}
	else
	{
		test_exs = ten_fold;
		train_exs = examples - test_exs;

		train_set = allocate2DArray(train_exs + 1,attributes + label);
		test_set = allocate2DArray(test_exs,attributes + label);
		
		for(int i=0;i< ((f)*(ten_fold + 1)); i++)
		{
			train_set[i] = origData[i];
		}
		for(int i=(f)*(ten_fold+1);i<examples-test_exs;i++)
		{
			train_set[i] = origData[i+test_exs];
		}
		for(int i=0;i<test_exs;i++)
		{
			test_set[i]=origData[i + ((f)*(ten_fold + 1))];
		}
	}
	trainx=train_exs;
	testx=test_exs;
}
