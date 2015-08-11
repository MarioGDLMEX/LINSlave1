/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %LED.h%
* Instance:         RPL_1
* %version:         1 %
* %created_by:      Mario Alberto Rivera González %
* %date_created:    Monday July  29 14:38:03 2015 %
*=============================================================================*/
/* DESCRIPTION : Header file template                                         */
/*============================================================================*/
/* FUNCTION COMMENT : Contains only symbols which are exported to internal    */
/* platform modules. This will not be delivered with the library.             */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/07/2015  |                               | Mario Rivera     */
/* Integration programming layer. Driver to use Led's in any program.         */
/*----------------------------------------------------------------------------*/
/*============================================================================*/

#ifndef LED_H                               /* To avoid double inclusion */
#define LED_H

/* Includes */
/* -------- */
#include "typedefs.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */

#define OUTPUT					1

#define OPEN_DRAIN_DISABLE		0
#define OPEN_DRAIN_ENABLE		1
#define LOGICAL_VALUE_OUT		1


//PORT C
#define LED1       					34
#define LED2        				35
#define LED3        				36
#define LED4        				37
#define LED5        				38
#define LED6        				39
#define LED7        				40
#define LED8        				41
#define LED9        				42
#define LED10        				43
#define LED_OPEN      				44
#define LED_CLOSED     				45

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

/* Functions prototypes */
extern void LED_Init( T_UBYTE lub_chanel );
extern void Led_OFF( T_UBYTE Led );
extern void Led_ON( T_UBYTE Led );
/* Functions macros */


/* Exported defines */


#endif


