#include "gui.h"
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


void ShowColorBar(void)
{
	int x0 = 60, y0 = 40, yStep = 25,i;
	int NumColors = LCD_GetDevCap(LCD_DEVCAP_NUMCOLORS);
	int xsize = LCD_GetDevCap(LCD_DEVCAP_XSIZE) - x0;
	u16 x, cs;
	GUI_SetFont(&GUI_Font13HB_1);
	GUI_DispStringHCenterAt("ucGui - sample: show color bars", 160, 0);
	GUI_SetFont((&GUI_Font32B_ASCII));
	GUI_SetColor(GUI_BLACK);
	GUI_SetBkColor(GUI_WHITE);
	#if(LCD_FIXEDPALETTE)
		GUI_DispString("fixed palette: ");
		GUI_DispDecMin(LCD_FIXEDPALETTE);
	#endif
	GUI_DispStringAt("Red", 0, y0 + yStep);
	GUI_DispStringAt("Green", 0, y0 + 3*yStep);
	GUI_DispStringAt("Blue", 0, y0 + 5*yStep);
	GUI_DispStringAt("Grey", 0, y0 + 6*yStep);
	GUI_DispStringAt("Yellow", 0, y0 + 8*yStep);
	GUI_DispStringAt("Cyan", 0, y0 + 10*yStep);
	GUI_DispStringAt("Magenta", 0, y0 + 12*yStep);
	for(i = 0; i < xsize; ++i){
			cs = (255*(u32)i)/ xsize;
			x = x0 + i;
		GUI_SetColor(cs);
		GUI_DrawVLine(x, y0, y0+yStep  -1);
		GUI_SetColor(0xff + (255-cs)*0x10100L);
		GUI_DrawVLine(x, y0+yStep, y0+2*yStep  -1);
		
		GUI_SetColor(cs<<8);
		GUI_DrawVLine(x, y0+2*yStep, y0+3*yStep  -1);
		GUI_SetColor(0xff + (255-cs)*0x10001L);
		GUI_DrawVLine(x, y0+3*yStep, y0+4*yStep  -1);

		GUI_SetColor(cs*0x10000);
		GUI_DrawVLine(x, y0+4*yStep, y0+5*yStep  -1);
		GUI_SetColor(0xff + (255-cs)*0x101L);
		GUI_DrawVLine(x, y0+5*yStep, y0+6*yStep  -1);
		
		GUI_SetColor(cs*0x10101);
		GUI_DrawVLine(x, y0+6*yStep, y0+7*yStep  -1);
		
		GUI_SetColor(cs*0x101);
		GUI_DrawVLine(x, y0+7*yStep, y0+8*yStep  -1);
		GUI_SetColor(0xff + (255-cs)*0x10000L);
		GUI_DrawVLine(x, y0+8*yStep, y0+9*yStep  -1);
		
		GUI_SetColor(cs*0x10100);
		GUI_DrawVLine(x, y0+9*yStep, y0+10*yStep  -1);
		GUI_SetColor(0xff + (255-cs)*0x1L);
		GUI_DrawVLine(x, y0+10*yStep, y0+11*yStep  -1);
		
		GUI_SetColor(cs*0x10001);
		GUI_DrawVLine(x, y0+11*yStep, y0+12*yStep  -1);
		GUI_SetColor(0xff + (255-cs)*0x1L);
		GUI_DrawVLine(x, y0+12*yStep, y0+13*yStep  -1);
	}
}
#include "GUI.h"
#include "GUI_X.h"
#include "mylcd.h"
void main(void)
{
	u16 x, y;
	u8 cnt = 0;
	delay_init();
	MCU_Init();
	GUI_Init();
	ShowColorBar();
	
	GUI_DrawVLine(600, 0, 400);
	GUI_InvertRect(720-30, 240-30, 720+30, 240+30);
	GUI_DrawVLine(400, 0, 480);
	
	while(1){
		delay_ms(50);	
		x = GUI_TOUCH_X_MeasureX();
		y = GUI_TOUCH_X_MeasureY();
		if(x > 720 - 30 && x < 720 + 30 && y > 240 - 30 && y < 240 + 30){
				LCD_ShowChar(720, 240 - 8, 'A'+cnt++, 16, 0);
		}
		else{
				LCD_ShowChar(720, 240 - 8, 'A'+(--cnt), 16, 0);
		}
	}
}