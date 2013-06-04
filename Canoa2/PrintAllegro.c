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

float color = 0.1;

/*
 Implementação
*/

void outputArray (pixel **array, int altura, int largura, int indice) {
    outputLine(array[0], largura);
}

void outputLine (pixel *linha, int largura) {
    color *= 1.01;
    al_clear_to_color(al_map_rgb_f(color, color, 0));
    
    ALLEGRO_COLOR bla = al_map_rgb(0, 0, 0);
    
    al_draw_filled_rectangle(100, 100, 200, 200, bla);
    
    al_flip_display();
}

void clearScreen () {
    
}