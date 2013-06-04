#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_native_dialog.h"
#include "Output.h"
#include "rio.h"
#include "pixel.h"

#define YES 1
#define NO 0
typedef int BOOL;

/*
 Variáveis globais
*/

static ALLEGRO_DISPLAY *display = NULL;    /* Display, ou seja, a janela criada pelo allegro */
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;    /* A event queue, usada para manejar eventos */
static ALLEGRO_TIMER *timer = NULL; /* O timer do programa */

float color = 0.1;

/*
 Protótipos
*/

void freeOutput ();

/*
 Implementação
*/

void initOutput (float velocidadeDoBarco) {
    
    if(!al_init()) {        /* Inicializa o allegro. Se falhar, imprime o erro e sai. */
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    
    display = al_create_display(640, 480);      /* Cria o display */
    
    if(!display) {          /* Caso haja erro na criação, imprime e sai. */
        al_show_native_message_box(display, "Error", "Error", "Failed to create display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    
    event_queue = al_create_event_queue();
    if(!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
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
    
}

void startOutput (pixel **array, int altura, int largura, int indice) {
    al_start_timer(timer);
    
    bool doexit = NO;
    
    outputArray(array, altura, largura, indice);
    
    while (!doexit) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);    /* Tells allegro to wait until an event comes from the queue "event_queue". */
        
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            doexit = YES;
        }
        
        else if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(event_queue)) {   /* If the event was the timer reaching the instant for another loop */
            
            outputArray(array, altura, largura, indice);
        }
        /* According to the wiki, we only want to redraw the frame if the event queue is completely empty.
         "Otherwise, the update loop could fall very far behind".*/
        
    }
    
    freeOutput();
}

void outputArray (pixel **array, int altura, int largura, int indice) {
    outputLine(array[0], largura);
}

void outputLine (pixel *linha, int largura) {
    color *= 1.01;
    al_clear_to_color(al_map_rgb_f(color, color, 0));
    al_flip_display();
    
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

void clearScreen () {
    
}