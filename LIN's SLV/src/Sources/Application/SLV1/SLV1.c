/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %SLV1.c%
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
/*  1.0      | 12/08/2015  |                               | Mario Rivera     */
/*  Implement Slave1 functionality.							                  */
/*  Fucntion that sets command slave1 to do.							      */
/*  A periodic task that will be call each 80ms by the scheduler.			  */
/*============================================================================*/


/*Me quede viendo como asignar a los bitfield lo del bus*/

/* Includes */
/* -------- */
#include "SLV1.h"
#include "typedefs.h"
#include "LED.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
#define LED_SLV			68

#define MASTER_CMD_ALL 	    	0x0F
#define MASTER_CMD_SLV1 		0x10  
#define SLAVE1_RSP  			0x20 
#define SLAVE1_ID   			0x30
/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */

static T_UBYTE rub_option_machine;
static T_UBYTE rub_command;
static T_UBYTE rub_type_ID;
/* WORD constants */


/* LONG and STRUCTURE constants */

enum
{
	CMD_NONE,
	CMD_LED_ON,
	CMD_LED_OFF,
	CMD_LED_TOGGLING,
	CMD_DISBLE_SLV,
	CMD_ENABLE_SLV
}E_TCMDTYPE;

enum
{
	ON,
	OFF,
	TOGGLING
}E_LED_STAT;

enum
{
	ENABLED,
	DISBALED
}E_SLV_STAT;

enum
{
	IDLE,
	ID,
	TRANSMIT,
	RECEIVED
}E_STATES1;

static T_UBYTE rub_SLV_status;
static T_UBYTE rub_LED_status;
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
 *  Name                 :	INIT_LIN
 *  Description          :	Initializes the slave1 variables and led
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 void INIT_LIN(void)
 {
 	rub_option_machine = IDLE;
 	rub_command = IDLE;
 	rub_SLV_status = ENABLED;
 	rub_LED_status = OFF;
 	/*INIT LED by GPIO*/
 	LED_Init(LED_SLV);
 }


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	cmd_Reception
 *  Description          :	Check if the Slave1 is able to recive commands
 *							Sets the command to the slave1 variables
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void cmd_Reception()
{
	if( rub_SLV_status == ENABLED )
	{	
		if( rub_command == CMD_NONE )
		{
			/*Do nothing*/
		}
		else if( rub_command == CMD_LED_ON )
		{
			rub_LED_status = ON;
		}
		else if( rub_command == CMD_LED_OFF )
		{
			rub_LED_status = OFF;
		}
		else if( rub_command == CMD_LED_TOGGLING )
		{
			rub_LED_status = TOGGLING;
		}
		else if( rub_command == CMD_DISBLE_SLV )
		{
			rub_SLV_status = DISBALED;
		}
		else if( rub_command == CMD_ENABLE_SLV )
		{
			rub_SLV_status = ENABLED;
		}
		else
		{
			/*Do nothing*/
		}	
	}
	else
	{
		/*rub_SLV_status is DISABLE, do nothing*/
	}
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	periodicTask100ms
 *  Description          :	Will be call each 80ms by the scheduler
 *							and will turn on,of or toggling the led.
 *  Parameters           :  void
 *  Return               :	T_UBYTE
 *  Critical/explanation :  [yes / No]
 **************************************************************/

void periodicTask80ms(void)
{
	if( rub_LED_status == ON)
	{
		Led_ON(LED_SLV);
	}
	else if( rub_LED_status == OFF )
	{
		Led_OFF(LED_SLV);
	}
	else if( rub_LED_status == TOGGLING )
	{
		LED_TOGGLE(LED_SLV);
	}
}



void SLV1_state_machine( void )
{
	switch(rub_option_machine)
	{
		case IDLE:
		break;
		/*Checks which type of ID is recived to make a response*/
		case ID:
			if( rub_type_ID == SLAVE1_RSP || rub_type_ID == SLAVE1_ID )
					rub_option_machine = TRANSMIT;
				else if( rub_type_ID == MASTER_CMD_SLV1 || rub_type_ID == MASTER_CMD_ALL )
				{
					rub_option_machine = RECEIVED;
				}
		break;
		case TRANSMIT:
			/*Send status*/
			Intc_LINFLEX_Tx(rub_type_ID);
			rub_option_machine = IDLE;
		break;
		case RECEIVED:
			rub_option_machine = IDLE;
			/*Make command: LED_ON, LED_OFF,LED_TOGGLE, SLV_ENABLE,SLV_DISABLE*/
			cmd_Reception();
		break;
	}

}

void set_option_machine(T_UBYTE option)
{
	rub_option_machine = option;
}

void set_command( T_UBYTE dato)
{
	rub_command = dato;
}

void ste_type_ID(T_UBYTE lub_type_ID)
{
	rub_type_ID = lub_type_ID;
}



T_UBYTE get_SLV_status()
{
	return rub_SLV_status;
}

T_UBYTE get_LED_status( )
{	
	return rub_LED_status;
}