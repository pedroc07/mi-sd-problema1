# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>

# include <intelfpgaup/video.h>
#include <intelfpgaup/SW.h>
#include <intelfpgaup/KEY.h>

//Funcao que preenche com 0 todas as celulas de uma matriz 10x24
void preenche_zero_10_x_24(int (*tela)[10][24]) {
  int cont0;
  int cont1;
  
  for(cont0 = 0; cont0 < 10; cont0++) {
    
    for(cont1 = 0; cont1 < 24; cont1++) {
      (*tela)[cont0][cont1] = 0;
    }
  }
}

//Funcao que preenche com 0 todas as celulas de uma matriz 4x4
void preenche_zero_4_x_4(int (*tela)[4][4]) {
    int cont0;
    int cont1;

  for(cont0 = 0; cont0 < 4; cont0++) {
    
    for(cont1 = 0; cont1 < 4; cont1++){
      (*tela)[cont0][cont1] = 0;
    }
  }
}


//Funcao que une (modifica matriz tela) uma matriz com posicao absoluta de tamanho 10x24 (estatico) com uma matriz com posicao relativa de tamanho 4x4 (peca em relacao a posx e posy)
void une_matriz(int (*tela)[10][24], int estatico[10][24], int peca[4][4], int posx, int posy) {
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
}


//Funcao que desenha uma matriz 10x24 em uma tela 320x240, preenchendo a altura da tela e centralizada na largura da mesma
void desenha_matriz(int t[10][24]){
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
    }
  }
}


//Funcao que exibe a pontuacao do jogador em uma tela 320x240, ao lado da matriz do jogo exibida na funcao anterior
void desenha_pontos(int pontos){
  
  //Converte int em array de caracteres de ate 32 caracteres (o que cabe na tela apartir da posicao inicial)
  char int_array[32];
  sprintf(int_array, "%d", pontos);

  char mensagem_pontos[32] = "PONTOS:";

  video_text(240, 200, mensagem_pontos);
  video_text(240, 215, int_array);
}

//Funcao que exibe a linha limite da colocacao das pecas e diz o estado do jogo caso esteja pausado ou seja "fim de jogo" em tela 320x240
void desenha_estado(int estado_jogo, int linha_limite) {

  //Desenha a linha limite da area de jogo
  video_box((110), (linha_limite * 10), (209), (((linha_limite + 1) * 10) - 1), video_GREY);

  //Exibe as mensagens de estado de jogo para "pausa" e "fim de jogo"
  if(estado_jogo == 1) {

    char mensagem_estado[12] = "JOGO PAUSADO";
    video_text(240, 200, mensagem_estado);
  }
  else if(estado_jogo == 3) {
    
    char mensagem_estado[11] = "FIM DE JOGO";
    video_text(240, 100, mensagem_estado);
  }

  video_show();
  video_clear();
}

//Funcao que desenha uma matriz 10x24
//Versao de teste (print)
/*void desenha_matriz(int t[10][24]){
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
}*/

//Funcao que exibe a pontuacao do jogador na tela
//Versao de teste (print)
/*void desenha_pontos(int pontos){
  int cont0;
  int cont1;

  printf("\n");
  printf("PONTUACAO: %d", pontos);
}*/

//Funcao que exibe a linha limite da colocacao das pecas e diz o estado do jogo caso esteja pausado ou seja "fim de jogo"
//Versao de teste (print)
/*void desenha_estado(int estado_jogo, int linha_limite) {

  if(estado_jogo == 0) {
    //printf("\n");
    //printf("%d", linha_limite);
  }
  else if(estado_jogo == 1) {
    printf("\n");
    printf("JOGO PAUSADO");
  }
  else if(estado_jogo == 3) {
    printf("\n");
    printf("FIM DA PARTIDA. INICIE UMA NOVA PARTIDA PARA CONTINUAR JOGANDO.");
  }
}*/

//Funcao que consolida as funcoes de atualizacao da tela
void atualiza_tela(int estatico[10][24], int peca[4][4], int posx, int posy, int pontos, int estado_jogo, int linha_limite) {
  
  int tela[10][24];

  une_matriz(&tela, estatico, peca, posx, posy);

  desenha_matriz(tela);
  desenha_pontos(pontos);
  desenha_estado(estado_jogo, linha_limite);
}


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


//Funcao que interpreta o movimento
//A direcao na verdade e a quantidade de ciclos necessarias desde a ultima movimentacao lateral com sinal indicando a real direcao do movimento
//Versao de teste (pre-programada)
int ler_movimento(int contador_loop) {
  int direcao = 0;
  
  if(contador_loop == 10) {
    direcao = 10;
  }
  else if(contador_loop == 30) {
    direcao = 10;
  }
  else if(contador_loop == 45) {
    direcao = 10;
  }
  else if(contador_loop == 705) {
    direcao = -10;
  }
  else if(contador_loop == 711) {
    direcao = -10;
  }
  else if(contador_loop == 714) {
    direcao = -10;
  }
  else if(contador_loop == 715) {
    direcao = -10;
  }

  return direcao;
}

//Funcao que le a entrada atual de chaves para controle do game
int ler_comando() {
  int estado;

  SW_open();
  SW_read(&estado);
  SW_close();

  return estado;
}

//Funcao que le a entrada atual de chaves para controle do game
int ler_reset() {
  int estado;

  KEY_open();
  KEY_read(&estado);
  KEY_close();

  return estado;
}


int main ( void ) {
  
  //Matriz de objetos estaticos e peca em movimento, respectivamente
  int estatico[10][24];
  int peca[4][4];
  int Rst;

  //Linha limite (minima de cima para baixo) para colocacao das pecas
  int linha_limite = 7;

  video_open();

  //Loop externo que serve para reiniciar o game caso o interno seja quebrado
  while(1 == 1) {
    
    //Inicia com 0 os espacos de jogo e da peca
    preenche_zero_10_x_24(&estatico);
    preenche_zero_4_x_4(&peca);

    //Preenche certos espacos da matriz estatica para fins de teste
    estatico[0][23] = 3;
    estatico[1][23] = 7;
    estatico[2][23] = 5;
    estatico[3][23] = 1;
    estatico[4][23] = 2;
    estatico[8][23] = 4;
    estatico[9][23] = 6;

    //Contador de ciclos do game, usado para testes
    int cont = 0;

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
    int rColor = ((rand() % 8) + 1);

    //"Cria" uma peca com as caracteristicas desejadas
    gerar_peca(&peca, rShape, rColor);

    //Contador de pontos
    int contador_pontos = 0;

    //Obtem o estado do jogo
    int estado_jogo = ler_comando();

    //Lê o botão de reset
    Rst = ler_reset();
    printf("Botao: %d", Rst);

    //Display inicial da tela
    atualiza_tela(estatico, peca, posx, posy, contador_pontos, estado_jogo, linha_limite);

    //Estrutura do intervalo de tempo para o sleep da aplicacao (periodo de 10,000,000 nanossegundos ou 10 milissegundos)
    struct timespec intervalo;
    intervalo.tv_sec = 0;
    intervalo.tv_nsec = 10000000;

    //Contador de ciclos para o "cooldown" da acao de mover
    int contador_movimento = 10;

    //Variavel para determinar se esta sendo pedida exibicao do estado
    int quer_exibir_estado = 0;
    
    //Loop interno da sessao de jogo
    while(estado_jogo != 2) {
      
      //Sleep de acordo com o clock da aplicacao
      nanosleep(&intervalo, NULL);

      //Atualiza o estado do jogo
      estado_jogo = ler_comando();
      printf("%d", estado_jogo);

      //Atualiza a tela caso o estado do jogo tenha mudado de rodando para pausa / game over
      if((quer_exibir_estado == 1) && (estado_jogo != 0)) {
        atualiza_tela(estatico, peca, posx, posy, contador_pontos, estado_jogo, linha_limite);
      }

      //Acoes executadas a cada ciclo do clock, caso o jogo esteja em andamento
      if(((cont % 1) == 0) && (estado_jogo == 0)) {

        quer_exibir_estado = 1;

        //Obtem o vetor movimento
        int valor_movimento = ler_movimento(cont);

        //Espera maxima e direcao do movimento
        int espera_maxima;
        int direcao_movimento;

        //Atualiza a espera maxima e o vetor unitario do movimento de acordo com o valor do movimento, caso a funcao de ler o movimento retorne valor diferente de 0
        if (valor_movimento != 0) {
          espera_maxima = (abs(valor_movimento));
          direcao_movimento = (valor_movimento/espera_maxima);
        }
        //Caso retorne zero, isso quer dizer que nao houve movimento algum
        else {
          espera_maxima = 10;
          direcao_movimento = 0;
        }
        
        //Se ja passou o intervalo necessario para a acao de movimento, ve se esta pedindo isso
        if(contador_movimento >= espera_maxima) {
          
          //Executa o movimento
          if(direcao_movimento != 0) {
            contador_movimento = 1;
            mover(estatico, peca, &posx, &posy, direcao_movimento, 0);

            //Desenha os novos elementos na tela
            atualiza_tela(estatico, peca, posx, posy, contador_pontos, estado_jogo, linha_limite);
          }
        }
        //Caso contrario, aumenta o contador do "cooldown"
        else {
          contador_movimento = (contador_movimento + 1);
        }
      }
      
      //Acoes executadas a cada 50 ciclos do clock, caso o jogo esteja em andamento
      if(((cont % 50) == 0) && (estado_jogo == 0)) {

        quer_exibir_estado = 1;
        
        //Move a peca um espaco para baixo e verifica se houve obstrucao ao executar acao de mover
        int resultado_mover = mover(estatico, peca, &posx, &posy, 0, 1);
        
        //Se houve obstrucao, significa que a peca sera colocada e acontecera uma verificacao para "implodir" linhas
        //Tambem reseta a peca atual
        //Por fim, verifica se a peca colocada esta dentro dos limites da area de jogo, para ver se configura "game over"
        if(resultado_mover == 1) {
          
          //Colocacao da peca (une a matriz dos objetos com a matriz da peca na propria matriz dos objetos)
          une_matriz(&estatico, estatico, peca, posx, posy);

          //A peca atual deixa de existir
          preenche_zero_4_x_4(&peca);
          
          //Tenta eliminar linhas e guarda o resultado
          int linha_eliminada = implodir(&estatico);

          //Caso elimine linha... 
          while (linha_eliminada != (-1)) {
            
            //Aumenta a contagem de pontos
            contador_pontos = (contador_pontos + 1);

            //...E continua tentando ate nao mais eliminar
            cascada(&estatico, linha_eliminada);
            linha_eliminada = implodir(&estatico);
          }

          //Verificacao do limite do jogo
          //Se estiver nos limites, o jogo continua
          if (posy > linha_limite) {

            //"Reset" da peca
            posx = 4;
            posy = 0;

            gettimeofday(&tempo, NULL);
            tempo_preciso = tempo.tv_usec;
            tempo_simples = tempo.tv_sec;
            
            srand (tempo_preciso);
            rShape = (rand() % 6);
            
            srand(tempo_simples);
            rColor = ((rand() % 8) + 1);

            gerar_peca(&peca, rShape, rColor);
          }
          //Se nao estiver, o jogo terminou
          else {
            estado_jogo = 3;
          }
        }

        //Desenha os novos elementos na tela
        atualiza_tela(estatico, peca, posx, posy, contador_pontos, estado_jogo, linha_limite);
      }

      //Artificio para "prender" a execucao do programa quando o estado acabar sendo 3 (so permite sair caso seja mudado para estado 2)
      //Estado 3 significa "fim de jogo", sendo por isso que so permite ser mudado para "restart"
      if (estado_jogo == 3) {
        /*while(Rst != 14){
            Rst = ler_reset();
          }
          estado_jogo = ler_comando();
        */
        while(estado_jogo != 2) {
          estado_jogo = ler_comando();
        }
      }

      //Sobe o contador de ciclos utilizado para testes
      cont = (cont + 1);
    }

    //Artificio para "prender" a execucao do programa ate que o input de restart seja "solto"
    while(estado_jogo == 2) {
      estado_jogo = ler_comando();
    }
  }
}