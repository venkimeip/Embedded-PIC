#ifndef _ADC
#define _ADC

#define E0_E1_SHORT 1
#define E0_E1_OPEN 2
#define E0_E1_UNKNOWN 0xFF

#define TRUE 1
#define FALSE 0
#define AN0 0
#define AN1 1

#define ADC_Cutoff_E0_MIN  0x4C // 1.5v
#define ADC_Cutoff_E0_MAX  0x5C
#define ADC_Cutoff_E1_MAX  0x47 // 1.4V
#define ADC_Cutoff_E1_MIN  0x38 // 1.10V

#define ADC_INPUTS  (0x03) // Ativate AN0 and AN1 as ADC Inputs

void init_adc(void);
unsigned char Read_Adc(unsigned char Channel);
unsigned char Read_Adc_E0(void);
unsigned char Read_Adc_E1(void);

void adc_delay(unsigned char x);

#endif