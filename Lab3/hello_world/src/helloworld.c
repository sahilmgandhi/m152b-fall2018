/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "xgpio.h"
#include "platform.h"
#include "gpio_header.h"

XGpio gpio_output;

int main()
{
    init_platform();
    print("Please enter a string \n\r");

    int selector = 0;
    int digit = 0;
    char num1[2] = "";
    char num2[2] = "";

    while (1){
        input = getc(stdin);
        getchar(); // get rid of the nullbyte
        if (isdigit(input)){
            printf("%c", input);
            if (selector == 0){
                num1[digit] = input;
                digit++;
            }
            else{
                num2[digit] = digit;
                digit++;
            }
        }
        else if (input == '/' || input == '*' || input == ' '){
            printf("\r\n", input);
            digit = 0;
            selector++;
        }
        if (selector >= 2 || (selector == 1 && digit > 2)){
            break;
        }
    }

    int n1 = atoi(num1);
    int n2 = atoi(num2);
    int res = n1*n2;

    printf("%d * %d = %d\r\n", n1, n2, res);
	if (res > 100)
	{
		XGpio_DiscreteWrite(&GpioOutput, 1, 1 << 0);
	}
	else
	{
		XGpio_DiscreteWrite(&GpioOutput, 1, 0 << 0);
	}
	print("Exiting program...\r\n");
	return 0;
}

