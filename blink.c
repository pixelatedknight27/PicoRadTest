/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include <stdio.h>

int main() {


    stdio_init_all();

    // wait until usb is intialized

    while(!stdio_usb_connected);

    char uinput1;

    uinput1 = getchar();

    printf("connection established\n", uinput1);

    printf("Writing 0x55 to writable SRAM\n");

    int input = 0x55;

    for(int i = 0x20004000; i < 0x20040000; i++){
        uint8_t volatile * const p_reg = (uint8_t *) (i);
        *p_reg = input;
    }

    //test byte
    // uint8_t volatile * const p_reg = (uint8_t *) (0x20004000);
    // *p_reg = 0b01000000;


    printf("done\n");
    sleep_ms(5*100);

    printf("send any message to continue to memory check\n");

    char uinput2;

    uinput2 = getchar();

    printf("connection established\n", uinput2);

    printf("scanning for changes\n");

    unsigned int changed = 0;

    // only checks if not equal to input, does not count the number of diff bits
    for(int i = 0x20004000; i < 0x20040000; i++){
        char *p = (char *)i;

        u_int8_t word = p[0] ^ input;
        for(int i = 0; i < 8; i++){
            if(word & 1){
                changed++;
            }
            word = word >> 1;
        }
    }

    printf("number of effected bits: %d\n", changed);

    return(0);

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

    // #ifndef PICO_DEFAULT_LED_PIN
    // #warning blink example requires a board with a regular LED
    // #else
    //     const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    //     gpio_init(LED_PIN);
    //     gpio_set_dir(LED_PIN, GPIO_OUT);
    //     while (true) {
    //         printf("Hello, world!\n");
    //         gpio_put(LED_PIN, 1);
    //         sleep_ms(250);
    //         gpio_put(LED_PIN, 0);
    //         sleep_ms(250);
    //     }
    // #endif
}
