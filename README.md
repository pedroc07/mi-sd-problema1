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

###### (Executa o jogo.)

## Lógica do jogo

Para criar a tela do jogo, foi feito o uso de uma matriz de inteiros (tipo int) 10x24 onde os elementos representam as células do jogo. Para gerar as peças utilizadas são geradas matrizes de inteiros (tipo int) 4x4. Nessas matrizes o número 0 representa os espaços vazios e os demais números são referentes ao índice da cor dos blocos. As matrizes são unidas, por meio do preenchimento de uma segunda matriz 10x24, imediatamente antes da exibição da tela.

A movimentação da peça atual - isto é, a atualização de suas posições x e y - é feita em duas ocasiões distintas: A primeira, que pode acontecer em qualquer ciclo de execução do programa, acontece caso exista inclinação suficiente do acelerômetro para tal, bem como haja passado tempo suficiente desde o último movimento (tal intervalo é determinado pelo módulo da própria inclinação, com inclinações mais significantes resultando em intervalos menores), e resulta em movimento lateral; A segunda, que deve sempre acontecer a cada 50 ciclos de execução do programa, resulta no movimento vertical da peça atual (para baixo). Todos os movimentos só podem ocorrer caso não exista obstrução e tão somente se o movimento não resulte na saída da peça da área de jogo.

A seguir, em se tratando do movimento vertical, sua impossibilidade resulta na colocação dos blocos da peça na matriz "estática" do jogo. Ademais, quando isto ocorre, avalia-se a posição y final da peça que acabou de ser colocada: Caso dentro da área permitida (aquela delimitada pela área abaixo da linha horizontal de cor branca), o jogo continua por meio do "sorteio" de um formato e cor para uma nova peça; Caso fora desta área, o jogo é marcado como "finalizado".

O controle do fluxo de jogo é feito por meio da combinação dos resultados da leitura de certos dispositivos de entrada da placa DE1-SoC (chaves SW0 e SW1) e do próprio código do programa. Em execução, o jogo pode realizar ações de movimento e atualização da tela, como dito anteriormente; Em pausa e quando finalizada a sessão de jogo, movimentos e atualizações de tela não podem ocorrer, mas o usuário pode reiniciar o jogo inteiro em ambas as ocasiões e retomar a sessão atual apenas em caso de pausa.

<a href="url"><img src="https://github.com/user-attachments/assets/0a81c3e7-06b9-47bc-b8e5-eb3080df686d"></a>

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

Com a configuração do I2C em funcionamento, desenvolve-se funções específicas para leitura e escrita nos registradores do ADXL345. Essas funções abstraem os detalhes da comunicação I2C, permitindo uma interação mais fácil com o acelerômetro. Por exemplo, implementa-se funções para ler os dados de aceleração dos eixos X, Y e Z, além de escrever valores de configuração nos registradores do acelerômetro.

O próximo passo é a inicialização do ADXL345. Durante esta fase, condigura-se o dispositivo para operar na faixa de ±16g e em resolução total. Também é definido a taxa de amostragem para 250 Hz, garantindo que o acelerômetro forneça dados em tempo real com a precisão necessária para nossas aplicações. Essa configuração é fundamental para obter leituras precisas e confiáveis.

Após a inicialização, realiza-se a calibração do acelerômetro. Este processo envolve coletar amostras dos dados de aceleração enquanto o dispositivo está em repouso e calcular offsets para os eixos. Esses offsets são então escritos de volta nos registradores do ADXL345, garantindo que as medições sejam ajustadas corretamente e representem a aceleração real.

Finalmente, implementa-se uma thread dedicada à leitura dos eixos do acelerômetro. Essa thread opera continuamente, lendo os valores de aceleração e armazenando-os em variáveis globais. Essa abordagem permite que o sistema processe os dados em tempo real, possibilitando a realização de ações ou análises baseadas nas leituras do acelerômetro.

<a href="url"><img src="https://github.com/user-attachments/assets/d34bb88c-5d28-4aca-98d7-384ca1df3343"></a>

## Desenvolvimento do projeto

A fase inicial do projeto foi constituída de considerações acerca da lógica básica do jogo e sobre a modularidade mínima necessária em todo o projeto. Foi decidido que o jogo utilizaria as bibliotecas permitidas para uma implementação rápida, ou seja, todas menos as referentes ao acelerômetro ADXL345, o que resultou na divisão do projeto entre o desenvolvimento do jogo e o desenvolvimento da biblioteca do acelerômetro.

O jogo foi desenvolvido tendo em mente um critério de pontuação simples, tal como o encontrado no TETRIS clássico (cada linha completa é totalmente eliminada e essa ação aumenta a pontuação do jogador); No entanto, tendo em vista a limitação de movimento das peças (rotação não deve ser permitida), foi necessário limitar o tamanho e complexidade das formas das peças (quadado 1x1, quadrado 2x2, 2 cantos de 3 blocos e linhas de 3 blocos horizontais e verticais), de modo a permitir uma sessão de jogo satisfatória.

O processo de desenvolvimento do jogo seguiu sem muito percalços, salvo uma dificuldade inicial com o uso de ponteiros em c para passagem de argumento de função via referência ao invés de cópia (o que acontece quando tentamos passar o "objeto" ao invés de seu ponteiro).

A biblioteca de controle do acelerômetro ADXL345 foi densenvolvida a partir da observação do funcionamento do código para outras bibliotecas utilizadas pela placa DE1-SoC (em especial aquela utilizada para comunicação com as Chaves SW0-SW9 da placa, acessada pelo caminho <intelfpgaup/SW.h>). Seguindo o exemplo dessas bibliotecas, faz-se alteração nos endereços físicos mapeados na memória virtual para refletir aqueles referentes ao controlador I2C que acessa o acelerômetro. A seguir, foram desenvolvidas as funções de initcialização e calibragem do aparelho conforme instruções contidas em documentos técnicos e tendo como base tutoriais de uso. Na aplicação, tendo em vista modularidade e organização do código, foi utilizado "thread" para atualizar constantemente os valores lidos nos eixos X, Y e Z, os quais estão atrelados a variáveis globais acessadas por outras funções.
 
A maior dificuldade encontrada nessa parte do processo foi identificar que o endereço do acelerômetro "linkado" ao controlador I2C estava incorreto, o que impossibilitou qualquer acesso aos dados de aceleração. Resolvido tal problema, o processo de implementação da biblioteca seguiu normalmente com testes dos valores obtidos e desenvolvimento de uma função capaz de obter uma leitura inicial do eixo X em questão, a qual é usada como base para avaliar a inclinação da placa DE1-SoC como um todo.

Por fim, foram decididos os intervalos de aceleração no eixo e que tipo de dispositivo de entrada controlaria a sessão de jogo. Optou-se pelo uso das chaves HH tanto para PAUSA/CONTINUAR quanto para "RESET" do jogo, já que a biblioteca disponível para controle dos botões necessitava mudança do estado dos mesmos para leitura, o que acarretaria em mudanças significativas no código já implementado até o momento.

## Testes de Funcionamento

O programa foi testado num kit de desenvolvimento DE1-SoC, que é composto por uma placa Altera SoC (System-on-Chip) FPGA combinada com um processador ARM Cortex-A9 dual core. Essa integração permite também o uso de alguns periféricos em hardware através do HPS(Hard Processor System).

Os testes foram feitos de forma a verificar as funcionalidades básicas do programa em cada uma de suas telas.

<a href="url"><img src="https://github.com/user-attachments/assets/3ba0ca4f-9343-4284-847f-fb2e64f5b633" height=75% width=75% ></a>

Durante a tela inicial, a única ação que o jogador pode fazer é inicir o jogo acionando a chave. Essa funcionalidade foi conferida.

<a href="url"><img src="https://github.com/user-attachments/assets/9986ba7c-9d8f-473c-87a5-0c35e73634a6" height=75% width=75% ></a>

A tela de execução é basicamente a tela exposta quando o jogo está funcionando. Nela o jogador pode mover a placa DE1-SoC para mudar a direção da peça, pode pontuar preenchendo a linha final com peças, pausar e continuar o jogo através de uma das chaves e reiniciar através de outra. Todas essas funcionalidades foram devidamente desenvolvidas e testadas.

<a href="url"><img src="https://github.com/user-attachments/assets/21532620-132c-4dd2-960c-dd47fcba242c" height=75% width=75% ></a>

A tela final é exibida quando o jogador atinge a linha limite na tela de execução e a única funcionalidade possível nela é o reinicio do jogo e o retorno à tela inicial.


## Referências

- [Tutorial de Desenvolvimento Linux em ARM, por FPGA Academy](https://github.com/fpgacademy/Tutorials/releases/download/v21.1/Linux_with_ARM_A9.pdf)
- [Manual da Placa FPGA DE1-SoC](https://drive.google.com/file/d/1HzYtd1LwzVC8eDobg0ZXE0eLhyUrIYYE/view)
- [GCC - Coletânea de Compiladores GNU](https://gcc.gnu.org/)
- [C/C++ no Visual Studio Code para Iniciantes](https://code.visualstudio.com/docs/cpp/config-mingw)
- [MinGW - GCC Minimalista para Windows](https://sourceforge.net/projects/mingw/)
