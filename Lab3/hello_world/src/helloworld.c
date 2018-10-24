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
#include "xparameters.h"

XGpio gpio_output;

int main()
{
	XGpio_Initialize(&gpio_output, XPAR_LEDS_8BIT_DEVICE_ID);
	 XGpio_SetDataDirection(&gpio_output, 1, 0x00000000);
    init_platform();

    char continue_loop = 'y';
	while(continue_loop == 'y' || continue_loop == 'Y'){
		print("Please enter a string \n\r");
		int selector = 0;
		int digit = 0;
		char num1[5] = "";
		char num2[5] = "";
		char input;
		while (1){
			input = getc(stdin);
			if (input == '\r'){
				print("\r\n");
				break;
			}
			getchar(); // get rid of the nullbyte
			if (isdigit(input)){
				//printf("%c", input);
				if (selector == 0){
					num1[digit] = input;
					digit++;
				}
				else{
					num2[digit] = input;
					digit++;
				}
			}
			else if (input == '/' || input == '*' || input == ' '){
				//printf("\r\n", input);
				digit = 0;
				selector++;
			}
		}

		int n1 = atoi(num1);
		int n2 = atoi(num2);
		int res = n1*n2;

		xil_printf("%d * %d = %d\r\n", n1, n2, res);
		if (res > 100)
		{
			XGpio_DiscreteWrite(&gpio_output, 1, 1);
		}
		else
		{
			XGpio_DiscreteWrite(&gpio_output, 1, 0);
		}
		xil_printf("Enter 'y' to continue\r\n");
		continue_loop = getc(stdin);
		getchar(); // get rid of nullbyte
		xil_printf("\r\n");
    }
	print("Exiting program...\r\n");
	return 0;
}

