//return 1 for certainty, 0 otherwise
#include "global.h"

int certainty(double err, double p[])
{
	int ctr = 0;
	for (int i=1; i<=classes;i++)
    	if(p[i-1] > err)
    	    ctr = ctr + 1;
   
	if (ctr <= 1)
    	return 1;
	else
    	return 0;
}
