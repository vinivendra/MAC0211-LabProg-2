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

void outputArray (pixel **array, int altura, int largura, int indice, int player_x, int player_y) {
    ALLEGRO_COLOR terra = al_map_rgb(110, 60, 40);      /* Cores */
    ALLEGRO_COLOR agua = al_map_rgb(51, 153, 255);
    ALLEGRO_COLOR ilha = al_map_rgb(6, 96, 0);
    ALLEGRO_COLOR canoa = al_map_rgb(51, 51, 51);
    
    int i, j;
    int ilha0 = 999999, ilhaf = 0;      /* Variáveis que guardam o começo de uma ilha e o final dela */
    
#warning Size tem que ser passado como argumento a partir do main
    
    int size = 5;
    
    
    for (i = 0; i < altura; i ++) { /* Imprime uma linha de cada vez */
        
        int TMargemEsquerda = margemEsquerda(array[(i+indice)%altura]);         /* Os tamanhos das margens */
        int TMargemDireita = margemDireita(array[(i+indice)%altura], largura);
        
        /* Desenha a margem esquerda */
        al_draw_filled_rectangle(0, size*i, size*(TMargemEsquerda - 2), size*(i+1), terra);
        
        
        /* Desenha o encontro da terra com a água, criando triângulos ou retângulos conforme necessário */
        j = TMargemEsquerda - 2;
        
#warning arrumar o encontro da terra com a agua na linha mais de baixo
        
        if (tipo(&array[(i+indice+1)%altura][j+2]) == TERRA) {          /* Se a linha de baixo era maior */
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
            j++;
            al_draw_filled_triangle(size*j, size*i, size*j, size*(i+1), size*(j+1), size*(i+1), terra);
            al_draw_filled_triangle(size*j, size*i, size*(j+1), size*i, size*(j+1), size*(i+1), agua);
        }
        else if (tipo(&array[(i+indice+1)%altura][j+1]) == TERRA) {     /* Se era igual */
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), terra);
            j++;
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), agua);
        }
        else {      /* Se era menor */
            al_draw_filled_triangle(size*j, size*i, size*(j+1), size*i, size*j, size*(i+1), terra);
            al_draw_filled_triangle(size*(j+1), size*(i+1), size*(j+1), size*i, size*j, size*(i+1), agua);
            j++;
            al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), agua);
        }
        
        
        
        /* Descobre onde começa e termina a ilha */
        for (j = TMargemEsquerda; j < largura - TMargemDireita - 2; j++)
            if (tipo(&array[(i+indice)%altura][j]) == TERRA) {
                if (j < ilha0)
                    ilha0 = j;
                if (j > ilhaf)
                    ilhaf = j;
            }
    
        
        if (ilhaf != 0) {       /* Se existe uma ilha, desenha primeiro as duas partes de água, depois ela em cima */
            al_draw_filled_rectangle(size*TMargemEsquerda, size*i, size*(ilha0 + 1), size*(i+1), agua);
            al_draw_filled_rectangle(size*(ilhaf), size*i, size*(largura - TMargemDireita), size*(i+1), agua);
            al_draw_filled_rounded_rectangle(size*ilha0,size*i,size*(ilhaf+1),size*(i+1),3,3, ilha);
        }
        else {                  /* Caso contrário, bastea desenhar uma parte de água */
            al_draw_filled_rectangle(size*TMargemEsquerda, size*i, size*(largura - TMargemDireita), size*(i+1), agua);
        }
        ilha0 = 999999;         /* Reseta os valores */
        ilhaf = 0;
#warning limitar a altura e a largura de acordo com o tamanho maximo da janela fornecido pelo allegro. Limita-lo também a multiplos de size.
        
        
        /* Desenha o segundo encontro da água com a terra */
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
        
        
        /* Desenha a margem direita */
        al_draw_filled_rectangle(size*(largura - TMargemDireita), size*i, size*(largura), size*(i+1), terra);
        
    }
    
    /* Desenha o jogador na posição correta */
    al_draw_filled_ellipse(player_x, player_y, playerSize/3, playerSize, canoa);
    
    /* Coloca tudo o que foi desenhado na tela */
    al_flip_display();
}