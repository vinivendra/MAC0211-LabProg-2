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
    outputLine(array[0], largura);
}

void outputLine (pixel *linha, int largura) {
    
    ALLEGRO_COLOR terra = al_map_rgb(110, 60, 40);
    ALLEGRO_COLOR agua = al_map_rgb(35, 200, 240);
    int i = 0;
    
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
    
    for (i = 0; i < largura; i ++) {
        if (tipo(&linha[i]) == '#') {
            al_draw_filled_rectangle((640/largura)*(i+1), 0, (640/largura)*i, 640/largura, terra);
        }
        else al_draw_filled_rectangle((640/largura)*(i+1), 0, (640/largura)*i, 640/largura, agua);
    }
    
    al_draw_filled_rectangle(100, 100, 200, 200, terra);
    
    al_flip_display();
}

void clearScreen () {
    
}