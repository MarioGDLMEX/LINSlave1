/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %Uart.h%
* Instance:         RPL_1
* %version:         1 %
* %created_by:      uid02495 %
* %date_created:    Fri Feb 28 13:41:01 2003 %
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
/*  1.0      | DD/MM/YYYY  | SAR/SIF/SCN_xxx               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef UART_H                               /* To avoid double inclusion */
#define UART_H

/* Includes */
/* -------- */


/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */
#include "typedefs.h"
/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */
extern T_ULONG received_caracter[4];


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
extern T_UBYTE UART_RXCompleted(void);

/* Functions macros */


/* Exported defines */


#endif

