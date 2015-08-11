/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %SLV1_LIN.c%
* Instance:         RPL_1
* %version:         1 %
* %created_by:      Mario Alberto Rivera González %
* %date_created:    Fri Jan  9 14:38:03 2004 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT :   Implement LIN protocol as requirements matrix.		  */
/* 							                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 10/08/2015  |                               | Mario Rivera     */
/* Initializes UART mode from LINFLEX_2 and interruptions                     */
/* Implement LIN state machine.											      */
/*============================================================================*/

/* Includes */
/* -------- */
#include "SLV1_LIN.h"
#include "typedefs.h"
#include "Uart.h"
#include "MPC5606B.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */
#define LINFLEX2_RX_Vector 	119
#define LINFLEX2_TX_Vector 	120
#define	PRIORITY10	10


void LIN_init_Intrruptions( void );
enum
{
	IDLE,
	BREAK_DETECTED,
	SYNC,
	VALID_ID,
	TRANSMIT,
	RECEIVED
}states;

T_UBYTE option_machine;
extern T_ULONG received_caracter[4];
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
 *  Name                 :	Init_LIN_SLV1
 *  Description          :	Sets variable that controls state machine LIN as IDLE.
 *							Initializes Interruption and UART
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void Init_LIN_SLV1(void)
{
	option_machine = IDLE;
	LIN_init_Intrruptions();
	Init_Uart();
}


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	LIN_state_Machine
 *  Description          :	State machine that implements LIN protocol.
 *							Check's that all the data was send it.
 *							IDLE state: detect a break.
 *  Parameters           :  
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void LIN_state_Machine(void)
{
	T_ULONG aux[4];
	T_UBYTE resultado;
	static T_UBYTE sum = 0;
	resultado = UART_RXCompleted();
	sum = sum+resultado;
	 if( resultado == 1 )//Transmition complete
	 {
	 	switch(option_machine)
		{
			case IDLE:
			aux[0] = received_caracter[0];
			aux[0] = aux[0]<<24;
			aux[1] = received_caracter[1];
			aux[1] = aux[1]<<16;
			aux[2] = received_caracter[2];
			aux[2] = aux[2]<<8;
			aux[3] = received_caracter[3];
			//aux[3] = aux[3]<<8;
			aux[0] = aux[0]|aux[1]|aux[2]|aux[3];
				/*if()
					option_machine = BREAK_DETECTED;
				else
				{
					option_machine = IDLE;
				}*/
			break;
			case BREAK_DETECTED:
			break;
			case SYNC:
			break;
			case VALID_ID:
			break;
			case TRANSMIT:
			break;
			case RECEIVED:
			break;
		}	
	 }
}


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	LIN_init_Intrruptions
 *  Description          :	Initializes interrution that will call when a transmition or 
 *							receptions are detected.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void LIN_init_Intrruptions( void )
{
	//INTC_InstallINTCInterruptHandler(&UART_TXCompleted, LINFLEX2_TX_Vector, PRIORITY10);
	
	
	INTC_InstallINTCInterruptHandler(&LIN_state_Machine, LINFLEX2_RX_Vector, PRIORITY10);
}