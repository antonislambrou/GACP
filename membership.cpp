#include <stdio.h>
#include "global.h"
#include <math.h>
double membership(int attr, double x, short fuzzyGene[])
{
	double membership = 0.0;
	double total = 0.0;
	double width[] = {0.5, 0.5, 0.5};

	//double mns[] = {0.0,1.0}; //2 fuzzysets
	//double mns[] = {0.0, 0.5, 1.0}; // 3 fuzzysets
	double mns[] = {0.00,0.25,0.5,0.75,1.00};	//5 fuzzysets
	//double mns[] = {0.00,0.15,0.3,0.45,0.70,0.85,1.00}; //7 fuzzysets
	//double mns[] = {0.0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0}; //10 fuzzysets
	
	double a;
	double b;
	double g;
	double d;
	double max = -1;
	
	
	for(int i=0;i<fuzzysets;i++)
	{
		//a = means[i][attr]-0;
		//b = means[i][attr]+0;
		//g = widths[i*2][attr];
		//d = widths[i*2+1][attr];
		
		
		a= mns[i];
		b= mns[i];
		g=0.25;//width[i];//mns[1]-mns[0];
		d=g;
		
		//TRIANGULAR
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
		
		
		//GAUSSIAN
		//membership = exp(-(pow(mns[i]-x,2.0) / 2.0*pow(g,2.0)));

		membership = (double) membership * fuzzyGene[i];
		total += membership;
		/*
		if(membership > max)
			max = membership;
		total = max;
		*/
	}
	/*
	printf("Total: %.2f %.2f %.2f ",total,total/fuzzysets,x);
	for(int q=0;q<fuzzysets;q++)
		printf("%d",fuzzyGene[q]);
	printf("\n");
	*/
	total = (double) total / (double) fuzzysets;
	return total;
}
