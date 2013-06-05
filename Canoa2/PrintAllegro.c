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
    ALLEGRO_COLOR agua = al_map_rgb(51, 153, 255);
    ALLEGRO_COLOR ilha = al_map_rgb(180, 0, 0);
    ALLEGRO_COLOR color = al_map_rgb(51, 51, 51);
    
    int i, j;
    int ilha0 = 999999, ilhaf = 0;
    
    
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
            if (tipo(&array[(i+indice)%altura][j]) == TERRA) {
                if (j < ilha0)
                    ilha0 = j;
                if (j > ilhaf)
                    ilhaf = j;
                al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), ilha);
            }
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
        
        
        /*for (i = 0; i < altura; i ++) { /* Imprime cada linha, de trás para frente */
        /*
         margEsq = margemEsquerda(array[i]);
         margDir = margemDireita(array[i], largura);
         for (j = 0; j < largura; j++){
         
         if (tipo(&array[(i+indice)%altura][j]) == '#'){*/
        /*if( j == margDir){
         al_draw_filled_rounded_rectangle(size*i,size*j,size*(i+1),size*(j+1),0.2,0.2, terra);
         }
         else if (j == margEsq){
         al_draw_filled_rounded_rectangle(size*i,size*j,size*(j+1),size*(i+1),0.2, terra);
         }
         else*//*  al_draw_filled_circle(size*j, size*i, size, terra);
                }
                else{
                al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), agua);
                }
                }
                }*/
    }
    al_draw_filled_ellipse(largura*5/2, altura*5*0.9, playerSize/3, playerSize, color);
    
    al_flip_display();
}