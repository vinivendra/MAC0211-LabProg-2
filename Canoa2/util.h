#ifndef H_UTIL_DEFINE
#define H_UTIL_DEFINE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Defines
*/

#define clearScreen() printf("%c[2J%c[1;1H", 27, 27)

/*
 Protótipos
*/

int getArgs(int argc,char *argv[],float *velocidadeDoBarco, int *larguraDoRio, int *seed, int *fluxoDesejado, int *verbose, int *dIlha, float *pIlha, float *limiteMargens);
void corrigeArgs (int argc,char *argv[],float *velocidadeDoBarco, int *larguraDoRio, int *seed, int *fluxoDesejado, int *verbose, int *dIlha, float *pIlha, float *limiteMargens);
#endif
