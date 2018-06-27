#include "protocol.h"
#include "crc16.h"

/*******************************************************************************
* Copyright 2015 SuZhou 智御电子淘宝店
* All right reserved
*
* 文件名称：protocol
*
* 文件标识：protocol.c
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

uint8_t test_send[10]={0};
	 uint8_t relay1_status=0,relay2_status=0;
	 uint16_t dac1_value=0,dac2_value=0;
	 uint16_t servo_value1=1250,servo_value2=0;
/*******************************函数声明****************************************
* 函数名称: void Parsed_Data_FromPC(uint8_t *receivedata ,uint16_t DataCheckLen) 
* 输入参数: uint8_t *receivedata ,uint16_t DataCheckLen
* 返回参数: void  
* 功    能: 解析从PC机接收的数据指令  .
* 作    者: by 智御电子淘宝店店主 https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* 日    期: 2015/7/22
*******************************************************************************/ 
uint8_t Parsed_Data_FromPC(uint8_t *receivedata ,uint16_t DataCheckLen)
{
 uint16_t crc_result=0,crc_package=0;
 uint8_t contrast_result=0;
 //check the data packge by crc16 mothod
 crc_result = CRC16(receivedata,DataCheckLen,0xffff);
 //get the CRC16 data from the data package
 crc_package = (receivedata[DataCheckLen]<<8) | (receivedata[DataCheckLen+1]);
 //contrast the two CRC data
   contrast_result = (crc_package ==crc_result ? 1 : 0);
 //CRC check is correct
	return contrast_result;
 
}

/*******************************函数声明****************************************
* 函数名称:  SendDataToPC(uint8_t *usbSendBuf) 
* 输入参数: uint8_t *usbSendBuf 
* 返回参数: void  
* 功    能: 准备发送给电脑的数据包  
* 作    者: by 智御电子淘宝店店主 https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* 日    期: 2015/7/22
*******************************************************************************/ 
void SendDataToPC(uint8_t *usbSendBufdata )
{
  uint16_t crc_result=0,stemp=0;
  //usbReceiveBuf[2]=0;
  usbSendBufdata[0]=0;  //high byte
  usbSendBufdata[1]=0;  //low byte
  usbSendBufdata[3]=RESEARCH_BOARD;  //type of control board
  //UpdateADNS9800(usbSendBuf);
  //UpdateMPU9250(usbSendBuf);
  usbSendBufdata[4]=0x00;
  usbSendBufdata[5]=0x01;
  crc_result = CRC16(usbSendBufdata,5,0xffff);
  stemp = crc_result;
  usbSendBufdata[6]=(uint8_t)((stemp&0xFF00)>>8);  
  usbSendBufdata[5]=(uint8_t)(stemp&0x00FF);  
  //USB_SendData(usbSendBuf,sizeof(usbSendBuf));
}

/*******************************函数声明****************************************
* 函数名称:  SendCRCDataToPC(uint8_t *usbSendBuf) 
* 输入参数: uint8_t *usbSendBuf 
* 返回参数: void  
* 功    能: 准备发送给电脑的数据包  
* 作    者: by 智御电子淘宝店店主 https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* 日    期: 2015/7/22
*******************************************************************************/ 
void SendCRCDataToPC(uint8_t *usbSendBufdata, uint8_t* pDesLength)
{
  uint16_t crc_result=0,stemp=0;
  
  crc_result = CRC16(usbSendBufdata,(*pDesLength)+5,0xffff);
  stemp = crc_result;
	
	usbSendBufdata[(*pDesLength)+5] = (uint8_t)((stemp&0xFF00)>>8);  
	usbSendBufdata[(*pDesLength)+6]  = (uint8_t)(stemp&0x00FF);	

	
  //USB_SendData(usbSendBuf,sizeof(usbSendBuf));
}

/*******************************函数声明****************************************
* 函数名称: void Parse_Pack_Data(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 将具体的数据包解析到相应的变量  
* 作    者: by 智御电子淘宝店店主 https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197aOrWx00&mytmenu=mdianpu&user_number_id=106855850
* 日    期: 2015/8/12
*******************************************************************************/ 
void Parse_Pack_Data(uint8_t *usbReceiveBufdata)
{
  
  relay1_status = usbReceiveBufdata[6];
  relay2_status = usbReceiveBufdata[7];
}

