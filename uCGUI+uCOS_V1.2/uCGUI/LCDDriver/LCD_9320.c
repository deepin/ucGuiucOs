#include "LCD_9320.H"	   

#define LCD_WriteReg        Init_data
#define Lcd_Write_Com_Data  Init_data	
#define LCD_WR_CMD          LCD_WriteReg

u16 ABS(s16 a)//��ȡ����ֵ
{
   if(a<0)
   a=-a;
   return (u16)a;
}
void LCD9320_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE , ENABLE); 	 	
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |  GPIO_Pin_11 |GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;  //RESET=0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
//   GPIO_SetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_4);  
//   GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10); 
//   GPIO_ResetBits(GPIOE, GPIO_Pin_0);
//   GPIO_ResetBits(GPIOE, GPIO_Pin_1);		//RESET=0	 
}
//===============================================================
//д��������
void Init_data(u16 X,u16 Y)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= X;	
	*(__IO uint16_t *) (Bank1_LCD_D)= Y;
}
//====================== д���� ==========================//
void Write_COM(u16 CMD)
{
*(__IO uint16_t *) (Bank1_LCD_C)= CMD;
}
//===================== д���� ===========================//
void Write_DATA(u16 shuju)
{
	*(__IO uint16_t *) (Bank1_LCD_D)= shuju;
}
u16 LCD_RD_data(void)
{
	u16 a=0;
	a=*(__IO uint16_t *) (Bank1_LCD_D); //Dummy
	a=*(__IO uint16_t *) (Bank1_LCD_D); //L
	return(a);	
}

void ili9320_Initializtion(void)
{
	ili9320_Init();
}
void ili9320_Init(void)
{	
	RES_0;	
	delayms(1000);	
	RES_1;	
	delayms(50);     
	LCD_WriteReg(0x0000,0x0001); 
	delayms(50); // LCD_Delay 50 ms 
        
	LCD_WriteReg(0x00,0x0000);    
	LCD_WriteReg(0x01,0x0100);  //Driver Output Contral.     
	LCD_WriteReg(0x02,0x0700);  //LCD Driver Waveform Contral.     
	LCD_WriteReg(0x03,0x1030);//Entry Mode Set.     
	//LCD_WriteReg(0x03,0x1018);    //Entry Mode Set.        
	LCD_WriteReg(0x04,0x0000);  //Scalling Contral.       
	LCD_WriteReg(0x08,0x0202);  //Display Contral 2.(0x0207)       
	LCD_WriteReg(0x09,0x0000);  //Display Contral 3.(0x0000)       
	LCD_WriteReg(0x0a,0x0000);  //Frame Cycle Contal.(0x0000)      
	LCD_WriteReg(0x0c,(1<<0));  //Extern Display Interface Contral 1.(0x0000)		
	LCD_WriteReg(0x0d,0x0000);  //Frame Maker Position.		
	LCD_WriteReg(0x0f,0x0000);  //Extern Display Interface Contral 2.       
  delayms(50);  	
	LCD_WriteReg(0x07,0x0101);  //Display Contral.
	delayms(50);                                
	LCD_WriteReg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4)); //Power Control 1.(0x16b0)
	LCD_WriteReg(0x11,0x0007);                              //Power Control 2.(0x0001)
	LCD_WriteReg(0x12,(1<<8)|(1<<4)|(0<<0));                //Power Control 3.(0x0138)
	LCD_WriteReg(0x13,0x0b00);                              //Power Control 4.
	LCD_WriteReg(0x29,0x0000);                              //Power Control 7.
	
	LCD_WriteReg(0x2b,(1<<14)|(1<<4));      
	LCD_WriteReg(0x50,0);   //Set X Star
	//ˮƽGRAM��ֹλ��Set X End.
	LCD_WriteReg(0x51,239); //Set Y Star
	LCD_WriteReg(0x52,0);   //Set Y End.t.
	LCD_WriteReg(0x53,319); //
	
	LCD_WriteReg(0x60,0x2700);  //Driver Output Control.
	LCD_WriteReg(0x61,0x0001);  //Driver Output Control.
	LCD_WriteReg(0x6a,0x0000);  //Vertical Srcoll Control.
	
	LCD_WriteReg(0x80,0x0000);  //Display Position? Partial Display 1.
	LCD_WriteReg(0x81,0x0000);  //RAM Address Start? Partial Display 1.
	LCD_WriteReg(0x82,0x0000);  //RAM Address End-Partial Display 1.
	LCD_WriteReg(0x83,0x0000);  //Displsy Position? Partial Display 2.
	LCD_WriteReg(0x84,0x0000);  //RAM Address Start? Partial Display 2.
	LCD_WriteReg(0x85,0x0000);  //RAM Address End? Partial Display 2.
	
	LCD_WriteReg(0x90,(0<<7)|(16<<0));  //Frame Cycle Contral.(0x0013)
	LCD_WriteReg(0x92,0x0000);  //Panel Interface Contral 2.(0x0000)
	LCD_WriteReg(0x93,0x0001);  //Panel Interface Contral 3.
	LCD_WriteReg(0x95,0x0110);  //Frame Cycle Contral.(0x0110)
	LCD_WriteReg(0x97,(0<<8));  //
	LCD_WriteReg(0x98,0x0000);  //Frame Cycle Contral.     
	LCD_WriteReg(0x07,0x0173);  //(0x0173) 
  delayms(50);			 
}

 void Address_set(u16 x1,u16 y1,u16 x2,u16 y2)
{
	  Write_COM(0x0020);Write_DATA(x1);	//����X����λ��
    Write_COM(0x0021);Write_DATA(y1); //����Y����λ��
    Write_COM(0x0050);Write_DATA(x1); //��ʼX
	  Write_COM(0x0052);Write_DATA(y1);	//��ʼY
    Write_COM(0x0051);Write_DATA(x2); //����X
	  Write_COM(0x0053);Write_DATA(y2); //����Y
    Write_COM(0x0022);							 
}
/************************����һ�����ص�*****************************/
void Draw_Pixel(u16 x,u16 y,u16 color)
{ 
  *(__IO uint16_t *) (Bank1_LCD_C)= 32;	
  *(__IO uint16_t *) (Bank1_LCD_D)= x;
  *(__IO uint16_t *) (Bank1_LCD_C)= 33;	
  *(__IO uint16_t *) (Bank1_LCD_D)= y;
  *(__IO uint16_t *) (Bank1_LCD_C)= 34;	
  *(__IO uint16_t *) (Bank1_LCD_D)= color;
}
/****************************************************************************
* ��    �ƣ�u16 ili9320_GetPoint(u16 x,u16 y)
* ��    �ܣ���ȡָ���������ɫֵ
* ��ڲ�����x      ������
*           y      ������
* ���ڲ�������ǰ������ɫֵ
****************************************************************************/
u16 ili9320_GetPoint(u16 x,u16 y)
{ 
  *(__IO uint16_t *) (Bank1_LCD_C)= 32;
  *(__IO uint16_t *) (Bank1_LCD_D)= x;
  *(__IO uint16_t *) (Bank1_LCD_C)= 33;
  *(__IO uint16_t *) (Bank1_LCD_D)= y;
  *(__IO uint16_t *) (Bank1_LCD_C)= 34;
  return (ili9320_BGR2RGB(LCD_RD_data()));
	//return (LCD_RD_data());
}
/*************************��һ����****************************
���迼�Ƿ���
**/
void draw_hline(s16 x0,s16 x1,u16 y,u16 color)
{
   u16 f;
   if(x0>x1)
   Address_set(x1,y,x0,y);
   else
   Address_set(x0,y,x1,y);
   for(f=0;f<(ABS(x1-x0)+1);f++)
   Write_DATA(color);
}
/*************************��һ��ֱ��***************************
 ���迼�Ƿ���
*/
void draw_vline(s16 y0,s16 y1,u16 x,u16 color)
{
   u16 f;
   if(y0>y1)
   Address_set(x,y1,x,y0);
   else
   Address_set(x,y0,x,y1);
   for(f=0;f<(ABS(y1-y0)+1);f++)
   Write_DATA(color);
}  
void delayms(u16 count)
{
    u16 j;                                                                                
    for(;count>0;count--)                                                                   
	  for(j=0;j<500;j++);                                                                                    
}

/****************************************************************************
* ��    �ƣ�u16 ili9320_BGR2RGB(u16 c)
* ��    �ܣ�RRRRRGGGGGGBBBBB ��Ϊ BBBBBGGGGGGRRRRR ��ʽ
* ��ڲ�����c      BRG ��ɫֵ
* ���ڲ�����RGB ��ɫֵ
* ˵    �����ڲ���������
* ���÷�����
****************************************************************************/
u16 ili9320_BGR2RGB(u16 c)
{
  u16  r, g, b;

  b =  c  & 0x1f;
  g = (c>>5)  & 0x3f;
  r = (c>>11) & 0x1f;
  
  return( (b<<11) | (g<<5) | r );
}
