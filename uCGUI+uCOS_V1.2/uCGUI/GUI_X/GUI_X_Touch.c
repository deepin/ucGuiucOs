/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_TOUCH_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUI_X.h"
#include "Touch_s.h"
#include "touch.h"
extern u16 TP_X,TP_Y;

void GUI_TOUCH_X_ActivateX(void) 
{
}

void GUI_TOUCH_X_ActivateY(void) 
{
}

int  GUI_TOUCH_X_MeasureX(void) 
{
	unsigned int TX[5];
	unsigned char i = 0;
	u16 min,temp; //ʹ��ѡ������
	u8 k = 0;	
	TCS_0;
	for (i = 0;i <5 ;i++) {
		WriteCharTo7843(0xD0);        //�Ϳ����� 10010000 ���ò�ַ�ʽ��X���� ��ϸ����й�����
		DCLK_1; 
		delays(1);
		DCLK_0; 
		TX[i]=ReadFromCharFrom7843();	
	}
	TCS_1;
	for(i = 0;i < 5;i++) {	 
		min = i;  
		for(k = i+1;k != 5;k++){		
			if(TX[min] > TX[k])  		
			    min = k;
    }	   
		temp=TX[i];		    
		TX[i]=TX[min];	   
		TX[min]=temp;
	}
  return TX[2];
}

int  GUI_TOUCH_X_MeasureY(void) 
{
	int TY[5];
	unsigned char i = 0;
	u16 min,temp; //ʹ��ѡ������
	u8 k = 0;
	TCS_0;
	for (i = 0;i <5 ;i++) {
		WriteCharTo7843(0x90);        //�Ϳ����� 10010000 ���ò�ַ�ʽ��Y���� ��ϸ����й�����
		DCLK_1; 
		delays(1);
		DCLK_0; 
		TY[i]=ReadFromCharFrom7843();
  }
	TCS_1;
	for(i = 0;i < 5;i++) {	 
		min = i;  
		for(k = i+1;k != 5;k++){		
			if(TY[min] > TY[k])  		
			    min = k;
    }	   
		temp=TY[i];		    
		TY[i]=TY[min];	   
		TY[min]=temp;
	}
  return TY[2];
}


