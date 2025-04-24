/**
 * @file main.c
 * @author Nguyen Dinh Le Quang (ndlequang1242@gmail.com)
 * @brief  This file contains the LPUART HAL driver for S32K144.
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

#include "../include/s32k144_uart_hal.h"

/*******************************************************************************
* Code
******************************************************************************/

void HAL_UART_SetCtrlTe(LPUART_Type *lpuart)
{
    lpuart->CTRL |= LPUART_CTRL_TE_MASK;
}

void HAL_UART_ClearCtrlTe(LPUART_Type *lpuart)
{
    lpuart->CTRL &= ~LPUART_CTRL_TE_MASK;
}

void HAL_UART_SetCtrlRe(LPUART_Type *lpuart)
{
    lpuart->CTRL |= LPUART_CTRL_RE_MASK;
}

void HAL_UART_ClearCtrlRe(LPUART_Type *lpuart)
{
    lpuart->CTRL &= ~LPUART_CTRL_RE_MASK;
}

void HAL_UART_SetCtrlM(LPUART_Type *lpuart)
{
    lpuart->CTRL |= LPUART_CTRL_M_MASK;
}

void HAL_UART_ClearCtrlM(LPUART_Type *lpuart)
{
    lpuart->CTRL &= ~LPUART_CTRL_M_MASK;
}

void HAL_UART_SetCtrlM7(LPUART_Type *lpuart)
{
    lpuart->CTRL |= LPUART_CTRL_M7_MASK;
}

void HAL_UART_ClearCtrlM7(LPUART_Type *lpuart)
{
    lpuart->CTRL &= ~LPUART_CTRL_M7_MASK;
}

void HAL_UART_SetBaudM10(LPUART_Type *lpuart)
{
    lpuart->BAUD |= LPUART_BAUD_M10_MASK;
}

void HAL_UART_ClearBaudM10(LPUART_Type *lpuart)
{
    lpuart->BAUD &= ~LPUART_BAUD_M10_MASK;
}

void HAL_UART_SetBaudSbns(LPUART_Type *lpuart)
{
    lpuart->BAUD |= LPUART_BAUD_SBNS_MASK;
}

void HAL_UART_ClearBaudSbns(LPUART_Type *lpuart)
{
    lpuart->BAUD &= ~LPUART_BAUD_SBNS_MASK;
}

void HAL_UART_SetCtrlPe(LPUART_Type *lpuart)
{
    lpuart->CTRL |= LPUART_CTRL_PE_MASK;
}

void HAL_UART_ClearCtrlPe(LPUART_Type *lpuart)
{
    lpuart->CTRL &= ~LPUART_CTRL_PE_MASK;
}

void HAL_UART_SetCtrlPt(LPUART_Type *lpuart)
{
    lpuart->CTRL |= LPUART_CTRL_PT_MASK;
}

void HAL_UART_ClearCtrlPt(LPUART_Type *lpuart)
{
    lpuart->CTRL &= ~LPUART_CTRL_PT_MASK;
}

void HAL_UART_SetStatMsbf(LPUART_Type *lpuart)
{
    lpuart->STAT |= LPUART_STAT_MSBF_MASK;
}

void HAL_UART_ClearStatMsbf(LPUART_Type *lpuart)
{
    lpuart->STAT &= ~LPUART_STAT_MSBF_MASK;
}

void HAL_UART_SetStatRxinv(LPUART_Type *lpuart)
{
    lpuart->STAT |= LPUART_STAT_RXINV_MASK;
}

void HAL_UART_ClearStatRxinv(LPUART_Type *lpuart)
{
    lpuart->STAT &= ~LPUART_STAT_RXINV_MASK;
}

void HAL_UART_SetCtrlTxinv(LPUART_Type *lpuart)
{
    lpuart->CTRL |= LPUART_CTRL_TXINV_MASK;
}
void HAL_UART_ClearCtrlTxinv(LPUART_Type *lpuart)
{
    lpuart->CTRL &= ~LPUART_CTRL_TXINV_MASK;
}

void HAL_UART_SetBaudSbr(LPUART_Type *lpuart, uint32_t sbr)
{
    lpuart->BAUD |= LPUART_BAUD_SBR(sbr);
}

void HAL_UART_ClearBaudSbr(LPUART_Type *lpuart)
{
    lpuart->BAUD &= ~LPUART_BAUD_SBR_MASK;
}

void HAL_UART_SetBaudOsr(LPUART_Type *lpuart, uint8_t osr)
{
    lpuart->BAUD = LPUART_BAUD_OSR(osr);
}

void HAL_UART_ClearBaudOsr(LPUART_Type *lpuart)
{
    lpuart->BAUD &= ~LPUART_BAUD_OSR_MASK;
}

uint8_t HAL_UART_ReadStatRdrf(LPUART_Type *lpuart)
{
    return (lpuart->STAT & LPUART_STAT_RDRF_MASK) ? 1 : 0;
}

uint8_t HAL_UART_ReadStatTdrf(LPUART_Type *lpuart)
{
    uint8_t result = (uint8_t)(lpuart->STAT & LPUART_STAT_TDRE_MASK);
    return result;
}

void HAL_UART_SetCtrlRie(LPUART_Type *lpuart)
{
    lpuart->CTRL |= LPUART_CTRL_RIE_MASK;
}

void HAL_UART_ClearCtrlRie(LPUART_Type *lpuart)
{
    lpuart->CTRL &= ~LPUART_CTRL_RIE_MASK;
}

