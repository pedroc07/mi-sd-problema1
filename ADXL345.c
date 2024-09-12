//Pin Mux Registers
#define SYSMGR_GENERALIO7 ((volatile unsigned int *) 0xFFD0849C)
#define SYSMGR_GENERALIO8 ((volatile unsigned int *) 0xFFD084A0)
#define SYSMGR_I2C0USEFPGA ((volatile unsigned int *) 0xFFD08704)

// I2C0 Controller Registers
#define I2C0_CON                ((volatile unsigned int *) 0xffc04000)
#define I2C0_TAR                ((volatile unsigned int *) 0xffc04004)
#define I2C0_DATA_CMD           ((volatile unsigned int *) 0xffc04010)
#define I2C0_SS_SCL_HCNT        ((volatile unsigned int *) 0xffc04014)
#define I2C0_SS_SCL_LCNT        ((volatile unsigned int *) 0xffc04028)
#define I2C0_FS_SCL_HCNT        ((volatile unsigned int *) 0xffc0401c)
#define I2C0_FS_SCL_LCNT        ((volatile unsigned int *) 0xffc04020)
#define I2C0_INTR_MASK          ((volatile unsigned int *) 0xffc04030)
#define I2C0_CLR_INTR           ((volatile unsigned int *) 0xffc04040)
#define I2C0_TX_ABRT            ((volatile unsigned int *) 0xffc04054)
#define I2C0_ENABLE             ((volatile unsigned int *) 0xffc0406c)
#define I2C0_STATUS             ((volatile unsigned int *) 0xffc04070)
#define I2C0_TXFLR              ((volatile unsigned int *) 0xffc04074)
#define I2C0_RXFLR              ((volatile unsigned int *) 0xffc04078)
#define I2C0_TX_ABRT_SOURCE     ((volatile unsigned int *) 0xffc04080)
#define I2C0_ENABLE_STATUS      ((volatile unsigned int *) 0xffc0409c)

// ADXL345 Register List
#define ADXL345_REG_DEVID       	0x00
#define ADXL345_REG_POWER_CTL   	0x2D
#define ADXL345_REG_DATA_FORMAT 	0x31
#define ADXL345_REG_FIFO_CTL    	0x38
#define ADXL345_REG_BW_RATE     	0x2C
#define ADXL345_REG_INT_ENABLE  	0x2E  // default value: 0x00
#define ADXL345_REG_INT_MAP     	0x2F  // default value: 0x00
#define ADXL345_REG_INT_SOURCE  	0x30  // default value: 0x02
#define ADXL345_REG_DATAX0      	0x32  // read only
#define ADXL345_REG_DATAX1      	0x33  // read only
#define ADXL345_REG_DATAY0      	0x34  // read only
#define ADXL345_REG_DATAY1      	0x35  // read only
#define ADXL345_REG_DATAZ0      	0x36  // read only
#define ADXL345_REG_DATAZ1      	0x37  // read only
#define ADXL345_REG_OFSX        	0x1E
#define ADXL345_REG_OFSY        	0x1F
#define ADXL345_REG_OFSZ        	0x20
#define ADXL345_REG_THRESH_ACT		0x24
#define ADXL345_REG_THRESH_INACT	0x25
#define ADXL345_REG_TIME_INACT		0x26
#define ADXL345_REG_ACT_INACT_CTL	0x27

/* Bit values in BW_RATE                                                */
/* Expresed as output data rate */
#define XL345_RATE_3200       0x0f
#define XL345_RATE_1600       0x0e
#define XL345_RATE_800        0x0d
#define XL345_RATE_400        0x0c
#define XL345_RATE_200        0x0b
#define XL345_RATE_100        0x0a
#define XL345_RATE_50         0x09
#define XL345_RATE_25         0x08
#define XL345_RATE_12_5       0x07
#define XL345_RATE_6_25       0x06
#define XL345_RATE_3_125      0x05
#define XL345_RATE_1_563      0x04
#define XL345_RATE__782       0x03
#define XL345_RATE__39        0x02
#define XL345_RATE__195       0x01
#define XL345_RATE__098       0x00

/* Bit values in DATA_FORMAT                                            */

/* Register values read in DATAX0 through DATAZ1 are dependant on the 
   value specified in data format.  Customer code will need to interpret
   the data as desired.                                                 */
#define XL345_RANGE_2G             0x00
#define XL345_RANGE_4G             0x01
#define XL345_RANGE_8G             0x02
#define XL345_RANGE_16G            0x03
#define XL345_DATA_JUST_RIGHT      0x00
#define XL345_DATA_JUST_LEFT       0x04
#define XL345_10BIT                0x00
#define XL345_FULL_RESOLUTION      0x08
#define XL345_INT_LOW              0x20
#define XL345_INT_HIGH             0x00
#define XL345_SPI3WIRE             0x40
#define XL345_SPI4WIRE             0x00
#define XL345_SELFTEST             0x80

/* Bit values in INT_ENABLE, INT_MAP, and INT_SOURCE are identical
   use these bit values to read or write any of these registers.        */
#define XL345_OVERRUN              0x01
#define XL345_WATERMARK            0x02
#define XL345_FREEFALL             0x04
#define XL345_INACTIVITY           0x08
#define XL345_ACTIVITY             0x10
#define XL345_DOUBLETAP            0x20
#define XL345_SINGLETAP            0x40
#define XL345_DATAREADY            0x80

/* Bit values in POWER_CTL                                              */
#define XL345_WAKEUP_8HZ           0x00
#define XL345_WAKEUP_4HZ           0x01
#define XL345_WAKEUP_2HZ           0x02
#define XL345_WAKEUP_1HZ           0x03
#define XL345_SLEEP                0x04
#define XL345_MEASURE              0x08
#define XL345_STANDBY              0x00
#define XL345_AUTO_SLEEP           0x10
#define XL345_ACT_INACT_SERIAL     0x20
#define XL345_ACT_INACT_CONCURRENT 0x00

void configure_pinmux(){
   *SYSMGR_I2C0USEFPGA = 0;
   *SYSMGR_GENERALIO7 = 1;
   *SYSMGR_GENERALIO8 = 1; 
}

//Iniciaa o I2C0
void I2C0_init(){
    //Encerra as operações e desliga o I2C0
    *I2C0_ENABLE = 2;

    //Espera até que o I2C0 esteja completamente desligado
    while(((*I2C0_ENABLE_STATUS)&0x1) == 1){}

    /*Configura o registrador para que funcione como mestre,
    em 400 kbits/s e endereçmento de 7-bit */
    *I2C0_CON = 0x65;

    //Seleciona o endereço alvo como o ADXL345
    *I2C0_TAR = 0x53;

    //Define o período de clock
    *I2C0_FS_SCL_HCNT = 60 + 30; // 0.6us + 0.3us
    *I2C0_FS_SCL_LCNT = 130 + 30; // 1.3us + 0.3us

    //Liga o I2C0
    *I2C0_ENABLE = 1;

    //Espera até que o I2C0 esteja completamente ligado
    while(((*I2C0_ENABLE_STATUS)&0x1) == 0){}
}

//Lê um valor de um endereço
void ADXL345_REG_READ(uint8_t address, uint8_t *value){

    //Envia o endereço + sinal de START
    *I2C0_DATA_CMD = address + 0x400;

    //Envia um sinal de leitura
    *I2C0_DATA_CMD = address + 0x400;

    // Espera que os dados entrem no buffer e então lê o valor
    while(*I2C0_RXFLR == 0){}
    *value = *I2C0_DATA_CMD;
}

//Escreve um valor em um endereço
void ADXL345_REG_WRITE(uint8_t address, uint8_t value){

    //Envia o endereço + sinal de START
    *I2C0_DATA_CMD = address + 0x400;

    //Envia um valor
    *I2C0_DATA_CMD = value;
}

//Lê múltiplos registradores
void ADXL345_REG_MULTI_READ(uint8_t address, uint8_t values[], uint8_t
len){

    int nth_byte=0;
    int i;
    //Envia o endereço + sinal de START
    *I2C0_DATA_CMD = address + 0x400;

    for(i=0; i<len; i++){
        *I2C0_DATA_CMD = 0x100;
    }

    //Lê os bytes
    while(len){
        if ((*I2C0_RXFLR) > 0){
            values[nth_byte] = *I2C0_DATA_CMD;
            nth_byte++;
            len--;
        }
    }
}

//Inicia o ADXL345
void ADXL345_Init(){

    //+-16g range, full resolution
    ADXL345_REG_WRITE(ADXL345_REG_DATA_FORMAT, XL345_RANGE_16G | XL345_FULL_RESOLUTION);

    //taxa de aceleração: 200Hz
    ADXL345_REG_WRITE(ADXL345_REG_BW_RATE, XL345_RATE_200);

    ADXL345_REG_WRITE(ADXL345_REG_THRESH_ACT, 0x04); //atividade
    ADXL345_REG_WRITE(ADXL345_REG_THRESH_INACT, 0x02); //inatividade

    ADXL345_REG_WRITE(ADXL345_REG_TIME_INACT, 0x02); //tempo para inatividade
    ADXL345_REG_WRITE(ADXL345_REG_ACT_INACT_CTL, 0xFF);
    ADXL345_REG_WRITE(ADXL345_REG_INT_ENABLE, XL345_ACTIVITY | XL345_INACTIVITY );

    // para a medição
    ADXL345_REG_WRITE(ADXL345_REG_POWER_CTL, XL345_STANDBY);

    // começa a medição
    ADXL345_REG_WRITE(ADXL345_REG_POWER_CTL, XL345_MEASURE);
}

//Lê dados dos 3 eixos
void ADXL345_XYZ_Read(int16_t szData16[3]){
    uint8_t szData8[6];
    ADXL345_REG_MULTI_READ(0x32, (uint8_t *)&szData8, sizeof(szData8));

    szData16[0] = (szData8[1] << 8) | szData8[0];
    szData16[1] = (szData8[3] << 8) | szData8[2];
    szData16[2] = (szData8[5] << 8) | szData8[4];
}

//Retorna 1 quando há novos dados
int ADXL345_IsDataReady(){
    int ready = 0;
    uint8_t data8;

    ADXL345_REG_READ(ADXL345_REG_INT_SOURCE,&data8);
    if (data8 & XL345_ACTIVITY){
        ready = 1;
    }
    return 1;
}

