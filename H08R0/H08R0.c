/*
    BitzOS (BOS) V0.0.0 - Copyright (C) 2016 Hexabitz
    All rights reserved

    File Name     : H08R0.c
    Description   : Source code for module H08R0.
										Eight industrial digital inputs (SN65HVS882PWP)
		
		Required MCU resources : 
		
			>> USARTs 1,2,3,4,5,6 for module ports.
			>> SPI 2 for SN65HVS882PWP
			>> GPIOB 12 for SN65HVS882PWP chip-select
			>> GPIOA 6 output for DI_LD (load shift register)
			>> GPIOA 7 input for DI_TOK (temperature OK flag)
			
*/
	
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"


/* Define UART variables */
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart6;

uint8_t inputs = 0;

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/	


/* Create CLI commands --------------------------------------------------------*/


/* -----------------------------------------------------------------------
	|												 Private Functions	 														|
   ----------------------------------------------------------------------- 
*/

/* --- H08R0 message processing task. 
*/
H08R0_Status H08R0_MessagingTask(uint16_t code, uint8_t port, uint8_t src, uint8_t dst)
{
	H08R0_Status result = H08R0_OK;
	
	switch (code)
	{

		default:
			result = H08R0_ERR_UnknownMessage;
			break;
	}			

	return result;	
}

/*-----------------------------------------------------------*/


/* -----------------------------------------------------------------------
	|																APIs	 																 	|
   ----------------------------------------------------------------------- 
*/
/* --- H08R0 module initialization. 
*/
void H08R0_Init(void)
{	
	/* Array ports */
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART4_UART_Init();
  MX_USART5_UART_Init();
  MX_USART6_UART_Init();
	
	/* SPI */
	MX_SPI2_Init();
	
	/* DI_LD */
	DI_LD_Init();
	
	/* DI_TOK */
	DI_TOK_Init();
	
}

/* --- Read digital input. 
*/
H08R0_Status ReadInputs(void)
{	
	HAL_StatusTypeDef result = HAL_OK;
	
	/* Load data into shift register */
	Load_SR();
	
	/* Read 8 bits from the shift register */
	CS_LOW();
	
	result = HAL_SPI_Receive(&hspi2, &inputs, 1, 10);
	while (result != HAL_BUSY) {};
	
	CS_HIGH();
	
	/* Return status */	
	if (result == HAL_OK)
		return H08R0_OK;
	else if (result == HAL_TIMEOUT)
		return H08R0_TIMEOUT;
	else 
		return H08R0_ERR_SPI;
	
}


/* -----------------------------------------------------------------------
	|															Commands																 	|
   ----------------------------------------------------------------------- 
*/


/*-----------------------------------------------------------*/

/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
