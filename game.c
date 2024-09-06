# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <intelfpgaup/video.h>

int preenche_zero(int t[10][24]){
    int cont0;
    int cont1;
    for(cont0 = 0; cont0 < 10; cont0++)
  {
        for(cont1 = 0; cont1 < 24; cont1++){
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

int desenha_matriz(int t[10][24]){
    int cont0;
    int cont1;

    int posx1, posx2, posy1, posy2;
    video_open();
    video_clear();
    for(cont0 = 0; cont0 < 10; cont0++)
  {
        for(cont1 = 0; cont1 < 24; cont1++){
          posx1 = (cont0*10) + 110;
          posy1 = (cont1*10) + 110;
          posx2 = ((cont0+1)*10) + 109;
          posy2 = ((cont1+1)*10) + 109;
          if (t[cont0][cont1] == 0){
            video_box(posx1, posy1, posx2, posy2, video_WHITE);
          }
          else if(t[cont0][cont1] == 1){
            video_box(posx1, posy1, posx2, posy2, video_RED);
          }
        }
  }
  video_show();
  video_close();
  return 0;
  
}

int mover(posy){
  posy++;

  return pos[0];
  
}

int somar_matriz(int tela[10[24], int matrixexibicao[10][24], int peca[3][3], int posx, int posy]){
  for(cont0 = 0; cont0 < 10; cont0++)
  {
        for(cont1 = 0; cont1 < 24; cont1++){

          if (tela[cont0][cont1] != 0){
            matrixexibicao[cont0][cont1] = tela[cont0][cont1];
          }
          else if(peca[cont0][cont1] != 0){
            matrixexibicao[cont0][cont1] = tela[cont0][cont1];
          }
        }
  }
}

int main ( void ) {
  int cont;
  int tela[10][24];
  int peca[3][3];
  int posx = 4;
  int posy = 0;
  int cols;
  int rows;
  int tcols;
  int trows;

  preenche_zero(tela);

  //Desenha a peça na tela
  peca[0][0] = 1;
  peca[0][1] = 1;
  peca[0][2] = 1;
  peca[1][0] = 1;
  peca[1][1] = 0;
  peca[1][2] = 0;
  peca[2][0] = 0;
  peca[2][1] = 0;
  peca[2][2] = 0;
  
  desenha_matriz(tela);

  //Movimenta a peça
  for(cont = 0; cont < 13; cont++){
    pos0[0] = mover(pos0, tela);
    pos1[1] = mover(pos1, tela);
    pos2[0]= mover(pos2, tela);
    pos3[0] = mover(pos3, tela);
    desenha_matriz(tela);
    sleep(1);
  }

  /*
    video_open();
    // Desenha o quadrado na tela
    for(cont = 0; cont < 10; cont++)
    {

      video_clear();

      video_box(posx[0], posy[0], posx[1], posy[1], video_WHITE);

      video_show();

      sleep(1);

      // Move o quadrado para baixo
      posy[0] = posy[0] + 10;
      posy[1] = posy[1] + 10;
    }
  video_read (&cols, &rows, &tcols, &trows);
  video_close();
  printf("Colunas: %d\nLinhas: %d", * cols, * rows);
  */
return 0;
}
