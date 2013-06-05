#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_primitives.h>
#include "rio.h"
#include "Output.h"
#include "rio.h"
#include "pixel.h"

#define YES 1
#define NO 0
typedef int BOOL;

#define TERRA '#'
#define AGUA '.'

#define playerSize 30

/*
 Implementação
 */

void outputArray (pixel **array, int altura, int largura, int indice) {
    ALLEGRO_COLOR terra = al_map_rgb(110, 60, 40);
    ALLEGRO_COLOR agua = al_map_rgb(35, 200, 240);
    ALLEGRO_COLOR color = al_map_rgb(180, 1, 2);
    
    int i, j;
    
    int size = (5);
    
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
    
    for (i = 0; i < altura; i ++) { /* Imprime cada linha, de trás para frente */
        
        int TMargemEsquerda = margemEsquerda(array[(i+indice)%altura]);
        int TMargemDireita = margemDireita(array[(i+indice)%altura], largura);
        
        for (j = 0; j < TMargemEsquerda - 2; j++)
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
                
        if (tipo(&array[(i+indice+1)%altura][j+2]) == TERRA) {
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
            j++;
            al_draw_filled_triangle(size*j, size*i, size*j, size*(i+1), size*(j+1), size*(i+1), terra);
            al_draw_filled_triangle(size*j, size*i, size*(j+1), size*i, size*(j+1), size*(i+1), agua);
        }
        else if (tipo(&array[(i+indice+1)%altura][j+1]) == TERRA) {
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
            j++;
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), agua);
        }
        else {
            al_draw_filled_triangle(size*j, size*i, size*(j+1), size*i, size*j, size*(i+1), terra);
            al_draw_filled_triangle(size*(j+1), size*(i+1), size*(j+1), size*i, size*j, size*(i+1), agua);
            j++;
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), agua);
        }
        
        
        for (j = TMargemEsquerda; j < largura - TMargemDireita - 2; j++) {
            if (tipo(&array[(i+indice)%altura][j]) == TERRA)
                al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
            else
                al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), agua);
        }
        
        if (tipo(&array[(i+indice+1)%altura][j+2]) == AGUA) {
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), agua);
            j++;
            al_draw_filled_triangle(size*j, size*i, size*j, size*(i+1), size*(j+1), size*(i+1), agua);
            al_draw_filled_triangle(size*j, size*i, size*(j+1), size*i, size*(j+1), size*(i+1), terra);
        }
        else if (tipo(&array[(i+indice+1)%altura][j+1]) == AGUA) {
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), agua);
            j++;
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
        }
        else {
            al_draw_filled_triangle(size*j, size*i, size*(j+1), size*i, size*j, size*(i+1), agua);
            al_draw_filled_triangle(size*(j+1), size*(i+1), size*(j+1), size*i, size*j, size*(i+1), terra);
            j++;
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
        }
        
        for (j = largura - TMargemDireita; j < largura; j++)
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
    }
        
    al_draw_filled_ellipse(largura*5/2, altura*5*0.9, playerSize/3, playerSize, color);
    
    al_flip_display();
}