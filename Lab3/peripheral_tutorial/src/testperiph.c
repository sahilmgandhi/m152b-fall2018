/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * 
 *
 * This file is a generated sample test application.
 *
 * This application is intended to test and/or illustrate some 
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * SDK application project when you run the "Generate Libraries" menu item.
 *
 */


#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
#include "xgpio.h"
#include "gpio_header.h"
#include "uartlite_header.h"
#include "xuartns550_l.h"
#include "xuartns550_l.h"
#include "uartns550_header.h"


int main() 
{


   /* Initialize rs232_uart_0 - Set baudrate and number of stop bits */
   XUartNs550_SetBaud(XPAR_RS232_UART_0_BASEADDR, XPAR_XUARTNS550_CLOCK_HZ, 9600);
   XUartNs550_SetLineControlReg(XPAR_RS232_UART_0_BASEADDR, XUN_LCR_8_DATA_BITS);

   Xil_ICacheEnable();
   Xil_DCacheEnable();

   print("---Entering main---\n\r");

   

   {
      u32 status;
      
      print("\r\nRunning GpioInputExample() for dip_switches_8bit...\r\n");

      u32 DataRead;
      
      status = GpioInputExample(XPAR_DIP_SWITCHES_8BIT_DEVICE_ID, &DataRead);
      
      if (status == 0) {
         xil_printf("GpioInputExample PASSED. Read data:0x%X\r\n", DataRead);
      }
      else {
         print("GpioInputExample FAILED.\r\n");
      }
   }
   

   {
      u32 status;
      
      print("\r\nRunning GpioOutputExample() for leds_8bit...\r\n");

      status = GpioOutputExample(XPAR_LEDS_8BIT_DEVICE_ID,8);
      
      if (status == 0) {
         print("GpioOutputExample PASSED.\r\n");
      }
      else {
         print("GpioOutputExample FAILED.\r\n");
      }
   }
   

   {
      u32 status;
      
      print("\r\nRunning GpioInputExample() for push_buttons_7bit...\r\n");

      u32 DataRead;
      
      status = GpioInputExample(XPAR_PUSH_BUTTONS_7BIT_DEVICE_ID, &DataRead);
      
      if (status == 0) {
         xil_printf("GpioInputExample PASSED. Read data:0x%X\r\n", DataRead);
      }
      else {
         print("GpioInputExample FAILED.\r\n");
      }
   }
   

   {
      int status;
      
      print("\r\nRunning UartLiteSelfTestExample() for mdm_0...\r\n");
      status = UartLiteSelfTestExample(XPAR_MDM_0_DEVICE_ID);
      if (status == 0) {
         print("UartLiteSelfTestExample PASSED\r\n");
      }
      else {
         print("UartLiteSelfTestExample FAILED\r\n");
      }
   }
   
   /*
    * Peripheral SelfTest will not be run for rs232_uart_0
    * because it has been selected as the STDOUT device
    */

   

   {
      XStatus status;

      print("\r\nRunning UartNs550SelfTestExample() for rs232_uart_1...\r\n");
      status = UartNs550SelfTestExample(XPAR_RS232_UART_1_DEVICE_ID);
      if (status == 0) {
         print("UartNs550SelfTestExample PASSED\r\n");
      }
      else {
         print("UartNs550SelfTestExample FAILED\r\n");
      }
   }

   print("---Exiting main---\n\r");

   Xil_DCacheDisable();
   Xil_ICacheDisable();

   return 0;
}

