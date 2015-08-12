/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %LED.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      Mario Alberto Rivera González %
* %date_created:    Monday July  29 14:38:03 2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : It contains functions generic to init leds, turn on     */
/* and off leds.			                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/07/2015  |                               | Mario Rivera     */
/* Integration programming layer. Driver to use Led's in any program.         */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  2.0      | 12/08/2015  |                               | Mario Rivera     */
/* Add toggling led functionality.									          */
/*============================================================================*/

/* Includes */
/* -------- */
/** MCU derivative information */
#include "MCU_derivative.h"
#include "LED.h"
#include "GPIO.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

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
 *  Name                 :	LED_Init
 *  Description          :	Initialitation led as output.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void LED_Init( T_UBYTE lub_chanel )
{
	GPIO_Init_channel(lub_chanel,(T_UBYTE)OUTPUT,(T_UBYTE)OPEN_DRAIN_DISABLE);/*Sets the channel as output*/
	GPIO_Output(lub_chanel, (T_UBYTE)LOGICAL_VALUE_OUT);/*Sets a logical value as output*/
}


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 : Led_ON
 *  Description          : Put the pin(chanel) in high(Turn on). 
 *  Parameters           : T_UBYTE lub_Led
 *  Return               : void
 *  Critical/explanation : NO
 **************************************************************/
 void Led_ON( T_UBYTE lub_Led )
 {
 	HIGH(lub_Led);/*Turn on the led*/
 }
 
 /* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	Led_OFF
 *  Description          :	Put the pin(chanel) in low(Turn off).
 *  Parameters           :  T_UBYTE lub_Led
 *  Return               :	void
 *  Critical/explanation :  NO
 **************************************************************/
 
 void Led_OFF( T_UBYTE lub_Led )
 {
 	LOW(lub_Led);/*Turn off the led*/
 }
 
 /* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	LED_TOGGLE
 *  Description          :	Put the pin(chanel) toggling.
 *  Parameters           :  T_UBYTE lub_Led
 *  Return               :	void
 *  Critical/explanation :  NO
 **************************************************************/
 void LED_TOGGLE( T_UBYTE lub_Led )
 {
 	TOGGLE(lub_Led);/*Toggling the led*/
 }

