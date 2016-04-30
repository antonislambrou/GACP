/* Variable size initialiser */
#include <ga/ga.h>
#include <ga/GAStringGenome.h>
#include <ga/GA1DBinStrGenome.h>
#include <ga/GAAllele.h>
#include "global.h"
#include <stdio.h>
void VariableSizeInitializer(GAGenome & c)
{

	GA1DBinaryStringGenome &child=(GA1DBinaryStringGenome &)c;

	//info &data = *(info *)c.userData();
	//int Rlength = data.RuleSize;
	int Rlength = (attributes) * fuzzysets;
	int RuleNum = GARandomInt(1, child.resizeBehaviour()/Rlength);
	//printf("%d\n",RuleNum*Rlength);
	//char alleles[2] = {'0','1'};

	child.resize(RuleNum*Rlength);

	//srandom(seed);
	for(int i = 0; i < RuleNum*Rlength; i++)
	{

		child.gene(i, (int)GAFlipCoin(0.9));
	}
}
