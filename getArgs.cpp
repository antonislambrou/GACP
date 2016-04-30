#include "global.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
using namespace std;

void getArgs(int argc,char **argv)
{
	int no_train_set=1;
	
	for(int ii=1;ii<argc;ii++){
		if(strcmp(argv[ii++],"pop_size") == 0){
			pop_size = atoi(argv[ii]);
		}
	}
	for(int ii=1;ii<argc;ii++){
		if(strcmp(argv[ii++],"gens") == 0){
			gens = atoi(argv[ii++]);
		}
	}
	
	for(int ii=1; ii<argc; ii++) {
		if(strcmp(argv[ii++],"data_set") == 0) {
			filename = argv[ii];
			no_train_set = 0;
		}
	}
	
	for(int ii=1; ii<argc; ii++) {
		if(strcmp(argv[ii++],"rules") == 0) {
			rules = atoi(argv[ii]);
		}
	}
	
	for(int ii=1; ii<argc; ii++) {
		if(strcmp(argv[ii++],"output") == 0) {
			output = argv[ii];
		}
	}
	
	//check command line arguments
	if(argc<5)
	{
		printf("usage: ./ecp data_set <filename> gens <#> pop_size <#> rules <#> output <filename>\n");
		exit(-1);
	}
}
