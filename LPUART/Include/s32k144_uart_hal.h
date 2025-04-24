/**
 * @file main.c
 * @author Nguyen Dinh Le Quang (ndlequang1242@gmail.com)
 * @brief  This file contains the LPUART HAL driver for S32K144
 *
 * @version 0.1
 * @date 2025-2-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef S32K144_UART_HAL_H
#define S32K144_UART_HAL_H

/*******************************************************************************
 * Inclusion
 ******************************************************************************/

#include "S32K144.h"
#include "stdio.h"

/*******************************************************************************
* API
******************************************************************************/

/**
 * @brief Set field TE of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetCtrlTe(LPUART_Type *lpuart);

/**
 * @brief Clear field TE of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearCtrlTe(LPUART_Type *lpuart);

/**
 * @brief Set field RE of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetCtrlRe(LPUART_Type *lpuart);

/**
 * @brief Clear field RE of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearCtrlRe(LPUART_Type *lpuart);

/**
 * @brief Set field M of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetCtrlM(LPUART_Type *lpuart);

/**
 * @brief Clear field M of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearCtrlM(LPUART_Type *lpuart);

/**
 * @brief Set field M7 of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetCtrlM7(LPUART_Type *lpuart);

/**
 * @brief Clear field M7 of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearCtrlM7(LPUART_Type *lpuart);

/**
 * @brief Set field M10 of BAULD register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetBaudM10(LPUART_Type *lpuart);

/**
 * @brief Clear field M10 of BAULD register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearBaudM10(LPUART_Type *lpuart);

/**
 * @brief Set field SBNS of BAULD register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetBaudSbns(LPUART_Type *lpuart);

/**
 * @brief Clear field SBNS of BAULD register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearBaudSbns(LPUART_Type *lpuart);

/**
 * @brief Set field PE of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetCtrlPe(LPUART_Type *lpuart);

/**
 * @brief Clear field PE of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearCtrlPe(LPUART_Type *lpuart);

/**
 * @brief Set field PT of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetCtrlPt(LPUART_Type *lpuart);

/**
 * @brief Clear field PT of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearCtrlPt(LPUART_Type *lpuart);

/**
 * @brief Set field MSBF of STAT register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetStatMsbf(LPUART_Type *lpuart);

/**
 * @brief Clear field MSBF of STAT register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearStatMsbf(LPUART_Type *lpuart);

/**
 * @brief Set field RXINV of STAT register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetStatRxinv(LPUART_Type *lpuart);

/**
 * @brief Clear field RXINV of STAT register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearStatRxinv(LPUART_Type *lpuart);

/**
 * @brief Set field TXINV of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetCtrlTxinv(LPUART_Type *lpuart);

/**
 * @brief Clear field TXINV of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearCtrlTxinv(LPUART_Type *lpuart);

/**
 * @brief Set field SBR of BAUD register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetBaudSbr(LPUART_Type *lpuart, uint32_t sbr);

/**
 * @brief Clear field SBR of BAUD register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearBaudSbr(LPUART_Type *lpuart);

/**
 * @brief Set field OSR of BAUD register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetBaudOsr(LPUART_Type *lpuart, uint8_t osr);

/**
 * @brief Clear field OSR of BAUD register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearBaudOsr(LPUART_Type *lpuart);

/**
 * @brief Read value field RDRF of STAT register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 * @return uint8_t Return 1 or 0.
 */
uint8_t HAL_UART_ReadStatRdrf(LPUART_Type *lpuart);

/**
 * @brief Read value field TDRF of STAT register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 * @return uint8_t Return 1 or 0.
 */
uint8_t HAL_UART_ReadStatTdrf(LPUART_Type *lpuart);

/**
 * @brief Set field RIE of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_SetCtrlRie(LPUART_Type *lpuart);

/**
 * @brief Clear field RIE of CTRL register.
 *
 * @param[in] lpuart Pointer to the LPUART register structure.
 */
void HAL_UART_ClearCtrlRie(LPUART_Type *lpuart);

#endif /* S32K144_UART_HAL_H */
