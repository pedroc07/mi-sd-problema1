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

void multi_read(uint8_t address, uint8_t values[], uint8_t
len, volatile int *I2C0_data){

    int nth_byte=0;
    int i;
    //Envia o endereço + sinal de START
    *I2C0_data = address + 0x400;

    for(i=0; i<len; i++){
        *I2C0_data = 0x100;
    }

    //Lê os bytes
    while(len){
        if ((*I2C0_RXFLR) > 0){
            values[nth_byte] = *I2C0_data;
            nth_byte++;
            len--;
        }
    }
}


int main(void) {
    volatile int *I2C0_con, *I2C0_tar, *I2C0_data;
    uint8_t *valor;
    int fd = -1;
    void *LW_virtual;
	printf("1");

    // Abrir /dev/mem e mapear a área de memória do I2C
    if ((fd = open_physical(fd)) == -1)
        return (-1);
    if (!(LW_virtual = map_physical(fd, I2C0_BASE, I2C0_SPAN)))
        return (-1);

   I2C0_con = (int *) (LW_virtual + I2C0_CON);
   I2C0_tar = (int *) (LW_virtual + I2C0_TAR);
   I2C0_data = (int *) (LW_virtual + I2C0_DATA_CMD);


   //Seta o I2C como mestre e o ADXL345 como escravo
   *I2C0_con = 0x65;
   *I2C0_tar = 0x53;
  // *I2C0_data = *I2C0_tar + 0x400;
  // *I2C0_data = 0x100;

    // Ler os valores dos eixos

    // Desvincular e fechar
    unmap_physical(LW_virtual, I2C0_SPAN);
    close_physical(fd);

    return 0;
}

