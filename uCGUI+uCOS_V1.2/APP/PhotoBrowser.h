#ifndef _PhotoBrowser_h
#define _PhotoBrowser_h
#include "includes.h"
#include "My_UI.h"
#include "GUI.H"
#include "bmp.h"
#include "Fat_API.h"
extern u8 FileList[][30];//���֧��100���ļ�
extern char FilePath[];
extern u16 filecount;
extern u8 TouchFlag;

extern MenuInfo    OtherMenu_Info;
extern u8 Menu_ID;  //�˵������ID
extern SingleList  OtherMenu_pHead;    /* ��������Ŀؼ������ͷָ��      */
extern MenuInfo    OtherMenu_Info;
extern u8 TouchCmd;            //��־���ǵ㴥���ǻ���������
extern GUI_COLOR  ThemeColor;
extern GUI_COLOR  DesktopColor;
extern u8 MenuDisnable;
extern WM_HWIN hDesktopWindow; //����ľ��
#endif
