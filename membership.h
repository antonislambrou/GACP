#ifndef MEMBERSHIP_H
#define MEMBERSHIP_H
#include <stdio.h>
#include "global.h"
inline double membership(int attr, double x, short fuzzyGene[])
{
	double membership = 0.0;
	double max = 0.0;

	//double mns[] = {0.00,1.00}; //2 fuzzysets
	//double mns[] = {0.0, 0.5, 1.00}; // 3 fuzzysets
	double mns[] = {0.00,0.25,0.5,0.75,1.00};	//5 fuzzysets
	//double mns[] = {0.00,0.15,0.3,0.45,0.70,0.85,1.00}; //7 fuzzysets
	
	double a;
	double b;
	double g;
	double d;
	
	
	for(int i=0;i<fuzzysets;i++)
	{
		//discretized
		//a = means[i][attr]-0;
		//b = means[i][attr]+0;
		//g = widths[i*2][attr];
		//d = widths[i*2+1][attr];
		
		//two sets
		//a = mns[i];
		//b = mns[i];
		//g = 1;
		//d = g;
		
		//five sets / seven sets / 3 sets
		a = mns[i];
		b = mns[i];
		g = mns[1]-mns[0];
		d = g;
		
		if((a-g) <= x && x <= a)
		{
			membership = 1 - ( (double) (a-x) / (double)g);
		}
		else if(a <= x && x<=b)
		{
			membership = 1;
		}
		else if(b <= x && x <= (b+d))
		{
			membership = 1 - ((double)(x-b)/(double)d);
		}
		else
			membership = 0.0;
		
		membership = (double) membership * fuzzyGene[i];
		
		//if(max<membership)
			//max=membership;
		max += membership;
	}
	return max;
}
#endif
