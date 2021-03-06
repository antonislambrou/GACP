#ifndef GLOBAL_H
#define GLOBAL_H
#define classes 2
#define FOLDS 10
#define fuzzysets 5
extern int trainx;
extern int testx;
extern double **train_set;
extern double **test_set;
extern double **means;
extern double **widths;

extern int rules;
extern int pop_size;
extern int gens;
extern char *filename;
extern char *output;
extern int attributes;
extern int examples;
extern int label;
extern int c;
#endif
