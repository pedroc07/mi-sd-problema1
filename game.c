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

  pos[0] = 0;  // Define a posicao 0 do bloco
  pos[1] = 10; // Define a posicao 1 do bloco

  preenche_zero(tela);
  tela[0][10] = 1;

  /*for(cont = 0; cont < 10; cont++)
    {
    system("clear");
    imprime_tela(tela);
    pos[0] = mover(pos, tela);
    sleep(1);
    }
  */
  video_box (int /*x1*/, int /*y1*/, int /*x2*/, int /*y2*/, short /*color*/);  printf("Colunas:%d\nLinhas:%d", cols, rows);
return 0;
}
