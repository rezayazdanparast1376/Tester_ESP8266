#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_
#include "../../Tools/buffer.h"
#include "config.h"
#include "main.h"

#define MEM_SIZE 200

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

extern volatile SERIAL_BUFFER uart_buffer_1;
extern volatile SERIAL_BUFFER uart_buffer_2;
extern volatile SERIAL_BUFFER uart_buffer_3;

extern uint8_t uart_1_mem[MEM_SIZE];
extern uint8_t uart_2_mem[MEM_SIZE];
extern uint8_t uart_3_mem[MEM_SIZE];

extern UInt8 esp8266_buffer[MEM_SIZE];


extern volatile uint8_t uart_1_rx_byte;
extern volatile uint8_t uart_2_rx_byte;
extern volatile uint8_t uart_3_rx_byte;

extern volatile uint32_t uart_1_rx_counter;
extern volatile uint32_t uart_2_rx_counter;
extern volatile uint32_t uart_3_rx_counter;

void config_manager(void);

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);




























#endif  //_CONFIG_MANAGER_H_
