#include "usbd_pack.h"
#include "usb_device.h"
#include "usbd_customhid.h"
#include "crc16.h"
#include "protocol.h"
#include "adc_dma.h"

extern FlagStatus USB_Out_Flag;

/**
  * @brief  ���մ�USB��ȡ������
  * @param  data ���ݴ洢�׵�ַ
  * @param  dataNum ׼����ȡ�������ֽ���
  * @retval ��ȡ���ֽ���
  */
uint32_t USB_GetData(uint8_t *data,uint32_t dataNum)
{
    uint32_t len=0;
	USBD_CUSTOM_HID_HandleTypeDef	*hhid;
  hhid = (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDeviceFS.pClassData;//�õ����յĵ�ַ
	
	for(len=0;len<dataNum;len++){
		*data=hhid->Report_buf[len];
		data++;
	}
    return dataNum;
}

/**
  * @brief  ͨ��USB��������
  * @param  data ���ݴ洢�׵�ַ
  * @param  dataNum ���͵������ֽ���
  * @retval ���͵��ֽ���
  */
void USB_SendData(uint8_t *data,uint32_t dataNum)
{
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, data, dataNum);
}

/*ʾ��Ӧ�ã�������Լ�������и���*/
void USB_Mission(void)
{
	uint8_t usbReceiveBuf[64]= {0x00};
	static uint8_t usbSendBuf[64]= {0x00};
	static uint8_t usbSendVaildLength=0;
  //1.�ж��Ƿ���յ�out���ݰ�
	if(USB_Out_Flag==SET)
	{
  //2.׼��IN���ݰ�
	 USB_Out_Flag=RESET;
		/*��ȡ���ݰ�*/
	 USB_GetData(usbReceiveBuf,sizeof(usbReceiveBuf));
		if(usbReceiveBuf[0])
		{
			memset(usbSendBuf,0,sizeof(usbSendBuf));
			switch(usbReceiveBuf[5])
				{
				  case 0xc1:
					{		
                  /*�������͵����ݰ�*/									
									Update_ADC_Value(usbSendBuf,&usbSendVaildLength);
									//3.��������	
									USB_SendData(usbSendBuf,sizeof(usbSendBuf));
								}
								break;

								default :
									break;

								}
						}
	}
	
}

