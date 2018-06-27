#include "adc_dma.h"
#include <stdio.h>
//#include "delay.h"
/*******************************************************************************
* Copyright 2015 SuZhou ���������Ա���
* All right reserved
*
* �ļ����ƣ�adc_dma
*
* �ļ���ʶ��adc_dma.c
* ժ    Ҫ���ɼ�STM32��6·ADC�źţ�����DMA��ʽ
*
*
* ��ǰ�汾��
* ��    �ߣ����������Ա������ https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* ��    �ڣ�2015/7/13
* ���뻷����Keil
*
* ��ʷ��Ϣ��
*******************************************************************************/

__IO uint16_t ADCConvertedValue[6]={0};
__IO uint16_t ADC_Value[6];
ADC_Channel_Value adc_sampe;
ADC_Channel_Value *p_ADC_SampeValue = &adc_sampe;
uint16_t ADCConvertedValue_Arr[6][50]={0};
double ADCConvertedValue_old[6]={0.0};
float Adc_a2=-0.9844142,  Adc_b1=0.0077929, Adc_b2=0.0077929;

 //float Adc_a2_2s=-1.982228929792529,  Adc_a3_2s=0.982385450614126, Adc_b1_2s=0.00003913, Adc_b2_2s=0.00007826,Adc_b3_2s=0.00003913;
 float Adc_a2_2s=-1.911197067426073,  Adc_a3_2s=0.914975834801433, Adc_b1_2s=9.446918438401619e-04, Adc_b2_2s=0.001889383687680,Adc_b3_2s=9.446918438401619e-04;

/*******************************��������****************************************
* ��������: void ADC_data_filter(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ��ʱ��ȡADC����ֵ�����Ҽ����˲��㷨����  
* ��    ��: by ���������Ա������ https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* ��    ��: 2015/7/13
*******************************************************************************/ 
void ADC_data_filter(void)
{
  float temp[6]={0.0};
  uint8_t i=0;
  for(i=0;i<6;i++)
  {
    temp[i]=ADCConvertedValue[i];
  }
  
  p_ADC_SampeValue->ADC_ValueChannel_1    =  (Adc_b1*temp[0] + Adc_b2*ADCConvertedValue_old[0] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_1); 
  p_ADC_SampeValue->ADC_ValueChannel_2    =  (Adc_b1*temp[1] + Adc_b2*ADCConvertedValue_old[1] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_2); 
  p_ADC_SampeValue->ADC_ValueChannel_3    =  (Adc_b1*temp[2] + Adc_b2*ADCConvertedValue_old[2] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_3); 
  p_ADC_SampeValue->ADC_ValueChannel_4    =  (Adc_b1*temp[3] + Adc_b2*ADCConvertedValue_old[3] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_4); 
  p_ADC_SampeValue->ADC_ValueChannel_5    =  (Adc_b1*temp[4] + Adc_b2*ADCConvertedValue_old[4] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_5); 
  p_ADC_SampeValue->ADC_ValueChannel_6    =  (Adc_b1*temp[5] + Adc_b2*ADCConvertedValue_old[5] - Adc_a2 * p_ADC_SampeValue->ADC_ValueChannel_6); 
  
  for(i=0;i<6;i++)
  {
    ADCConvertedValue_old[i]=temp[i];
  }
 // printf("channel1:%f \r\n",p_ADC_SampeValue->ADC_ValueChannel_1);
 // printf("channel2:%f \n",p_ADC_SampeValue->ADC_ValueChannel_2);
 // printf("channel3:%f \n",p_ADC_SampeValue->ADC_ValueChannel_3);
 // printf("channel4:%f \n",p_ADC_SampeValue->ADC_ValueChannel_4);
  //printf("channel5:%f \n",p_ADC_SampeValue->ADC_ValueChannel_5);
 // printf("channel6:%f \n",p_ADC_SampeValue->ADC_ValueChannel_6);
  
}

//const float Adc_a2_2s=-1.9822,  Adc_a3_2s=0.9824, Adc_b1_2s=0.00003913, Adc_b2_2s=0.00007826,Adc_b3_2s=0.00003913;

//float Adc_a2_2s=-1.9556,  Adc_a3_2s=0.95665, Adc_b1_2s=0.0002414, Adc_b2_2s=0.0004827,Adc_b3_2s=0.0002414;
float  origin[4][3]={0};
float  fliter[4][3]={0};
float temp[5]={0};
void ADC_data_filter_2(void)
{
  uint8_t i=0;

  for(i=0;i<4;i++)
  {
    origin[i][2] = ADCConvertedValue[i];
//		temp[0] = Adc_b1_2s + Adc_b2_2s + Adc_b3_2s - Adc_a2_2s -  Adc_a3_2s;
//		temp[0] = Adc_b1_2s*origin[i][2];
//		temp[1] = Adc_b2_2s*origin[i][1];
//		temp[2] = Adc_b3_2s*origin[i][0];
//		temp[3] = Adc_a2_2s*fliter[i][1];
//		temp[4] = Adc_a3_2s*fliter[i][0];
//		fliter[i][2] = temp[0]+temp[1]+temp[2]-temp[3]-temp[4];
		fliter[i][2] = (Adc_b1_2s*origin[i][2] +  Adc_b2_2s*origin[i][1] + Adc_b3_2s*origin[i][0] - Adc_a2_2s*fliter[i][1] - Adc_a3_2s*fliter[i][0]);
    origin[i][0] = origin[i][1];
		origin[i][1] = origin[i][2];
		fliter[i][0]=  fliter[i][1];
		fliter[i][1] = fliter[i][2];	
	}
  
  p_ADC_SampeValue->ADC_ValueChannel_1    = fliter[0][2];
  p_ADC_SampeValue->ADC_ValueChannel_2    = fliter[1][2];
  p_ADC_SampeValue->ADC_ValueChannel_3    = fliter[2][2];
  p_ADC_SampeValue->ADC_ValueChannel_4    = fliter[3][2]; 
 
//	p_ADC_SampeValue->ADC_ValueChannel_1    = ADCConvertedValue[0];
//  p_ADC_SampeValue->ADC_ValueChannel_2    = ADCConvertedValue[1];
//  p_ADC_SampeValue->ADC_ValueChannel_3    = ADCConvertedValue[2];
//  p_ADC_SampeValue->ADC_ValueChannel_4    = ADCConvertedValue[3]; 
// 
	
//	printf("%d %lf\r\n",ADCConvertedValue[0],fliter[0]);
}

void LimitRange(float * data , float max, float mix)
{
  *data = *data > max ? max : *data ;
	*data = *data < mix ? mix : *data ;
}

/*******************************��������****************************************
* ��������: uint8_t Is_ADC1_ShortOut()
* �������: uint8_t
* ���ز���: void  
* ��    ��: �ж�ADC1������Ƿ�ӵأ�����ӵط���0��
* ��    ��: by ���������Ա������ https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* ��    ��: 2015/7/13
*******************************************************************************/ 
uint8_t Is_ADC1_ShortOut()
{
  if(p_ADC_SampeValue->ADC_ValueChannel_1>100)
		return 1;
	else
		return 0;
}

/*******************************��������****************************************
* ��������: Is_ADC1_ShortOut2(uint16_t upper,uint16_t lower)
* �������: uint8_t
* ���ز���: void  
* ��    ��: �ж�ADC1������Ƿ�ӵأ�����ӵط���0������ķ�ֹ�ͺŴ��ҵĹ��ܡ���������ȷ�źŵ�ʶ������
* ��    ��: by ���������Ա������ https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* ��    ��: 2015/7/13
*******************************************************************************/ 
static uint8_t isShort=1; //Ĭ��û�йر�

uint8_t Is_ADC1_ShortOut2(uint16_t upper,uint16_t lower)
{
  static uint16_t value_new=0;
	value_new = p_ADC_SampeValue->ADC_ValueChannel_1;
	
	if((upper-AMPLITUDE_SHORT)<=value_new<=(upper+AMPLITUDE_SHORT))
	{
	  isShort =1;
	}
	
		if((lower-AMPLITUDE_SHORT)<=value_new<=(lower+AMPLITUDE_SHORT))  
	{
	  isShort =0;
	}
	
	return isShort;
}


/*******************************��������****************************************
* ��������: uint16_t Limit_ADC_Value(uint16_t result,uint16_t upper,uint16_t lower)
* �������: uint8_t
* ���ز���: void  
* ��    ��: ����ͨ���ķ�ֵ�����ޣ���������������ߣ�ά����һ����ֵ���ı�
* ��    ��: by ���������Ա������ https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* ��    ��: 2015/7/13
*******************************************************************************/ 
uint16_t Limit_ADC_Value(uint16_t result,uint16_t upper,uint16_t lower)
{
  static uint16_t value_result=4095;
  value_result = ((result>=lower) && (result<=upper)) ? result : value_result;
	return value_result;
}
/*******************************��������****************************************
* ��������: void Update_ADC_Value(uint8_t* pDesArr,uint8_t* pDesLength)
* �������: uint8_t* pDesArr,uint8_t* pDesLength 
* ���ز���: void  
* ��    ��: ��ADC��6ͨ��ֵ���뵽usb send���ݰ��С�
            ע��˺�����ͬ�ĵ��ô���Ӱ��������������������ݰ��е�λ��
* ��    ��: by ���������Ա������ https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* ��    ��: 2015/7/13
*******************************************************************************/ 
void Update_ADC_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{
  int16_t t=0;
  // t = DS18B20_Get_Temp();
  t = 1234;
  //ADC1 value
 // t=ADC_Value[0];
	LimitRange(&p_ADC_SampeValue->ADC_ValueChannel_3,4096,0);
	//t=(int16_t)p_ADC_SampeValue->ADC_ValueChannel_3;
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (uint8_t)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (uint8_t)(t&0x00FF);
  
  //ADC2 value
  //t=ADC_Value[1];
	LimitRange(&p_ADC_SampeValue->ADC_ValueChannel_4,4096,0);
 // t=(int16_t)p_ADC_SampeValue->ADC_ValueChannel_4;
	*pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (uint8_t)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (uint8_t)(t&0x00FF);	
  
  //ADC3 value
  //t=ADC_Value[2];
	LimitRange(&p_ADC_SampeValue->ADC_ValueChannel_1,4096,0);
//   t=(int16_t)p_ADC_SampeValue->ADC_ValueChannel_1;
	*pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (uint8_t)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (uint8_t)(t&0x00FF);	
  
  //ADC4 value
  //t=ADC_Value[3];
	LimitRange(&p_ADC_SampeValue->ADC_ValueChannel_2,4096,0);
 // t=(int16_t)p_ADC_SampeValue->ADC_ValueChannel_2;
	*pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = (uint8_t)((t&0xFF00)>>8);  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = (uint8_t)(t&0x00FF);	


  //change the vaild data length
  pDesArr[4]=*pDesLength;
}

