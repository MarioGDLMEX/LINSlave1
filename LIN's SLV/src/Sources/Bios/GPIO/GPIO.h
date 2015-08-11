/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %GPIO.h%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      Edgar Mosqueda Cardenas %
* %date_created:    Thu jul 16 13:43:01 2015 %
*=============================================================================*/
/* DESCRIPTION : Header file template                                         */
/*============================================================================*/
/* FUNCTION COMMENT : contains only symbols which are exported to internal    */
/* platform modules. This will not be delivered with the library              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 16/07/2015  | SAR/SIF/SCN_xxx               | Edgar Mosqueda   */
/* Integration under Continuus CM                                             */
/*============================================================================*/
//Eddy modifico este archivo
#ifndef _GPIO_H        /*prevent duplicated includes*/
#define _GPIO_H

/* Includes */
/** MCU derivative information */
#include "MCU_derivative.h"
#include "typedefs.h"
/** Variable types and common definitions */

/* Exported types and constants */
/* ---------------------------- */
#define GPIO_INPUT					0
#define GPIO_OUTPUT					1

#define GPIO_OPEN_DRAIN_DISABLE		0
#define GPIO_OPEN_DRAIN_ENABLE		1



/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */ 
#define HIGH(channel)                     (SIU.GPDO[channel].B.PDO =  1)
#define LOW(channel)                    (SIU.GPDO[channel].B.PDO =  0)
#define TOGGLE(channel)                 (SIU.GPDO[channel].B.PDO ^= 1) 


#define PULL_DOWN(channel)				( SIU.GPDI[channel].R )


/* Functions prototypes */

extern void GPIO_Init_channel(T_UBYTE channel, T_UBYTE input_output, T_UBYTE Open_drain);
extern void GPIO_Output(T_UBYTE channel, T_UBYTE logical_value);
extern void GPIO_Input(T_UBYTE channel, T_UBYTE logical_value);
/* Functions macros */


/* Exported defines */

#endif /* _GPIO_H */

/*******************************************************************************/
