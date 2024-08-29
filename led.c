# include <stdio.h>
#include <intelfpgaup/HEX.h>

int main(void){
    HEX_open ();
    int data = 010101;
    HEX_set ( data);
    HEX_close ();
}