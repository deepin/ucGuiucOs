#include "MusicPlayer.h"
#include "vs1003.h"
FIL infile;
MusicInfo  PlayMusicInfo;
MusicPlayerInfo   PlayerInfo;
OS_STK  TASK_PlaySong_STK[PlaySong_STK_SIZE];

void Task_PlaySong(void *pdata);//�������ֲ�������
void NextSong(void);   // ��һ��
void PrevSong(void);   // ��һ��
static void DisWave(s16 x,s16 y);//Ƶ����ʾ

/********************************************************************************************************** 
** Function name:      NextSong
** Descriptions:       ��һ��
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
**********************************************************************************************************/
void NextSong(void)
{
	char  buf1[38] = {"0:/MUSIC/"};
	PlayMusicInfo.PlayFlag = 0;
	f_close(&infile);    //�ر��ļ�
	if(PlayMusicInfo.NowPlayNum	== PlayMusicInfo.TotalNum - 1) {
	    PlayMusicInfo.NowPlayNum = 0;
	} else {
	    PlayMusicInfo.NowPlayNum++;
	}
	strcpy(PlayMusicInfo.MusicName,(char*)FileList[PlayMusicInfo.NowPlayNum+2]);
	strcat(buf1,PlayMusicInfo.MusicName);
	f_open(&infile, buf1, FA_OPEN_EXISTING | FA_READ);
	PlayMusicInfo.PlaySize = 0;
	PlayMusicInfo.PlayFlag = 1;
}
/********************************************************************************************************** 
** Function name:      PrevSong
** Descriptions:       ��һ��
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
**********************************************************************************************************/
void PrevSong(void)
{
   char  buf1[38] = {"0:/MUSIC/"};
   PlayMusicInfo.PlayFlag = 0;
	f_close(&infile);    //�ر��ļ�
	if(PlayMusicInfo.NowPlayNum	== 0) {
	    PlayMusicInfo.NowPlayNum = PlayMusicInfo.TotalNum - 1;
	} else {
	    PlayMusicInfo.NowPlayNum--;
	}
	strcpy(PlayMusicInfo.MusicName,(char*)FileList[PlayMusicInfo.NowPlayNum+2]);
	strcat(buf1,PlayMusicInfo.MusicName);
	f_open(&infile, buf1, FA_OPEN_EXISTING | FA_READ);
	PlayMusicInfo.PlaySize = 0;
	PlayMusicInfo.PlayFlag = 1;
}
/********************************************������Դ��**************************************************/
const GUI_WIDGET_CREATE_INFO PlaylistDialog[] = {
	{ FRAMEWIN_CreateIndirect,"���ֲ����б�",0,0,0,240,320,FRAMEWIN_CF_MOVEABLE},
  { LISTBOX_CreateIndirect,0,GUI_ID_LISTBOX0,2,4,231,262,WM_CF_SHOW},
  { BUTTON_CreateIndirect,"����",Button_ID8,40, 270,50, 25},
	{ BUTTON_CreateIndirect,"�˳�",Button_ID9,130,270,50,25}
};
const GUI_WIDGET_CREATE_INFO PlayerSetDialog[] = {
	{ FRAMEWIN_CreateIndirect,"����������",0,20,20,200,285,FRAMEWIN_CF_MOVEABLE},
	{ SLIDER_CreateIndirect,NULL,GUI_ID_SLIDER0,5,25,150,20, 0, 0},
	{ TEXT_CreateIndirect,"��������:",GUI_ID_TEXT0,3,2,100,20,TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,"��Ч����:",GUI_ID_TEXT1,3,54,100,20,TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,"������ǿ",GUI_ID_TEXT2,30,75,100,20,TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,"����",GUI_ID_TEXT3,30,95,100,20,TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,"������ǿ",GUI_ID_TEXT4,30,115,100,20,TEXT_CF_LEFT},

	{ TEXT_CreateIndirect,"�Ӿ�Ч��:",GUI_ID_TEXT5,3,140,100,20,TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,"��״Ƶ��",GUI_ID_TEXT6,30,160,100,20,TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,"LRC���",GUI_ID_TEXT7,30,180,100,20,TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,"��̬ͼ",GUI_ID_TEXT8,30,200,100,20,TEXT_CF_LEFT},

	{ RADIO_CreateIndirect,NULL,GUI_ID_RADIO0,5,77,20,60, 0, 3},
  { RADIO_CreateIndirect,NULL,GUI_ID_RADIO1,5,162,20,60, 0, 3},
  { BUTTON_CreateIndirect,"Ӧ��",Button_ID8,33, 230,50, 25},
	{ BUTTON_CreateIndirect,"�˳�",Button_ID9,116,230,50,25}
};
/********************************************************************************************************** 
** Function name:      PlaylistCallBack
** Descriptions:       �����б�Ի���ص�����
** input parameters:   WM_MESSAGE *pMsg����Ϣ
** output parameters:  ��
** Returned value:     ��
**********************************************************************************************************/
static void PlaylistCallBack(WM_MESSAGE *pMsg)
{
	int Id,NCode;
	char  buf[30];
	char  buf1[38] = {"0:/MUSIC/"};
// 	u16   file_num = 0;
  LISTBOX_Handle hListBox;
	WM_HWIN hWin = pMsg->hWin;
	hListBox = WM_GetDialogItem(hWin,GUI_ID_LISTBOX0);
	switch(pMsg -> MsgId) {
		
		case WM_INIT_DIALOG:
			MenuDisnable++;
		  LISTBOX_SetAutoScrollV (hListBox, 1);
// 		FRAMEWIN_AddCloseButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT,0);
      FRAMEWIN_AddMaxButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT, 0);
 	    FRAMEWIN_AddMinButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT, 0);
		  FatFs_Open("0:/MUSIC");//��SD������ȡ��Ŀ¼�б�
			for(Id = 2;Id < filecount;Id++){ //ǰ�����ǡ�.���͡�..��Ŀ¼�Ӧ������
		    LISTBOX_AddString(hListBox, (char*)FileList[Id]);
	    }
			break;
	  case WM_NOTIFY_PARENT:
		  Id = WM_GetId(pMsg ->hWinSrc);
		  NCode = pMsg ->Data.v;
		  switch(NCode) {
				
		    case WM_NOTIFICATION_RELEASED:
			    if (Id == Button_ID8) {
						PlayMusicInfo.PlayFlag = 0;
						f_close(&infile);    //�ر��ļ�
						PlayMusicInfo.NowPlayNum = LISTBOX_GetSel(hListBox)	;
						LISTBOX_GetItemText(hListBox,PlayMusicInfo.NowPlayNum,buf,30);
						strcpy(PlayMusicInfo.MusicName,buf);
						strcat(buf1,buf);
						f_open(&infile, buf1, FA_OPEN_EXISTING | FA_READ);
						PlayMusicInfo.PlaySize = 0;
						PlayMusicInfo.PlayFlag = 1;
// 						FileOpen(hFileBrowseListBox,"..");     //������һ��
// 						FRAMEWIN_SetText(pMsg->hWin, (const char*)FilePath);
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
** Function name:      PlayerSetCallBack
** Descriptions:       ���������öԻ���ص�����
** input parameters:   WM_MESSAGE *pMsg����Ϣ
** output parameters:  ��
** Returned value:     ��
**********************************************************************************************************/
static void PlayerSetCallBack(WM_MESSAGE *pMsg)
{
    int Id,NCode;
	switch(pMsg -> MsgId) {
		
		case WM_INIT_DIALOG:
			MenuDisnable++;
// 		FRAMEWIN_AddCloseButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT,0);
//      FRAMEWIN_AddMaxButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT, 0);
 	    FRAMEWIN_AddMinButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT, 0);
		TEXT_SetFont(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT0),&GUI_FontHZ_MicrosoftFont_13);
		TEXT_SetFont(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT1),&GUI_FontHZ_MicrosoftFont_13);
		TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT0), ThemeColor);
		TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT1), ThemeColor);
		TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT5), ThemeColor);
		TEXT_SetFont(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT2),&GUI_FontHZ_MicrosoftFont_13);
		TEXT_SetFont(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT3),&GUI_FontHZ_MicrosoftFont_13);
		TEXT_SetFont(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT4),&GUI_FontHZ_MicrosoftFont_13);
		TEXT_SetFont(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT5),&GUI_FontHZ_MicrosoftFont_13);
		TEXT_SetFont(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT6),&GUI_FontHZ_MicrosoftFont_13);
		TEXT_SetFont(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT7),&GUI_FontHZ_MicrosoftFont_13);
		TEXT_SetFont(WM_GetDialogItem(pMsg->hWin,GUI_ID_TEXT8),&GUI_FontHZ_MicrosoftFont_13);
		RADIO_SetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_RADIO0), PlayerInfo.EQ);
		RADIO_SetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_RADIO1), PlayerInfo.Display);
		SLIDER_SetRange(WM_GetDialogItem(pMsg->hWin,GUI_ID_SLIDER0),10,160);
		SLIDER_SetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_SLIDER0), PlayerInfo.Vol);

			break;
	  case WM_NOTIFY_PARENT:
		  Id = WM_GetId(pMsg ->hWinSrc);
		  NCode = pMsg ->Data.v;
		  switch(NCode) {
				
		    case WM_NOTIFICATION_RELEASED:
			    if (Id == Button_ID8) {
						PlayerInfo.Vol = (u8)SLIDER_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_SLIDER0));
						PlayerInfo.EQ = (u8)RADIO_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_RADIO0));
						PlayerInfo.Display = (u8)RADIO_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_RADIO1));
						GUI_EndDialog(pMsg->hWin, 1);
						MenuDisnable--;
						PlayerInfo.SetFlag = 1;
					} else if(Id == Button_ID9) {
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
** Function name:      Task_MusicPlayer
** Descriptions:       ���ֲ���������
** input parameters:   void *pdata
** output parameters:  ��
** Returned value:     ��
**********************************************************************************************************/
void Task_MusicPlayer(void *pdata)
{	
	s16 i;
	u8 count = 0;
	BUTTON_Handle hButton_else[6];
	PROGBAR_Handle ahProgBar;
	TEXT_Handle hTextelse[5];
// 	SLIDER_Handle hSlider;
	SingleList   pos   = NULL;
	Menu_ID = MusicPlayeMenu_ID;
	OtherMenu_pHead = SingleListNodeCreate();        /* �������������ͷ�ڵ�    */
	pos = OtherMenu_pHead;
	
	hTextelse[0] = TEXT_Create(0, 5,200, 24, 2, WM_CF_SHOW, "���ֲ�����", TEXT_CF_LEFT);	
	TEXT_SetFont(hTextelse[0],&GUI_FontHZ_YouYuan_24);	
	
	hTextelse[1] = TEXT_Create(0, 300,200, 24, 2, WM_CF_SHOW, "�����б�", TEXT_CF_LEFT);	
	TEXT_SetFont(hTextelse[1],&GUI_FontHZ_YouYuan_24);
	
	hTextelse[2] = TEXT_Create(0, 35,240, 24, 2, WM_CF_SHOW,PlayMusicInfo.MusicName, TEXT_CF_HCENTER);	
	TEXT_SetFont(hTextelse[2],&GUI_FontHZ_MicrosoftFont_13);
	
	hTextelse[3] = TEXT_Create(0, 370,200, 24, 2, WM_CF_SHOW, "����������", TEXT_CF_LEFT);	
	TEXT_SetFont(hTextelse[3],&GUI_FontHZ_YouYuan_24);	
	
	hTextelse[4] = TEXT_Create(0, 440,200, 24, 2, WM_CF_SHOW,"�����˵�", TEXT_CF_LEFT);	
	TEXT_SetFont(hTextelse[4],&GUI_FontHZ_YouYuan_24);	
	for (i = 0;i < 5;i++) {
		TEXT_SetTextColor(hTextelse[i],GUI_WHITE);
// 	  TEXT_SetBkColor(hTextelse[i],GUI_BLACK);
		pos = SingleListInsert(OtherMenu_pHead,pos,hTextelse[i]);//�������ı�������������
	}
// 	hListBox = LISTBOX_CreateAsChild (TilesColor, hDesktopWindow, 0, 100,240,130, WM_CF_SHOW);
// 	LISTBOX_SetAutoScrollV (hListBox, 1);
// 	pos = SingleListInsert(OtherMenu_pHead,pos,hListBox);
	
	ahProgBar = PROGBAR_Create(0, 250, 240, 5, WM_CF_SHOW);
	PROGBAR_SetBarColor (ahProgBar, 0,ThemeColor);
	PROGBAR_SetText(ahProgBar, " ");
// 	hSlider = SLIDER_Create(-4,240, 248,18, hDesktopWindow, GUI_ID_SLIDER0, WM_CF_SHOW, WM_CF_SHOW);
// 	SLIDER_SetBkColor  (hSlider, GUI_BLACK);
	pos = SingleListInsert(OtherMenu_pHead,pos,ahProgBar);
	
 /* Create the button*/   
  hButton_else[0] = BUTTON_Create(22, 265, 50, 25, Button_ID0, WM_CF_SHOW);   
	hButton_else[1] = BUTTON_Create(95, 265, 50, 25, Button_ID1, WM_CF_SHOW);
	hButton_else[2] = BUTTON_Create(167, 265, 50, 25, Button_ID2, WM_CF_SHOW);
	hButton_else[3] = BUTTON_Create(5, 335, 70, 25, Button_ID3, WM_CF_SHOW);
	hButton_else[4] = BUTTON_Create(5, 405, 70, 25, Button_ID4, WM_CF_SHOW);
	hButton_else[5] = BUTTON_Create(5, 475, 70, 25, Button_ID5, WM_CF_SHOW);
	for (i = 0;i < 6;i++) {
	  BUTTON_SetTextColor(hButton_else[i],0,GUI_WHITE);
	  BUTTON_SetBkColor  (hButton_else[i],0,ThemeColor);
    BUTTON_SetBkColor  (hButton_else[i],1,GUI_GRAY);
	  pos = SingleListInsert(OtherMenu_pHead,pos,hButton_else[i]);
	}
	/* Set the button text */   
	BUTTON_SetBitmapEx (hButton_else[0],0, &bmprevbpp, 17, 4);
	if(PlayMusicInfo.PlayFlag == 1){
		BUTTON_SetBitmapEx (hButton_else[1],0, &bmplaybpp, 17, 3);
	} else {
		BUTTON_SetBitmapEx (hButton_else[1],0, &bmpause, 18, 3);
	}	
  BUTTON_SetBitmapEx (hButton_else[2],0, &bmnextbpp, 18, 4);
	
	BUTTON_SetText(hButton_else[3],"�����б�");
	BUTTON_SetText(hButton_else[4],"����");
	BUTTON_SetText(hButton_else[5],"���˵�");
	OtherMenu_Info.FirstHandle = hTextelse[0];
	OtherMenu_Info.EndHandle = hButton_else[5];
	FatFs_Open("0:/MUSIC");//��SD������ȡ��Ŀ¼�б�
	PlayMusicInfo.TotalNum =  filecount - 2; //ǰ�����ǡ�.���͡�..��Ŀ¼�Ӧ������
	if(PlayMusicInfo.MusicName[0]==0){	     //��һ�ν��벥����ָ��ڶ��׸�
	   PlayerInfo.SetFlag = 0;
	   PlayerInfo.Vol =  170 - DefaultVol;
	   PlayerInfo.EQ = 1;
	  NextSong();	  //��һ��
		PlayMusicInfo.PlayFlag = 0;
	}
  OSTaskCreate(Task_PlaySong, (void * )0, (OS_STK *)&TASK_PlaySong_STK[PlaySong_STK_SIZE-1], PlaySong_TASK_Prio);
	
	while(1) {
//     SLIDER_SetValue(hSlider, PlayMusicInfo.PlaySize*100/infile.fsize);
		count ++;
		PROGBAR_SetValue(ahProgBar, PlayMusicInfo.PlaySize * 100 / infile.fsize);
		TEXT_SetText(hTextelse[2] , PlayMusicInfo.MusicName);
		if(count % 2 == 0) {
			i = WM_GetWindowOrgY(OtherMenu_Info.FirstHandle);
			if(i < - 55 && TouchFlag == TouchPressed ) {
				WM_SetDesktopColor(DesktopColor);
//      GUI_FillRect(68,i+75,170, i+240);
			}
			if(PlayerInfo.Display == 0){
			  DisWave(57,i+120);
			} else if(PlayerInfo.Display == 1){
				GUI_SetFont(&GUI_FontHZ_MicrosoftFont_13);
				GUI_DispStringAt("û�п���ʾ����!",70,i+130);
			} else {
				GUI_DrawBitmap(&bmmusicbitmap,62,i + 72);
			}
		}
		if(TouchCmd == 1){
			TouchCmd = 0;	
		  switch(GUI_GetKey()) {
				case Button_ID0:
				    PrevSong();   //��һ��
				    break;
				case Button_ID1:
					PlayMusicInfo.PlayFlag = !PlayMusicInfo.PlayFlag;
			    	if(PlayMusicInfo.PlayFlag){
					  BUTTON_SetBitmapEx (hButton_else[1],0, &bmplaybpp, 17, 3);
					} else {
					  BUTTON_SetBitmapEx (hButton_else[1],0, &bmpause, 18, 3);
					}
					break;
				case Button_ID2:
				    NextSong();	  //��һ��
				    break;				
				case Button_ID3:
					FatFs_Open("0:/MUSIC");//��SD������ȡ��Ŀ¼�б�
					GUI_CreateDialogBox(PlaylistDialog, GUI_COUNTOF(PlaylistDialog), PlaylistCallBack, 0, 0, 0);
					break;
				case Button_ID4:
					GUI_CreateDialogBox(PlayerSetDialog, GUI_COUNTOF(PlayerSetDialog), PlayerSetCallBack, 0, 0, 0);
					break;
				case Button_ID5:
					WM_SetDesktopColor(DesktopColor);
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
/********************************************************************************************************** 
** Function name:      Task_PlaySong
** Descriptions:       ���ֲ�������
** input parameters:   void *pdata
** output parameters:  ��
** Returned value:     ��
**********************************************************************************************************/
void Task_PlaySong(void *pdata)
{	
	u16 i = 0 , j= 0;
	UINT ss;
	while(1) {	
	  i = 0;
		if(PlayMusicInfo.PlayFlag == 1){
		  f_read(&infile, SD_Buffer, 512, &ss);
      PlayMusicInfo.PlaySize += ss;
		  if(ss<512) {             //�����ļ�ĩβ
		    f_close(&infile);      //�ر��ļ�
			FatFs_Open("0:/MUSIC");  //��SD������ȡ��Ŀ¼�б�
			NextSong();              //��һ��
		  }
		  while(i<500){ 
        while(DREQ == 0);
        for(j=i;j!=i+32;j++)
          WriteByteADS(SD_Buffer[j]); 
        i+=32;
      }
    }
	if(PlayerInfo.SetFlag) {
	  PlayerInfo.SetFlag = 0;
	  Mp3SetVolume(170 - PlayerInfo.Vol,170 - PlayerInfo.Vol);//��������
	  switch(PlayerInfo.EQ) {
		 case 0:
		     Mp3WriteRegister(SPI_BASS, 0xfc, 0);//���ø�����ǿ
		     break;
		 case 1:
		     Mp3WriteRegister(SPI_BASS, 0, 0);//��������
		     break;
		 case 2:
		     Mp3WriteRegister(SPI_BASS, 0, 0xf9);//���õ�����ǿ
		     break;
		 default:break;
	  }
	  TXDCS_0;
	}
	if(PlayerInfo.Display == 0){
		Get_wave();
	}
// 		PlayMusicInfo.DecodeTime = Mp3ReadRegister(SPI_DECODE_TIME);
// 		TXDCS_0;
// 		printf("DecodeTime = %d\r\n",	PlayMusicInfo.DecodeTime);
		OSTimeDly(18);            //�ȴ�ʱ���ɵ�ǰ������Ƶ�ı����ʾ������ڴ��ǲ���96kbps����Ƶ��
	//Ҫ��ʵ������Ӧ���ֱ����ʣ����Զ�ȡVS1003�ļĴ����õ���������Ϣ���ٶ�̬�����ȴ�ʱ�伴�ɡ�
	//�ڴ�֮�����趨��96kbps����Ϊ���������ʸߵ���Ƶʱ������������ýϿ��٣�����һ�����е�ѡ��
  }
}

static void DisWave(s16 x,s16 y)
{
	u8 count = 0;
	for(count = 0;count < 14;count++){
		if(wave[count] > 240) wave[count] = 240;
		GUI_SetColor(DesktopColor);
	  GUI_FillRect(x,y,x+7, y+ 80 - wave[count]/3);
		GUI_SetColor(ThemeColor);
		GUI_FillRect(x,y + 80 - wave[count]/3,x+7,y+80);
		x+=9;
	}
}
