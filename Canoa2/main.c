#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <allegro5/allegro.h>
#include "Output.h"
#include "grade.h"
#include "util.h"
#include "pixel.h"

#define velocidadeDoBarcoInicial 1
#define larguraDoRioInicial 100
#define fluxoDesejadoInicial 50
#define alturaDaGrade 30
#define distanciaEntreIlhasInicial 10
#define probabilidadeDeObstaculosInicial 0.5
#define limiteDasMargens 0.9

int main (int argc, char *argv[]) {
    
    /*
     Declaração de variáveis
     */
    
    float velocidadeDoBarco = velocidadeDoBarcoInicial;
    int larguraDoRio = larguraDoRioInicial;
    int fluxoDesejado = fluxoDesejadoInicial;
    int dIlha = distanciaEntreIlhasInicial;
    float pIlha = probabilidadeDeObstaculosInicial;
    float limiteMargens = limiteDasMargens;
    
    struct timespec tim2;
    struct timespec tim;
    
    int seed = 1;
    int verbose = 0;
    int indice = 0;
    pixel **grade;
    
    /*
     Leitura de parametros
     */
    
    getArgs(argc, argv, &velocidadeDoBarco, &larguraDoRio, &seed, &fluxoDesejado, &verbose, &dIlha, &pIlha, &limiteMargens);
    corrigeArgs(argc, argv, &velocidadeDoBarco, &larguraDoRio, &seed, &fluxoDesejado, &verbose, &dIlha, &pIlha, &limiteMargens);
    
    
    
    if (verbose) {
        printf ("\t \t Opcoes disponiveis: \n"
                "-b = %f  - Velocidade do barco\n"
                "-l = %d  - Largura do Rio\n"
                "-s = %d  - Semente para o gerador aleatorio\n"
                "-f = %d  - Fluxo da agua\n"
                "-v = %d  - Verbose\n"
                "-pI = %f - Probabilidade de haver obstaculos\n"
                "-dI = %d - Distancia minima entre obstaculos\n"
                "-lM = %f - Limite de tamanho das margens (de 0 a 1)\n"
                "Pressione Enter para continuar...\n", velocidadeDoBarco, larguraDoRio, seed, fluxoDesejado, verbose, pIlha, dIlha, limiteMargens);
        getchar();
    }
    
    /*
     Inicialização
     */
    
    tim.tv_sec  = 0;
    tim.tv_nsec = 100000000/velocidadeDoBarco;
    
    /*
     Seed
     */
    
    if (seed == 0)
        seed = (int)time(NULL);
    
    srand(seed);
    
    /*
     Criação do primeiro frame
     */
    
    grade = initGrade(alturaDaGrade, larguraDoRio);
    
    criaPrimeiroFrame(grade, alturaDaGrade, larguraDoRio, limiteMargens, fluxoDesejado, dIlha, pIlha);
    
    initOutput();
    
    outputArray(grade, alturaDaGrade, larguraDoRio, indice);
    
    clearScreen();
    
    /*
     Frames subsequentes
     */
    
    for(;;){
        indice = (indice - 1+alturaDaGrade) % alturaDaGrade;
        
        criaProximoFrame(grade, alturaDaGrade, larguraDoRio, limiteMargens, fluxoDesejado, indice, dIlha, pIlha);
        
        outputArray(grade, alturaDaGrade, larguraDoRio, indice);
        
        clearScreen();
        
        nanosleep(&tim, &tim2);
    }
    
    /*
     Frees
     */
    
    freeGrade(grade, alturaDaGrade, larguraDoRio);
    freeOutput ();
    
    return 0;
}





