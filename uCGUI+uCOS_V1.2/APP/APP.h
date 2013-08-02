#ifndef _APP_H
#define _APP_H
#include "stm32f10x.h"
#include "includes.h"
#include "GUI.H"
#include "My_UI.h"
#include "Initialize.h"

extern TEXT_Handle hText;
extern u8 Menu_ID;                         //�˵������ID
extern WM_HWIN hDesktopWindow;             //����ľ��
extern u8 TouchCmd;                        //��־���ǵ㴥���ǻ���������
extern u8 TouchFlag;
/************************************************************************************************
**��������ȼ�����
************************************************************************************************/
#define Touch_TASK_Prio   	      3        //�����������
#define Menu_TASK_Prio   	        30       //GUI�˵���������
#define START_TASK_Prio           55       //��ʼ����
#define LED_DEMO_TASK_Prio        50       //LED����
#define Setting_TASK_Prio         12       //��������
#define FileBrowser_TASK_Prio     14       //�ļ��������
#define MusicPlayer_TASK_Prio     16       //���ֲ���������
#define PhotoBrowser_TASK_Prio    18       //ͼƬ���������
#define TextBrowser_TASK_Prio     20       //�ı����������
/************************************************************************************************
**�����ջ�����������ֽڣ�
************************************************************************************************/
#define Touch_STK_SIZE            128      //�����������
#define Menu_STK_SIZE             256      //GUI�˵���������
#define START_STK_SIZE            164//32       //��ʼ����
#define LED_STK_SIZE              164       //LED����
#define Setting_STK_SIZE          256      //��������
#define FileBrowser_STK_SIZE      256      //�ļ����������
#define MusicPlayer_STK_SIZE      320      //���ֲ���������
#define PhotoBrowser_STK_SIZE     256      //ͼƬ���������
#define TextBrowser_STK_SIZE      256      //�ı����������
/************************************************************************************************
**��������
************************************************************************************************/
void TaskStart(void * pdata);              //��ʼ����
void Task_Touch(void *pdata);              //�����������
void Task_Menu(void *pdata);               //GUI�˵���������
void Task_LED_DEMO(void *pdata);           //LED����
extern void Task_Setting(void *pdata);     //��������
extern void Task_FileBrowser(void *pdata); //�ļ����������
extern void Task_MusicPlayer(void *pdata); //���ֲ���������
extern void Task_PhotoBrowser(void *pdata);//ͼƬ���������
extern void Task_TextBrowser(void *pdata); //�ı����������
#endif
