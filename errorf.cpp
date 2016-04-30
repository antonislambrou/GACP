//return 1 for error, 0 otherwise
#include "global.h"
int errorf(double err,double p[],int actual)
{
	int y=1;
	for(int i=1; i<=classes;i++)
    {
    	if(p[i-1] > err && i == actual)
     	{
     		y = 0;
        	break;
    	}
	}
	return y;
}
