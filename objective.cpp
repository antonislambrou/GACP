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

	int rules2 = genome.length() / attributes / fuzzysets;
	double conf[rules2];
	double max = -1;
	double min = 1000;
	double compat = 0;
	double weight = 0;
	
	for (int x=0;x<trainx;x++)
	{	

		max = -1;
		for(int r=0;r<rules2;r++)
		{
			min = 1000;
			for(int a=0;a<attributes;a++)
			{
				short fuzzyGene[fuzzysets];
				for(int g=0;g<fuzzysets;g++)
				{
					fuzzyGene[g] = genome.gene(fuzzysets*a+(r*(attributes *fuzzysets))+g);
				}
				
				compat = membership(a,train_set[x][a],fuzzyGene);
				if(compat < min)
					min = compat;
			}
			if(compat > max)
				max = compat;			
			
		}
		weight = max;
		
			
		if(train_set[x][attributes] == c)
		{
			TP += sqrt(weight);
			FN += sqrt(1-weight);
		}
		else
		{
			FP += sqrt(weight);
			TN += sqrt(1-weight);	
		}

	}

	fitness = (float) (TP / (TP+FN)) + (TN / (FP+TN));
	//fitness =  ((float) (1 * ((float) (TP) / (float) (TP + FN)) +
	//		(1 * ((float) (TN) / (float) (FP + TN))));// + 0.05 * ((double)1/(double)sqrt(rules));

	return fitness;
}
