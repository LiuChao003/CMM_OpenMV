/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
// UART config
#ifndef _UART_H_
#define _UART_H_
#define LPUART_FIFO_CAP		4

//#if defined(BOARD_OMVRT1)
//#define MICROPY_HW_UART4_NAME   "uart4"	//ALT2
//#define MICROPY_HW_UART4_RX     (pin_EMC_20)	// D0/RXD
//#define MICROPY_HW_UART4_TX     (pin_EMC_19)	// D1/TXD
//#define MICROPY_HW_UART4_ALT	2

//#else 
//// default board is i.MX RT1050/60 EVK
//#define MICROPY_HW_UART1_NAME   "repl"	//ALT2
//#define MICROPY_HW_UART1_RX     (pin_AD_B0_13)	// CMSIS-DAP
//#define MICROPY_HW_UART1_TX     (pin_AD_B0_12)	// CMSIS-DAP
//#define MICROPY_HW_UART1_ALT	2

//#define MICROPY_HW_UART2_NAME   "uart2"	//ALT2
//#define MICROPY_HW_UART2_RX    (pin_AD_B1_03)	// D7
//#define MICROPY_HW_UART2_TX    (pin_AD_B1_02)	// D6
//#define MICROPY_HW_UART2_ALT	2

//#define MICROPY_HW_UART3_NAME   "uart3"	//ALT2
//#define MICROPY_HW_UART3_RX     (pin_AD_B1_06)	// D0/RXD
//#define MICROPY_HW_UART3_TX     (pin_AD_B1_07)	// D1/TXD
//#define MICROPY_HW_UART3_ALT	2

//#define MICROPY_HW_UART6_NAME   "uart6"	//ALT2
//#define MICROPY_HW_UART6_RX    (pin_AD_B0_03)		// D8
//#define MICROPY_HW_UART6_TX    (pin_AD_B0_02)		// D9
//#define MICROPY_HW_UART6_ALT	2

//#define MICROPY_HW_UART8_NAME   "uart8"	// ALT2
//#define MICROPY_HW_UART8_RX    (pin_AD_B1_11)	// A1
//#define MICROPY_HW_UART8_TX    (pin_AD_B1_10)	// A0
//#define MICROPY_HW_UART8_ALT	2
//#endif

typedef enum {
	PYB_UART_0 = 0,
    PYB_UART_1 = 1,
    PYB_UART_2 = 2,
    PYB_UART_3 = 3,
    PYB_UART_4 = 4,
    PYB_UART_5 = 5,
    PYB_UART_6 = 6,
    PYB_UART_7 = 7,
    PYB_UART_8 = 8,
    PYB_UART_9 = 9,
    PYB_UART_NONE = 31, 
} pyb_uart_t;


#ifndef BOARD_OMVRT1
#define MICROPY_HW_UART_REPL_NAME   "repl"
#define repl_uart_id	PYB_UART_1
#endif

typedef struct _pyb_uart_obj_t pyb_uart_obj_t;
extern const mp_obj_type_t pyb_uart_type;

void uart_init0(void);
void uart_deinit(void);
void uart_irq_handler(void *base, void* pCtx);

mp_uint_t uart_rx_any(pyb_uart_obj_t *uart_obj);
int uart_rx_char(pyb_uart_obj_t *uart_obj);
void uart_tx_strn(pyb_uart_obj_t *uart_obj, const char *str, uint len);
void uart_tx_strn_cooked(pyb_uart_obj_t *uart_obj, const char *str, uint len);
#endif
