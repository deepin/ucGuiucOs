#ifndef _Initialize_H_
#define _Initialize_H_
#include "stm32f10x.h"
#include  <stdio.h>

#define Addr_Base 0x08080000-2048//Flash�ĵ�ַ

void ADC1_Configuration(u8 type);
void RCC_Configuration(void);
void TIM_PWM_Init(void);
void SysTick_Configuration(void);
void RTC_Configuration(void);
void SD_SPI_Init(void);
void SPI1_SetSpeed(u8 Speed);
void GPIO_Configuration(void);
void USART1_Configuration(void);
void FSMC_LCD_Init(void);
void EXTI_Configuration(void);
void TIM1_Configuration(void);
void Light_Duty_Ctrl(u8 duty);
void NVIC_Configuration(void);
void Get_start_info(void);
void FLASH_write_data(u32 add_page,u32 add,u32 data);
u32 FLASH_read_data(u32 add);
u8 SPI1_ReadWriteByte(u8 byte);

u8 MCU_Init(void);
#endif
