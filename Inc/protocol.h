#ifndef __PROTOCOL_H
#define __PROTOCOL_H	 
#include "stm32f1xx_hal.h"
/*******************************************************************************
* Copyright 2015 SuZhou 智御电子淘宝店
* All right reserved
*
* 文件名称：protocol
*
* 文件标识：protocol.h
* 摘    要：数据协议包定义、解析文件
*
*
* 当前版本：
* 作    者：智御电子淘宝店店主 https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* 日    期：2015/7/22
* 编译环境：Keil
*
* 历史信息：
*******************************************************************************/


#define RESEARCH_BOARD 0x30
#define GreenBoard     0x10
#define BlackBoard     0x00

#define ReadDateToPC   0x01

uint8_t Parsed_Data_FromPC(uint8_t *receivedata ,uint16_t DataCheckLen);
void SendDataToPC(uint8_t *usbSendBuf );
void SendCRCDataToPC(uint8_t *usbSendBufdata, uint8_t* pDesLength);
void Parse_Pack_Data(uint8_t *usbReceiveBufdata);
#endif
