/********************************************************************************************************
FAT32�ļ�ϵͳ��ʵ�֣����ܽϵ�һ��ֻ֧�����������������
�ݲ�֧���ļ��Ĵ�����ɾ�����ƶ������Ƶȹ��ܡ�

��ΪFAT32Ĭ��:ÿ���ص�������Ϊ0x08��ÿ���������ֽ���Ϊ0X200�����������ļ��������洢��
�����г��ֵĵ�ַ��Ϊ������ַ���������ַ��
˵�����ݲ�֧�ֳ��ļ�����ʾ
********************************************************************************************************/
#include "FAT32_SYS.H" 
#include <stdio.h>
#include "ff.h"
//#include"unicode_to_gb2312.h" //unicodeתgb2312��˳�����У�����ʹ�ö��ַ�����

// u32 Keep_sector=0;          //����������
// u32 Data_start_add=0;       //��������ʼ��ַ
// u32 FAT1_add=0;             //FAT1�����ʼ��ַ
// //u32 FAT2_add=0;           //FAT2�����ʼ��ַ
// u32 FAT_Block=0;            //ÿ��FAT��ռ�õ�������,λ�ã�0X24--4 �ڴ�ֻ�õ�16λ����TF����������2GB��ʹ��32λ

// extern FATFS fs; 

// /************��ȡ����������ʼ��ַ��FAT1�����ʼ��ַ***************/
// void Get_Data_Start_Add(void)
// {
//   u32 stay_Block=0;           //������������λ�ã�0X0E--2
//   SD_ReadDisk(fs.win,0,1);
//   if(fs.win[3]==0x4d&&fs.win[4]==0x53)Keep_sector=0;     //û�б�������
//   else Keep_sector=(u32)fs.win[0x01c7]<<8|fs.win[0x01c6];//��ñ���������  
//   printf("Keep_sector = %d\r\n",Keep_sector);
// 	
// 	SD_ReadDisk(fs.win,Keep_sector+0,1);
//   printf((char *)fs.win);printf("\r\n");
// 	
//   FAT_Block=256*(u32)(fs.win[0x25])+(u32)(fs.win[0x24]);
//   stay_Block=256*(u32)(fs.win[0x0f])+(u32)(fs.win[0x0e]);
//   FAT1_add=stay_Block;
//  //FAT2_add=FAT_Block*512+FAT1_add;
//   Data_start_add=FAT1_add+FAT_Block*2;
// 	printf("Data_start_add = %d\r\n",Data_start_add);
// }  

