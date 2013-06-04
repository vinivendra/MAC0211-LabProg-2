#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include "Output.h"
#include "rio.h"
#include "pixel.h"

void initOutput () {
    al_init();
    al_create_display(640, 480);
}

void clearScreen () {
    
}

void outputArray (pixel **array, int altura, int largura, int indice) {
    al_clear_to_color(al_map_rgb_f(1, 1, 0));
    al_flip_display();
}

void outputLine (pixel *linha, int largura) {
    
    al_clear_to_color(al_map_rgb_f(1, 1, 0));
    al_flip_display();
    
}