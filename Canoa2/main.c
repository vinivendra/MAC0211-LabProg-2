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

#define velocidadeDoBarcoInicial 50
#define larguraDoRioInicial (480/5)
#define fluxoDesejadoInicial 50
#define alturaDaGrade (200)
#define distanciaEntreIlhasInicial 25
#define probabilidadeDeObstaculosInicial 0.3
#define limiteDasMargens 0.25

/*
 Defines de valores iniciais
*/
#pragma mark Defines

/*
 BOOL
*/


#define YES 1
#define NO 0
typedef int BOOL;

/*
 Teclas das setas
*/

enum KEYS {
  KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

/*
 Protótipos
*/
#pragma mark Protótipos

void freeOutput(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer);

/*
 main
*/
#pragma mark main

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
    
  int size = 5;
    
  bool doexit = NO;
    
  bool key[4] = {NO, NO, NO, NO};
    
  int player_x = larguraDoRio*size/2, player_y = alturaDaGrade*size - 40;
  int boatSize = size + larguraDoRio*0.1;

  int velLR =  size*larguraDoRio*0.006 + 2;
  int velU = (size*alturaDaGrade*0.006);
  int velD = (size*alturaDaGrade*0.02);

  int seed = 1;
  int verbose = 0;
  int indice = 0;
  pixel **grade;
    
  ALLEGRO_DISPLAY *display = NULL;    /* Display, ou seja, a janela criada pelo allegro */
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;    /* A event queue, usada para manejar eventos */
  ALLEGRO_TIMER *timer = NULL; /* O timer do programa */
    
  /*
    Leitura de parametros
  */
    
  getArgs(argc, argv, &velocidadeDoBarco, &larguraDoRio, &seed, &fluxoDesejado, &verbose, &dIlha, &pIlha, &limiteMargens, &size);
  corrigeArgs(argc, argv, &velocidadeDoBarco, &larguraDoRio, &seed, &fluxoDesejado, &verbose, &dIlha, &pIlha, &limiteMargens, &size);
  
  if(boatSize > 30) boatSize = 30;
  if(velU > 5) velU = 5;
  if(velD > 7) velD = 9;
    
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
	    "-D = %d - Tamanho de cada pixel\n"
	    "Pressione Enter para continuar...\n", velocidadeDoBarco, larguraDoRio, seed, fluxoDesejado, verbose, pIlha, dIlha, limiteMargens, size);
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
    
  /*
    Allegro initialization
  */
    
  if(!al_init()) {        /* Inicializa o allegro. Se falhar, imprime o erro e sai. */
    al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    exit(-1);
  }
    
  al_init_primitives_addon();
    
  display = al_create_display(larguraDoRio*size, (alturaDaGrade-1)*size);      /* Cria o display */
    
  if(!display) {          /* Caso haja erro na criação, imprime e sai. */
    al_show_native_message_box(display, "Error", "Error", "Failed to create display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    exit(-1);
  }
    
  event_queue = al_create_event_queue();
  if(!event_queue) {
    al_show_native_message_box(display, "Error", "Error", "Failed to create event queue!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    freeOutput(display, event_queue, timer);
    exit(-1);
  }
    
  timer = al_create_timer(1.0/velocidadeDoBarco);
  if(!timer) {
    al_show_native_message_box(display, "Error", "Error", "Failed to create timer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    freeOutput(display, event_queue, timer);
    exit(-1);
  }
    
  if(!al_install_keyboard()) {
    al_show_native_message_box(display, "Error", "Error", "Failed to initialize keyboard!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    freeOutput(display, event_queue, timer);
    exit(-1);
  }

    
  /* Registrar quaisquer fontes de eventos */
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
    
  /*
    Frames subsequentes
  */

  al_start_timer(timer);
    
  outputArray(grade, alturaDaGrade, larguraDoRio, indice, player_x, player_y, size);
    
  while (!doexit) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);    /* Tells allegro to wait until an event comes from the queue "event_queue". */
        
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      doexit = YES;
    }
        
    else if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(event_queue)) {   /* If the event was the timer reaching the instant for another loop */
            
      if(key[KEY_UP] && player_y > (2*velU + boatSize*2) ) {
	player_y -= velU;
      }
      if(key[KEY_DOWN] && player_y < alturaDaGrade*size-(2*velD + boatSize*2)) {
	player_y += velD;
      }
      if(key[KEY_LEFT] && player_x > (2*velLR + 2*boatSize/3)) {
	player_x -= velLR;
      }
      if(key[KEY_RIGHT] && player_x < larguraDoRio*size - (2*velLR + 2*boatSize/3)) {
	player_x += velLR;
      }
            
      indice = (indice - 1+alturaDaGrade) % alturaDaGrade;
            
      criaProximoFrame(grade, alturaDaGrade, larguraDoRio, limiteMargens, fluxoDesejado, indice, dIlha, pIlha);
            
      outputArray(grade, alturaDaGrade, larguraDoRio, indice, player_x, player_y, size);
            
    }
        
    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch(ev.keyboard.keycode) {
      case ALLEGRO_KEY_UP:
	key[KEY_UP] = YES;
	break;
      case ALLEGRO_KEY_DOWN:
	key[KEY_DOWN] = YES;
	break;
      case ALLEGRO_KEY_LEFT:
	key[KEY_LEFT] = YES;
	break;
      case ALLEGRO_KEY_RIGHT:
	key[KEY_RIGHT] = YES;
	break;
      }
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
      switch(ev.keyboard.keycode) {
      case ALLEGRO_KEY_UP:
	key[KEY_UP] = NO;
	break;
      case ALLEGRO_KEY_DOWN:
	key[KEY_DOWN] = NO;
	break;
      case ALLEGRO_KEY_LEFT:
	key[KEY_LEFT] = NO;
	break;
      case ALLEGRO_KEY_RIGHT:
	key[KEY_RIGHT] = NO;
	break;
      case ALLEGRO_KEY_ESCAPE:
	doexit = YES;
	break;
      }
    }
  }

    freeOutput(display, event_queue, timer);        /* Dá free em qualquer coisa que o allegro tenha allocado */
    
    freeGrade(grade, alturaDaGrade, larguraDoRio);  /* Dá free na matriz da grade */
    
    return 0;
}

#pragma mark Funções auxiliares

void freeOutput(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer) { /* Dá free em qualquer coisa que o allegro tenha allocado */
    if (display != NULL)
        al_destroy_display(display);            /* Dá free no display */
    if (event_queue != NULL)
        al_destroy_event_queue(event_queue);    /* Dá free na event queue */
    if (timer != NULL) {
        al_destroy_timer(timer);                /* Dá free no timer */
    }

}


