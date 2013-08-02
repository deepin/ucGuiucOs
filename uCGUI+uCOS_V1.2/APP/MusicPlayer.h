#ifndef _MusicPlayer_h
#define _MusicPlayer_h

#include "stm32f10x.h"
#include "includes.h"
#include "GUI.H"
#include "My_UI.h"
#include "BUTTON.h"
#include "progbar.h"
#include "framewin.h"
#include "TEXT.h"
#include "WM.h"
#include "LISTBOX.h"
#include "MENU.h"
#include "Fat_API.h"


#define PlaySong_STK_SIZE      128      //���ֲ���������
#define PlaySong_TASK_Prio     5        //���ֲ���������

typedef struct {	
// 	u8 Artist[20];
// 	u16 Bitrate;
// 	u16 Frequency;//�����ʡ�������
// 	u16 PlayTime;
	u8  NowPlayNum;
	u8  TotalNum;
	u8  PlayFlag;
	u32 PlaySize;
	u32 TotalSize;
	u16 DecodeTime;
	char MusicName[30];
}MusicInfo;  
 
typedef struct {
    u8  SetFlag;
	u8  Vol;
	u8  EQ;
	u8  Display;
}MusicPlayerInfo;
 
extern const GUI_FONT GUI_FontHZ_MicrosoftFont_13;
extern const GUI_FONT GUI_FontHZ_YouYuan_24;

extern u8 SD_Buffer[BufferSize];
extern const GUI_BITMAP bmmusicbitmap;
extern const GUI_BITMAP bmplaybpp;
extern const GUI_BITMAP bmpause;
extern const GUI_BITMAP bmprevbpp;
extern const GUI_BITMAP bmnextbpp;

extern u8 wave[14];
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
