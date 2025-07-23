#include "receiver.h"
#include "ConfigManager.h"


void receive_esp8266_data(void) {
    Int16 len = PullSerialBuffer(&uart_buffer_3, esp8266_buffer, MEM_SIZE);
    for (int counter = 0; counter < len; counter++) {
        parser_esp8266(esp8266_buffer[counter]);
    }
}

void receive_all(void) {
    receive_esp8266_data();
}