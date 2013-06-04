#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_native_dialog.h"
#include "Output.h"
#include "rio.h"
#include "pixel.h"

/*
 Variáveis globais
*/

static ALLEGRO_DISPLAY *display = NULL;    /* Display, ou seja, a janela criada pelo allegro */
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;    /* A event queue, usada para manejar eventos */

/*
 Protótipos
*/

void freeOutput ();

/*
 Implementação
*/

void initOutput (float velocidadeDoBarco) {
    
    if(!al_init()) {        /* Inicializa o allegro. Se falhar, imprime o erro e sai. */
    zx    al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
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
    
    /* Registrar quaisquer fontes de eventos */
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
}

void outputArray (pixel **array, int altura, int largura, int indice) {
    ALLEGRO_EVENT ev;
    
    bool get_event = al_wait_for_event_timed(event_queue, &ev, 1/60);
    
    if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        freeOutput();
        exit(1);
    }
    
    al_clear_to_color(al_map_rgb_f(1, 1, 0));
    al_flip_display();
}

void outputLine (pixel *linha, int largura) {
    
    al_clear_to_color(al_map_rgb_f(1, 1, 0));
    al_flip_display();
    
}

void freeOutput () {
    if (display != NULL)
        al_destroy_display(display);            /* Dá free no display */
    if (event_queue != NULL)
        al_destroy_event_queue(event_queue);    /* Dá free na event queue */
}

void clearScreen () {
    
}