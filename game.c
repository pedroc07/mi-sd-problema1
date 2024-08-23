# include <stdio.h>

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

int main ( void ) {
    int tela[10][20];
    preenche_zero(tela);
    imprime_tela(tela);
return 0;
}
