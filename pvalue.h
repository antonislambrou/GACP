#ifndef PVALUE_H
#define PVALUE_H
#include <ga/ga.h>
#include <ga/GAStringGenome.h>
#include <ga/GA1DBinStrGenome.h>
#include <ga/GAAllele.h>
#include "global.h"
#include "membership.h"

double pvalue(int **hypotheses, int l, int eq, float gamma);
#endif
