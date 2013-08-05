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

void SysTick_Configuration(void);
OS_STK  TASK_START_STK[START_STK_SIZE];

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
#define bigger_stk_size 128
OS_STK  deadloopTask_STK[bigger_stk_size];
void deadloopTask(void *data)
{
	delay_init();	    	 
 	LED_Init();			     //LED
	LED0 = 0;
	GUI_Init();
	while(1)
	{

		LED0 = !LED0;

		GUI_SetBkColor(GUI_BLUE);
		GUI_Clear();
	//GUI_Delay(10);
		GUI_SetFont(&GUI_Font32B_ASCII);
		GUI_DispString("Hello World!");	
			//printf("string by printf!");

		GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
		//GUI_FillCircle(300, 64, 40);	
		delay_ms(500);
	}
	
}

OS_STK  deadloopTask_STK2[bigger_stk_size];
void deadloopTask2(void *data)
{
	delay_init();	    	 
 	LED_Init();			     //LED
	GUI_Init();
	while(1)
	{

		LED1 = !LED1;

		GUI_SetBkColor(GUI_BLUE);
		GUI_Clear();
	//GUI_Delay(10);
		GUI_SetFont(&GUI_Font32B_ASCII);
		//GUI_DispString("Hello World!");	
			//printf("string by printf!");

		GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
		//GUI_FillCircle(300, 64, 40);	
		delay_ms(500);
	}
	
}
void startTask(void *data)
{
		OSTaskCreate(deadloopTask,	   //task pointer
					(void *)0,	       //parameter
					(OS_STK *)&deadloopTask_STK[bigger_stk_size-1],//task stack top pointer
					4 ); //task priority
	delay_ms(100);
	OSTaskCreate(deadloopTask2,	   //task pointer
					(void *)0,	       //parameter
					(OS_STK *)&deadloopTask_STK2[bigger_stk_size-1],//task stack top pointer
					3 ); //task priority
}

int main(void)
{
  /* Add your application code here */
	MCU_Init();
	SysTick_Configuration(); 
	OSInit();
	
		delay_init();	    	 
	GUI_Init();
			//GUI_SetBkColor(GUI_BLUE);
		GUI_Clear();
	
	
	OSTaskCreate(TaskStart,	   //task pointer
					(void *)0,	       //parameter
					(OS_STK *)&TASK_START_STK[START_STK_SIZE-1],//task stack top pointer
					START_TASK_Prio ); //task priority
	OSStart();                 //��ʼ������ִ��
		
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
