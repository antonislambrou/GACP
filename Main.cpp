#include <stdio.h>
#include <ga/ga.h>
#include <ga/std_stream.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ga/GAStringGenome.h>
#include <ga/GA1DBinStrGenome.h>
#include <ga/GAAllele.h>
#include <time.h>

#include "global.h"
#include "getArgs.h"
#include "objective.h"
#include "allocate2D.h"
#include "readData.h"
#include "pvalue.h"
#include "aux.h"
#include "certainty.h"
#include "errorf.h"
#include "discrete.h"
#include "varXover.h"
#include "varInit.h"

using namespace std;

#define cout STD_COUT
#define endl STD_ENDL

/* Conformal Prediction with Genetic Algorithm maximization -
   Binary representation with fuzzysets
   Antonis Lambrou
*/

//Terminator
GABoolean myTerm(GAGeneticAlgorithm & ga){
  printf("						%d\n",ga.generation());
  if(ga.generation() >= ga.nGenerations())
  	return gaTrue;
  else
  	return gaFalse;
}


int main(int argc, char **argv)
{
	//Initialise variables
	int actual=0;
	int seed=1;

	GAGenome *h;

	int correct[6][FOLDS];
	int **certaint1;
	int **err1;
	int **errm1;
	
	int **certaint2;
	int **err2;
	int **errm2;
	
	int **certaint3;
	int **err3;
	int **errm3;
	
	int **certaint4;
	int **err4;
	int **errm4;
	
	int **certaint5;
	int **err5;
	int **errm5;
	
	int **certaint6;
	int **err6;
	int **errm6;
	
	int total_correct[6];

	int total_certaint[6][30];
	int total_err[6][30];

	double p[6][classes];
	
	time_t secs1;
	time_t secs2;
	
	getArgs(argc,argv);
	
	for(int b=0;b<6;b++)
		total_correct[b] = 0;
		
	for(int z=0;z<30;z++)
	{
		if(z<FOLDS){
			for(int b=0;b<6;b++)
				correct[b][z] = 0;
		}
		for(int b=0;b<6;b++)
		{	
			total_certaint[b][z] = 0;
			total_err[b][z] = 0;
		}
	}
	certaint1 = allocate2Dint(FOLDS,30);
	err1 = allocate2Dint(FOLDS,30);
	errm1 = allocate2Dint(30,classes);
	
	certaint2 = allocate2Dint(FOLDS,30);
	err2 = allocate2Dint(FOLDS,30);
	errm2 = allocate2Dint(30,classes);
	
	certaint3 = allocate2Dint(FOLDS,30);
	err3 = allocate2Dint(FOLDS,30);
	errm3 = allocate2Dint(30,classes);
	
	certaint4 = allocate2Dint(FOLDS,30);
	err4 = allocate2Dint(FOLDS,30);
	errm4 = allocate2Dint(30,classes);
	
	certaint5 = allocate2Dint(FOLDS,30);
	err5 = allocate2Dint(FOLDS,30);
	errm5 = allocate2Dint(30,classes);
	
	certaint6 = allocate2Dint(FOLDS,30);
	err6 = allocate2Dint(FOLDS,30);
	errm6 = allocate2Dint(30,classes);
	
	
	int class_len[2];
	class_len[0] = 0;
	class_len[1] = 0;
	class_len[2] = 0;
	class_len[3] = 0;
	class_len[4] = 0;
	
	/* Transductive algorithm with x-fold cross validation */
	//for each fold
	for(int f=0;f<FOLDS;f++)
	{
		//separate train set with test set
		readData(f);
		//discrete();
		GA1DBinaryStringGenome genome(attributes*fuzzysets*rules, Objective);
		genome.resizeBehaviour((attributes)*fuzzysets*1, fuzzysets*rules*(attributes));
		genome.initializer(VariableSizeInitializer);
		genome.crossover(VariableSizeCrossover);

		GAParameterList params;
		GASteadyStateGA::registerDefaultParameters(params);
		params.set(gaNscoreFilename, "bog.dat");
		params.set(gaNnGenerations, gens);
		params.set(gaNpopulationSize, pop_size);
		params.set(gaNscoreFrequency, 10);
		params.set(gaNflushFrequency, 50);
		params.set(gaNselectScores, (int)GAStatistics::AllScores);
		//params.parse(argc, argv, gaFalse);
		

		GASteadyStateGA ga(genome);
		ga.terminator(GAGeneticAlgorithm::TerminateUponConvergence);
		ga.parameters(params);
		ga.pConvergence(1);
  		ga.nConvergence(50);
  				
		ga.pReplacement(0.9);
		ga.pMutation(0.01);
		ga.pCrossover(0.9);

		
		char stats[32];

		//for each test example
		for(int t=0;t<testx;t++)
		{
			secs1 = time(NULL);
			//add test example in train_set
			for(int x=0;x<attributes;x++)
			{
				train_set[trainx][x] = test_set[t][x];
			}

			//for each label of test example
			for(int l=1;l<=classes;l++)
			{
				printf("Class %d\n",l);
				int **hypotheses;

				hypotheses = allocate2Dint(classes,(attributes * fuzzysets * rules) + 1);
				//change the label of the last instance
				train_set[trainx][attributes] = l;

				//for each class generate a hypothesis given train_set
				for(c=1;c<=classes;c++)
				{
					ga.initialize(seed);
					//sprintf(stats,"generations/fold%dtest%dclass%dclass%d.txt",f,t,l,c);
					//ga.set(gaNscoreFilename, stats);
					printf("Population evolving...\n");
					ga.evolve(seed);
					printf("Population converged at %d generations.\n",ga.statistics().generation()); 
					//ga.flushScores();
					//the 0th index is the number of rules
					hypotheses[c-1][0] = (int)((GA1DBinaryStringGenome &) ga.statistics().bestIndividual()).length() /
											(attributes*fuzzysets);
					//printf("%d ",hypotheses[c-1][0]);

					for(int w=0;w<hypotheses[c-1][0]*(attributes)*fuzzysets;w++)
					{
						GA1DBinaryStringGenome& genome = (GA1DBinaryStringGenome&) ga.statistics().bestIndividual();
						hypotheses[c-1][w+1] = genome.gene(w);
					}
					//cout << endl;

				}
				//find pvalue for this bag
				p[0][l-1] = pvalue(hypotheses,l,14,1);
				free2Dint(hypotheses);
				ga.flushScores();
			}

			for(int b=0;b<1;b++)
			{
				//Mode 1
				int prediction = class_of_first(p[b]);
				double credibility = first(p[b]);
				double confidence = 1 - second(p[b],credibility);

				int actual = test_set[t][attributes];
				if(prediction == actual)
					correct[b][f]++;

				display1(actual,prediction,credibility,confidence,f,t,p[b]);
				printf("%d correct so far\n",correct[b][f]);
				//Mode 2
				//10 levels from 0.01-0.10
				for(int s=1;s<=30;s++)
				{
					float sig = (float) s /(float) 100;
					
					switch(b)
					{
						case 0:
							certaint1[f][s-1] += certainty(sig,p[b]);
							err1[f][s-1] += errorf(sig,p[b],actual);
							errm1[s-1][actual-1] += errorf(sig,p[b],actual);
							break;
						case 1:
							certaint2[f][s-1] += certainty(sig,p[b]);
							err2[f][s-1] += errorf(sig,p[b],actual);
							errm2[s-1][actual-1] += errorf(sig,p[b],actual);
							break;
						case 2:
							certaint3[f][s-1] += certainty(sig,p[b]);
							err3[f][s-1] += errorf(sig,p[b],actual);
							errm3[s-1][actual-1] += errorf(sig,p[b],actual);
							break;
						case 3:
							certaint4[f][s-1] += certainty(sig,p[b]);
							err4[f][s-1] += errorf(sig,p[b],actual);
							errm4[s-1][actual-1] += errorf(sig,p[b],actual);
							break;
						case 4:
							certaint5[f][s-1] += certainty(sig,p[b]);
							err5[f][s-1] += errorf(sig,p[b],actual);
							errm5[s-1][actual-1] += errorf(sig,p[b],actual);
							break;
						case 5:
							certaint6[f][s-1] += certainty(sig,p[b]);
							err6[f][s-1] += errorf(sig,p[b],actual);
							errm6[s-1][actual-1] += errorf(sig,p[b],actual);
							break;
					}
					
					
				}
				class_len[actual-1]++;
			}
			secs2 = time(NULL);
			printf("%ld secs\n",(secs2-secs1));
		}
		
		printf("1:\n");
		display2(f,correct[0][f],certaint1[f],err1[f]);
		
		/*
		printf("2:\n");
		display2(f,correct[1][f],certaint2[f],err2[f]);
		printf("3:\n");
		display2(f,correct[2][f],certaint3[f],err3[f]);
		printf("4:\n");
		display2(f,correct[3][f],certaint4[f],err4[f]);
		printf("5:\n");
		display2(f,correct[4][f],certaint5[f],err5[f]);
		printf("6:\n");
		display2(f,correct[5][f],certaint6[f],err6[f]);
		*/
		for(int b=0;b<6;b++){
			total_correct[b] += correct[b][f];

			for(int i=0;i<30;i++)
			{
				switch(b)
				{
					case 0:
						total_certaint[b][i] += certaint1[f][i];
						total_err[b][i] += err1[f][i];
						break;
					case 1:
						total_certaint[b][i] += certaint2[f][i];
						total_err[b][i] += err1[f][i];
						break;
					case 2:
						total_certaint[b][i] += certaint3[f][i];
						total_err[b][i] += err1[f][i];
						break;
					case 3:
						total_certaint[b][i] += certaint4[f][i];
						total_err[b][i] += err1[f][i];
						break;
					case 4:
						total_certaint[b][i] += certaint5[f][i];
						total_err[b][i] += err1[f][i];
						break;
					case 5:
						total_certaint[b][i] += certaint6[f][i];
						total_err[b][i] += err1[f][i];
						break;
				}
			}
		}
		free2DArray(train_set);
		free2DArray(test_set);

	} //end folds

	char avg_correctness[] = "Accuracy";
	char avg_certainty[] = "Average certainty";
	char avg_error[] = "Average error";

	for(int b=0;b<1;b++){
		printf("%d: ",b);
		display3(avg_correctness,0,(float) total_correct[b] / (float) examples);
	}
	
	FILE *file;
	file = fopen(output,"a");
	
	for(int b=0;b<1;b++){
		printf("%d: confidence certainty error\n",b);
		fprintf(file,"%d: confidence certainty error\n",b);
		for(int s=1;s<=30;s++)
		{
			int l=100-s;
			
			printf("%d %.4f %.4f\n",l,(float) total_certaint[b][s-1] / (float) examples,(float) total_err[b][s-1] / (float) examples);
			fprintf(file,"%d %.4f %.4f\n",l,(float) total_certaint[b][s-1] / (float) examples,(float) total_err[b][s-1] / (float) examples);
			
			//printf("%d %.4f %.4f\n",l,(float) total_certaint[b][s-1],(float) total_err[b][s-1]);
			//fprintf(file,"%d %.4f %.4f\n",l,(float) total_certaint[b][s-1],(float) total_err[b][s-1]);
			//display3(avg_certainty,l,(float) total_certaint[b][s-1] / (float) examples);
			//display3(avg_error,l,(float) total_err[b][s-1] / (float) examples);
			//printf("Class 1 error: %.5f\n",(double) errm[s-1][0] / (double) class_len[0]);
			//printf("Class 2 error: %.5f\n",(double) errm[s-1][1] / (double) class_len[1]);
			
		}
	}
	//printf("Class 1 length: %d\n",class_len[0]);
	//printf("Class 2 length: %d\n",class_len[1]);
	printf("Total: %d\n",examples);
	
	//finish
	return 0;
}

