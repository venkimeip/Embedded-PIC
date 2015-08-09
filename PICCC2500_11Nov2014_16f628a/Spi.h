#ifndef _SPI
#define _SPI
void init_spi(void);
unsigned char spi_TxByte(unsigned char txchar);
void SPI_SS_Enable(void);
void SPI_SS_Disable(void);

void Delay_ms(unsigned int delayms);

void SPI_MOSI_SETHIGH(void);
void SPI_MOSI_SETLOW(void);
void SPI_SCK_SETLOW(void);
void SPI_SCK_SETHIGH(void);
unsigned char SPI_MISO_READ(void);

#endif
