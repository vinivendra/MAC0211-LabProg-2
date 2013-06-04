#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#define maxCaracter 30

/*
 Implementações
 */


static void clear_newlines()
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
/*Faz a leitura dos parâmetros e permite a usuário corrigir alguma entrada incorreta*/
int getArgs(int argc,char *argv[],float *velocidadeDoBarco, int *larguraDoRio, int *seed, int *fluxoDesejado, int *verbose, int *dIlha, float *pIlha, float *limiteMargens) {
    int read = 0;
    char decision, input[maxCaracter];
    
    while(--argc){ /* Le todos os parâmetros */
        if (sscanf(argv[argc], "-b%f", velocidadeDoBarco)) read++;
        else if (sscanf(argv[argc], "-l%d", larguraDoRio)) read++;
        else if (sscanf(argv[argc], "-s%d", seed)) read++;
        else if (sscanf(argv[argc], "-f%d", fluxoDesejado)) read++;
        else if (sscanf(argv[argc], "-pI%f", pIlha)) read++;
        else if (sscanf(argv[argc], "-dI%d", dIlha)) read++;
        else if (sscanf(argv[argc], "-lM%f", limiteMargens)) read++;
        else if (strcmp(argv[argc],"-v") == 0) *verbose = 1;
        
        /*else { /* Caso o usuário tenha passado um parâmetro que não é aceito, mostramos o que ele pode passar 
            printf ("\nOpcoes disponiveis: \n"
                    "\t-b  - Velocidade do barco\n"
                    "\t-l  - Largura do Rio\n"
                    "\t-s  - semente para o gerador aleatorio\n"
                    "\t-f  - Fluxo da agua\n"
                    "\t-pI - Probabilidade de haver obstaculos\n"
                    "\t-dI - Distancia minima entre obstaculos\n"
                    "\t-lM - Limite das margens\n"
                    "\t-v  - Verbose\n\n"
                    "Você passou um parâmetro errado. "
                    "Gostaria de entrar novamente com os parâmetros? \n"
                    "S - Sim \t\t outro caracter - Nao\n");
            
            scanf ("%c",&decision); /* Pega a decisão 
            clear_newlines();
            
            if(decision == 'S' || decision == 's'){ /* Se ele quer entrar os parâmetros, repetimos até que ele saia (-q) 
                while (1){
                    printf ("Insira os parametros ou digite -q  para continuar:\n");
                    fgets(input,maxCaracter-1,stdin);
                    if (sscanf(input, "-b%f", velocidadeDoBarco)) read++;
                    else if (sscanf(input, " -l%d ", larguraDoRio)) read++;
                    else if (sscanf(input, " -s%d ", seed)) read++;
                    else if (sscanf(input, " -f%d ", fluxoDesejado)) read++;
                    else if (sscanf(input, " -pI%f ", pIlha)) read++;
                    else if (sscanf(input, " -dI%d ", dIlha)) read++;
                    else if (sscanf(argv[argc], "-lM%f", limiteMargens)) read++;
                    else if (strcmp(input,"-v\n") == 0) *verbose = 1;
                    else if (strcmp(input,"-q\n") == 0) return read;
                    
                    else {
                        printf ("\t \t Opcoes disponiveis: \n"
                                "-b  - Velocidade do barco\n"
                                "-l  - Largura do Rio\n"
                                "-s  - semente para o gerador aleatorio\n"
                                "-f  - Fluxo da agua\n"
                                "-pI - Probabilidade de haver obstaculos\n"
                                "-dI - Distancia minima entre obstaculos\n"
                                "-lM - Limite das margens\n"
                                "-v  - Verbose\n");
                    }
                }
            }
            
            else /* Se ele não quer passar mais parâmetros, assumimos que ele só queria saber quais parâmetros eram aceitos 
                exit(-1);
        }*/
    }
    return read;
}

void corrigeArgs (int argc,char *argv[],float *velocidadeDoBarco, int *larguraDoRio, int *seed, int *fluxoDesejado, int *verbose, int *dIlha, float *pIlha, float *limiteMargens) {
    /* Corrige os argumentos passados pelo usuário para atenderem os padrões necessários para o bom funcionamento do programa */
    
    if (*larguraDoRio < 12) {
        *larguraDoRio = 12;
        printf("A largura do rio deve ser um int maior ou igual a 12.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
    if (*velocidadeDoBarco < 0.11) {
        *velocidadeDoBarco = 0.11;
        printf("A velocidade do barco deve ser um float maior ou igual a 0.11.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
    if (*fluxoDesejado <= 0) {
        *fluxoDesejado = 1;
        printf("O fluxo desejado deve ser um int maior que 0.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
    if (*pIlha < 0) {
        *pIlha = 0;
        printf("A probabilidade de ilhas deve ser um float entre 0 e 1.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    else if (*pIlha > 1) {
        *pIlha = 1;
        printf("A probabilidade de ilhas deve ser um float entre 0 e 1.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
    else if (*dIlha < 1) {
        printf("%d\n", *dIlha);
        *dIlha = 1;
        printf("A distância entre ilhas deve ser um int maior ou igual a 1.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
    else if (*limiteMargens <= 0) {
        *limiteMargens = 0.1;
        printf("O limite das margens deve ser um float maior que 0 e menor que 1.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
    else if (*limiteMargens >= 1) {
        *limiteMargens = 0.9;
        printf("O limite das margens deve ser um float maior que 0 e menor que 1.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
}