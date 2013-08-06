/**
  ******************************************************************************
  * @file   main.c 
  ******************************************************************************
  * @attention
	*
  * ����һ��ͨ��UI���򣬳���д���˳�������п�ܣ���ֻ��Ҫ�����ʵ���ɳ�Ϊ���Լ���UI����
	* ����uC/OS-IIʵ������Ĺ����򻯳���ṹ���ڴ˻���֮�ϣ������ʵ������Ҫ�Ĺ��ܣ�����MP3��������ͼƬ�������ʾ������Ƶ�׷����ǡ�������������������ֻ�����벻����û���������ģ�
	* ��������豸���߱����޵�UI���棨��Ȼ�Ƿ���Matro����ˣ�����ȫΪ���Ի�������
	* ȱ�㣺1)��Ҫ�ϴ��RAM��������Ҫ�������Ӧ�ô�С����ȡ�ᡣ
	        2)����Ĳ�����ʽ���ã���Ҫ�������Ӵ��졣����Ҫ��û��ʵ�尴����������ֻ��һ���ͻ�úܶ࣬����WP��3��������Android��Ҫ4������iphone������Ҫ���������أ�����
						��ȫ����������̫��ʵ�ַǳ��򵥵Ĳ���ģʽ��ֻ��������Ļ�ռ䣬ר������һ���������̶���ť��
						������һ�㣬ϣ������о�һ�£�����Լ��Ĵ��⡭��
	*
	*
	*                                ������--���ϴ���  ^_^
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Hardwear.h"
#include "Initialize.h"
#include "ff.h"
#include "includes.h"
#include "APP.h"
#include "bmp.h"
#include "delay.h"
#include "led.h"
#include "MusicPlayer.h"
#include "mylcd.h"
#include "BUTTON.H"
#include "wm.h"
#include "string.h"
void SysTick_Configuration(void);


/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
	
	
void delay_clk(u16 n)
{
	while(n){
			--n;
	}
}
#define bigger_stk_size 128
OS_STK  myTask_STK[bigger_stk_size];
void myTask(void *data)
{
	u8 cnt= 0;
	u16 x, y;
	U16 BUTTONsizeX = 50, BUTTONsizeY = 30;
	u16 x1 = 100, y1 = 100, x2 = 160, y2 = 160;
	u16 x3 = x1 + 100, y3 = y1 + 60, x4 = x2 + 100, y4 = y2 + 60;
	int key = 0;
	
	BUTTON_Handle hbutton;
		
  GUI_InvertRect(x1, y1, x2, y2);
	GUI_DrawCircle(x2+30, (y1+y2)/2, 30);
	
	
	LED0 = 0;
	
	hbutton = BUTTON_Create(x2+60, y2, BUTTONsizeX, BUTTONsizeY, GUI_ID_OK, WM_CF_SHOW);
	if(!hbutton){
			GUI_DispString("Button is not created!");	
	}
	else{
			GUI_DispString("Button is created!");	
	}
	BUTTON_SetBkColor(hbutton, 0, GUI_GREEN);
	BUTTON_SetBkColor(hbutton, 1, GUI_YELLOW);
	BUTTON_SetText(hbutton, "click!");
	WM_Paint(hbutton);
	//key = GUI_WaitKey();


	while(1)	{
		x = GUI_TOUCH_X_MeasureX();
		y = GUI_TOUCH_X_MeasureY();
		if(x > x1 && x < x2 && y > y1 && y < y2){
				LCD_ShowChar(x1, (y1 + y2) / 2 - 8, '0'+cnt++, 16, 0);
		}
		LED0 = ~LED0;
		//GUI_Delay(10);

		delay_ms(20);//delay_ms(200);
		GUI_Exec();
	}
	
}

OS_STK  myTask_STK2[bigger_stk_size];
void myTask2(void *data)
{
	LED1 = 0;
	while(1)
	{

		LED1 = !LED1;

		GUI_SetBkColor(GUI_BLUE);
		GUI_Clear();
	//GUI_Delay(10);
		GUI_SetFont(&GUI_Font32B_ASCII);
		GUI_DispString("How are you!");	

		GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
		//GUI_FillCircle(300, 64, 40);	
		delay_ms(500);
	}
	
}

OS_STK  TASK_START_STK[START_STK_SIZE];
void startTask(void *data)
{
		OSTaskCreate(myTask,	   //task pointer
					(void *)0,	       //parameter
					(OS_STK *)&myTask_STK[bigger_stk_size-1],//task stack top pointer
					3 ); //task priority
/*	delay_ms(100);
	OSTaskCreate(myTask2,	   //task pointer
					(void *)0,	       //parameter
					(OS_STK *)&myTask_STK2[bigger_stk_size-1],//task stack top pointer
					3 ); //task priority*/
	OSTaskDel(OS_PRIO_SELF);
	
}

void awindow(void *data)
{
	u16 x, y;
	U16 BUTTONsizeX = 100, BUTTONsizeY = 60;
	u16 x1 = 100, y1 = 100, x2 = 160, y2 = 160;
	u16 x3 = 160+100, y3 = 160+100, x4 = x3 + 40, y4 = y3 + 40;
	int key = 0;
	//WM_HWIN hwin = WM_CreateWindow(x1, y1, x3 - x1, y3 - y1, WM_CF_SHOW, 0, 0);
	BUTTON_Handle hbutton;
	WM_HWIN hDesktopWindow;	
	
	WM_SetDesktopColor(DesktopColor); 
	hDesktopWindow = WM_GetDesktopWindow();//��ȡ����ľ��
	
	GUI_SetBkColor(GUI_GREEN);
	GUI_Clear();
  //GUI_InvertRect(x1, y1, x2, y2);
	LED1 = 1;
	
	hbutton = BUTTON_Create(x1, y1, BUTTONsizeX, BUTTONsizeY, GUI_ID_OK, WM_CF_SHOW);
	if(!hbutton){
			GUI_DispString("Button is not created!");	
	}
	else{
			GUI_DispString("Button is created!");	
	}
	BUTTON_SetBkColor(hbutton, 0, GREEN);
	BUTTON_SetBkColor(hbutton, 1, YELLOW);
	BUTTON_SetText(hbutton, "click!");
	key = GUI_WaitKey();

	
	GUI_InvertRect(x3, y3, x4, y4);
	while(1)	{
		x = GUI_TOUCH_X_MeasureX();
		y = GUI_TOUCH_X_MeasureY();
		if(x > x3 && x < x4 && y > y3 && y < y4){
				LCD_ShowChar(x3, (y3 + y4) / 2 - 8, 'Y', 16, 0);
		}
		delay_ms(20);
	}
	
}
int main(void)
{
	SysTick_Configuration(); 
	delay_init();	
	MCU_Init();
	LED_Init();	
	
	//OSInit();    	 
	GUI_Init();	
	
	{

		LED0=0;
		LED1=0;
		delay_clk(60000);
	}	
  /* Add your application code here */

	GUI_SetBkColor(GUI_GREEN);
	GUI_SetColor(GUI_YELLOW);
	GUI_Clear();
	
/*		{
		FRAMEWIN_Handle hFrame;
		BUTTON_Handle hButton1;
		BUTTON_Handle hButton2;

		hFrame = FRAMEWIN_Create("test", 0, WM_CF_SHOW, 0, 0, 150, 150);
		WM_Paint(hFrame);
		hButton1 = BUTTON_CreateAsChild(50, 50, 60, 30, hFrame, 1, WM_CF_SHOW);
		BUTTON_SetText(hButton1, "1");
		WM_Paint(hButton1);
		hButton2 = BUTTON_CreateAsChild(50, 90, 60, 30, hFrame, 1, WM_CF_SHOW);
		BUTTON_SetText(hButton2, "2");
		WM_Paint(hButton2);
	}*/

	
	GUI_DispStringHCenterAt("Hello World!\n", 690, 10);	
	myTask(0);
	
	/*OSTaskCreate(startTask,	   //task pointer
					(void *)0,	       //parameter
					(OS_STK *)&TASK_START_STK[START_STK_SIZE-1],//task stack top pointer
					START_TASK_Prio ); //task priority
	
	OSStart();                 //��ʼ������ִ��*/
		
	return 0;	   
}

//ϵͳʱ������
void SysTick_Configuration(void)
{
 	SysTick->CTRL&=~(1<<2); //SYSTICKʹ���ⲿʱ��Դ
	SysTick->CTRL|=1<<1;    //����SYSTICK�ж�
	SysTick->LOAD=10000000/OS_TICKS_PER_SEC;  //��������Ƶ����80MHz������8��Ƶ��Ϊ10MHz
	SysTick->CTRL|=1<<0;    //����SYSTICK
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
