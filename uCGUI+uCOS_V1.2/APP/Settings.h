#ifndef _Settings_h
#define _Settings_h
#include "stm32f10x.h"
#include "includes.h"
#include "GUI.H"
#include "My_UI.h"
#include "BUTTON.h"
#include "framewin.h"
#include "TEXT.h"
#include "WM.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"

extern const GUI_FONT GUI_FontHZ_MicrosoftFont_13;
extern const GUI_FONT GUI_FontHZ_YouYuan_24;

extern MenuInfo    OtherMenu_Info;
extern u8 Menu_ID;                      // �˵������ID
extern SingleList  OtherMenu_pHead;     // ��������Ŀؼ������ͷָ��
extern MenuInfo    OtherMenu_Info;
extern u8 TouchCmd;                     // ��־���ǵ㴥���ǻ���������
extern GUI_COLOR  ThemeColor;
extern GUI_COLOR  DesktopColor;
extern u8 MenuDisnable;

extern const GUI_BITMAP bmButtonBmp1_1bpp;
extern const GUI_BITMAP bmButtonBmp2_1bpp;

void Task_Setting(void *pdata);

#endif
