# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
#include "map.c"

int main(){
    int fd = -1;
    int fd1 = -1;
    void *I2C0_virtual;
    int16_t XYZ[3];

    // Abrir /dev/mem e mapear a área de memória do I2C e do SYSMGR
    if ((fd = open_physical(fd)) == -1)
        return (-1);
    if (!(I2C0_virtual = map_physical(fd, I2C0_BASE, I2C0_SPAN)))
        return (-1);
    close_physical(fd);


    //Mapeamento de memória do I2C0
    I2C0_con = (int *) (I2C0_virtual + I2C0_CON);
    I2C0_tar = (int *) (I2C0_virtual + 0x4);
    I2C0_data = (int *) (I2C0_virtual + 0x10);
    I2C0_readbuffer = (int *) (I2C0_virtual + 0x78);
    I2C0_enable = (int *) (I2C0_virtual + 0x6C);
    I2C0_enable_sts = (int *) (I2C0_virtual + 0x9C);
    I2C0_fs_hcnt = (int *) (I2C0_virtual + 0x1C);
    I2C0_fs_lcnt = (int *) (I2C0_virtual + 0x20);

    I2C0_init();

    uint8_t value;
    ADXL345_read(ADXL345_REG_DEVID, &value);

    if(value == 0XE5){
        ADXL_345_init();

        ADXL345_Calibrate();

        while(1){
            if(ADXL345_IsDataReady()){
                ADXL345_XYZ_Read(XYZ);
                printf("X = %d, Y = %d, Z = %d", XYZ[0], XYZ[1], XYZ[2]);
                usleep(10000000);
            }
        }
    }


    unmap_physical(I2C0_virtual, I2C0_SPAN);
    close_physical(fd);
    
    return 0;
}
