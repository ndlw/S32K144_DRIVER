/**
 * @file HAL_PCC_Module.c
 * @author Vo Doan Quynh Nhi
 * @brief
 * @version 0.1
 * @date 2025-01-21
 *
 * @copyright Copyright (c) 2025
 *
 */
/*******************************************************************************
* Include
*******************************************************************************/
#include "../src/Driver/PCC/Include/s32k144_PCC_hal.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t clock = 48000000;

/**
 * @brief This bit shows whether the peripheral is present on this device.
 *

 * @param peripheralIndex            [Input] Index of the peripheral to check.
 * @return uint32_t                  Returns 0 if the check is successful
 */
uint32_t HAL_Check_PR( uint32_t peripheralIndex)
{
    uint32_t PR_bit = (PCC->PCCn[peripheralIndex] & PCC_PCCn_PR_MASK) >> PCC_PCCn_PR_SHIFT;
    return (PR_bit == 1) ? PR_BIT_SET : PR_BIT_CLEAR;
}

/**
 * @brief Enable the clock for a specified peripheral.
 *
 * @param peripheralIndex           [Input] Index of the peripheral to check.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Enable_Peripheral_Clock(uint32_t peripheralIndex)
{
    /* Set the CGC bit to enable the clock. */
    PCC->PCCn[peripheralIndex] |= PCC_PCCn_CGC(1);
    return 0;
}

/**
 * @brief select the clock source for a specified peripheral.
 *
 * @param peripheralIndex           [Input] Index of the peripheral to check.
 * @param source                    [Input] Clock source to be set for the peripheral.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Clock_Source_Select( uint32_t peripheralIndex, PeripheralClockSource source)
{
    /* Clear the CGC bit before setting the source. */
    PCC->PCCn[peripheralIndex] &= ~PCC_PCCn_CGC_MASK;
    /* Set the PCS bits to select the clock source. */
    PCC->PCCn[peripheralIndex] &= ~PCC_PCCn_PCS_MASK;
    PCC->PCCn[peripheralIndex] |= PCC_PCCn_PCS(source);
    PCC->PCCn[peripheralIndex] |= PCC_PCCn_CGC_MASK;
    return 0;
}

/**
 * @brief Set the clock divider and fraction for a specified peripheral.
 *
 * @param peripheralIndex           [Input] Index of the peripheral.
 * @param divider                   [Input] Clock divider value to set.
 * @param fraction                  [Input] Clock fraction value to set.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Clock_Divider_Select(uint32_t peripheralIndex, PeripheralClockDividerSelect divider, PeripheralClockFractionSelect fraction)
{
    /* Clear the CGC bit before setting the divider and fraction. */
    PCC->PCCn[peripheralIndex] &= ~PCC_PCCn_CGC_MASK;
    /* Set the divider bits. */
    PCC->PCCn[peripheralIndex] |= (uint32_t)(divider << PCC_PCCn_CGC_SHIFT);
    /* Set the fraction bits. */
    PCC->PCCn[peripheralIndex] |= (uint32_t)(fraction << PCC_PCCn_FRAC_SHIFT);
    return 0;
}

/**
 * @brief Disable the clock
 *
 * @param peripheralIndex           [Input] Index of the peripheral.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Disable_Peripheral_Clock(uint32_t peripheralIndex)
{
    /* Clear the CGC bit to disable the clock. */
    PCC->PCCn[peripheralIndex] &= ~PCC_PCCn_CGC_MASK;
    return 0;
}

void HAL_SystemClock_Config(void)
{
    SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(1);
    SCG->FIRCCSR |= SCG_FIRCCSR_FIRCEN(1);

    while (!(SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK))
    {
        // Wait until the FIRC is valid
    }

    SCG->SPLLCFG |= 1U;
    SCG->SPLLCFG |= SCG_SPLLCFG_PREDIV(0x7U);
    SCG->SPLLCFG &= ~SCG_SPLLCFG_MULT(0x1FU);
    SCG->SPLLDIV |= SCG_SPLLDIV_SPLLDIV2(0x1U);
    SCG->SPLLCSR |= SCG_SPLLCSR_SPLLEN(1U);

    while (!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK))
    {
        // Wait until the SPLL is valid
    }
}
