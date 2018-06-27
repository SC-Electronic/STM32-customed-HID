#include "crc16.h"
/*******************************************************************************
* Copyright 2015 SuZhou ���������Ա���
* All right reserved
*
* �ļ����ƣ�crc16.h
*
* �ļ���ʶ��crc16
* ժ    Ҫ��CRC16���ݰ�У��
*
*
* ��ǰ�汾��v1.0
* ��    �ߣ����������Ա������ https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* ��    �ڣ�2015/7/22
* ���뻷����Keil
*
* ��ʷ��Ϣ��
*******************************************************************************/

/*******************************��������****************************************
* ��������: uint16_t crc16_ccitt(uint8_t  *q,int16_t len) 
* �������: uint8_t  *q,int16_t len 
* ���ز���: uint16_t  
* ��    ��: CRC16_CCITT���У��  
* ��    ��: by ���������Ա������ https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* ��    ��: 2015/7/22
*******************************************************************************/ 
uint16_t crc16_ccitt(uint8_t  *q,int16_t len)
{
  uint16_t crc = 0;
  while (len-- > 0)
    crc = ccitt_table[(crc >> 8 ^ *q++) & 0xff] ^ (crc << 8);
  return crc;
}


/*******************************��������****************************************
* ��������: uint16_t crc16(uint8_t  *q,int16_t len) 
* �������: uint8_t  *q,int16_t len 
* ���ز���: uint16_t  
* ��    ��: CRC16 ���У��  
* ��    ��: by ���������Ա������ https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* ��    ��: 2015/7/22
*******************************************************************************/
uint16_t CRC16(uint8_t *puchMsgg,uint8_t usDataLen,uint16_t crcInput)
{
  uint8_t uchCRCHi;  
  uint8_t uchCRCLo;  
  uint8_t uIndex ; 
  uchCRCHi = (uint8_t)(crcInput>>8);
  uchCRCLo = (uint8_t)crcInput;
  
  while (usDataLen--) 
  { 
    uIndex = uchCRCHi ^ *puchMsgg++ ; 
    uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ; 
    uchCRCLo = auchCRCLo[uIndex] ; 
  } 
  return (uchCRCHi << 8 | uchCRCLo) ; 
}
