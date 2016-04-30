
#include <ga/ga.h>
#include <ga/GAStringGenome.h>
#include <ga/GA1DBinStrGenome.h>
#include <ga/GAAllele.h>
#include "global.h"
#include "membership.h"
#include <math.h>

double pvalue(int **hypotheses, int l, int eq, float gamma)
{
	double p=0;
	double others=0;
	double own=0;
	double *strangeness;
	int ctr = 0;
	int rules2;
	double Q[classes][::rules]; //global rules
	
	strangeness = (double *) malloc(sizeof(double) * (trainx+1));
	
	//find a quality value for each rule
	for (int cl = 1;cl<=classes;cl++)
	{	
		for (int r=0;r<hypotheses[cl-1][0];r++)
		{	
			double TP = 0;
			double FP = 0;
			
			for(int x=0;x<=trainx;x++)
			{
				double min = 1000;
				for(int a=0;a<attributes;a++)
				{
					short fuzzyGene[fuzzysets];
					for(int g=0;g<fuzzysets;g++)
					{
						fuzzyGene[g] = hypotheses[cl-1][fuzzysets*a+(r*((attributes) *fuzzysets))+g+1];
					}
					
					double ms = membership(a,train_set[x][a],fuzzyGene);
					if(min < ms)
						min = ms;
				}
				if(hypotheses[cl-1][attributes] == train_set[x][attributes])
				{
					TP += min;
				}
				else
				{
					FP += min;
				}	
			}
			
			Q[cl-1][r] = TP / (TP+FP);		
		}		
	}
		
	
	for(int x=0;x<=trainx ;x++)
	{
		others = 0;
		double mem[] = {0,0};
		double max = -1;
		double min = 1000;
		for(int cl=1;cl<=classes;cl++)
		{
			rules2 = hypotheses[cl-1][0];
			max = -1;
			for(int r=0;r<rules2;r++)
			{
				min = 1000;
				for(int a=0;a<attributes;a++)
				{
					short fuzzyGene[fuzzysets];

					for(int g=0;g<fuzzysets;g++)
					{
						fuzzyGene[g] = hypotheses[cl-1][fuzzysets*a+(r*((attributes) *fuzzysets))+g+1];
					}
					double ms = membership(a,train_set[x][a],fuzzyGene);
					if(ms <  min)
						min = ms;
				}

				min *= Q[cl-1][r];
				if(min > max)
					max = min;
			}

			mem[cl-1] = max;
		}
		
		
		//find sum of others 
    	for(int j=1;j<=classes;j++)
        	if (j != (int) train_set[x][attributes] ){
        	    others = others + mem[j-1];
        	    //printf("%.4f ",mem[j-1]);
        	}
		//printf("others: %.2f\n",others);
    	own = mem[(int)train_set[x][attributes]-1];
    	//printf("own: %d %.2f\n",(int)train_set[x][attributes],own);
    	if(eq == 13)
    		strangeness[x] = (double) others / ((double)own+(double)gamma);
    	else if(eq == 14)
    		strangeness[x] = others - own*gamma;
    	//else
    	//	strangeness[x] = 1 - own;

	}

	int another_ctr = 0;
	for(int i=0;i<=trainx;i++){
    		another_ctr++;
    		if(strangeness[i] >= strangeness[trainx]){
    		    ctr = ctr+1;
    		}
    }
	p = (double) ctr / (double) (another_ctr);

	return p;
}
