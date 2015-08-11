/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %WindowLifter.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      Mario Alberto Rivera González %
* %date_created:    Monday July  29 14:38:03 2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : Implements a module that controls windows movement.     */
/* I have in this file a few function that help me implements Close, Open.    */
/* A states machine that helpe to move trough Automatic, Manual and Anti-Pinch*/
/* mode.                                                                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 03/07/2015  |                               | Mario Rivera     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/** Core modules */
/** MCU derivative information */
#include "MCU_derivative.h"
/* Variable types and common definitions */

/** Own headers */
/* GPIO routines prototypes */ 
#include "GPIO.h"

/** Used modules */


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
 *  Name                 : Task_1ms	
 *  Description          : This function controls all flows program.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    YES
 **************************************************************/
 
void GPIO_Init_channel(T_UBYTE channel, T_UBYTE input_output, T_UBYTE Open_drain)
{
    if (input_output == GPIO_OUTPUT)
    {
    	SIU.PCR[channel].B.PA  = 0;  				/* GPIO */
    	SIU.PCR[channel].B.OBE = 1;					/* Output buffer enable */
    	if (Open_drain == GPIO_OPEN_DRAIN_ENABLE)
    	{
    		SIU.PCR[channel].B.ODE = 1;				/* Open drain option enable */	
    	}
    	else
    	{	
    		SIU.PCR[channel].B.ODE = 0;				/* Push-pull option enable */	
    	}
    }
    else if (input_output == GPIO_INPUT)
    {
    	SIU.PCR[channel].B.PA  = 0;  				/* GPIO */
    	SIU.PCR[channel].B.IBE = 1;					/* Input buffer enable */	
    }

}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Task_1ms	
 *  Description          : This function controls all flows program.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    YES
 **************************************************************/
 
void GPIO_Output(T_UBYTE channel, T_UBYTE logical_value)
{
    SIU.GPDO[channel].B.PDO  = logical_value;  		/* Drive the logical output value to the pin */

}

void GPIO_Input(T_UBYTE channel, T_UBYTE logical_value)
{
    SIU.GPDI[channel].B.PDI  = logical_value;  		/* Drive the logical input value to the pin */

}
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
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 