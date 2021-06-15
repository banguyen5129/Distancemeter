/*******************************************************************************
* File Name: beeperpin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_beeperpin_H) /* Pins beeperpin_H */
#define CY_PINS_beeperpin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "beeperpin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 beeperpin__PORT == 15 && ((beeperpin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    beeperpin_Write(uint8 value);
void    beeperpin_SetDriveMode(uint8 mode);
uint8   beeperpin_ReadDataReg(void);
uint8   beeperpin_Read(void);
void    beeperpin_SetInterruptMode(uint16 position, uint16 mode);
uint8   beeperpin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the beeperpin_SetDriveMode() function.
     *  @{
     */
        #define beeperpin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define beeperpin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define beeperpin_DM_RES_UP          PIN_DM_RES_UP
        #define beeperpin_DM_RES_DWN         PIN_DM_RES_DWN
        #define beeperpin_DM_OD_LO           PIN_DM_OD_LO
        #define beeperpin_DM_OD_HI           PIN_DM_OD_HI
        #define beeperpin_DM_STRONG          PIN_DM_STRONG
        #define beeperpin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define beeperpin_MASK               beeperpin__MASK
#define beeperpin_SHIFT              beeperpin__SHIFT
#define beeperpin_WIDTH              1u

/* Interrupt constants */
#if defined(beeperpin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in beeperpin_SetInterruptMode() function.
     *  @{
     */
        #define beeperpin_INTR_NONE      (uint16)(0x0000u)
        #define beeperpin_INTR_RISING    (uint16)(0x0001u)
        #define beeperpin_INTR_FALLING   (uint16)(0x0002u)
        #define beeperpin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define beeperpin_INTR_MASK      (0x01u) 
#endif /* (beeperpin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define beeperpin_PS                     (* (reg8 *) beeperpin__PS)
/* Data Register */
#define beeperpin_DR                     (* (reg8 *) beeperpin__DR)
/* Port Number */
#define beeperpin_PRT_NUM                (* (reg8 *) beeperpin__PRT) 
/* Connect to Analog Globals */                                                  
#define beeperpin_AG                     (* (reg8 *) beeperpin__AG)                       
/* Analog MUX bux enable */
#define beeperpin_AMUX                   (* (reg8 *) beeperpin__AMUX) 
/* Bidirectional Enable */                                                        
#define beeperpin_BIE                    (* (reg8 *) beeperpin__BIE)
/* Bit-mask for Aliased Register Access */
#define beeperpin_BIT_MASK               (* (reg8 *) beeperpin__BIT_MASK)
/* Bypass Enable */
#define beeperpin_BYP                    (* (reg8 *) beeperpin__BYP)
/* Port wide control signals */                                                   
#define beeperpin_CTL                    (* (reg8 *) beeperpin__CTL)
/* Drive Modes */
#define beeperpin_DM0                    (* (reg8 *) beeperpin__DM0) 
#define beeperpin_DM1                    (* (reg8 *) beeperpin__DM1)
#define beeperpin_DM2                    (* (reg8 *) beeperpin__DM2) 
/* Input Buffer Disable Override */
#define beeperpin_INP_DIS                (* (reg8 *) beeperpin__INP_DIS)
/* LCD Common or Segment Drive */
#define beeperpin_LCD_COM_SEG            (* (reg8 *) beeperpin__LCD_COM_SEG)
/* Enable Segment LCD */
#define beeperpin_LCD_EN                 (* (reg8 *) beeperpin__LCD_EN)
/* Slew Rate Control */
#define beeperpin_SLW                    (* (reg8 *) beeperpin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define beeperpin_PRTDSI__CAPS_SEL       (* (reg8 *) beeperpin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define beeperpin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) beeperpin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define beeperpin_PRTDSI__OE_SEL0        (* (reg8 *) beeperpin__PRTDSI__OE_SEL0) 
#define beeperpin_PRTDSI__OE_SEL1        (* (reg8 *) beeperpin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define beeperpin_PRTDSI__OUT_SEL0       (* (reg8 *) beeperpin__PRTDSI__OUT_SEL0) 
#define beeperpin_PRTDSI__OUT_SEL1       (* (reg8 *) beeperpin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define beeperpin_PRTDSI__SYNC_OUT       (* (reg8 *) beeperpin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(beeperpin__SIO_CFG)
    #define beeperpin_SIO_HYST_EN        (* (reg8 *) beeperpin__SIO_HYST_EN)
    #define beeperpin_SIO_REG_HIFREQ     (* (reg8 *) beeperpin__SIO_REG_HIFREQ)
    #define beeperpin_SIO_CFG            (* (reg8 *) beeperpin__SIO_CFG)
    #define beeperpin_SIO_DIFF           (* (reg8 *) beeperpin__SIO_DIFF)
#endif /* (beeperpin__SIO_CFG) */

/* Interrupt Registers */
#if defined(beeperpin__INTSTAT)
    #define beeperpin_INTSTAT            (* (reg8 *) beeperpin__INTSTAT)
    #define beeperpin_SNAP               (* (reg8 *) beeperpin__SNAP)
    
	#define beeperpin_0_INTTYPE_REG 		(* (reg8 *) beeperpin__0__INTTYPE)
#endif /* (beeperpin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_beeperpin_H */


/* [] END OF FILE */
