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

#ifndef S32K144_UART_DRIVER_H
#define S32K144_UART_DRIVER_H

/*******************************************************************************
 * Inclusion
 ******************************************************************************/

#include "s32k144_uart_hal.h"

/*******************************************************************************
* Definitions
******************************************************************************/

typedef void (*LPUART_FUNC_PTR_type)(void);

typedef enum
{
    UART_E_OK,    /* Successful */
    UART_E_NOT_OK /* failure */
} Std_UART_Status;

typedef enum
{
    DISABLE_PARITY = 0, /* Disable parity*/
    ENABLE_PARITY  = 1, /* Enable parity */
    EVEN_PARITY    = 2, /* Even parity */
    ODD_PARITY     = 3  /* Odd parity*/
} LPUART_PARITY_type;

typedef enum
{
    DATA_BIT_7  = 0, /* 7 bit data characters */
    DATA_BIT_8  = 1, /* 8 bit data characters */
    DATA_BIT_9  = 2, /* 9 bit data characters */
    DATA_BIT_10 = 3  /* 10 bit data characters */
} LPUART_DATA_BIT_type;

typedef enum
{
    STOP_BIT_1 = 0, /* 1 stop bit */
    STOP_BIT_2 = 1  /* 2 stop bits */
} LPUART_STOP_BIT_type;

typedef enum
{
    LSB = 0, /* LSB */
    MSB = 1  /* MSB */
} LPUART_MSB_type;

typedef enum
{
    NOT_INVERT = 0, /* Not invert */
    INVERT     = 1  /* Invert */
} LPUART_POLARITY_type;

typedef enum
{
    DISABLE_INTERRUPT = 0, /* Disable interrupt */
    ENABLE_INTERRUPT  = 1  /* Enable interrupt */
} LPUART_INTERRUPT_type;

typedef struct {
    LPUART_Type *lpuart;
    uint32_t baud_rate;
    LPUART_PARITY_type  parity;
    LPUART_PARITY_type  parity_type;
    LPUART_DATA_BIT_type  data_bits;
    LPUART_STOP_BIT_type  stop_bits;
    LPUART_MSB_type  msb_first;
    LPUART_POLARITY_type  rx_polarity;
    LPUART_POLARITY_type  tx_polarity;
    LPUART_INTERRUPT_type  rx_interrupt;
} LPUART_Config_type;

/*******************************************************************************
* API
******************************************************************************/

/**
 * @brief Config baud rate.
 *
 * @param[in] baud_rate Baud rate.
 * @return Std_UART_Status Returns LPUART_DRIVER_OK if successful, otherwise returns LPUART_DRIVER_NOT_OK.
 */
Std_UART_Status LPUART_SetBaudrate(uint32_t baud_rate);

/**
 * @brief Initialize the specified LPUART with the given configuration.
 *
 * @param[in][out] lpuart_config Pointer to the LPUART configuration structure.
 * @return Std_UART_Status Returns LPUART_DRIVER_OK if successful, otherwise returns LPUART_DRIVER_NOT_OK.
 */
Std_UART_Status LPUART_init(LPUART_Config_type* lpuart_config);

/**
 * @brief Receives data from LPUART.
 *
 * @return uint8_t Returns the received data from LPUART.
 */
uint8_t LPUART_Receive(void);

/**
 * @brief Transmits data via LPUART.
 *
 * @param[in] data The data to be transmitted.
 * @return Std_UART_Status Returns LPUART_DRIVER_OK if successful, otherwise returns LPUART_DRIVER_NOT_OK.
 */
Std_UART_Status LPUART_Transmit(uint8_t data);

/**
 * @brief Transmits a sequence of data via LPUART.
 *
 * @param[in] data Pointer to the data array to be transmitted.
 * @param[in] length The number of bytes to transmit.
 * @return Std_UART_Status Returns LPUART_DRIVER_OK if successful, otherwise returns LPUART_DRIVER_NOT_OK.
 */
Std_UART_Status LPUART_Transmits(uint8_t *data, uint32_t length);

/**
 * @brief Enables LPUART interrupts.
 *
 * @return Std_UART_Status Returns LPUART_DRIVER_OK if successful, otherwise returns LPUART_DRIVER_NOT_OK.
 */
Std_UART_Status LPUART_IRQEnable(void);

/**
 * @brief Disable LPUART interrupts.
 *
 * @return Std_UART_Status Returns LPUART_DRIVER_OK if successful, otherwise returns LPUART_DRIVER_NOT_OK.
 */
Std_UART_Status LPUART_IRQDisable(void);

/**
 * @brief Registers an interrupt handler for the LPUART.
 *
 * @param[in] App_Function Pointer to the callback function to be registered.
 * @return Std_UART_Status Returns LPUART_DRIVER_OK if successful, otherwise returns LPUART_DRIVER_NOT_OK.
 */
Std_UART_Status LPUART_Register_InterruptHandler(LPUART_FUNC_PTR_type App_Function);

/**
 * @brief De-initializes the LPUART.
 *
 * @return Std_UART_Status Returns LPUART_DRIVER_OK if successful, otherwise returns LPUART_DRIVER_NOT_OK.
 */
Std_UART_Status LPUART_DeInit(void);

#endif /* S32K144_UART_DRIVER_H */
