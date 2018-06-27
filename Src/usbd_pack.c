#include "usbd_pack.h"
#include "usb_device.h"
#include "usbd_customhid.h"
#include "crc16.h"
#include "protocol.h"
#include "adc_dma.h"

extern FlagStatus USB_Out_Flag;

/**
  * @brief  接收从USB获取的数据
  * @param  data 数据存储首地址
  * @param  dataNum 准备读取的数据字节数
  * @retval 读取的字节数
  */
uint32_t USB_GetData(uint8_t *data,uint32_t dataNum)
{
    uint32_t len=0;
	USBD_CUSTOM_HID_HandleTypeDef	*hhid;
  hhid = (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDeviceFS.pClassData;//得到接收的地址
	
	for(len=0;len<dataNum;len++){
		*data=hhid->Report_buf[len];
		data++;
	}
    return dataNum;
}

/**
  * @brief  通过USB发送数据
  * @param  data 数据存储首地址
  * @param  dataNum 发送的数据字节数
  * @retval 发送的字节数
  */
void USB_SendData(uint8_t *data,uint32_t dataNum)
{
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, data, dataNum);
}

/*示意应用，请根据自己需求进行更改*/
void USB_Mission(void)
{
	uint8_t usbReceiveBuf[64]= {0x00};
	static uint8_t usbSendBuf[64]= {0x00};
	static uint8_t usbSendVaildLength=0;
  //1.判断是否接收到out数据包
	if(USB_Out_Flag==SET)
	{
  //2.准备IN数据包
	 USB_Out_Flag=RESET;
		/*读取数据包*/
	 USB_GetData(usbReceiveBuf,sizeof(usbReceiveBuf));
		if(usbReceiveBuf[0])
		{
			memset(usbSendBuf,0,sizeof(usbSendBuf));
			switch(usbReceiveBuf[5])
				{
				  case 0xc1:
					{		
                  /*填充待发送的数据包*/									
									Update_ADC_Value(usbSendBuf,&usbSendVaildLength);
									//3.发送数据	
									USB_SendData(usbSendBuf,sizeof(usbSendBuf));
								}
								break;

								default :
									break;

								}
						}
	}
	
}

