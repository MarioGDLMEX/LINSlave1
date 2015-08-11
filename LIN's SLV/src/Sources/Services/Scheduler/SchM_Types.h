/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %SchM_Types.h%
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

#ifndef SCHM_TYPES_H                               /* To avoid double inclusion */
#define SCHM_TYPES_H

/* Includes */
/* -------- */
#include "typedefs.h"


/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */





typedef void(*TaskFunctionPtrType)(void);
typedef T_UBYTE SchTaskOffsetType;

typedef enum
{
	MASK_2P5MS = 3,
	MASK_5Ms  = 7,
	MASK_10MS  = 15,
	MASK_20MS    = 31,
	MASK_40MS    = 63,
	MASK_80MS   = 127
}SchTaskMaskType;


typedef enum
{
	TASK_BKG,
	TASK_2P5MS,
	TASK_5MS,
	TASK_10MS,
	TASK_20MS,
	TASK_40MS,
	TASK_80MS
}ScheTaskIDType;



typedef enum
{
	TASK_STATE_SUSPENDED,
	TASK_STATE_READY,
	TASK_STATE_RUNNING
}SchTaskStateType;


typedef struct
{
	SchTaskStateType SchTaskState;
	TaskFunctionPtrType TaskFunctionControlPtr;
}SchTaskControlType;

typedef struct
{
	SchTaskOffsetType SchTaskOffset;//T_UBYTE
	SchTaskMaskType SchTaskMask;//ENUM
	ScheTaskIDType SchTaskId;//ENUM
	TaskFunctionPtrType TaskFunctionPtr;//
}SchTaskTableType;

typedef struct
{
	T_UBYTE SchNumberOfTask;
	const SchTaskTableType *SchTaskTable;
}SchConfigType;

typedef enum
{
	SCH_UNINIT,
	SCH_INIT,
	SCH_RUNNING,
	SCH_OVERLOAD,
	SCH_HALTED
}SchStateType;

typedef struct
{
	T_UBYTE SchCounter;
	ScheTaskIDType SchTaskRunning;
	SchStateType SchStatus;
}SchControlType;


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


/* Functions macros */


/* Exported defines */


#endif


