#include "FileBrowser.h"
extern SDCardInfo SDCard_Info;
static void FileOpen(LISTBOX_Handle hFileBrowseListBox,char *buf);

/********************************************������Դ��**************************************************/
const GUI_WIDGET_CREATE_INFO FileBrowseDialog[] = {
	{ FRAMEWIN_CreateIndirect,"SD ��",0,0,0,240,320,FRAMEWIN_CF_MOVEABLE},
  { LISTBOX_CreateIndirect,0,GUI_ID_LISTBOX0,2,4,231,262,WM_CF_SHOW},
	{ BUTTON_CreateIndirect,"����",Button_ID7,2, 270,50, 25},
  { BUTTON_CreateIndirect,"��",Button_ID8,95, 270,50, 25},
	{ BUTTON_CreateIndirect,"�ر�",Button_ID9,183,270,50,25}
};
/********************************************************************************************************** 
** Function name:      FileBrowserCallBack
** Descriptions:       �ļ�����Ի���ص�����
** input parameters:   WM_MESSAGE *pMsg����Ϣ
** output parameters:  ��
** Returned value:     ��
**********************************************************************************************************/
static void FileBrowserCallBack(WM_MESSAGE *pMsg)
{
	int Id,NCode;
	char  buf[30];
	u16   file_num = 0;
	LISTBOX_Handle hFileBrowseListBox;
	WM_HWIN hWin = pMsg->hWin;
	hFileBrowseListBox = WM_GetDialogItem(hWin,GUI_ID_LISTBOX0);
	switch(pMsg -> MsgId) {
		
		case WM_INIT_DIALOG:
			MenuDisnable++;
		  LISTBOX_SetAutoScrollV (hFileBrowseListBox, 1);
// 		  FRAMEWIN_AddCloseButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT,0);
   	  FRAMEWIN_AddMaxButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT, 0);
 	    FRAMEWIN_AddMinButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT, 0);
		  FatFs_Open("");//��SD������ȡ��Ŀ¼�б�
			for(Id = 0;Id < filecount;Id++){
		    LISTBOX_AddString(hFileBrowseListBox, (char*)FileList[Id]);
	    }
			break;
	  case WM_NOTIFY_PARENT:
		  Id = WM_GetId(pMsg ->hWinSrc);
		  NCode = pMsg ->Data.v;
		  switch(NCode) {
				
		    case WM_NOTIFICATION_RELEASED:
			    if (Id == Button_ID7) {
						FileOpen(hFileBrowseListBox,"..");     //������һ��
						FRAMEWIN_SetText(pMsg->hWin, (const char*)FilePath);
					} else if (Id == Button_ID8) {
						 file_num = LISTBOX_GetSel(hFileBrowseListBox);//����ֵ��Ϊѡ�������ڵ�����
		         LISTBOX_GetItemText(hFileBrowseListBox,file_num,buf,30);
						 FileOpen(hFileBrowseListBox,buf);
						 FRAMEWIN_SetText(pMsg->hWin, (const char*)FilePath);
					} else if(Id == Button_ID9) {
						ClearPath(FilePath);
						GUI_EndDialog(pMsg->hWin, 1);
						MenuDisnable--;
					}
					break;
				default:
				  break;
		  }		
      break;			
		default:
      WM_DefaultProc(pMsg);
		  break;
	 }
}
/********************************************************************************************************** 
** Function name:      Task_FileBrowser
** Descriptions:       �ļ����������
** input parameters:   void *pdata
** output parameters:  ��
** Returned value:     ��
**********************************************************************************************************/
void Task_FileBrowser(void *pdata)
{	
	BUTTON_Handle hButton_else[3];
  TEXT_Handle   hTextelse[6];
	PROGBAR_Handle ahProgBar[2];
  char buf[25] = {0};
	u16 i = 0 ;
	SingleList   pos   = NULL;
	Menu_ID = FileBrowseMenu_ID;
	OtherMenu_pHead = SingleListNodeCreate();        /* �������������ͷ�ڵ�    */
	pos = OtherMenu_pHead;
	
// 	FatFs_Open("");//��SD������ȡ��Ŀ¼�б�
	sprintf(buf,"Free:%dMB,Total:%dMB",SDCard_Info.FreeSize,SDCard_Info.TotalSize);
	hTextelse[0] = TEXT_Create(5,20,200, 20, 2, WM_CF_SHOW, "�洢�豸",TEXT_CF_LEFT);
	TEXT_SetFont(hTextelse[0],&GUI_FontHZ_MicrosoftFont_13);
	
	hTextelse[1] = TEXT_Create(5,50,100, 25, 3, WM_CF_SHOW, "SD CARD",TEXT_CF_LEFT);
	TEXT_SetFont(hTextelse[1],&GUI_Font24_ASCII);

	hTextelse[2] = TEXT_Create(5,120,115, 25, 4, WM_CF_SHOW, "SPI FLASH",TEXT_CF_LEFT);
	TEXT_SetFont(hTextelse[2],&GUI_Font24_ASCII);

	hTextelse[3] = TEXT_Create(5,300,200, 25, 5, WM_CF_SHOW, "�����˵�",TEXT_CF_LEFT);
	TEXT_SetFont(hTextelse[3],&GUI_FontHZ_YouYuan_24);
	
	hTextelse[4] = TEXT_Create(100,97,140, 10, 6, WM_CF_SHOW, buf,TEXT_CF_HCENTER);
	TEXT_SetFont(hTextelse[4],&GUI_Font8_ASCII);
	sprintf(buf,"Free:%dMB,Total:%dMB",0,0);
	hTextelse[5] = TEXT_Create(100,167,140, 10, 7, WM_CF_SHOW, buf,TEXT_CF_HCENTER);
	TEXT_SetFont(hTextelse[5],&GUI_Font8_ASCII);
	for (i = 0;i < 6;i++) {
		TEXT_SetTextColor(hTextelse[i],GUI_WHITE);
// 	  TEXT_SetBkColor(hTextelse[i],GUI_BLACK);
		pos = SingleListInsert(OtherMenu_pHead,pos,hTextelse[i]);//�������ı�������������
	}
	ahProgBar[0] = PROGBAR_Create(120, 63, 100, 22, WM_CF_SHOW);
	PROGBAR_SetBarColor (ahProgBar[0], 0,ThemeColor);
	PROGBAR_SetValue(ahProgBar[0], (u32)SDCard_Info.FreeSize * 100 / SDCard_Info.TotalSize);
	
	ahProgBar[1] = PROGBAR_Create(120, 133, 100, 22, WM_CF_SHOW);
	PROGBAR_SetBarColor (ahProgBar[1], 0,ThemeColor);
	PROGBAR_SetValue(ahProgBar[1], 0);
	
	pos = SingleListInsert(OtherMenu_pHead,pos,ahProgBar[0]);
	pos = SingleListInsert(OtherMenu_pHead,pos,ahProgBar[1]);
// 	hFileBrowseListBox = LISTBOX_CreateAsChild(0,hDesktopWindow,-2,110,245,filecount*16+5,WM_CF_SHOW);

	hButton_else[0] = BUTTON_Create (5, 80,70, 25, Button_ID0, WM_CF_SHOW);
	hButton_else[1] = BUTTON_Create (5, 150,70, 25, Button_ID1, WM_CF_SHOW);
	hButton_else[2] = BUTTON_Create (5, 335,70, 25, Button_ID2, WM_CF_SHOW);
	for (i = 0;i < 3;i++) {
	  BUTTON_SetTextColor(hButton_else[i],0,GUI_WHITE);
	  BUTTON_SetBkColor  (hButton_else[i],0,ThemeColor);
    BUTTON_SetBkColor  (hButton_else[i],1,GUI_GRAY);
	  pos = SingleListInsert(OtherMenu_pHead,pos,hButton_else[i]);
	}
	BUTTON_SetText(hButton_else[0],"��");
	BUTTON_SetText(hButton_else[1],"��");
	BUTTON_SetText(hButton_else[2],"���˵�");
	OtherMenu_Info.FirstHandle = hTextelse[0];
	OtherMenu_Info.EndHandle = hButton_else[2];
	
	/*******************************************************************************************************/
	while(1){
		if(TouchCmd == 1){
			TouchCmd = 0;	
		  switch(GUI_GetKey()) {
				case Button_ID0:
					if(SDCard_Info.ExistFlag){
						GUI_CreateDialogBox(FileBrowseDialog, GUI_COUNTOF(FileBrowseDialog), FileBrowserCallBack, 0, 0, 0);
					} else {
					  GUI_MessageBox("Hardware does not exist!","Ӳ��������!",GUI_MESSAGEBOX_CF_MOVEABLE);
					}
					break;
				case Button_ID1:
					GUI_MessageBox("Hardware does not exist!","Ӳ��������!",GUI_MESSAGEBOX_CF_MOVEABLE);
					break;
				case Button_ID2:
					Out_OtherMenu();            //�˳����ý���
				  Go_MainMenu();              //����������
				  OSTaskDel(OS_PRIO_SELF);    //ɾ���Լ�
					break;
				default :	
					TouchCmd = 1;
					break;
		  }
	  }
	  OSTimeDly(10);   //��֤50Hz��ִ��Ƶ��
	}
}


static void FileOpen(LISTBOX_Handle hFileBrowseListBox,char *buf)
{
	u16 i;
	FilePath_process(FilePath,buf);
	FatFs_Open(FilePath);
	for (i =  LISTBOX_GetNumItems(hFileBrowseListBox);i > 0;i--){
		LISTBOX_DeleteItem(hFileBrowseListBox, i-1);
	}
	for(i = 0;i < filecount;i++){
		 LISTBOX_AddString(hFileBrowseListBox, (char*)FileList[i]);
	}
}
