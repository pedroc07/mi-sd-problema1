# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>

# include <intelfpgaup/video.h>


//Funcao que preenche com 0 todas as celulas de uma matriz 10x24
int preenche_zero_10_x_24(int (*tela)[10][24]) {
  int cont0;
  int cont1;
  
  for(cont0 = 0; cont0 < 10; cont0++) {
    
    for(cont1 = 0; cont1 < 24; cont1++) {
      (*tela)[cont0][cont1] = 0;
    }
  }

  return 0;
}

//Funcao que preenche com 0 todas as celulas de uma matriz 4x4
int preenche_zero_4_x_4(int (*tela)[4][4]) {
    int cont0;
    int cont1;

  for(cont0 = 0; cont0 < 4; cont0++) {
    
    for(cont1 = 0; cont1 < 4; cont1++){
      (*tela)[cont0][cont1] = 0;
    }
  }

  return 0;
}


//Funcao que une (modifica matriz tela) uma matriz com posicao absoluta de tamanho 10x24 (estatico) com uma matriz com posicao relativa de tamanho 4x4 (peca em relacao a posx e posy)
int une_matriz(int (*tela)[10][24], int estatico[10][24], int peca[4][4], int posx, int posy) {
  int cont0;
  int cont1;

  for(cont0 = 0; cont0 < 10; cont0++) {
    
    for(cont1 = 0; cont1 < 24; cont1++){
      (*tela)[cont0][cont1] = estatico[cont0][cont1];
      
      if (((cont0 - posx) >= 0) && ((cont1 - posy) >= 0) && ((cont0 - posx) < 4) && ((cont1 - posy) < 4) && peca[(cont0 - posx)][(cont1 - posy)] != 0) {
        (*tela)[cont0][cont1] = peca[(cont0 - posx)][(cont1 - posy)];
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
    }
  }

  video_show();
  video_close();
  
  return 0;
}

//Funcao que desenha uma matriz 10x24
//Versao de teste (print)
/*int desenha_matriz(int t[10][24]){
  int cont0;
  int cont1;

  printf("\n\n");

  for(cont1 = 0; cont1 < 24; cont1++) {
    printf("\n");

    for(cont0 = 0; cont0 < 10; cont0++){
      
      if(t[cont0][cont1] == 1) {
        printf("\033[1;31m");
      }
      else if(t[cont0][cont1] == 2) {
        printf("\033[0;31m");
      }
      else if(t[cont0][cont1] == 3) {
        printf("\033[0;35m");
      }
      else if(t[cont0][cont1] == 4) {
        printf("\033[1;33m");
      }
      else if(t[cont0][cont1] == 5) {
        printf("\033[1;32m");
      }
      else if(t[cont0][cont1] == 6) {
        printf("\033[1;36m");
      }
      else if(t[cont0][cont1] == 7) {
        printf("\033[1;34m");
      }
      else if(t[cont0][cont1] == 8) {
        printf("\033[1;35m");
      }
      else if(t[cont0][cont1] == 9) {
        printf("\033[1;37m");
      }
      
      if (t[cont0][cont1] == 0) {
        printf("- ");
      }
      else {
        printf("# ");
      }
      
      printf("\033[0m");
    }
  }

  printf("\n\n");
  
  return 0;
}*/


//Funcao que verifica a possibilidade de mover uma pecao de posicao
int mover(int estatico[10][24], int peca[4][4], int *posx, int *posy, int dx, int dy) {
  int cont0;
  int cont1;

  int result = 0;

  for(cont0 = 0; cont0 < 4; cont0++) {
    
    for(cont1 = 0; cont1 < 4; cont1++) {

      //Condicional para verificar se o bloco atual da peca, caso preenchido, "sai" do limite da tela apos o deslocamento
      //Se passar, significa que o movimento e impossivel
      if ((peca[cont0][cont1] != 0) && (((cont0 + (*posx) + dx) < 0) || ((cont1 + (*posy) + dy) < 0) || ((cont0 + (*posx) + dx) > 9) || ((cont1 + (*posy) + dy) > 23))) {
        result = 1;
      }
      //Condicional para verificar se o bloco atual da peca, caso preenchido, sobreporia os blocos ja estaticos apos o deslocamento
      //Se passar, significa que o movimento e impossivel
      else if ((peca[cont0][cont1] != 0) && (estatico[(cont0 + (*posx) + dx)][(cont1 + (*posy) + dy)] != 0)) {
        result = 1;
      }
    }
  }

  //Se nao houve obstrucao, ocorre o movimento (atualiza a posicao em relacao ao deslocamento requerido)
  if(result == 0) {
    *posx = (*posx + dx);
    *posy = (*posy + dy);
  }

  //Retorna se a operacao foi bem-sucedida (0) ou nao (1)
  return result;
}


//Funcao que detecta uma linha preenchida totalmente e apaga o conteudo
int implodir(int (*estatico)[10][24]) {
  int cont0;
  int cont1;

  //Percorre linha por linha, de cima a baixo
  for(cont1 = 0; cont1 < 24; cont1++) {
    int result = 0;
    int line = (23-cont1);

    //E coluna por coluna, da esquerda para a direita
    for(cont0 = 0; cont0 < 10; cont0++) {
      
      //Caso seja encontrado um espaco vazio na linha, sabemos que nao pode ser eliminada
      if((*estatico)[cont0][line] == 0) {
        result = 1;
      }
    }

    //Se nao existiram espacos vazios
    if(result == 0){
      
      //A linha sera eliminada
      for(cont0 = 0; cont0 < 10; cont0++) {
        (*estatico)[cont0][line] = 0;
      }

      return line;
    }
  }

  return (-1);
}

//Funcao que move para baixo as pecas acima da linha eliminada
int cascada(int (*estatico)[10][24], int inicio) {
  int cont0;
  int cont1;

  for(cont1 = (inicio - 1); cont1 >= 0; cont1--) {
    
    for(cont0 = 0; cont0 < 10; cont0++) {
      (*estatico)[cont0][(cont1 + 1)] = (*estatico)[cont0][cont1];
    }
  }

  return 0;
}


//Funcao que preenche os espacos da peca desejada
int gerar_peca(int (*peca)[4][4], int forma, int cor) {
  preenche_zero_4_x_4(peca);

  if(forma == 0) {
    (*peca)[0][0] = cor;
    (*peca)[0][1] = cor;
    (*peca)[0][2] = cor;
    (*peca)[1][0] = cor;
  }
  else if(forma == 1) {
    (*peca)[0][0] = cor;
    (*peca)[1][1] = cor;
    (*peca)[1][2] = cor;
    (*peca)[1][0] = cor;
  }
  else if(forma == 2) {
    (*peca)[0][0] = cor;
    (*peca)[0][1] = cor;
    (*peca)[0][2] = cor;
    (*peca)[0][3] = cor;
  }
  else if(forma == 3) {
    (*peca)[0][0] = cor;
    (*peca)[1][0] = cor;
    (*peca)[2][0] = cor;
    (*peca)[3][0] = cor;
  }
  else if(forma == 4) {
    (*peca)[0][1] = cor;
    (*peca)[1][1] = cor;
    (*peca)[2][1] = cor;
    (*peca)[1][0] = cor;
  }
  else if(forma == 5) {
    (*peca)[0][0] = cor;
    (*peca)[1][0] = cor;
    (*peca)[2][0] = cor;
    (*peca)[1][1] = cor;
  }
 
  return 0;
}


//Funcao que detecta o movimento
//Versao de teste (pre-programada)
int detectar_comando(int contador_loop) {
  int direcao = 0;
  
  if(contador_loop == 10) {
    direcao = 1;
  }
  else if(contador_loop == 30) {
    direcao = 1;
  }
  else if(contador_loop == 45) {
    direcao = 1;
  }
  else if(contador_loop == 205) {
    direcao = -1;
  }
  else if(contador_loop == 211) {
    direcao = -1;
  }
  else if(contador_loop == 214) {
    direcao = -1;
  }
  else if(contador_loop == 215) {
    direcao = -1;
  }

  return direcao;
}


int main ( void ) {
  
  //Matriz de exibicao, objetos estaticos e peca em movimento, respectivamente
  int tela[10][24];
  int estatico[10][24];
  int peca[4][4];

  //Inicia com 0 os espacos de jogo e da peca
  preenche_zero_10_x_24(&estatico);
  preenche_zero_4_x_4(&peca);

  estatico[0][23] = 3;
  estatico[1][23] = 7;
  estatico[2][23] = 5;
  estatico[3][23] = 1;
  estatico[4][23] = 2;
  estatico[8][23] = 4;
  estatico[9][23] = 6;

  //Posicao inicial da peca
  int posx = 4;
  int posy = 0;

  //Obtem o tempo em microsegundos e em segundos, para uso na seed do RNG do formato da peca e da cor
  struct timeval tempo;
  gettimeofday(&tempo, NULL);
  int tempo_preciso = tempo.tv_usec;
  int tempo_simples = tempo.tv_sec;
  
  //Gera um indice do formato da peca aleatorio
  srand (tempo_preciso);
  int rShape = (rand() % 6);
  
  //Gera um indice de cor aleatorio entre 1 e 9
  srand(tempo_simples);
  int rColor = ((rand() % 9) + 1);

  //"Cria" uma peca com as caracteristicas desejadas
  gerar_peca(&peca, rShape, rColor);

  //Display inicial da tela
  une_matriz(&tela, estatico, peca, posx, posy);
  desenha_matriz(tela);

  //Estrutura do intervalo de tempo para o sleep da aplicacao (periodo de 10,000,000 nanossegundos ou 10 milissegundo)
  struct timespec intervalo;
  intervalo.tv_sec = 0;
  intervalo.tv_nsec = 10000000;

  //Quantidade de ciclos entre cada vez que o comando de movimento pode ser recebido
  int espera_maxima = 10;

  //Contador de ciclos para o "cooldown" da acao de mover
  int espera_comando = 10;
  
  int cont;
  //Loop da sessao de jogo
  for(cont = 1; cont < 4801; cont++) {
    //Sleep de acordo com o clock da aplicacao
    nanosleep(&intervalo, NULL);

    //Acoes executadas a cada ciclo do clock
    if((cont % 1) == 0) {
      
      //Se ja passou o intervalo necessario para a acao de movimento, ve se esta pedindo isso
      if(espera_comando == espera_maxima) {
        int direcao_movimento = detectar_comando(cont);

        if(direcao_movimento != 0) {
          espera_comando = 1;
          mover(estatico, peca, &posx, &posy, direcao_movimento, 0);

          //Desenha os novos elementos na tela
          une_matriz(&tela, estatico, peca, posx, posy);
          desenha_matriz(tela);
        }
      }
      //Caso contrario, aumenta o contador do "cooldown"
      else {
        espera_comando = (espera_comando + 1);
      }
    }
    
    //Acoes executadas a cada 50 ciclos do clock
    if ((cont % 50) == 0) {
      
      //Move a peca um espaco para baixo e verifica se houve obstrucao ao executar acao de mover
      int resultado_mover = mover(estatico, peca, &posx, &posy, 0, 1);
      
      //Se houve obstrucao, significa que a peca sera colocada e acontecera uma verificacao para "implodir" linhas
      //Tambem reseta a peca atual
      if(resultado_mover == 1) {
        //Colocacao da peca (une a matriz dos objetos com a matriz da peca na propria matriz dos objetos)
        une_matriz(&estatico, estatico, peca, posx, posy);
        
        //Tenta eliminar linhas e guarda o resultado
        int linha_eliminada = implodir(&estatico);

        //Caso elimine linha, continua tentando ate nao mais eliminar
        while (linha_eliminada != (-1)) {
          cascada(&estatico, linha_eliminada);
          linha_eliminada = implodir(&estatico);
        }

        //"Reset" da peca
        preenche_zero_4_x_4(&peca);

        posx = 4;
        posy = 0;

        gettimeofday(&tempo, NULL);
        tempo_preciso = tempo.tv_usec;
        tempo_simples = tempo.tv_sec;
        
        srand (tempo_preciso);
        rShape = (rand() % 6);
        
        srand(tempo_simples);
        rColor = ((rand() % 9) + 1);

        gerar_peca(&peca, rShape, rColor);
      }

      //Desenha os novos elementos na tela
      une_matriz(&tela, estatico, peca, posx, posy);
      desenha_matriz(tela);
    }
  }
  
  return 0;

  /*int cols;
  int rows;
  int tcols;
  int trows;

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
  printf("Colunas: %d\nLinhas: %d", * cols, * rows);*/
}