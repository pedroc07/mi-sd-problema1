# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <intelfpgaup/video.h>

int preenche_zero(int t[10][20]){
    int cont0;
    int cont1;
    for(cont0 = 0; cont0 < 10; cont0++)
  {
        for(cont1 = 0; cont1 < 20; cont1++){
            t[cont0][cont1] = 0;
        }
  }
  return 0;
  
}

int imprime_tela(int t[10][20]){
    int cont0;
    int cont1;
    for(cont0 = 0; cont0 < 10; cont0++)
  {
        for(cont1 = 0; cont1 < 20; cont1++){
            printf("%d", t[cont0][cont1]);
        }
        printf("\n");
  }
  return 0;
  
}

int mover(int pos[2], int t[10][20]){
  t[pos[0]][pos[1]] = 0;
  pos[0]++;
  t[pos[0]][pos[1]] = 1;

  return pos[0];
  
}

int main ( void ) {
  int cont;
  int tela[10][20];
  int pos[2];

  posx[0] = 20;  // Define a posicao x1 do bloco
  posx[1] = 60; // Define a posicao x2 do bloco

  posy[0] = 20;  // Define a posicao y1 do bloco
  posy[1] = 60; // Define a posicao y2 do bloco

  preenche_zero(tela);
  tela[0][10] = 1;

    int colunas, linhas, tColunas, tLinhas;

    // Desenha o quadrado na tela
    for(cont = 0; cont < 10; cont++)
    {
      video_open();

      video_clear();

      video_box(posx[0], posx[1], posy[0], posy[1], video_WHITE);

      video_show();

      sleep(1);

      video_close();

      // Move o quadrado para baixo
      posx[0] = posx[0] + 10;
      posx[1] = posx[1] + 10;
      posy[0] = posy[0] + 10;
      posy[1] = posy[1] + 10;
    }

  /*for(cont = 0; cont < 10; cont++)
    {
    system("clear");
    imprime_tela(tela);
    pos[0] = mover(pos, tela);
    sleep(1);
    }
  */
return 0;
}
