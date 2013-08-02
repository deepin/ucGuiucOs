#include "gt811.h"
#include "ctiic.h"
#include "usart.h"
#include "delay.h"	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//7����ݴ���������-GT811����	  
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2013/3/17
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved	
//********************************************************************************
//��
//////////////////////////////////////////////////////////////////////////////////	 

//���ݴ�����������

void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM)
{
    u8 EXTADDR;
    u8 EXTOFFSET;
    EXTADDR = BITx/4;                  
    EXTOFFSET = (BITx%4)*4;            
    RCC->APB2ENR |= 0x01;              
    AFIO->EXTICR[EXTADDR] |= GPIOx << EXTOFFSET;
    //????
    EXTI->IMR |= 1<<BITx;              
    //EXTI->EMR|=1<<BITx;//???line BITx???? (???????,????????,????????????????!)
    if(TRIM & 0x01) EXTI->FTSR |= 1<<BITx;   
    if(TRIM & 0x02) EXTI->RTSR |= 1<<BITx;   
}

void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group) {
u32 temp, temp1;

temp1=(~NVIC_Group)&0x07;//???? temp1<<=8;

temp=SCB->AIRCR; //??????? temp&=0X0000F8FF; //?????? temp|=0X05FA0000; //???? temp|=temp1;

SCB->AIRCR=temp; //???

}
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;	
	u8 IPRADDR=NVIC_Channel/4;  //ÿ��ֻ�ܴ�4��,�õ����ַ 
	u8 IPROFFSET=NVIC_Channel%4;//�����ڵ�ƫ��
	IPROFFSET=IPROFFSET*8+4;    //�õ�ƫ�Ƶ�ȷ��λ��
	MY_NVIC_PriorityGroupConfig(NVIC_Group);//���÷���
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;//ȡ����λ

	if(NVIC_Channel<32)NVIC->ISER[0]|=1<<NVIC_Channel;//ʹ���ж�λ(Ҫ����Ļ�,�෴������OK)
	else NVIC->ISER[1]|=1<<(NVIC_Channel-32);    
	NVIC->IP[IPRADDR]|=temp<<IPROFFSET;//������Ӧ���ȼ����������ȼ�   	    	  				   
}

_m_ctp_dev ctp_dev=
{
	GT811_Init,
	GT811_Scan,
	0,
	0,
	0,
	0,
};	  																				   
//���������ò���(�����������ṩ)
const u8 GTP_CFG_DATA[]=
{
    0x12,0x10,0x0E,0x0C,0x0A,0x08,0x06,0x04,0x02,0x00,0x05,0x55,0x15,0x55,0x25,0x55,
    0x35,0x55,0x45,0x55,0x55,0x55,0x65,0x55,0x75,0x55,0x85,0x55,0x95,0x55,0xA5,0x55,
    0xB5,0x55,0xC5,0x55,0xD5,0x55,0xE5,0x55,0xF5,0x55,0x1B,0x03,0x00,0x00,0x00,0x13,
    0x13,0x13,0x0F,0x0F,0x0A,0x50,0x30,0x05,0x03,0x64,0x05,0xe0,0x01,0x20,0x03,0x00,
    0x00,0x32,0x2C,0x34,0x2E,0x00,0x00,0x04,0x14,0x22,0x04,0x00,0x00,0x00,0x00,0x00,
    0x20,0x14,0xEC,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x30,
    0x25,0x28,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x01, 
};	 

//�������жϴ���
void EXTI15_10_IRQHandler(void)
{
 	if(CT_INT==0)	 //�д����ж�
	{				  
		ctp_dev.tpsta|=0X80;//�������Ч����
	}		 
	EXTI->PR=1<<10;  //���LINE10�ϵ��жϱ�־λ  	   
} 
//��GT811д��һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:д���ݳ���
//����ֵ:0,�ɹ�;1,ʧ��.
u8 GT811_WR_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i;
	u8 ret=0;
	CT_IIC_Start();	
 	CT_IIC_Send_Byte(CT_CMD_WR);   	//����д���� 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8);   	//���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
    	CT_IIC_Send_Byte(buf[i]);  	//������
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
    CT_IIC_Stop();					//����һ��ֹͣ����	    
	return ret; 
}
//��GT811����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���			  
void GT811_RD_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i;
 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(CT_CMD_WR);   	//����д���� 	 
	CT_IIC_Wait_Ack();
 	CT_IIC_Send_Byte(reg>>8);   	//���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(CT_CMD_RD);    //���Ͷ�����		   
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //������	  
	} 
    CT_IIC_Stop();//����һ��ֹͣ����	    
}
//��GT811�������ò���
//buf:���ò�����ָ��
//cfg_len:���ò�������
//����ֵ:0,�ɹ�;1,ʧ��.
u8 GT811_Send_Cfg(u8 * buf,u16 cfg_len)
{
	u8 ret=0;
	u8 retry=0;
	for(retry=0;retry<5;retry++)
	{
		ret=GT811_WR_Reg(CT_CONFIG_REG,buf,cfg_len);
		if(ret==0)break;
		delay_ms(10);	 
	}
	return ret;
}
//GT811����
void GT811_Wakeup_Sleep(void)
{
	CT_RST=0;	//��λ
	delay_ms(10);
 	CT_RST=1;	//�ͷŸ�λ		    
	delay_ms(100);
}	    
//GT811��ʼ��
//����ֵ:��ʼ�����
//0,��ʼ���ɹ�;
//1,�������ò�������
//2,�汾����

#define EXTI15_10_IRQChannel         ((u8)0x28)  /* External Line[15:10] Interrupts */

u8 GT811_Init(void)
{
 	u16 version=0;
	u8 temp;
 	RCC->APB2ENR|=1<<3;		//��ʹ������IO PORTBʱ�� 							 
 	RCC->APB2ENR|=1<<7;		//��ʹ������IO PORTFʱ�� 							 
	GPIOB->CRL&=0XFFFFF0FF;	//PB2 �������
	GPIOB->CRL|=0X00000300;	   
	GPIOB->ODR|=1<<2;	    //PB2 �����
	GPIOF->CRH&=0XFFFFF0FF;	//PF10 ����
	GPIOF->CRH|=0X00000800;	   
	GPIOF->ODR|=1<<10;	   	//PF10 ����	  
 	Ex_NVIC_Config(GPIO_F,10,FTIR); 			//�½��ش���		   
	MY_NVIC_Init(3,3,EXTI15_10_IRQChannel,2);	//��ռ3�������ȼ�3����2	  									   								
 	CT_IIC_Init();								//���ݴ���������,IIC��ʼ��
	GT811_Wakeup_Sleep(); 						//����GT811 
  	GT811_RD_Reg(0X717,&temp,1);				//��ȡ�汾�߰�λ
	version=(u16)temp<<8; 
	GT811_RD_Reg(0X718,&temp,1);				//��ȡ�汾�Ͱ�λ  
	version|=temp;
	printf("version:%x\r\n",version); 
	if(version==0X2010)							//�汾��ȷ,�������ò���
	{ 
		temp=GT811_Send_Cfg((u8*)GTP_CFG_DATA,sizeof(GTP_CFG_DATA));//�������ò���
	}else temp=2;	//�汾����
	return temp;   
}	   
//ɨ��GT811
//�õ��Ľ��������ctp_dev�ṹ����								   									 
void GT811_Scan(void)
{			   
	u8 buf[34];//һ�ζ�ȡ34�ֽ�
	if((ctp_dev.tpsta&0X80)==0)return;			//����Ч����,���ȡ����,����ֱ���˳�
  	GT811_RD_Reg(CT_READ_XY_REG,buf,34);		//һ�ζ�ȡ34���ֽ�
	ctp_dev.tpsta=buf[0]&0X1F;					//��������λ,ͬʱ�����Ч�������
#if CT_EXCHG_XY==1								//��תXY
	ctp_dev.y[0]=480-(((u16)buf[2]<<8)+buf[3]);	//������0����
	ctp_dev.x[0]=((u16)buf[4]<<8)+buf[5];	  
	ctp_dev.ppr[0]=buf[6];	 
	ctp_dev.y[1]=480-(((u16)buf[7]<<8)+buf[8]);	//������1����
	ctp_dev.x[1]=((u16)buf[9]<<8)+buf[10];	  
	ctp_dev.ppr[1]=buf[11];
	ctp_dev.y[2]=480-(((u16)buf[12]<<8)+buf[13]);//������2����
	ctp_dev.x[2]=((u16)buf[14]<<8)+buf[15];	  
	ctp_dev.ppr[2]=buf[16];					   
	ctp_dev.y[3]=480-(((u16)buf[17]<<8)+buf[24]);//������3����
	ctp_dev.x[3]=((u16)buf[25]<<8)+buf[26];	  
	ctp_dev.ppr[3]=buf[27];
	ctp_dev.y[4]=480-(((u16)buf[28]<<8)+buf[29]);//������4����
	ctp_dev.x[4]=((u16)buf[30]<<8)+buf[31];	  
	ctp_dev.ppr[4]=buf[32];
#else 
	ctp_dev.y[0]=((u16)buf[2]<<8)+buf[3];		//������0����
	ctp_dev.x[0]=800-(((u16)buf[4]<<8)+buf[5]);	  
	ctp_dev.ppr[0]=buf[6];	 
	ctp_dev.y[1]=((u16)buf[7]<<8)+buf[8];		//������1����
	ctp_dev.x[1]=800-(((u16)buf[9]<<8)+buf[10]);	  
	ctp_dev.ppr[1]=buf[11];
	ctp_dev.y[2]=((u16)buf[12]<<8)+buf[13];		//������2����
	ctp_dev.x[2]=800-(((u16)buf[14]<<8)+buf[15]);	  
	ctp_dev.ppr[2]=buf[16];					   
	ctp_dev.y[3]=((u16)buf[17]<<8)+buf[24];		//������3����
	ctp_dev.x[3]=800-(((u16)buf[25]<<8)+buf[26]);	  
	ctp_dev.ppr[3]=buf[27];
	ctp_dev.y[4]=((u16)buf[28]<<8)+buf[29];		//������4����
	ctp_dev.x[4]=800-(((u16)buf[30]<<8)+buf[31]);	  
	ctp_dev.ppr[4]=buf[32];
#endif	 		    
}




















