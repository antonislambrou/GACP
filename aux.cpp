#include <stdio.h>
#include <stdlib.h>
#include "global.h"

void display3(char *str,int l, float result)
{
	FILE *file;
	file = fopen(output,"a");
	if(l==0){
		fprintf(file,"%s: %.4f\n",str,result);
		fprintf(stdout,"%s: %.4f\n",str,result);
	}
	else{
		fprintf(file,"%s %d%%: %.4f\n",str,l,result);
		fprintf(stdout,"%s %d%%: %.4f\n",str,l,result);
	}
	fclose(file);
}


void display2(int fold,int correct,int certaint[],int err[])
{
	FILE *file;
	file = fopen(output,"a");	
	
	fprintf(file,"\nFOLD %d\n",fold);
	fprintf(file," Correctness: %.4f\n", (float) correct / (float) testx);
	fprintf(stdout,"\nFOLD %d\n",fold);
	fprintf(stdout," Correctness: %.4f\n", (float) correct / (float) testx);
	
	for(int l=1;l<=30;l++)
	{
		int level = 100 - l;
		
		fprintf(file,"%d %.4f %.4f\n",level, (float) certaint[l-1] / (float) testx, (float) err[l-1] /  (float) testx);
		//fprintf(file," Certainty: %.4f\n",(float) certaint[l-1] / (float) testx);
		//fprintf(file," Error	 : %.4f\n\n", (float) err[l-1] /  (float) testx);
		
		fprintf(stdout,"%d %.4f %.4f\n",level, (float) certaint[l-1] / (float) testx, (float) err[l-1] /  (float) testx);
		//fprintf(stdout," Certainty: %.4f\n",(float) certaint[l-1] / (float) testx);
		//fprintf(stdout," Error	 : %.4f\n\n", (float) err[l-1] /  (float) testx);
	}
	fclose(file); 
}

void display1(int actual,int prediction,double credibility,
				double confidence,int f,int t, double p[])
{
	FILE *file;
	file = fopen(output,"a");	
	fprintf(file,"Fold %d, example %d\n",f,t);
	fprintf(stdout,"Fold %d, example %d\n",f,t);
	for(int x=0;x<classes;x++)
	{	
		fprintf(file," %d: %.4f\n",x,p[x]);
		fprintf(stdout," %d: %.4f\n",x,p[x]);
	}
	fprintf(file,"Actual class: %d, Prediction %d, Confidence %.4f \
Credibility: %.2f\n",actual,prediction,confidence,credibility);
	fprintf(stdout,"Actual class: %d, Prediction %d, Confidence %.4f \
Credibility: %.2f\n",actual,prediction,confidence,credibility);
	fclose(file);	
}

/* return the largest pvalue */
double first(double p[])
{
	double val = 0;
	
	for(int i=0;i<classes;i++)
	{
		if(val<p[i])
			val=p[i];
	}
	return val;
}

/* return the class of the first pvalue */
int class_of_first(double p[])
{
	int c=0;
	double val=0;
	for(int i=0;i<classes;i++)
	{
		if(val<p[i])
		{
			val=p[i];
			c=i+1;
		}
	}
	return c;
}

/* return the second largest pvalue */
double second(double p[], double first)
{
	double val = 0;
	for(int i=0;i<classes;i++)
	{
		if(p[i] == first)
			continue;
			
		if(val<p[i])
			val=p[i];
	}
	
	return val;
}

