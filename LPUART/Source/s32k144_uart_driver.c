/**
 * @file main.c
 * @author Nguyen Dinh Le Quang (ndlequang1242@gmail.com)
 * @brief  This file contains the LPUART driver for S32K144.
 *
 * @version 0.1
 * @date 2025-2-10
 *
 * @copyright Copyright (c) 2025
 *
 */

/*******************************************************************************
 * Inclusion
 ******************************************************************************/

#include "../src/Driver/LPUART/Include/s32k144_uart_driver.h"

/*******************************************************************************
 * Macro
 ******************************************************************************/

#define ERROR_PERCENTAGE (0.003) /* Maximum percentage error of baud rate */

#define MIN_VALUE_OSR (4U)  /* Min value of OSR */
#define MAX_VALUE_OSR (31U) /* Max value of OSR */

/*******************************************************************************
* Variables
******************************************************************************/

static LPUART_FUNC_PTR_type LPUART_callback_func_arr[3] = {NULL};

static LPUART_Type *default_lpuart;

extern uint32_t clock;

/*******************************************************************************
* Code
******************************************************************************/

Std_UART_Status LPUART_SetBaudrate(uint32_t baud_rate)
{
    Std_UART_Status status = UART_E_OK;
    uint32_t valid_baud_rates[] = {4800, 9600, 14400, 19200, 38400, 57600, 115200};
    uint8_t num_valid_baud_rates = sizeof(valid_baud_rates) / sizeof(valid_baud_rates[0]);
    uint8_t is_valid = 0;

    for(int idx = 0; idx < num_valid_baud_rates; idx++)
    {
        if(valid_baud_rates[idx] == baud_rate)
        {
            is_valid = 1;
            /* stop looping */
            idx = num_valid_baud_rates;
        }
    }

    if(is_valid)
    {
    	// uint32_t min = (uint32_t)(baud_rate * ERROR_PERCENTAGE);
    	uint32_t min = baud_rate;
        uint8_t osr = 0;
        uint32_t sbr = 0;
        for(uint8_t tmp_osr = MIN_VALUE_OSR; tmp_osr <= MAX_VALUE_OSR; tmp_osr++)
        {
        	uint32_t tmp_sbr = clock / (baud_rate * (tmp_osr + 1));
            uint32_t tmp_baud_rate = clock / (tmp_sbr*(tmp_osr + 1));
            if((baud_rate - tmp_baud_rate) <= min || (tmp_baud_rate - baud_rate) <= min)
            {
                min = (uint32_t)(baud_rate - tmp_baud_rate);
                osr = tmp_osr;
                sbr = tmp_sbr;
            }
            else
            {
                /* Do nothing */
            }
        }

        /* Clear SBR and OSR */
        HAL_UART_ClearBaudSbr(default_lpuart);
        HAL_UART_ClearBaudOsr(default_lpuart);
        /* Write SBR and OSR */
        HAL_UART_SetBaudOsr(default_lpuart, osr);
        HAL_UART_SetBaudSbr(default_lpuart, sbr);
        }
    else
    {
        status = UART_E_NOT_OK;
    }

    return status;
}

Std_UART_Status LPUART_init(LPUART_Config_type* lpuart_config)
{
    Std_UART_Status status = UART_E_OK;
    if(NULL != lpuart_config)
    {
        if((NULL != lpuart_config->lpuart)
        && ((DISABLE_PARITY == lpuart_config->parity) || (ENABLE_PARITY == lpuart_config->parity))
        && ((EVEN_PARITY == lpuart_config->parity_type) || (ODD_PARITY == lpuart_config->parity_type))
        && ((DATA_BIT_7 == lpuart_config->data_bits) || (DATA_BIT_8 == lpuart_config->data_bits) || (DATA_BIT_9 == lpuart_config->data_bits) || (DATA_BIT_10 == lpuart_config->data_bits))
        && ((STOP_BIT_1 == lpuart_config->stop_bits) || (STOP_BIT_1 == lpuart_config->stop_bits))
        && ((LSB == lpuart_config->msb_first) || (MSB == lpuart_config->msb_first))
        && ((NOT_INVERT == lpuart_config->rx_polarity) || (INVERT == lpuart_config->rx_polarity))
        && ((NOT_INVERT == lpuart_config->tx_polarity) || (INVERT == lpuart_config->tx_polarity))
        && ((DISABLE_INTERRUPT == lpuart_config->rx_interrupt) || (ENABLE_INTERRUPT == lpuart_config->rx_interrupt))
        )
        {
            default_lpuart = lpuart_config->lpuart;
            /* Disable TX RX via bits CTRL[RE, TE] */
            HAL_UART_ClearCtrlTe(default_lpuart);

            HAL_UART_ClearCtrlRe(default_lpuart);

            /* config baud rate */
            status = LPUART_SetBaudrate(lpuart_config->baud_rate);

            /* config number of data bit*/
            switch (lpuart_config->data_bits)
            {
            case DATA_BIT_7:
                HAL_UART_ClearCtrlM(default_lpuart);
                HAL_UART_SetCtrlM7(default_lpuart);
                HAL_UART_ClearBaudM10(default_lpuart);
                break;
            case DATA_BIT_8:
                HAL_UART_ClearCtrlM(default_lpuart);
                HAL_UART_ClearCtrlM7(default_lpuart);
                HAL_UART_ClearBaudM10(default_lpuart);
                break;
            case DATA_BIT_9:
                HAL_UART_SetCtrlM(default_lpuart);
                HAL_UART_ClearCtrlM7(default_lpuart);
                HAL_UART_ClearBaudM10(default_lpuart);
                break;
            case DATA_BIT_10:
                HAL_UART_ClearCtrlM(default_lpuart);
                HAL_UART_ClearCtrlM7(default_lpuart);
                HAL_UART_SetBaudM10(default_lpuart);
                break;
            default:
                HAL_UART_ClearCtrlM(default_lpuart);
                HAL_UART_ClearCtrlM7(default_lpuart);
                HAL_UART_ClearBaudM10(default_lpuart);
                break;
            }
            /* config number of stop bit */
            if(STOP_BIT_1 == lpuart_config->stop_bits)
            {
                HAL_UART_ClearBaudSbns(default_lpuart);
            }
            else if(STOP_BIT_2 == lpuart_config->stop_bits)
            {
                HAL_UART_SetBaudSbns(default_lpuart);
            }
            else
            {
                /* Do nothing */
            }

            /* config parity */
            if(DISABLE_PARITY == lpuart_config->parity)
            {
                HAL_UART_ClearCtrlPe(default_lpuart);
            }
            else if (ENABLE_PARITY ==  lpuart_config->parity)
            {
                HAL_UART_SetCtrlPe(default_lpuart);
                if(EVEN_PARITY == lpuart_config->parity_type)
                {
                    HAL_UART_ClearCtrlPt(default_lpuart);
                }
                else if(ODD_PARITY == lpuart_config->parity_type)
                {
                    HAL_UART_SetCtrlPt(default_lpuart);
                }
                else
                {
                    /* Do nothing */
                }
            }
            else
            {
                /* Do nothing */
            }

            /* Configure MSB or LSB first */
            if(LSB == lpuart_config->msb_first)
            {
                HAL_UART_ClearStatMsbf(default_lpuart);
            }
            else if (MSB ==  lpuart_config->msb_first)
            {
                HAL_UART_SetStatMsbf(default_lpuart);
            }
            else
            {
                /* Do nothing */
            }

            /* Configure Rx data polarity */
            if(NOT_INVERT == lpuart_config->rx_polarity)
            {
                HAL_UART_ClearStatRxinv(default_lpuart);
            }
            else if (INVERT ==  lpuart_config->rx_polarity)
            {
                HAL_UART_SetStatRxinv(default_lpuart);
            }
            else
            {
                /* Do nothing */
            }

            /* Configure Tx data polarity */
            if(NOT_INVERT == lpuart_config->tx_polarity)
            {
                default_lpuart->CTRL &= ~LPUART_CTRL_TXINV_MASK;
            }
            else if (INVERT ==  lpuart_config->tx_polarity)
            {
                default_lpuart->STAT |= LPUART_CTRL_TXINV_MASK;
            }
            else
            {
                /* Do nothing */
            }

            if(DISABLE_INTERRUPT == lpuart_config->rx_interrupt)
            {
                HAL_UART_ClearCtrlRie(default_lpuart);
            }
            else if(ENABLE_INTERRUPT == lpuart_config->rx_interrupt)
            {
                HAL_UART_SetCtrlRie(default_lpuart);
            }
            else
            {
                /* Do nothing */
            }

            /* enable TX RX via bits CTRL[RE, TE] */
            HAL_UART_SetCtrlTe(default_lpuart);

            HAL_UART_SetCtrlRe(default_lpuart);
        }
        else
        {
            status = UART_E_NOT_OK;
        }
    }
    else
    {
        status = UART_E_NOT_OK;
    }

    return status;
}

uint8_t LPUART_Receive(void)
{
    uint8_t data;
    while (!HAL_UART_ReadStatRdrf(default_lpuart))
    {
        /* Wait data */
    };

    data = default_lpuart->DATA;
    /* clear RDRF */
    default_lpuart->STAT |= LPUART_STAT_RDRF_MASK;
    return data;
}


Std_UART_Status LPUART_Transmit(uint8_t data)
{
    Std_UART_Status status = UART_E_OK;
//    if(NULL != default_lpuart)
//    {
//        while (!(HAL_UART_ReadStatTdrf(default_lpuart)))
//        {
//            /* Wait data */
//        };
//        default_lpuart->DATA = data;
//    }
//    else
//    {
//        status = UART_E_NOT_OK;
//    }
    while (!(LPUART1->STAT & LPUART_STAT_TDRE_MASK));
		LPUART1->DATA = data;
	while (!(LPUART1->STAT & LPUART_STAT_TC_MASK)) {}

    return status;
}

Std_UART_Status LPUART_Transmits(uint8_t *data, uint32_t length)
{
    Std_UART_Status status = UART_E_OK;
    if(NULL != data)
    {
        for (uint32_t i = 0; i < length; i++)
        {
            LPUART_Transmit(data[i]);
        }
    }
    else
    {
        status = UART_E_NOT_OK;
    }

    return status;
}

Std_UART_Status LPUART_IRQEnable(void)
{
    Std_UART_Status status = UART_E_OK;
    if(NULL != default_lpuart)
    {
        HAL_UART_SetCtrlRie(default_lpuart);
    }
    else
    {
        status = UART_E_NOT_OK;
    }

    return status;
}


Std_UART_Status LPUART_IRQDisable(void)
{
    Std_UART_Status status = UART_E_OK;
    if(NULL != default_lpuart)
    {
        HAL_UART_ClearCtrlRie(default_lpuart);
    }
    else
    {
        status = UART_E_NOT_OK;
    }

    return status;
}


Std_UART_Status LPUART_Register_InterruptHandler(LPUART_FUNC_PTR_type App_Function)
{
    Std_UART_Status status = UART_E_OK;

        if(NULL != App_Function)
        {
            if (default_lpuart == LPUART0)
            {
                LPUART_callback_func_arr[0] = App_Function;
            }
            else if (default_lpuart == LPUART1)
            {
                LPUART_callback_func_arr[1] = App_Function;
            }
            else if (default_lpuart == LPUART2)
            {
                LPUART_callback_func_arr[2] = App_Function;
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            status = UART_E_NOT_OK;
        }

    return status;
}

void LPUART0_RxTx_IRQHandler(void)
{
    if (NULL != LPUART_callback_func_arr[0])
    {
        LPUART_callback_func_arr[0]();
    }
    else
    {
        /* do nothing */
    }
}

void LPUART1_RxTx_IRQHandler(void)
{
   if (NULL != LPUART_callback_func_arr[1])
   {
       LPUART_callback_func_arr[1]();
   }
   else
   {
       /* do nothing */
   }
}

void LPUART2_RxTx_IRQHandler(void)
{
    if (NULL != LPUART_callback_func_arr[2])
    {
        LPUART_callback_func_arr[2]();
    }
    else
    {
        /* do nothing */
    }
}

Std_UART_Status LPUART_DeInit(void)
{
    Std_UART_Status status = UART_E_OK;
    if(NULL != default_lpuart)
    {
        HAL_UART_ClearCtrlTe(default_lpuart);
        HAL_UART_ClearCtrlRe(default_lpuart);
    }
    else
    {
        status = UART_E_NOT_OK;
    }

    return status;
}
