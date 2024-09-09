# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <intelfpgaup/video.h>


//Funcao que preenche com 0 todas as celulas de uma matriz 10x24
int preenche_zero_10_x_24(int tela[10][24]) {
  int cont0;
  int cont1;
  
  for(cont0 = 0; cont0 < 10; cont0++) {
    
    for(cont1 = 0; cont1 < 24; cont1++) {
      tela[cont0][cont1] = 0;
    }
  }

  return 0;
}

//Funcao que preenche com 0 todas as celulas de uma matriz 4x4
int preenche_zero_4_x_4(int tela[4][4]) {
    int cont0;
    int cont1;
  
  for(cont0 = 0; cont0 < 4; cont0++) {
    
    for(cont1 = 0; cont1 < 4; cont1++){
      tela[cont0][cont1] = 0;
    }
  }

  return 0;
}


//Funcao que une (modifica matriz tela) uma matriz com posicao absoluta de tamanho 10x24 (estatico) com uma matriz com posicao relativa de tamanho 4x4 (peca em relacao a posx e posy)
int une_matriz(int tela[10][24], int estatico[10][24], int peca[4][4], int posx, int posy) {
  int cont0;
  int cont1;

  for(cont0 = 0; cont0 < 10; cont0++) {
    
    for(cont1 = 0; cont1 < 24; cont1++){
      tela[cont0][cont1] = estatico[cont0][cont1];
      
      if (((cont0 - posx) >= 0) && ((cont1 - posy) >= 0) && ((cont0 - posy) < 4) && ((cont1- posy) < 4) && peca[(cont0 - posx)][(cont1 - posy)] != 0) {
        tela[cont0][cont1] = peca[(cont0 - posx)][(cont1 - posy)];
      }
    }
  }

  return 0;
}

//Funcao que desenha uma matriz 10x24 em uma tela 320x240, preenchendo a altura da tela e centralizada na largura da mesma
int desenha_matriz(int t[10][24]){
  int cont0;
  int cont1;
  int posx1, posx2;
  int posy1, posy2;

  video_open();
  video_clear();

  for(cont0 = 0; cont0 < 10; cont0++) {
    
    for(cont1 = 0; cont1 < 24; cont1++){
      posx1 = (cont0 * 10) + 110;
      posy1 = (cont1 * 10);
      posx2 = ((cont0 + 1) * 10 ) + 109;
      posy2 = ((cont1 + 1) * 10) - 1;
      
      if (t[cont0][cont1] == 0) {
        video_box(posx1, posy1, posx2, posy2, video_WHITE);
      }
      else if(t[cont0][cont1] == 1) {
        video_box(posx1, posy1, posx2, posy2, video_RED);
      }
      else if(t[cont0][cont1] == 2) {
        video_box(posx1, posy1, posx2, posy2, video_ORANGE);
      }
      else if(t[cont0][cont1] == 3) {
        video_box(posx1, posy1, posx2, posy2, video_PINK);
      }
      else if(t[cont0][cont1] == 4) {
        video_box(posx1, posy1, posx2, posy2, video_YELLOW);
      }
      else if(t[cont0][cont1] == 5) {
        video_box(posx1, posy1, posx2, posy2, video_GREEN);
      }
      else if(t[cont0][cont1] == 6) {
        video_box(posx1, posy1, posx2, posy2, video_CYAN);
      }
      else if(t[cont0][cont1] == 7) {
        video_box(posx1, posy1, posx2, posy2, video_BLUE);
      }
      else if(t[cont0][cont1] == 8) {
        video_box(posx1, posy1, posx2, posy2, video_MAGENTA);
      }
      else if(t[cont0][cont1] == 9) {
        video_box(posx1, posy1, posx2, posy2, video_GREY);
      }
      else if(t[cont0][cont1] == 10) {
        video_box(posx1, posy1, posx2, posy2, video_BLACK);
      }
    }
  }

  video_show();
  video_close();
  
  return 0;
}


//Funcao que verifica a possibilidade de mover uma pecao de posicao
int mover(int estatico[10][24], int peca[4][4], int posx, int posy, int dx, int dy) {
  int cont0;
  int cont1;

  int result = 0;

  for(cont0 = 0; cont0 < 4; cont0++) {
    
    for(cont1 = 0; cont1 < 4; cont1++) {

      //Condicional para verificar se o bloco atual da peca, caso preenchido, "sai" do limite da tela apos o deslocamento
      //Se passar, significa que o movimento e impossivel
      if ((peca[cont0][cont1] != 0) && (((cont0 + posx + dx) < 0) || ((cont1 + posy + dy) < 0) || ((cont0 + posx + dx) > 9) || ((cont1 + posy + dy) > 23))) {
        result = 1;
      }
      //Condicional para verificar se o bloco atual da peca, caso preenchido, sobreporia os blocos ja estaticos apos o deslocamento
      //Se passar, significa que o movimento e impossivel
      else if ((peca[cont0][cont1] != 0) && (estatico[(cont0 + posx + dx)][(cont1 + posy + dy)] != 0)) {
        result = 1;
      }
    }
  }

  //Se nao houve obstrucao, ocorre o movimento (atualiza a posicao em relacao ao deslocamento requerido)
  if(result == 0) {
    posx = (posx + dx);
    posy = (posy + dy);
  }

  //Retorna se a operacao foi bem-sucedida (0) ou nao (1)
  return result;
}


//Funcao que detecta uma linha preenchida totalmente e apaga o conteudo
int implodir(int estatico[10][24]) {
  int cont0;
  int cont1;
  
  int result0 = 1;
  int result1;

  //Percorre linha por linha, de cima a baixo
  for(cont1 = 23; cont0 >= 0; cont1--) {
    result1 = 0;

    //E coluna por coluna, da esquerda para a direita
    for(cont0 = 0; cont0 < 10; cont1++) {
      
      //Caso seja encontrado um espaco vazio na linha, sabemos que nao pode ser eliminada
      if(estatico[cont0][cont1] == 0) {
        result1 = 1;
      }
    }

    //Se nao existiram espacos vazios
    if(result1 == 0){
      result0 = 0;

      //A linha sera eliminada
      for(cont0 = 0; cont0 < 10; cont1++) {
        estatico[cont0][cont1] = 0;
      }
    }
  }

  return result0;
}

//Funcao que move para baixo as pecas acima da linha eliminada
int cascada(int estatico[10][24], int inicio) {
  int cont0;
  int cont1;

  for(cont1 = inicio; cont1 >= 0; cont1--) {
    
    for(cont0 = 0; cont0 < 10; cont1++) {
      estatico[cont0][cont1+1] = estatico[cont0][cont1];
      estatico[cont0][cont1] = 0;
    }
  }

  return 0;
}


int main ( void ) {
  int cont;

  int tela[10][24];
  int estatico[10][24];
  int peca[4][4];

  int posx = 4;
  int posy = 0;
  
  /*int cols;
  int rows;
  int tcols;
  int trows;*/

  //Inicia com 0 os espacos de jogo e da peca
  preenche_zero_10_x_24(estatico);
  preenche_zero_4_x_4(peca);

  //Gera um indice de cor aleatorio entre 1 e 12
  int rColor = ((rand() % 12) + 1);

  //Preenche os espacos da matriz da peca com o indice da cor
  peca[0][0] = rColor;
  peca[0][1] = rColor;
  peca[0][2] = rColor;
  peca[1][0] = rColor;
  
  preenche_zero_10_x_24(tela);
  une_matriz(tela, estatico, peca, posx, posy);
  desenha_matriz(tela);

  //Movimenta a peça
  for(cont = 0; cont < 30; cont++){
    mover(estatico, peca, posx, posy, 0, 1);
    
    preenche_zero_10_x_24(tela);
    une_matriz(tela, estatico, peca, posx, posy);
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

/*int imprime_tela(int t[10][20]){
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
*/