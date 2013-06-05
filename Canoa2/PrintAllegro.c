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

/*
 Implementação
 */

void outputArray (pixel **array, int altura, int largura, int indice) {
    ALLEGRO_COLOR terra = al_map_rgb(110, 60, 40);
    ALLEGRO_COLOR agua = al_map_rgb(35, 200, 240);
    
    int i, j;
    
    int size = (640/largura);
    
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
    
    for (i = 0; i < altura; i ++) { /* Imprime cada linha, de trás para frente */
        
        int TMargemEsquerda = margemEsquerda(array[(i+indice)%altura]);
        int TMargemDireita = margemDireita(array[(i+indice)%altura], largura);
        
        for (j = 0; j < TMargemEsquerda - 2; j++)
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
                
        if (tipo(&array[(i+indice+1)%altura][j+2]) == '#') {
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
            j++;
            al_draw_filled_triangle(size*j, size*i, size*j, size*(i+1), size*(j+1), size*(i+1), terra);
            al_draw_filled_triangle(size*j, size*i, size*(j+1), size*i, size*(j+1), size*(i+1), agua);
        }
        else if (tipo(&array[(i+indice+1)%altura][j+1]) == '#') {
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
        
        
        for (j = TMargemEsquerda; j < largura - TMargemDireita - 1; j++) {
            if (tipo(&array[(i+indice)%altura][j]) == '#')
                al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
            else
                al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), agua);
        }
        
        for (j = largura - TMargemDireita; j < largura; j++)
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
        
        for (j = 0; j < largura; j++) {
            printf("%c", tipo(&array[(i+indice)%altura][j]));
        }
        printf("\n");
        
    }
    
    printf("\n");
    al_flip_display();
}



void clearScreen () {
    
}