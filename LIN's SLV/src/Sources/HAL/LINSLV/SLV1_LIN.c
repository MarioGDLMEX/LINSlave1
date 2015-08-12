/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %SLV1_LIN.c%
* Instance:         RPL_1
* %version:         2 %
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
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  2.0      | 12/08/2015  |                               | Mario Rivera     */
/* Changes: LINFLEX mode UART was changed for LINFLEX slave mode.              */
/* Implement LIN state machine.											      */
/*============================================================================*/


/*Me quede viendo como asignar a los bitfield lo del bus*/

/* Includes */
/* -------- */
#include "SLV1_LIN.h"
#include "typedefs.h"
#include "MPC5606B.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
//Output LINFLEX_0 18 PIN PB2
//Input LINFLEX_0 19 PIN PB3 

/* Functions macros */
#define OUTPUT					1
#define INPUT					0
#define OPEN_DRAIN_DISABLE		0
#define OPEN_DRAIN_ENABLE		1


#define LOGICAL_VALUE_OUT		1
#define LOGICAL_VALUE_INT		1


#define LINFLEX0_RX_Vector 		79
#define LINFLEX0_TX_Vector 		80

#define TX        				18 /*Output LINFLEX_0 18 PIN PB2*/
#define RX        				19 /*Input LINFLEX_0 19 PIN PB3*/

#define	PRIORITY10				10

#define MASTER_CMD_ALL 	    	0x0F
#define MASTER_CMD_SLV1 		0x10  
#define SLAVE1_RSP  			0x20 
#define SLAVE1_ID   			0x30


void LIN_init_Intrruptions( void );
/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */
enum
{
	IDLE,
	ID,
	TRANSMIT,
	RECEIVED
}E_STATES;
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
	/*Sleep Mode Request Off*/
  	LINFLEX_0.LINCR1.B.SLEEP = 0;
  /* Put LINFlex hardware in init mode */
  	LINFLEX_0.LINCR1.B.INIT = 1;    
  
  /*sets UART as LIN Mode*/
  	LINFLEX_0.UARTCR.B.UART = 0;
	
	/*LIN master lenght break 13 bits*/ 
	  LINFLEX_0.LINCR1.B.MBL= 0x03; 
	  /*bypass filter, An RX interrupt is generated on identifier not matching any filter*/
	  LINFLEX_0.LINCR1.B.BF= 1;
	  /*Slave mode ON*/
	  LINFLEX_0.LINCR1.B.MME=0;
	  /*sets as 11 bit break*/
	  LINFLEX_0.LINCR1.B.SBDT=0;
	  /*Receive buffer not locked on overrun */
	  LINFLEX_0.LINCR1.B.RBLM=0;
	  /*Idle on bit error, Bit error does not reset state machine*/
	  LINFLEX_0.LINCR2.B.IOBE= 0;
	  /* Fraction baud rate divider component */ 
	  LINFLEX_0.LINFBRR.R=3u;
	  /* Mantissa baud rate divider component */
	  LINFLEX_0.LINIBRR.R=104u; 
	
	/*deactivate filters to be able to set them manually*/ 
  LINFLEX_0.IFER.R=0x0;
  LINFLEX_0.IFMR.R=0x0;
  
  /*Idle timeout , not reset to idle in tome out event*/
  LINFLEX_0.LINTCSR.B.IOT=0;
 
 /*Interrupt generated when data received flag (DRF) in LINSR or UARTSR is set.*/
  	LINFLEX_0.LINIER.B.DRIE = 1;	
  /*Interrupt generated when data transmitted flag (DTF) is set in LINSR or UARTSR.*/
	LINFLEX_0.LINIER.B.DTIE = 1;
 /*Interrupt generated when a valid LIN header has been received, that is, HRF bit in LINSR is set.*/
	LINFLEX_0.LINIER.B.HRIE = 1;
	/*Checksum error, Interrupt generated when checksum error flag (CEF) in LINESR is set.  */	
	LINFLEX_0.LINIER.B.CEIE = 1;	
	/* Header error, Interrupt generated on Break Delimiter error, Synch Field error, Identifier field error. */	
	LINFLEX_0.LINIER.B.HEIE = 1;
	/*Bit error Interrupt generated when BEF bit in LINESR is set.  */	
	LINFLEX_0.LINIER.B.BEIE = 1;	/*  */
    
  /*Data Field Lenght*/  
  LINFLEX_0.IFCR[0].B.DFL=0;
  /*Direction set as Receiver*/
  LINFLEX_0.IFCR[0].B.DIR=0;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[0].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[0].B.ID=0x0F;//MASTER_CMD_ALL == 0xCF 0x0F
    
  /*Data Field Lenght*/  
  LINFLEX_0.IFCR[1].B.DFL=6;
  /*Direction set as Receiver*/
  LINFLEX_0.IFCR[1].B.DIR=0;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[1].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[1].B.ID=0x50;//MASTER_CMD_SLV1 == 0x10 
  
  
  
  /*Data Field Lenght*/  
  LINFLEX_0.IFCR[2].B.DFL=1;
  /*Direction set as Receiver*/
  LINFLEX_0.IFCR[2].B.DIR=1;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[2].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[2].B.ID=0x20;//SLAVE1_RSP == 0x20 
  
  
  
  /*Data Field Lenght*/  
  LINFLEX_0.IFCR[3].B.DFL=0;
  /*Direction set as Receiver*/
  LINFLEX_0.IFCR[3].B.DIR=1;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[3].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[3].B.ID=0xF0;// SLAVE1_ID == 0x30 
  
  
  
  /*Activate Filters*/
  LINFLEX_0.IFER.R=0x2;
  
}


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	LINFLEX_Rx_Transmition_Complete
 *  Description          :	Check if the buffer is full and assign
 *							to global variable. This will keep doing until	
 *							there is not more data send it.
 *  Parameters           :  void
 *  Return               :	T_UBYTE
 *  Critical/explanation :  [yes / No]
 **************************************************************/

/*Interrupt function when data is received*/
T_UBYTE LINFLEX_Rx_Transmition_Complete(void)
{ 
	/*If slave linflex 0 receives data*/
	if(LINFLEX_0.LINSR.B.RMB == 1)
	{
		LINFLEX_0.LINSR.B.RMB=1;
		return 1;
	}
	else
		return 0;
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	LIN_state_Machine
 *  Description          :	State machine that implements LIN protocol.
 *							Check's if the receptios is completed
 *							IDLE state: detect if ID was correct.
 *							ID state: select which ID was sended.
 *							TRANSMIT state: send a response.
 *							RECEIVED state: make command.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void LIN_state_Machine(void)
{
	T_UBYTE dato;
	if( LINFLEX_Rx_Transmition_Complete() )/*Transmition complete*/
	{
		dato = (T_UBYTE)LINFLEX_0.BDRL.B.DATA0;//Command to do
		if( LINFLEX_0.BIDR.B.ID == SLAVE1_RSP || LINFLEX_0.BIDR.B.ID == SLAVE1_ID )
		{
			set_option_machine(ID);/*Move state machine*/
			ste_type_ID(LINFLEX_0.BIDR.B.ID);
		}
		else if( LINFLEX_0.BIDR.B.ID == MASTER_CMD_SLV1 || LINFLEX_0.BIDR.B.ID == MASTER_CMD_ALL )
		{
			set_option_machine(ID);/*Move state machine*/
			ste_type_ID(LINFLEX_0.BIDR.B.ID);
			set_command(dato);
		}
	}
	else
	{
		set_option_machine(IDLE);
	}
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	Intc_LINFLEX_Tx
 *  Description          :	Interrupt function when data is tranferred
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/

void Intc_LINFLEX_Tx(T_UBYTE option)
{
	if(option == SLAVE1_ID )
	{
		LINFLEX_1.BDRL.B.DATA0 = 'G';/*Name of each memmber of team*/
    	LINFLEX_1.BDRL.B.DATA1 = 'R';/*Name of each memmber of team*/
    	LINFLEX_1.BDRL.B.DATA2 = 'M';/*Name of each memmber of team*/
    	LINFLEX_1.BDRL.B.DATA3 = 'C';/*Name of each memmber of team*/
    	LINFLEX_1.BDRM.B.DATA4 = 'M';/*Name of each memmber of team*/
    	LINFLEX_1.BDRM.B.DATA5 = 'E';/*Name of each memmber of team*/
    	LINFLEX_1.BDRM.B.DATA6 = 0x01;/*No. team*/
    	LINFLEX_1.BDRM.B.DATA7 = 0x00;
	}
	else if( option == SLAVE1_RSP)
	{
		LINFLEX_1.BDRL.B.DATA0 = get_LED_status(); 
    	LINFLEX_1.BDRL.B.DATA1 = get_SLV_status();
    	LINFLEX_1.BDRL.B.DATA2 = 0x0;
    	LINFLEX_1.BDRL.B.DATA3 = 0x0;
    	LINFLEX_1.BDRM.B.DATA4 = 0x0;
    	LINFLEX_1.BDRM.B.DATA5 = 0x0;
    	LINFLEX_1.BDRM.B.DATA6 = 0x0;
    	LINFLEX_1.BDRM.B.DATA7 = 0x0;
	}
	 /* store the data in the message buffer BDR */

	/* Master to publish x bytes with ID and CCS from bidr_value */
    //LINFLEX_1.BIDR.R = bidr_value; //0x1E35;
    
    /* Trigger Frame transmission */
    LINFLEX_1.LINCR2.B.HTRQ = 1;    
    
    /* wait until Master response to the LIN header has been sent successfully */
    while(0 == LINFLEX_1.LINSR.B.DTF) 
    {
        /* track LIN Status for errors */
  
    }
    
    LINFLEX_1.LINSR.R = 0x0002; /* clear the DTF bit */
/*if slave linflex 0 transfers data*/
	if(LINFLEX_0.LINSR.B.DTF == 1)
	{
		LINFLEX_0.LINSR.B.DTF=1;
	}
}


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	LIN_init_Intrruptions
 *  Description          :	Initializes interrution that will call when a transmition or 
 *							receptions are detected.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void LIN_init_Intrruptions( void )
{	
	INTC_InstallINTCInterruptHandler(&Intc_LINFLEX_Tx, LINFLEX0_TX_Vector, PRIORITY10);
	INTC_InstallINTCInterruptHandler(&LIN_state_Machine, LINFLEX0_RX_Vector, PRIORITY10);
	INTC.CPR.R = 0x0;
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	Intc_LINFLEX_Err
 *  Description          :	interrupt function when error detected
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void Intc_LINFLEX_Err(void)
{
	LINFLEX_0.LINESR.B.BEF=1;
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	NormalModeLINFLEX_0
 *  Description          :	Sets GPIO to Rx and Tx
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void NormalModeLINFLEX_0(void)
{
	//SIU.PCR[TX].R = 0x0400;         /* MPC56xxB: Configure port B2 as LIN0TX (Output) */
	GPIO_Init_channel(TX,(T_UBYTE)OUTPUT,(T_UBYTE)OPEN_DRAIN_DISABLE);/*Sets the channel as output*/
	GPIO_Output(TX, (T_UBYTE)LOGICAL_VALUE_OUT);/*Sets a logical value as output*/
  	//SIU.PCR[RX].R = 0x0103;         /* MPC56xxB: Configure port B3 as LIN0RX (Input) */
  	GPIO_Init_channel(RX,(T_UBYTE)INPUT,(T_UBYTE)OPEN_DRAIN_ENABLE);
	GPIO_Input(RX, (T_UBYTE)LOGICAL_VALUE_INT);
	LINFLEX_0.LINCR1.B.SLEEP = 0;
	LINFLEX_0.LINCR1.B.INIT = 0; /* Configure module as LIN master & header */
}
