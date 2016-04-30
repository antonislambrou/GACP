#ifndef OBJECTIVE_H
#define OBJECTIVE_H
#include <ga/ga.h>
#include <ga/GAStringGenome.h>
#include <ga/GA1DBinStrGenome.h>
#include <ga/GAAllele.h>
#include "global.h"
#include <math.h>
#include "membership.h"
float Objective(GAGenome& g);
#endif
