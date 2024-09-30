# 🎮 Problema 1 Sistemas Digitais - Tetris

Com o objetivo de gerar o entendimento da arquitetura e funcionamento do kit de desenvolvimento DE1-SoC, além de conhecimentos de interação hardware-software através da linguagem C, foi desenvolvido um jogo digital semelhante ao Tetris. As funções principais do jogo são: movimento, que é calculado através dos valores obtidos pelo uso do acelerômetro; controle de execução - pausar, continuar e reiniciar o jogo; e contagem de pontos, que são calculados quando o jogador completa uma linha de blocos.

## Como executar

Os arquivos do código, escrito em C estão disponíveis no diretório da aplicação. Sendo eles:

`game.c

Arquivo principal onde se encontra a maior parte do código do jogo.

`map.c

Arquivo onde é feito 

## Lógica do jogo

Para criar a tela do jogo, foi feito o uso de uma matriz de inteiros (tipo int) 10x24 onde os elementos representam as células do jogo. Para gerar as peças utilizadas são geradas matrizes de inteiros (tipo int) 4x4. Nessas matrizes o número 0 representa os espaços vazios e os demais números são referentes ao índice da cor dos blocos. As matrizes são unidas, por meio do preenchimento de uma segunda matriz 10x24, imediatamente antes da exibição da tela.

A movimentação da peça atual - isto é, a atualização de suas posições x e y - é feita em duas ocasiões distintas: A primeira, que pode acontecer em qualquer ciclo de execução do programa, acontece caso exista inclinação suficiente do acelerômetro para tal, bem como haja passado tempo suficiente desde o último movimento (tal intervalo é determinado pelo módulo da própria inclinação, com inclinações mais significantes resultando em intervalos menores), e resulta em movimento lateral; A segunda, que deve sempre acontecer a cada 50 ciclos de execução do programa, resulta no movimento vertical da peça atual (para baixo). Todos os movimentos só podem ocorrer caso não exista obstrução e tão somente se o movimento não resulte na saída da peça da área de jogo.

A seguir, em se tratando do movimento vertical, sua impossibilidade resulta na colocação dos blocos da peça na matriz "estática" do jogo. Ademais, quando isto ocorre, avalia-se a posição y final da peça que acabou de ser colocada: Caso dentro da área permitida (aquela delimitada pela área abaixo da linha horizontal de cor branca), o jogo continua por meio do "sorteio" de um formato e cor para uma nova peça; Caso fora desta área, o jogo é marcado como "finalizado".

O controle do fluxo de jogo é feito por meio da combinação dos resultados da leitura de certos dispositivos de entrada da placa DE1-SoC (chaves SW0 e SW1) e do próprio código do programa. Em execução, o jogo pode realizar ações de movimento e atualização da tela, como dito anteriormente; Em pausa e quando finalizada a sessão de jogo, movimentos e atualizações de tela não podem ocorrer, mas o usuário pode reiniciar o jogo inteiro em ambas as ocasiões e retomar a sessão atual apenas em caso de pausa.

## Uso do acelerômetro

De modo a compreender o funcionamento básico de algumas bibliotecas usualmente empregadas pelo kit de desenvolvimento DE1-SoC (e seus equivalentes em modelos de produção), foi requisitado que a comunicação com o acelerômetro (modelo ADXL345) embutido na placa deve ser estabelecida sem o uso de bibliotecas para acelerômetros já disponíveis. Para tal, emprega-se o uso do mapeamento de memória e leitura/escrita dos registros assim indexados.

O mapeamento de memória é feito por meio do uso de funções da biblioteca mmap (função mmap). A função mmap estabelece ligação entre endereços físicos da memória e endereços virtuais dentro do espaço de memória do programa. Isso é necessário pois o espaço de modificação permitido para o programa não está na memória física, e sim em sua memória virtual.

Em suma, segue-se os seguintes procedimentos abaixo para a operação do acelerômetro ADXL345.

### Mapeamento de Memória

A comunicação com o ADXL345 começa com a abertura do espaço `/dev/mem`, que permite acessar a memória física do sistema. Isso é crucial, pois o ADXL345 é acessado por meio do barramento I2C, que requer acesso direto aos registradores de controle. Após abrir o dispositivo, mapea-se a região correspondente ao I2C, associando os registradores necessários ao espaço de memória do programa. Esse mapeamento nos permite ler e escrever diretamente nos registradores do I2C, facilitando a configuração e a comunicação com o acelerômetro.

### Inicialização do I2C

Uma vez mapeados os registradores, inicializa-se o barramento I2C. Nesta etapa, configura-se o I2C para operar como mestre e definimos o ADXL345 como o escravo. Isso envolve a definição de parâmetros como a frequência de operação e os períodos de temporização, garantindo que a comunicação seja realizada de forma eficiente. Os registradores do I2C são utilizados para enviar comandos e configurar o acelerômetro, preparando-o para a operação.

### Funções de Leitura e Escrita

Com a configuração do I2C em funcionamento, desenvolve-se funções específicas para leitura e escrita nos registradores do ADXL345. Essas funções abstraem os detalhes da comunicação I2C, permitindo uma interação mais fácil com o acelerômetro. Por exemplo, implementa-se funções para ler os dados de aceleração dos eixos X, Y e Z, além de escrever valores de configuração nos registradores do acelerômetro.

### Inicialização do ADXL345

O próximo passo é a inicialização do ADXL345. Durante esta fase, condigura-se o dispositivo para operar na faixa de ±16g e em resolução total. Também é definido a taxa de amostragem para 250 Hz, garantindo que o acelerômetro forneça dados em tempo real com a precisão necessária para nossas aplicações. Essa configuração é fundamental para obter leituras precisas e confiáveis.

### Calibração

Após a inicialização, realiza-se a calibração do acelerômetro. Este processo envolve coletar amostras dos dados de aceleração enquanto o dispositivo está em repouso e calcular offsets para os eixos. Esses offsets são então escritos de volta nos registradores do ADXL345, garantindo que as medições sejam ajustadas corretamente e representem a aceleração real.

### Leitura em Tempo Real

Finalmente, implementa-se uma thread dedicada à leitura dos eixos do acelerômetro. Essa thread opera continuamente, lendo os valores de aceleração e armazenando-os em variáveis globais. Essa abordagem permite que o sistema processe os dados em tempo real, possibilitando a realização de ações ou análises baseadas nas leituras do acelerômetro.

<!--### Conclusão

Nesse projeto é possível não somente demonstrar a comunicação eficaz com o ADXL345, mas também oferece uma visão prática sobre como trabalhar com dispositivos I2C e mapeamento de memória em sistemas embarcados.
-->
