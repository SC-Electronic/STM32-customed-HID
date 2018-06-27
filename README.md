# STM32 Customed HID开发流程 #

### 本文介绍的是STM32的cubeMX自定义HID的开发流程 ###

***-----------------由淘宝店铺[“智御电子”](https://shop198134226.taobao.com/shop/view_shop.htm?spm=a313o.201708ban.0.d53.64f0197ah2lhTI&mytmenu=mdianpu&user_number_id=106855850)提供，以便电子爱好者交流学习。----------------***

1. cubeMX配置customed HID模式。更多详细配置壳查看代码CubeMX的配置文件。
![](https://i.imgur.com/msogLfc.png)
2. 修改usbd_custome_hid_if.c 里面的CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] 数组。根据填入的数组内容修改宏USBD_CUSTOM_HID_REPORT_DESC_SIZE尺寸为34

```
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
  
//#ifdef usga 
//0x05, 0x8c, /* USAGE_PAGE (ST Page) */ 
0x06, 0xFF, 0x00,      /* USAGE_PAGE (Vendor Page: 0xFF00) */                       
0x09, 0x01,            /* USAGE (Demo Kit)               */    
0xa1, 0x01, /* COLLECTION (Application) */ 
/* 6 */ 

// The Input report 
0x09,0x03, // USAGE ID - Vendor defined 
0x15,0x00, // LOGICAL_MINIMUM (0) 
0x26,0x00, 0xFF, // LOGICAL_MAXIMUM (255) 
0x75,0x08, // REPORT_SIZE (8) 
0x95,64, // REPORT_COUNT :SendLength 
0x81,0x02, // INPUT (Data,Var,Abs) 
//19
// The Output report 
0x09,0x04, // USAGE ID - Vendor defined 
0x15,0x00, // LOGICAL_MINIMUM (0) 
0x26,0x00,0xFF, // LOGICAL_MAXIMUM (255) 
0x75,0x08, // REPORT_SIZE (8) 
0x95,64, // REPORT_COUNT:ReceiveLength 
0x91,0x02, // OUTPUT (Data,Var,Abs) 
//32
// The Feature report

/* 45 */ 
0xc0 /* END_COLLECTION */ 
//#endif 
  
  /* USER CODE END 0 */  /*     END_COLLECTION	             */
};

```

3.修改usbd_customhid.c 中的如下数组.

```
__ALIGN_BEGIN static uint8_t USBD_CUSTOM_HID_CfgDesc[USB_CUSTOM_HID_CONFIG_DESC_SIZ] __ALIGN_END =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_CUSTOM_HID_CONFIG_DESC_SIZ,
  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xC0,         /*bmAttributes: bus powered */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/
  
  /************** Descriptor of CUSTOM HID interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x02,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: CUSTOM_HID*/
  0x00,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x00,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of CUSTOM_HID *************************/
  /* 18 */
  0x09,         /*bLength: CUSTOM_HID Descriptor size*/
  CUSTOM_HID_DESCRIPTOR_TYPE, /*bDescriptorType: CUSTOM_HID*/
  0x11,         /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  USBD_CUSTOM_HID_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of Custom HID endpoints ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/
  
  CUSTOM_HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  CUSTOM_HID_EPIN_SIZE, /*wMaxPacketSize: 2 Byte max */
  0x00,
  0x05,          /*bInterval: Polling Interval (5ms)*/ //这边修改的是IN通信的速率，数值越小，速率越快。最快1000hz。
  /* 34 */
  
  0x07,	         /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,	/* bDescriptorType: */
  CUSTOM_HID_EPOUT_ADDR,  /*bEndpointAddress: Endpoint Address (OUT)*/
  0x03,	/* bmAttributes: Interrupt endpoint */
  CUSTOM_HID_EPOUT_SIZE,	/* wMaxPacketSize: 2 Bytes max  *///这边修改的是OUT通信的速率，数值越小，速率越快。最快1000hz。
  0x00,
  0x05,	/* bInterval: Polling Interval (5 ms) */
  /* 41 */
} ;

/* USB CUSTOM_HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_CUSTOM_HID_Desc[USB_CUSTOM_HID_DESC_SIZ] __ALIGN_END =
{
  /* 18 */
  0x09,         /*bLength: CUSTOM_HID Descriptor size*/
  CUSTOM_HID_DESCRIPTOR_TYPE, /*bDescriptorType: CUSTOM_HID*/
  0x11,         /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  USBD_CUSTOM_HID_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
};
``` 

5.修改

```
   #define CUSTOM_HID_EPIN_SIZE                 0x40
   #define CUSTOM_HID_EPOUT_SIZE                0x40
   #define USBD_CUSTOMHID_OUTREPORT_BUF_SIZE     64
   #define USBD_CUSTOM_HID_REPORT_DESC_SIZE      34
```

6.这个时候全局编译，下载程序到控制板。接着将控制板USB查到PC电脑端，顺利的话会看到“设备管理器”里面的“人体输入学设备”识别到了“hid-compliant device”。

好！到此为止说明我们的USB HID枚举部分修改成功。下面进行发送和接收的操作。

7.发送数据

发送数据包是最简单的，只要调用`USBD_CUSTOM_HID_SendReport`函数即可。

8.接收数据

接收数据相对发送要复杂一点。HAL库已经封装了底层的接收数据处理，所以用户主要知道：当芯片完成一组数据接收的时候，中断会调用`CUSTOM_HID_OutEvent_FS`这样一个回调函数。那本文就在这个回调函数里面设置了一个falg。如下：

```
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
	//flag设置成SET，代表有数据到来
	USB_Out_Flag=SET;
  return (USBD_OK);
  /* USER CODE END 6 */
}
```

而在main主循环函数中，我实时判断这个flag是否set了。如果set了就表示中断接收到一组数据，然后我们就可以读数据了。本文读数据函数如下：

```
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
```

9.到此，自定义HID基本讲解完毕，本文在main函数中实现一个USB_Mission应用。大体思路如下：判断有没有上位机发送过来的数据，如果有则解码数据，根据解析的数据回送上位机需要的数据。详情请查看代码。完整的代码[GitHub地址](https://github.com/SC-Electronic/STM32-customed-HID.git)。

