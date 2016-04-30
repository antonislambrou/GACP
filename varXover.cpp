#include <ga/ga.h>
#include <ga/GAStringGenome.h>
#include <ga/GA1DBinStrGenome.h>
#include <ga/GAAllele.h>
#include "global.h"
#include <stdio.h>
int VariableSizeCrossover(const GAGenome& p1, const GAGenome& p2, GAGenome* c1, GAGenome* c2)
{

	//  cout << "Crossover..." << endl;
	//  cout.flush();

	GA1DBinaryStringGenome &mom = (GA1DBinaryStringGenome &)p1;
	GA1DBinaryStringGenome &dad = (GA1DBinaryStringGenome &)p2;
	int nc=0;
	//info &data = *(info *)p1.userData();
	int Rlength = (attributes) * fuzzysets;

	int momRules = mom.length() / Rlength;
	int dadRules = dad.length() / Rlength;

	int momP1;  //P1 in mom genome
	int momP2;  //P2 in mom genome
	int dadP1;  //P1 in dad genome
	int dadP2;  //P2 in dad genome
	int momlen1, momlen2, dadlen1, dadlen2;

	unsigned int ruleP1 = GARandomInt(0, Rlength);  //P1 possition in the rule
	unsigned int ruleP2 = GARandomInt(0, Rlength);  //P2 possition in the rule
	if (ruleP1 > ruleP2)
	{
		int temp = ruleP1;
		ruleP1 = ruleP2;
		ruleP2 = temp;
	}
	unsigned int momRuleP1 = GARandomInt(0, momRules-1);  //Rule where moms P1 will be placed
	unsigned int momRuleP2 = GARandomInt(0, momRules-1);  //Rule where moms P2 will be placed
	if (momRuleP1 > momRuleP2)
	{
		int temp = momRuleP1;
		momRuleP1 = momRuleP2;
		momRuleP2 = temp;
	}
	unsigned int dadRuleP1 = GARandomInt(0, dadRules-1);  //Rule where dads P1 will be placed
	unsigned int dadRuleP2 = GARandomInt(0, dadRules-1);  //Rule where dads P2 will be placed
	if (dadRuleP1 > dadRuleP2)
	{
		int temp = dadRuleP1;
		dadRuleP1 = dadRuleP2;
		dadRuleP2 = temp;
	}

	momP1 = (momRuleP1*Rlength) + ruleP1;
	momP2 = (momRuleP2*Rlength) + ruleP2;
	dadP1 = (dadRuleP1*Rlength) + ruleP1;
	dadP2 = (dadRuleP2*Rlength) + ruleP2;

	momlen1 = momP2 - momP1;
	momlen2 = mom.length() - momP2;
	dadlen1 = dadP2 - dadP1;
	dadlen2 = dad.length() - dadP2;

	if (c1)
	{
		GA1DBinaryStringGenome &sis = (GA1DBinaryStringGenome &)*c1;
		int sisSize = momP1 + dadlen1 + momlen2;
		sis.resize(sisSize);

		sis.copy(mom, 0, 0, momP1);

		sis.copy(dad, momP1, dadP1, (dadP2-dadP1));

		sis.copy(mom, (momP1+dadP2-dadP1), momP2, mom.length()-momP2);

		nc += 1;
	}
	if (c2)
	{
		GA1DBinaryStringGenome &bro =
		(GA1DBinaryStringGenome &)*c2; int broSize =
		dadP1 + momlen1 + dadlen2; bro.resize(broSize);
		bro.copy(dad, 0, 0, dadP1);
		bro.copy(mom, dadP1, momP1, (momP2-momP1));
		bro.copy(dad, (dadP1+momP2-momP1), dadP2, dad.length()-dadP2);
		nc += 1;
	}

	return nc;
}
