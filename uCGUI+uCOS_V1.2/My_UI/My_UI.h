#ifndef _My_UI_h
#define _My_UI_h
#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "GUI.H"
#include "BUTTON.h"
#include "progbar.h"
#include "framewin.h"
#include "TEXT.h"
#include "WM.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "LISTVIEW.h"

#define _folder   1
#define _mp3      2
#define _txt      3
#define _bmp      4

#define TouchUnPress    0   //�״μ�⵽û�а���
#define TouchUnPressed  1   //û�а���
#define TouchPress      2   //�״μ�⵽����
#define TouchPressed    3   //����
/*   �˵��������ֵ�ID��   */
#define MainMenu_ID         1 
#define MusicPlayeMenu_ID   3 
#define FileBrowseMenu_ID   5
#define SetMenu_ID          10
#define TextMenu_ID         15

#define  Button_ID0   0x17a
#define  Button_ID1   0x17b
#define  Button_ID2   0x17c
#define  Button_ID3   0x17d
#define  Button_ID4   0x17e
#define  Button_ID5   0x17f
#define  Button_ID6   160
#define  Button_ID7   170
#define  Button_ID8   180
#define  Button_ID9   190
#define  Button_ID10  200
#define  Button_ID11  210
#define  Button_ID12  220
#define  Button_ID13  230
// #define _up   1
// #define _down 2

typedef struct SingleListNode {
	WM_HMEM                  handle;
	struct SingleListNode   *next;

}SingleListNode;                                                      /* ����SingleListNodeΪ�µ�������*/
typedef SingleListNode    *SingleList;                                /* ����ָ������                  */

typedef struct {
	WM_HMEM                  FirstHandle;
	WM_HMEM                  EndHandle;
}MenuInfo;                 

SingleList SingleListNodeCreate(void);
SingleList SingleListInsert(SingleList pList,SingleList pos,WM_HMEM x);
void SingleListFree(SingleList pHead);
void ClearStruct(unsigned char *pta, int size ) ;

u8 CheckFile(char *buf);

void MainMenu_Init(void); /* �������ʼ��*/
void Go_MainMenu(void);   /* �ص�������*/
void Out_MainMenu(void);  /*�˳������棬ע��������ֻ�ǲ�����Ļ����ʾ���ѣ�����Ȼ���ڣ�����Ļ��ʾ����֮��*/
void Out_OtherMenu(void);
void WM_MoveCtrl(void);   /* �˵�����Ļ�������*/
void WM_GoTop(void);      /* �ؽ��涥��*/
void WM_Move(SingleList pHead ,int dx,int dy); /* ʵ�������ڵ����пؼ�����*/
void SetThemeColor(GUI_COLOR color);
#endif
