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


/*
 Implementação
*/

void initOutput (float velocidadeDoBarco) {
    

    
}

void startOutput (pixel **array, int altura, int largura, int indice) {

}

void outputArray (pixel **array, int altura, int largura, int indice) {
    outputLine(array[0], largura);
}

void outputLine (pixel *linha, int largura) {
    color *= 1.01;
    al_clear_to_color(al_map_rgb_f(color, color, 0));
    al_flip_display();
    
}


void clearScreen () {
    
}