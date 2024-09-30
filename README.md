# 🎮 Problema 1 Sistemas Digitais - Tetris

Com o objetivo de gerar o entendimento da arquitetura e funcionamento do kit de desenvolvimento DE1-SoC, além de conhecimentos de interação hardware-software através da linguagem C, foi desenvolvido um jogo digital semelhante ao Tetris. As funções principais do jogo são: movimento, que é calculado através dos valores obtidos pelo uso do acelerômetro; controle de execução - pausar, continuar e reiniciar o jogo; e contagem de pontos, que são calculados quando o jogador completa uma linha de blocos.

##### DEMO da aplicação:
https://github.com/user-attachments/assets/42a0d176-4db6-48d7-817b-f2e1ef705115

## Como executar

O programa é compatível com linux, sendo desenvolvido para funcionar em uma máquina com processador ARM, mais especificamente numa placa DE1-SoC. Os arquivos do código, escrito em C estão disponíveis no diretório da aplicação. Sendo eles:

- game.c
###### (Arquivo principal onde se encontra a maior parte do código do jogo.)

- map.c
###### (Arquivo onde ficam as funções de mapeamento de memória e uso do acelerômetro.)

- address_map_arm.h
###### (Arquivo header com os endereços dos registradores usados.)

Para executar o programa, utilize o arquivo makefile também disponível; Em um diretório com os arquivos citados anteriormente, execute os seguintes comandos no terminal linux:

- make all
  
###### (Cria o executável.)

- sudo ./game

###### (Executa o jogo. Vale lembrar que o sufixo "sudo" executa o programa em "root" do Linux, e portanto seu uso faz-se desnecessario se o sistema no qual o programa é executado já está permitindo acesso aos recursos privilegiados necessários; Ademais, por ser um recurso do Linux, outros sistemas operacionais que porventura permitam a compilação do programa podem não reconhecer tal comando.)

## Lógica do jogo

Para criar a tela do jogo, foi feito o uso de uma matriz de inteiros (tipo int) 10x24 onde os elementos representam as células do jogo. Para gerar as peças utilizadas são geradas matrizes de inteiros (tipo int) 4x4. Nessas matrizes o número 0 representa os espaços vazios e os demais números são referentes ao índice da cor dos blocos. As matrizes são unidas, por meio do preenchimento de uma segunda matriz 10x24, imediatamente antes da exibição da tela.

A movimentação da peça atual - isto é, a atualização de suas posições x e y - é feita em duas ocasiões distintas: A primeira, que pode acontecer em qualquer ciclo de execução do programa, acontece caso exista inclinação suficiente do acelerômetro para tal, bem como haja passado tempo suficiente desde o último movimento (tal intervalo é determinado pelo módulo da própria inclinação, com inclinações mais significantes resultando em intervalos menores), e resulta em movimento lateral; A segunda, que deve sempre acontecer a cada 50 ciclos de execução do programa, resulta no movimento vertical da peça atual (para baixo). Todos os movimentos só podem ocorrer caso não exista obstrução e tão somente se o movimento não resulte na saída da peça da área de jogo.

A seguir, em se tratando do movimento vertical, sua impossibilidade resulta na colocação dos blocos da peça na matriz "estática" do jogo. Ademais, quando isto ocorre, avalia-se a posição y final da peça que acabou de ser colocada: Caso dentro da área permitida (aquela delimitada pela área abaixo da linha horizontal de cor branca), o jogo continua por meio do "sorteio" de um formato e cor para uma nova peça; Caso fora desta área, o jogo é marcado como "finalizado".

```c
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
```
###### Trecho do código contido no arquivo "game.c", referente à lógica de detecção de colisão vertical e continuidade do jogo.

O controle do fluxo de jogo é feito por meio da combinação dos resultados da leitura de certos dispositivos de entrada da placa DE1-SoC (chaves SW0 e SW1) e do próprio código do programa. Em execução, o jogo pode realizar ações de movimento e atualização da tela, como dito anteriormente; Em pausa e quando finalizada a sessão de jogo, movimentos e atualizações de tela não podem ocorrer, mas o usuário pode reiniciar o jogo inteiro em ambas as ocasiões e retomar a sessão atual apenas em caso de pausa.

![diagrama_sd](https://github.com/user-attachments/assets/0a81c3e7-06b9-47bc-b8e5-eb3080df686d)
###### Diagrama completo da lógica do jogo tal como implementada no arquivo "game.c"

## Uso do acelerômetro

De modo a compreender o funcionamento básico de algumas bibliotecas usualmente empregadas pelo kit de desenvolvimento DE1-SoC (e seus equivalentes em modelos de produção), foi requisitado que a comunicação com o acelerômetro (modelo ADXL345) embutido na placa deve ser estabelecida sem o uso de bibliotecas para acelerômetros já disponíveis. Para tal, emprega-se o uso do mapeamento de memória e leitura/escrita dos registros assim indexados.

A comunicação com o ADXL345 começa com a abertura do espaço `/dev/mem`, que permite acessar a memória física do sistema. Isso é crucial, pois o ADXL345 é acessado por meio do barramento I2C, que requer acesso direto aos registradores de controle. Após abrir o dispositivo, mapea-se a região correspondente ao I2C, associando os registradores necessários ao espaço de memória do programa. Esse mapeamento nos permite ler e escrever diretamente nos registradores do I2C, facilitando a configuração e a comunicação com o acelerômetro.

```c
void* map_physical(int fd, unsigned int base, unsigned int span) {
    void *virtual_base;
    virtual_base = mmap(NULL, span, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, base);
    if (virtual_base == MAP_FAILED) {
        perror("ERROR: mmap() failed");
        close(fd);
        return (NULL);
    }
    return virtual_base;
}
```
###### Trecho de código contido no arquivo "map.c", referente ao mapeamento de endereços de memória física para endereços virtuais cedidos ao programa.

Uma vez mapeados os registradores, inicializa-se o barramento I2C. Nesta etapa, configura-se o I2C para operar como mestre e definimos o ADXL345 como o escravo. Isso envolve a definição de parâmetros como a frequência de operação e os períodos de temporização, garantindo que a comunicação seja realizada de forma eficiente. Os registradores do I2C são utilizados para enviar comandos e configurar o acelerômetro, preparando-o para a operação.

```c
void I2C0_init(){
    //Para qualquer transmissão no I2C0
   *I2C0_enable = 2;
   printf("Desligando I2C0..\n");
   while(*I2C0_enable_sts == 1){}

   //Seta o I2C como mestre e o ADXL345 como escravo
   *I2C0_con = 0x65;
   *I2C0_tar = 0x53;

   //Seta o periodo
   *I2C0_fs_hcnt = 60 + 30;  // 0.6us + 0.3us
   *I2C0_fs_lcnt = 130 + 30; // 1.3us + 0.3us

   //Liga o controlador
   *I2C0_enable = 1;
   printf("Ligando I2C0..\n");
   while(*I2C0_enable_sts == 2){}
}
```
###### Trecho de código contido no arquivo "map.c", referente ao estabelecimento da comunicação do controlador I2C com o acelerômetro ADXL345

Com a configuração do I2C em funcionamento, desenvolve-se funções específicas para leitura e escrita nos registradores do ADXL345. Essas funções abstraem os detalhes da comunicação I2C, permitindo uma interação mais fácil com o acelerômetro. Por exemplo, implementa-se funções para ler os dados de aceleração dos eixos X, Y e Z, além de escrever valores de configuração nos registradores do acelerômetro.

O próximo passo é a inicialização do ADXL345. Durante esta fase, condigura-se o dispositivo para operar na faixa de ±16g e em resolução total. Também é definido a taxa de amostragem para 250 Hz, garantindo que o acelerômetro forneça dados em tempo real com a precisão necessária para nossas aplicações. Essa configuração é fundamental para obter leituras precisas e confiáveis.

Após a inicialização, realiza-se a calibração do acelerômetro. Este processo envolve coletar amostras dos dados de aceleração enquanto o dispositivo está em repouso e calcular offsets para os eixos. Esses offsets são então escritos de volta nos registradores do ADXL345, garantindo que as medições sejam ajustadas corretamente e representem a aceleração real.

Finalmente, implementa-se uma thread dedicada à leitura dos eixos do acelerômetro. Essa thread opera continuamente, lendo os valores de aceleração e armazenando-os em variáveis globais. Essa abordagem permite que o sistema processe os dados em tempo real, possibilitando a realização de ações ou análises baseadas nas leituras do acelerômetro.

<!--### Conclusão

Nesse projeto é possível não somente demonstrar a comunicação eficaz com o ADXL345, mas também oferece uma visão prática sobre como trabalhar com dispositivos I2C e mapeamento de memória em sistemas embarcados.
-->
