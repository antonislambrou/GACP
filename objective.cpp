/* Objective function for maximization */
#include <ga/ga.h>
#include <ga/GAStringGenome.h>
#include <ga/GA1DBinStrGenome.h>
#include <ga/GAAllele.h>
#include "global.h"
#include <math.h>
#include "membership.h"
#include <stdio.h>

float Objective(GAGenome& g)
{
	float fitness=0;

	double TP=0.00;
	double TN=0.00;
	double FP=0.00;
	double FN=0.00;
	
	GA1DBinaryStringGenome& genome = (GA1DBinaryStringGenome&)g;
	
	int rules = genome.length() / attributes / fuzzysets;
	
	for(int x=0;x<=trainx ;x++)
	{
		double max = 0;
		for(int r=0;r<rules;r++)
		{
			double m = 2;
			for(int a=0;a<attributes;a++)
			{
				short fuzzyGene[fuzzysets];
				
				for(int g=0;g<fuzzysets;g++)
				{
					fuzzyGene[g] = genome.gene(fuzzysets*a+(r*(attributes *fuzzysets))+g);
				}
				
				double ms = membership(a,train_set[x][a],fuzzyGene);
				if(m > ms)
					m = ms;
			}
			if(max < m)
				max = m;
		}

		if((int) train_set[x][attributes] == c)
		{
			TP += sqrt(max);
			FN += sqrt(1-max);
		}
		else
		{
			FP += sqrt(max);
			TN += sqrt(1-max);
		}
	}
	
	fitness = (float) (0.5 * ((float) TP / (float) (TP + FN))) + 
				(0.5 * ((float) TN / (float) (FP + TN)));
	
	//printf("fitness: %.3f\n",fitness);
	return fitness;
}
