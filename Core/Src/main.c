
#include "main.h"
#include "ConfigManager.h"
#include "../../Tools/buffer.h"
#include "esp8266.h"
#include "defs.h"
#include "../../Algorithms/receiver.h"
#include "debug.h"


int main(void) {
	config_manager();

    HAL_Delay(1000);

    debug_info(&DEBUG_PORT, "Initializing esp8266 ...");
	init_esp8266();

    // esp8266_Test();
    HAL_Delay(1000);

    while (1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

        HAL_Delay(1000);

        receive_all();
    }
}





void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        uart_1_rx_counter++;
        PushSerialBuffer(&uart_buffer_1, &uart_1_rx_byte, 1);
        HAL_UART_Receive_IT(&huart1, &uart_1_rx_byte, 1);
    }
    else if (huart->Instance == USART2) {
        uart_2_rx_counter++;
        PushSerialBuffer(&uart_buffer_2, &uart_2_rx_byte, 1);
        HAL_UART_Receive_IT(&huart2, &uart_2_rx_byte, 1);
    }
    else if (huart->Instance == USART3) {
        uart_3_rx_counter++;
        PushSerialBuffer(&uart_buffer_3, &uart_3_rx_byte, 1);
        HAL_UART_Receive_IT(&huart3, &uart_3_rx_byte, 1);
    }  
}



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
