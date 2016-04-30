#ifndef AUX_H
#define AUX_H
#include <stdio.h>
#include "global.h"
void display3(char *str,int l, float result);
void display2(int fold,int correct,int certaint[],int err[]);
void display1(int actual,int prediction,double credibility,
				double confidence,int f,int t,double p[]);
double first(double p[]);
int class_of_first(double p[]);
double second(double p[], double first);

#endif
