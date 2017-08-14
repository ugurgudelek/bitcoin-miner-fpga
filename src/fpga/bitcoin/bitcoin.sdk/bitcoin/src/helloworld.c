/******************************************************************************
*
* Copyright (C) 2010 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/****************************************************************************/
/**
*
* @file     xuartps_polled_example.c
*
* This file contains an example using the XUartPs driver in polled mode.
*
* This function sends data and expects to receive the data thru the device
* using the local loopback mode.
*
* @note
* If the device does not work properly, the example may hang.
*
* MODIFICATION HISTORY:
* <pre>
* Ver   Who    Date     Changes
* ----- ------ -------- -----------------------------------------------
* 1.00a  drg/jz 01/13/10 First Release
* 1.03a  sg     07/16/12 Modified the device ID to use the first Device Id
*			Removed the printf at the start of the main
* </pre>
******************************************************************************/

/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xuartps.h"
#include <xuartps_hw.h>
#include "xil_printf.h"
#include <stdio.h>
//#include <memory.h>
#include <string.h>
#include "sha256.h"


/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define UART_DEVICE_ID              XPAR_XUARTPS_0_DEVICE_ID

/*
 * The following constant controls the length of the buffers to be sent
 * and received with the device, this constant must be 32 bytes or less since
 * only as much as FIFO size data can be sent or received in polled mode.
 */
#define TEST_BUFFER_SIZE 32

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

int UartPsPolledExample(u16 DeviceId);
int sha256_test();

/************************** Variable Definitions *****************************/

XUartPs Uart_PS;		/* Instance of the UART Device */

/*
 * The following buffers are used in this example to send and receive data
 * with the UART.
 */
static u8 SendBuffer[TEST_BUFFER_SIZE];	/* Buffer for Transmitting Data */
static u8 RecvBuffer[TEST_BUFFER_SIZE];	/* Buffer for Receiving Data */


/*****************************************************************************/
/**
*
* Main function to call the Uart Polled mode example.
*
* @param	None
*
* @return	XST_SUCCESS if succesful, otherwise XST_FAILURE
*
* @note		None
*
******************************************************************************/
#ifndef TESTAPP_GEN
int main(void)
{
	int Status;
	Status = UartPsPolledExample(UART_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("UART Polled Mode Example Test Failed\r\n");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran UART Polled Mode Example Test\r\n");

	return XST_SUCCESS;
}
#endif

/*********************** FUNCTION DEFINITIONS ***********************/
int sha256_test()
{
	BYTE text1[] = {"abc"};
	BYTE text2[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
	BYTE text3[] = {"aaaaaaaaaa"};
	BYTE hash1[SHA256_BLOCK_SIZE] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
	                                 0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};
	BYTE hash2[SHA256_BLOCK_SIZE] = {0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,
	                                 0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};
	BYTE hash3[SHA256_BLOCK_SIZE] = {0xcd,0xc7,0x6e,0x5c,0x99,0x14,0xfb,0x92,0x81,0xa1,0xc7,0xe2,0x84,0xd7,0x3e,0x67,
	                                 0xf1,0x80,0x9a,0x48,0xa4,0x97,0x20,0x0e,0x04,0x6d,0x39,0xcc,0xc7,0x11,0x2c,0xd0};
	BYTE buf[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;
	int idx;
	int pass = 1;

	sha256_init(&ctx);
	sha256_update(&ctx, text1, strlen(text1));
	sha256_final(&ctx, buf);
	pass = pass && !memcmp(hash1, buf, SHA256_BLOCK_SIZE);

	sha256_init(&ctx);
	sha256_update(&ctx, text2, strlen(text2));
	sha256_final(&ctx, buf);
	pass = pass && !memcmp(hash2, buf, SHA256_BLOCK_SIZE);

	sha256_init(&ctx);
	for (idx = 0; idx < 100000; ++idx)
	   sha256_update(&ctx, text3, strlen(text3));
	sha256_final(&ctx, buf);
	pass = pass && !memcmp(hash3, buf, SHA256_BLOCK_SIZE);

	return(buf);
}
/*****************************************************************************/
/**
*
* This function does a minimal test on the XUartPs device in polled mode.
*
* This function sends data and expects to receive the data thru the UART
* using the local loopback mode.
*
*
* @param	DeviceId is the unique device id from hardware build.
*
* @return	XST_SUCCESS if successful, XST_FAILURE if unsuccessful
*
* @note
* This function polls the UART, it may hang if the hardware is not
* working correctly.
*
****************************************************************************/
int UartPsPolledExample(u16 DeviceId)
{
	int Status;
	XUartPs_Config *Config;
	unsigned int SentCount;
	unsigned int ReceivedCount;
	u16 Index;
	u32 LoopCount = 0;

	/*
	 * Initialize the UART driver so that it's ready to use.
	 * Look up the configuration in the config table, then initialize it.
	 */
	Config = XUartPs_LookupConfig(DeviceId);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	Status = XUartPs_CfgInitialize(&Uart_PS, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Check hardware build. */
	Status = XUartPs_SelfTest(&Uart_PS);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Use local loopback mode. */
	//XUartPs_SetOperMode(&Uart_PS, XUARTPS_OPER_MODE_LOCAL_LOOP);

	/*
	 * Initialize the send buffer bytes with a pattern and zero out
	 * the receive buffer.
	 */


	for (Index = 0; Index < TEST_BUFFER_SIZE; Index++) {
		//SendBuffer[Index] = buf[Index];
		RecvBuffer[Index] = 0;

	}

	/* Block sending the buffer. */
	//SentCount = XUartPs_Send(&Uart_PS, SendBuffer, TEST_BUFFER_SIZE);


	/*
	 * Wait while the UART is sending the data so that we are guaranteed
	 * to get the data the 1st time we call receive, otherwise this function
	 * may enter receive before the data has arrived
	 */
	while (XUartPs_IsSending(&Uart_PS)) {
		LoopCount++;
	}


	while(1){
		if(XUartPs_RecvByte(Config->BaseAddress) == 'a'){
			/*
			ReceivedCount = 0;
			while (ReceivedCount < TEST_BUFFER_SIZE) {
				ReceivedCount +=
					XUartPs_Recv(&Uart_PS, &RecvBuffer[ReceivedCount],
							  (TEST_BUFFER_SIZE - ReceivedCount));
			*/

			BYTE text2[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
			BYTE buf[SHA256_BLOCK_SIZE];
			SHA256_CTX ctx;
			sha256_init(&ctx);
			sha256_update(&ctx, text2, strlen(text2));
			//sha256_update(&ctx, RecvBuffer, ReceivedCount);
			sha256_final(&ctx, buf);

			XUartPs_Send(&Uart_PS, buf, TEST_BUFFER_SIZE);
			//xil_printf("%s", &buf);
			//xil_printf("%s", &RecvBuffer);
			while (XUartPs_IsSending(&Uart_PS)) {
				LoopCount++;
			}

			int i;
			for(i = 0; i < TEST_BUFFER_SIZE; i++){
				RecvBuffer[i] = 0;
			}
		}
	}




	/* Restore to normal mode. */
	//XUartPs_SetOperMode(&Uart_PS, XUARTPS_OPER_MODE_NORMAL);

	return XST_SUCCESS;
}
