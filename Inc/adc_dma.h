#ifndef __ADC_DMA_H
#define __ADC_DMA_H	 
#include "stm32f1xx_hal.h"
/*******************************************************************************
* Copyright 2015 SuZhou 智御电子淘宝店
* All right reserved
*
* 文件名称：adc_dma
*
* 文件标识：adc_dma.h
* 摘    要：采集STM32的6路ADC信号，采用DMA方式
*
*
* 当前版本：
* 作    者：智御电子淘宝店店主 https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* 日    期：2015/7/13
* 编译环境：Keil
*
* 历史信息：
*******************************************************************************/

#define ADC1_DR_Address    ((uint32_t)0x4001244C)
#define AMPLITUDE_SHORT 50
extern __IO uint16_t ADCConvertedValue[6];
extern __IO uint16_t ADC_Value[6];

typedef struct ADC_Value {
  float ADC_ValueChannel_1;
  float ADC_ValueChannel_2;
  float ADC_ValueChannel_3;
  float ADC_ValueChannel_4;
  float ADC_ValueChannel_5;
  float ADC_ValueChannel_6;
}ADC_Channel_Value;

typedef union bitStruct{
  struct 
  {
    unsigned char switch1:1;
    unsigned char switch2:1;
    unsigned char switch3:1;
    unsigned char switch4:1;
    unsigned char switch5:1;
    unsigned char switch6:1;
    unsigned char switch7:1;
    unsigned char switch8:1;
  }bit;
  unsigned char total_value;
}SwitchStruct;


void ADC_DMA_Init(void);
void ADC_data_filter(void);
void ADC_data_filter_ave(void);
void Get_ADC_data_filter_ave(void);
void Update_ADC_Value(uint8_t* pDesArr,uint8_t* pDesLength);

void  Adc_Init(void);
uint16_t Get_Adc(uint8_t ch);
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times);
void ADC_data_filter_2(void);
uint8_t Is_ADC1_ShortOut(void);
uint8_t Is_ADC1_ShortOut2(uint16_t upper,uint16_t lower);
void SWITCH_IO_Detection(void);
void Update_IO_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_OPTP_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_HandTouch_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_ENC3_Value(uint8_t* pDesArr,uint8_t* pDesLength);
void Update_StepMotor_Flag_Value(uint8_t* pDesArr,uint8_t* pDesLength);

#endif
