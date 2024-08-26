/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include <stdio.h>

int main() {

    int x = 0;

    for(int i = 0x20004000; i < 0x20040000; i++){
        uint8_t volatile * const p_reg = (uint8_t *) (i);
        *p_reg = 0x55;
    }

    stdio_init_all();

    sleep_ms(250);

    // char *p = (char *)0x20004000;

    // for(int i = 0; i < 15; i++) {
    //     printf("Hello, world!\n");
    //     sleep_ms(250);
    // }

    // printf("the value at address 0x20004000 is %x", p[0]);

    // for(int i = 0; i < 15; i++) {
    //     printf("Hello, world!\n");
    //     sleep_ms(250);
    // }

    // printf("input a character");

    // char input;

    // input = getchar();

    // printf("%c\n", input);

    #ifndef PICO_DEFAULT_LED_PIN
    #warning blink example requires a board with a regular LED
    #else
        const uint LED_PIN = PICO_DEFAULT_LED_PIN;
        gpio_init(LED_PIN);
        gpio_set_dir(LED_PIN, GPIO_OUT);
        while (true) {
            printf("Hello, world!\n");
            gpio_put(LED_PIN, 1);
            sleep_ms(250);
            gpio_put(LED_PIN, 0);
            sleep_ms(250);
        }
    #endif
}
