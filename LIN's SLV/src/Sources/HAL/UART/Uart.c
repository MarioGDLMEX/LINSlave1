/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %Uart.c%
* Instance:         RPL_1
* %version:         1 %
* %created_by:      Mario Alberto Rivera González %
* %date_created:    Fri Jan  9 14:38:03 2004 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : Implement UART Tx and Rx								  */
/* 							                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 10/08/2015  |                               | Mario Rivera     */
/* Integration LinFlex2 with UART mode.                                       */
/* It have added InitUART function, Function to receive and transmite data.   */
/*============================================================================*/

/* Includes */
/* -------- */
#include "Uart.h"
#include "GPIO.h"
#include "MPC5606B.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */
#define LINFLEX2_RX_Vector  	119
#define LINFLEX2_TX_Vector   	120
#define TX        				40
#define RX        				41

#define	PRIORITY10	10


 T_ULONG received_caracter[4];
/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */
void UART_init_Intrruptions( void );

/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	Init_Uart
 *  Description          :  Initializes LinFlex_2 as UART mode.
 *							Initializes PIN 40 and 41 as i/o
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void Init_Uart(void)
{
	GPIO_Init_channel(TX,GPIO_OUTPUT, 0);/*UartMode->Tx(PIN 40 as OutPut/GPIO)*/
	GPIO_Output(TX, 1);
	GPIO_Init_channel(RX,GPIO_INPUT	, 1);/*UartMode->Rx(PIN 41 as Input/GPIO)*/
	GPIO_Input(RX, 1);
	
	LINFLEX_2.LINCR1.B.SLEEP = 0;
	LINFLEX_2.LINCR1.B.INIT = 1;		/* UART Init Mode */
	
	LINFLEX_2.UARTCR.B.UART = 1;		/* UART Mode */ 
	LINFLEX_2.UARTCR.B.WL = 1;		/* Word Length 8 bit */
	LINFLEX_2.UARTCR.B.PCE = 0;		/* No parity check */
	LINFLEX_2.UARTCR.B.TDFL = 0; 		/* Transmit buffer size 1 byte */
	LINFLEX_2.UARTCR.B.RDFL = 0; 		/* Receive buffer size 1 byte */
	

	LINFLEX_2.LINIER.B.DRIE = 1;		/* Data reception */
	LINFLEX_2.LINIER.B.DTIE = 1;		/* Data transmission */

	
	//Make a function to calculate BaudRate
	/* To have a baudrate of 9600 */
	/* 1 / (9600*16 / 64000000) = 416.66666 */
	/* fractional part LINFBRR = 0.66666*16 = 10.6666, nearest integer is 11*/
	/* integer part LINIBRR = 416*/
	
	LINFLEX_2.LINFBRR.R = 11u;
	LINFLEX_2.LINIBRR.R = 416u;
	
	LINFLEX_2.LINCR1.B.INIT = 0;	/* UART Normal Mode */
	LINFLEX_2.UARTCR.B.RXEN = 1;//Active reception
	LINFLEX_2.UARTCR.B.TXEN = 1;//Active transmition
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	UART_RXCompleted
 *  Description          :	Check if the buffer is full and assign
 *							to global variable. This will keep doing until	
 *							there is not more data send it.
 *  Parameters           :  void
 *  Return               :	T_UBYTE
 *  Critical/explanation :  [yes / No]
 **************************************************************/
T_UBYTE UART_RXCompleted(void){
	static T_UBYTE i = 0;
	if(LINFLEX_2.UARTSR.B.DRF==1 && LINFLEX_2.UARTSR.B.RMB==1){
		/*Received data en pass to state machine LIN*/
		received_caracter[i] = (T_UBYTE)LINFLEX_2.BDRM.B.DATA4;
		LINFLEX_2.UARTSR.B.DRF=0;
		LINFLEX_2.UARTSR.B.RMB=0;
		if(i<4)
		{
			i++;	
		}
		if(i == 4)
		{
			i = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
		return 0;
}


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	UART_TXCompleted
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void UART_TXCompleted(void){
	if(LINFLEX_2.UARTSR.B.DTF==1){
		LINFLEX_2.UARTSR.B.DTF=1;
	}
}