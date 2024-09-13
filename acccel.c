#include <ADXL345.c>
#include <stdio.h>

int main(){
    int16_t XYZ[3];

    configure_pinmux();

    I2C0_init();

    ADXL345_Init();

    while(1){
        if(ADXL345_IsDataReady()){
            ADXL345_XYZ_Read(XYZ);
            printf("X=%d, Y=%d, Z=%d\n", XYZ[0], XYZ[1], XYZ[2]);
        }
    }

    return 0;
}