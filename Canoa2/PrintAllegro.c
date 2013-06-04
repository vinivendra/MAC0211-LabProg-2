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
  ALLEGRO_COLOR terra = al_map_rgb(102, 51, 0);
  ALLEGRO_COLOR agua = al_map_rgb(51,53,255);
  int margEsq, margDir;
  int i, j;
    
  int size = (640/largura);
    
  al_clear_to_color(al_map_rgb_f(0, 0, 0));
    
  for (i = 0; i < altura; i ++) { /* Imprime cada linha, de trás para frente */
    margEsq = margemEsquerda(array[i]);
    margDir = margemDireita(array[i], largura);
    for (j = 0; j < largura; j++){
            
      if (tipo(&array[(i+indice)%altura][j]) == '#'){
	/*if( j == margDir){
	  al_draw_filled_rounded_rectangle(size*i,size*j,size*(i+1),size*(j+1),0.2,0.2, terra);
	}
	else if (j == margEsq){
	  al_draw_filled_rounded_rectangle(size*i,size*j,size*(j+1),size*(i+1),0.2, terra);
	}
	else*/  al_draw_filled_circle(size*j, size*i, size, terra);
      }
	else{
	  al_draw_filled_rectangle(size*j, size*i, size*(j+1), size*(i+1), agua);
	}
      }	
    }
    
  al_flip_display();
}

void clearScreen () {
    
}
