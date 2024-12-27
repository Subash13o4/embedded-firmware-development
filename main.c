#include <stdint.h>
#include <stdlib.h>

// UART Register Definitions
#define __I  volatile const // 'read only' permissions
#define __O  volatile       // 'write only' permissions
#define __IO volatile       // 'read / write' permissions

#define UCSR_BASE_ADDR 0x50000000

// UART Register Structures
typedef struct {
    uint32_t DATA : 8;
    uint32_t : 24;
} ucsr_u_data_t;

typedef struct {
    uint32_t : 5;
    uint32_t READY : 1;
    uint32_t : 7;
    uint32_t TX_DONE : 1;
    uint32_t : 18;
} ucsr_u_stat_t;

typedef struct {
    uint32_t : 9;
    uint32_t START : 1;
    uint32_t : 22;
} ucsr_u_ctrl_t;

typedef struct {
    union {
        __IO uint32_t U_DATA;
        __IO ucsr_u_data_t U_DATA_bf;
    };
    union {
        __IO uint32_t U_STAT;
        __IO ucsr_u_stat_t U_STAT_bf;
    };
    union {
        __O uint32_t U_CTRL;
        __O ucsr_u_ctrl_t U_CTRL_bf;
    };
} ucsr_t;

#define UCSR ((ucsr_t*)(UCSR_BASE_ADDR))

// GPIO Register Definitions
#define GCSR_BASE_ADDR 0x40000000

typedef struct {
    uint32_t DATA : 32;
} gcsr_gpio_0_t;

typedef struct {
    union {
        __IO uint32_t GPIO_0;
        __IO gcsr_gpio_0_t GPIO_0_bf;
    };
} gcsr_t;

#define GCSR ((gcsr_t*)(GCSR_BASE_ADDR))

// UART Function Definitions
void uart_send_char(uint8_t my_char)
{
    while (UCSR->U_STAT_bf.READY == 0);
    UCSR->U_DATA = my_char;
    UCSR->U_CTRL_bf.START = 1;
}

void uart_send_str(char *my_str)
{
    for (uint8_t i = 0; my_str[i] != '\0'; i++)
    {
        uart_send_char(my_str[i]);
    }
}

// Delay Function (Simulated Timing)
void delay_short()
{
    for (volatile uint64_t i = 0; i < 100000; i++);
}

int main()
{
    // Send "Hello World" via UART
    uart_send_str("hello world");

    // GPIO LED Blinking Simulation
    while (1)
    {
        GCSR->GPIO_0 = 0x55; // LED pattern 0x55
        delay_short();
        GCSR->GPIO_0 = 0xAA; // LED pattern 0xAA
        delay_short();
    }

    return 0;
}
