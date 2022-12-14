/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  GPTM.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "GPTM.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void GPTM_Delay(uint32  del)       
* \Description     : to make a delay with timer and interrupt                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint32  del                   
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void GPTM_Delay(uint16  del)
{
	SYSCTL_RCGCTIMER_REG |= 0X01;       // to activater timer0
	TIMER0_CTL_REG = 0;         // disable timer0 during setup
	TIMER0_CFG_REG = 0x00;     // configure for 32 bit mode   ,, 16 bit >> 0x04
	TIMER0_TAMR_REG = 0X02;   // config for periodic down count
	
	// Prescaler Configuration
	//TIMER0_TAPR_R = 250 ;          //config prescaller
	TIMER0_TAILR_REG =((del *16000000)-1) ;   // reload value  starting value
	TIMER0_ICR_REG = 0x01;       // clear TIMER0A  timeout flag
	
	TIMER0_IMR_REG |= (1<<0);    // arm timeout interrupt
	TIMER0_CTL_REG |= 0x01;      //   Enable TimerA module
	NVIC_EN0 |= 1<<19 ;    // enable IRQ 19 in NVIC
}




/**********************************************************************************************************************
 *  END OF FILE: GPTM.c
 *********************************************************************************************************************/



