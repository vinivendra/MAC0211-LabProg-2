#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_primitives.h>
#include "Output.h"
#include "rio.h"
#include "pixel.h"

#define YES 1
#define NO 0
typedef int BOOL;

/*
 Implementação
*/

void outputArray (pixel **array, int altura, int largura, int indice) {
    int i;
    
    for (i = 0; i < altura; i ++) /* Imprime cada linha, de trás para frente */
        outputLine(array[(i+indice)%altura], largura, (i+indice)%altura);
}

void outputLine (pixel *linha, int largura, int indice) {
    
    ALLEGRO_COLOR terra = al_map_rgb(110, 60, 40);
    ALLEGRO_COLOR agua = al_map_rgb(35, 200, 240);
    int i = 0;
    
    int size = (640/largura);
    
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
    
    for (i = 0; i < largura; i ++) {
        if (tipo(&linha[i]) == '#') {
            al_draw_filled_rectangle(size*i, size*indice, size*(i+1), size*(indice+1), terra);
        }
        else al_draw_filled_rectangle(size*i, size*indice, size*(i+1), size*(indice+1), agua);
    }
    
    al_draw_filled_rectangle(100, 100, 200, 200, terra);
    
    al_flip_display();
}

void clearScreen () {
    
}