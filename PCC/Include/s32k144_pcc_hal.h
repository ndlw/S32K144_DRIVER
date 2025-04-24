/**
 * @file HAL_PCC_Module.h
 * @author Vo Doan Quynh Nhi
 * @brief
 * @version 0.1
 * @date 2025-01-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef INC_S32K1XX_PCC_HAL_H_
#define INC_S32K1XX_PCC_HAL_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "S32K144.h"

/*******************************************************************************
* MACRO
*******************************************************************************/
#define PR_BIT_SET   1U                 /* Macro to set a peripheral reset (PR) bit. */
#define PR_BIT_CLEAR 0U                 /* Macro to clear a peripheral reset (PR) bit. */

/*******************************************************************************/
/* Type Definitions                                                            */
/*******************************************************************************/

/**
 * @enum PeripheralClockSource
 * @brief Enumeration of possible clock sources for a peripheral.
 */
typedef enum
{
    CLOCK_OFF = 0x00U,                                  /* Clock is off */
    CLOCK_OPTION_1 = 0x01U,                             /* Clock option 1 */
    CLOCK_OPTION_2 = 0x02U,                             /* Clock option 2 */
    CLOCK_OPTION_3 = 0x03U,                             /* Clock option 3 */
    CLOCK_OPTION_4 = 0x04U,                             /* Clock option 4 */
    CLOCK_OPTION_5 = 0x05U,                             /* Clock option 5 */
    CLOCK_OPTION_6 = 0x06U,                             /* Clock option 6 */
    CLOCK_OPTION_7 = 0x07U                              /* Clock option 7 */
} PeripheralClockSource;

/**
 * @enum PeripheralClockFractionSelect
 * @brief Enumeration for selecting the fractional value of the clock divider.
 */
typedef enum
{
    PCD_FRACTIONAL_VALUE_0 = 0x0U,                      /* Fractional value is 0 */
    PCD_FRACTIONAL_VALUE_1 = 0X1U                       /* Fractional value is 1 */
} PeripheralClockFractionSelect;

/**
 * @enum PeripheralClockDividerSelect
 * @brief Enumeration for selecting the clock divider value.
 */
typedef enum
{
    PCD_DIVIDE_BY_1 = 0x00U,                            /* Divide by 1 */
    PCD_DIVIDE_BY_2 = 0x01U,                            /* Divide by 2 */
    PCD_DIVIDE_BY_3 = 0x02U,                            /* Divide by 3 */
    PCD_DIVIDE_BY_4 = 0x03U,                            /* Divide by 4 */
    PCD_DIVIDE_BY_5 = 0x04U,                            /* Divide by 5 */
    PCD_DIVIDE_BY_6 = 0x05U,                            /* Divide by 6 */
    PCD_DIVIDE_BY_7 = 0x06U,                            /* Divide by 7 */
    PCD_DIVIDE_BY_8 = 0x07U                             /* Divide by 8 */
} PeripheralClockDividerSelect;

/*******************************************************************************
* Prototypes
******************************************************************************/
/**
 * @brief Check the peripheral reset (PR) status.
 *
 * @param peripheralIndex            [Input] Index of the peripheral to check.
 * @return uint32_t                  Returns 0 if the check is successful
 */
uint32_t HAL_Check_PR( uint32_t peripheralIndex);

/**
 * @brief Enable the clock for a specified peripheral.
 *
 * @param peripheralIndex           [Input] Index of the peripheral to check.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Enable_Peripheral_Clock( uint32_t peripheralIndex);

/**
 * @brief select the clock source for a specified peripheral.
 *
 * @param peripheralIndex           [Input] Index of the peripheral to check.
 * @param source                    [Input] Clock source to be set for the peripheral.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Clock_Source_Select( uint32_t peripheralIndex, PeripheralClockSource source);

/**
 * @brief Set the clock divider and fraction for a specified peripheral.
 *

 * @param peripheralIndex           [Input] Index of the peripheral.
 * @param divider                   [Input] Clock divider value to set.
 * @param fraction                  [Input] Clock fraction value to set.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Clock_Divider_Select(uint32_t peripheralIndex, PeripheralClockDividerSelect divider, PeripheralClockFractionSelect fraction);

/**
 * @brief Disable the clock
 *
 * @param peripheralIndex           [Input] Index of the peripheral.
 * @return uint32_t                 Returns 0 if the check is successful
 */
uint32_t HAL_Disable_Peripheral_Clock(uint32_t peripheralIndex);

void HAL_SystemClock_Config(void);

#endif /* INC_S32K1XX_PCC_HAL_H_ */
