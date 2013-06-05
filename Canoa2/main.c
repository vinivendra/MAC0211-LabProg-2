#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_primitives.h>
#include "Output.h"
#include "grade.h"
#include "util.h"
#include "pixel.h"

#define velocidadeDoBarcoInicial 10
#define larguraDoRioInicial (480/5)
#define fluxoDesejadoInicial 50
#define alturaDaGrade (480/5)
#define distanciaEntreIlhasInicial 10
#define probabilidadeDeObstaculosInicial 0.5
#define limiteDasMargens 0.9

#define YES 1
#define NO 0
typedef int BOOL;


static ALLEGRO_DISPLAY *display = NULL;    /* Display, ou seja, a janela criada pelo allegro */
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;    /* A event queue, usada para manejar eventos */
static ALLEGRO_TIMER *timer = NULL; /* O timer do programa */

void freeOutput ();

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
    
    bool doexit = NO;
    
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
            
    clearScreen();
    
    /*
     Allegro initialization
    */
    
    if(!al_init()) {        /* Inicializa o allegro. Se falhar, imprime o erro e sai. */
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    
    al_init_primitives_addon();
    
    display = al_create_display(larguraDoRio*5, alturaDaGrade*5);      /* Cria o display */
    
    if(!display) {          /* Caso haja erro na criação, imprime e sai. */
        al_show_native_message_box(display, "Error", "Error", "Failed to create display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    
    event_queue = al_create_event_queue();
    if(!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event queue!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        freeOutput();
        exit(-1);
    }
    
    timer = al_create_timer(1.0/velocidadeDoBarco);
    if(!timer) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create timer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        freeOutput();
        exit(-1);
    }
    
    /* Registrar quaisquer fontes de eventos */
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    /*
     Frames subsequentes
     */
    
    al_start_timer(timer);
        
    outputArray(grade, alturaDaGrade, larguraDoRio, indice);
    
    while (!doexit) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);    /* Tells allegro to wait until an event comes from the queue "event_queue". */
        
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            doexit = YES;
        }
        
        else if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(event_queue)) {   /* If the event was the timer reaching the instant for another loop */
            
            indice = (indice - 1+alturaDaGrade) % alturaDaGrade;
            
            criaProximoFrame(grade, alturaDaGrade, larguraDoRio, limiteMargens, fluxoDesejado, indice, dIlha, pIlha);
            
            outputArray(grade, alturaDaGrade, larguraDoRio, indice);
            
        }
        /* According to the wiki, we only want to redraw the frame if the event queue is completely empty.
         "Otherwise, the update loop could fall very far behind".*/
        
    }
    
    /*
     Frees
     */
    
    freeOutput();
    
    freeGrade(grade, alturaDaGrade, larguraDoRio);
    
    return 0;
}



void freeOutput () {
    if (display != NULL)
        al_destroy_display(display);            /* Dá free no display */
    if (event_queue != NULL)
        al_destroy_event_queue(event_queue);    /* Dá free na event queue */
    if (timer != NULL) {
        al_destroy_timer(timer);
    }
}


