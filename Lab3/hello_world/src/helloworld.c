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
void multiplication(){
	xil_printf("Please enter a string \n\r");
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
}

void rockPaperScissors();
int processInputs(int playerOneVal, int playerTwoVal);

int main()
{
	XGpio_Initialize(&gpio_output, XPAR_LEDS_8BIT_DEVICE_ID);
	XGpio_SetDataDirection(&gpio_output, 1, 0x00000000);
    init_platform();

    char mode;
    xil_printf("Enter option: 'm' for multiplication, 'g' for rock-paper-scissors\n\r");
    mode = getc(stdin);
	getchar(); // get rid of nullbyte
	xil_printf("\r\n");
	while(mode == 'm' || mode == 'M' || mode == 'g' || mode == 'g'){
		if(mode == 'm' || mode == 'M'){
			multiplication();
		} else if(mode == 'g' || mode == 'g'){
			rockpaperscissors();
		}
		xil_printf("Enter option: 'm' for multiplication, 'g' for rock-paper-scissors\n\r");
		mode = getc(stdin);
		getchar(); // get rid of nullbyte
		xil_printf("\r\n");
		XGpio_DiscreteWrite(&gpio_output, 1, 0); // clear LEDs
    }
	xil_printf("Exiting program...\r\n");
	return 0;
}


void rockPaperScissors(){
    char input;

    print("Starting rock paper scissors. Player one get ready");

    int playerOneVal, playerTwoVal;
    char a[3][10];
    strcpy(a[0], "ROCK");
    strcpy(a[1], "PAPER");
    strcpy(a[2], "SCISSORS");

    while(1){
        print("Player 1 enter your input (0 = rock, 1 = paper, 2 = scissors");
        input = getc(stdin);
        getchar();
        playerOneVal = input - '0';
        print("Player 2 enter your input (0 = rock, 1 = paper, 2 = scissors");

        inputData = XGpio_DiscreteRead(&GpioInput,1);
        while(inputData == 0xef)
        {
            inputData = XGpio_DiscreteRead(&GpioInput,1);
        }
        if(inputData == 0xee)
        {
            P2 = "ROCK";
        }
        else if (inputData == 0xed)
        {
            P2 = "PAPER";
        }
        else
        {
            P2 = "SCISSORS";
        }
        int outcome = processInputs(playerOneVal, playerTwoVal);
        if (outcome == 1){
            xil_printf("The game is a tie (%s = %s)", a[playerOneVal], a[playerTwoVal]);
        }   
        else if (outcome == 0){
            xil_printf("Player One won! (%s > %s)", a[playerOneVal], a[playerTwoVal]);
        }
        else if (outcome == 2){
            xil_printf("Player Two won! (%s < %s)", a[playerOneVal], a[playerTwoVal]);
        }
    }
    
}

/**
 * Returns 0 if player one won, 2 if player 2 won, 1 if tie
 */
int processInputs(int playerOneVal, int playerTwoVal){
    if (playerOneVal == 0){
        if (playerTwoVal == 0)
            return 1;
        if (playerTwoVal == 1)
            return 2;
        return 0;
    }
    else if (playerOneVal == 1){
        if (playerTwoVal == 1)
            return 1;
        if (playerTwoVal == 2)
            return 2;
        return 0;
    }
    else if (playerOneVal == 2){
        if (playerTwoVal == 2)
            return 1;
        if (playerTwoVal == 0)
            return 2;
        return 0;
    }
}