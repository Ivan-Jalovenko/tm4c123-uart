#ifndef CONFIG_H
#define CONFIG_H

// Uncomment the line below to use external LEDs (Port B)
//#define USE_EXTERNAL_LEDS

// By default, use internal LEDs (Port F)
#ifndef USE_EXTERNAL_LEDS
#define USE_INTERNAL_LEDS
#endif


#include <TM4C123GH6PM.h>


/* ==============================
 *     		Port Definitions
 * ==============================
 */

#define GPIO_PORT_A         (1u << 0)
#define GPIO_PORT_B         (1u << 1)
#define GPIO_PORT_F         (1u << 5)

#define PA0                 (1u << 0)
#define PA1                 (1u << 1)

#define PB2                 (1u << 2)
#define PB3                 (1u << 3)
#define PB4                 (1u << 4)

#define PF1                 (1u << 1)
#define PF2                 (1u << 2)
#define PF3                 (1u << 3)


/* ==============================
 *						UART
 * ==============================
 */
// UART Module Selection
#define UART_0              (1u << 0) 

// UART Control Register
#define UART_CTL_DISABLE    (0x0u)
#define UART_CTL_UARTEN     (1u << 0)
#define UART_CTL_TXE        (1u << 8)
#define UART_CTL_RXE 	      (1u << 9)

// UART Flag Register
#define UART_FR_RXFF        (1u << 4)
#define UART_FR_TXFF        (1u << 5)

// UART Clock Configuration
#define UART_CC_PIOSC       0x5

// UART Baud Rate Configuration
#define UART_IBRD_9600      104
#define UART_FBRD_9600      11

// UART Line Control
#define UART_LCRH_8N1       (0x3 << 5) // 8-bit, no parity, 1 stop bit, no FIFO

// GPIO Pin Control for UART
#define GPIO_PCTL_PA0_M     (0xFu << 0)   // Mask for PA0 function bits
#define GPIO_PCTL_PA1_M     (0xFu << 4)   // Mask for PA1 function bits
#define GPIO_PCTL_PA0_U0RX  (0x1u << 0)   // PA0 = U0RX
#define GPIO_PCTL_PA1_U0TX  (0x1u << 4)   // PA1 = U0TX


/* ==============================
 *     		LED Configuration
 * ==============================
 */

#ifdef USE_INTERNAL_LEDS
	#define LED_GPIO          GPIOF
	#define LED_GPIO_BASE     GPIO_PORT_F

  #define LED_RED           PF1
  #define LED_BLUE          PF2
  #define LED_GREEN         PF3
#else
  #define LED_GPIO          GPIOB
	#define LED_GPIO_BASE     GPIO_PORT_B
	
	#define LED_RED           PB2
  #define LED_BLUE          PB3
  #define LED_GREEN         PB4 
#endif

#define CMD_LED_RED         'r'
#define CMD_LED_BLUE        'b'
#define CMD_LED_GREEN       'g'
#define CMD_LED_OFF         'f'

#define CMD_HELP            'h'


#endif // CONFIG_H
