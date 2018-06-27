#include "crc16.h"
/*******************************************************************************
* Copyright 2015 SuZhou 智御电子淘宝店
* All right reserved
*
* 文件名称：crc16.h
*
* 文件标识：crc16
* 摘    要：CRC16数据包校验
*
*
* 当前版本：v1.0
* 作    者：智御电子淘宝店店主 https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* 日    期：2015/7/22
* 编译环境：Keil
*
* 历史信息：
*******************************************************************************/

/*******************************函数声明****************************************
* 函数名称: uint16_t crc16_ccitt(uint8_t  *q,int16_t len) 
* 输入参数: uint8_t  *q,int16_t len 
* 返回参数: uint16_t  
* 功    能: CRC16_CCITT查表校验  
* 作    者: by 智御电子淘宝店店主 https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* 日    期: 2015/7/22
*******************************************************************************/ 
uint16_t crc16_ccitt(uint8_t  *q,int16_t len)
{
  uint16_t crc = 0;
  while (len-- > 0)
    crc = ccitt_table[(crc >> 8 ^ *q++) & 0xff] ^ (crc << 8);
  return crc;
}


/*******************************函数声明****************************************
* 函数名称: uint16_t crc16(uint8_t  *q,int16_t len) 
* 输入参数: uint8_t  *q,int16_t len 
* 返回参数: uint16_t  
* 功    能: CRC16 查表校验  
* 作    者: by 智御电子淘宝店店主 https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* 日    期: 2015/7/22
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
