#include "Touch_s.h"

u16 TP_X,TP_Y;		   
/****************************˵��************************/
//�����ԣ��������Ľ�����ֵ��x,y���ֱ��ǣ�
//���ϣ���130,115 �� ���ϣ���1880,115 ��
//���£���130,1850�� ���£���1880,1850��
//ɽկͼ����ױ�Y=1990
void delays(u16 d)
{
 while(d--);
}
void Touch_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  |
								                GPIO_Pin_1  |
								                GPIO_Pin_2  ;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   // ����������50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;	      
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //���ÿ�©����
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

//**********************************************************
void WriteCharTo7843(u8 num)          //SPIд����
{
u8 count=0;
DCLK_0;
for(count=0;count<8;count++)
{
if((num&0x80)==0x00)
DIN_0;
else
DIN_1;
num<<=1;                //��������Ч
DCLK_0;                 //��������Ч
delays(1);
DCLK_1; 
}
}
//**********************************************************
u16 ReadFromCharFrom7843(void)             //SPI ������
{
u8 count=0;
u16 Num=0;
for(;count<12;count++)
{
Num<<=1;
DCLK_1;
delays(1);
DCLK_0;
if(DOUT!=0) 
Num++;
}
return(Num);
}
