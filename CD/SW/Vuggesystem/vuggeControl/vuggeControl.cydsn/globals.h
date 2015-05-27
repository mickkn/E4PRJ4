#ifndef GLOBALS_H
#define GLOBALS_H
#include "project.h"
/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
// Definitons

#define FALSE 0u
#define TRUE !FALSE
typedef uint8 BOOL;


//    // Uncomment for UART testing
//    //********************************************************************************
//    UART_1_Start();
//    UART_1_UartPutString("Main startet: I2C test\n");
//    for(;;)
//    {
//        UART_1_UartPutString("\nI2C test \n");/* Place your application code here. */
//        uint8 i;
//        for(i = 0; i < 5; i++)
//        {
//            char string[20];
//            sprintf(string, "%d: %d, [%p]\n", i, i2cPtr_[i],i2cPtr_[i]);
//            UART_1_UartPutString(string);
//        }
//        CyDelay(2000);
//    //********************************************************************************

/* [] END OF FILE */
#endif