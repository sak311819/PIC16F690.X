/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
 
/*
 * File:   main.c
 * Author: Shahzad Anwar Khan
 *
 * Created on January 2, 2023, 11:26 AM
 */

#include <xc.h>
#include<stdbool.h>

#define SCL TRISBbits.TRISB6
#define SCL_PIN PORTBbits.RB6

#define SDA TRISBbits.TRISB4
#define SDA_PIN PORTBbits.RB4

#define I2C_Interrupt PIR1bits.SSPIF 
#define stop_bit SSPSTATbits.I2C_STOP
#define start_bit SSPSTATbits.I2C_START

#define ACK 1
#define NACK 0

bool I2C_Init(void);
bool I2C_Check_ACK(void);
void I2C_Send_ACK(bool ack);
bool I2C_Start(void);
void I2C_Stop(void);
bool I2C_busy(void);
void I2C_Delay(void);
bool I2C_Single_Write(unsigned char ,unsigned char );
unsigned int I2C_Multi_Write(unsigned char,unsigned char*,unsigned int);
unsigned char I2C_Single_Read(unsigned char);
unsigned int I2C_Multi_Read(unsigned char,unsigned char*,unsigned int );
bool I2C_Transmit_Byte(unsigned char);
unsigned char I2C_Receive_Byte(void);
void transmit_1(void);
void transmit_0(void);
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

