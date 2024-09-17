#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "address_map_arm.h"


#define ADXL345_ADDRESS 0x53  // Endereço I2C do ADXL345
#define ADXL345_POWER_CTL 0x2D
#define ADXL345_DATA_FORMAT 0x31
#define ADXL345_DATAX0 0x32
#define ADXL345_DATAX1 0x33
#define ADXL345_DATAY0 0x34
#define ADXL345_DATAY1 0x35
#define ADXL345_DATAZ0 0x36
#define ADXL345_DATAZ1 0x37

volatile int *I2C0_con, *I2C0_tar, *I2C0_data, *I2C0_readbuffer, *I2C0_enable, *I2C0_enable_sts, *I2C0_fs_hcnt, *I2C0_fs_lcnt, *I2C0USEFPGA, *GENERALIO7, *GENERALIO8;

// Funções para acessar memória física
int open_physical(int fd) {
    if (fd == -1)
        if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
            printf("ERROR: could not open \"/dev/mem\"");
            return (-1);
        }
    return fd;
}

void close_physical(int fd) {
    close(fd);
}

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

int unmap_physical(void *virtual_base, unsigned int span) {
    if (munmap(virtual_base, span) != 0) {
        perror("ERROR: munmap() failed");
        return (-1);
    }
    return 0;
}

void Pinmux_config(){
    *I2C0USEFPGA = 0;
    *GENERALIO7 = 1;
    *GENERALIO8 = 1;

}

void I2C0_init(){
    //Para qualquer transmissão no I2C0
   *I2C0_enable = 2;
   while(((*I2C0_enable_sts)&0x1) == 1){}
   
   //Seta o I2C como mestre e o ADXL345 como escravo
   *I2C0_con = 0x65;
   *I2C0_tar = 0x53;

   //Seta o periodo
   *I2C0_fs_hcnt = 60 + 30;  // 0.6us + 0.3us
   *I2C0_fs_lcnt = 130 + 30; // 1.3us + 0.3us

   //Liga o controlador
   *I2C0_enable = 1;
   while(((*I2C0_enable_sts)&0x1) == 0){}
}

//Realiza a leitura de vários registradores
void multi_read(uint8_t address, uint8_t values[], uint8_t
len){

    int nth_byte=0;
    int i;
    //Envia o endereço + sinal de START
    *I2C0_data = address + 0x400;

    for(i=0; i<len; i++){
        *I2C0_data = 0x100;
    }

    //Lê os bytes
    while(len){
        if ((*I2C0_readbuffer) > 0){
            values[nth_byte] = *I2C0_data;
            nth_byte++;
            len--;
        }
    }
}


int main(void) {
    uint8_t *valor;
    int fd = -1;
    void *LW_virtual;
	printf("1");

    // Abrir /dev/mem e mapear a área de memória do I2C
    if ((fd = open_physical(fd)) == -1)
        return (-1);
    if (!(LW_virtual = map_physical(fd, I2C0_BASE, I2C0_SPAN)))
        return (-1);

   //Mapeamento de memória do I2C0
   I2C0_con = (int *) (LW_virtual + I2C0_CON);
   I2C0_tar = (int *) (LW_virtual + I2C0_TAR);
   I2C0_data = (int *) (LW_virtual + I2C0_DATA_CMD);
   I2C0_readbuffer = (int *) (LW_virtual + I2C0_RXFLR);
   I2C0_enable = (int *) (LW_virtual + I2C0_ENABLE);
   I2C0_enable_sts = (int *) (LW_virtual + I2C0_ENABLE_STATUS);
   //Mapeamento do multiplexador
   /*I2C0USEFPGA = (int *) (LW_virtual + SYSMGR_I2C0USEFPGA);
   GENERALIO7 = (int *) (LW_virtual + SYSMGR_GENERALIO7);
   GENERALIO8 = (int *) (LW_virtual + SYSMGR_GENERALIO8);
    */

  // *I2C0_data = *I2C0_tar + 0x400;
  // *I2C0_data = 0x100;

    // Ler os valores dos eixos

    // Desvincular e fechar
    unmap_physical(LW_virtual, I2C0_SPAN);
    close_physical(fd);

    return 0;
}

