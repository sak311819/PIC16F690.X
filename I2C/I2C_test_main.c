/*
 * File:   main.c
 * Author: Shahzad Anwar Khan
 *
 * Created on January 2, 2023, 11:26 AM
 */

//#define SCL TRISBbits.TRISB6
//
//#define SDA TRISBbits.TRISB4
//#define I2C_Interrupt PIR1bits.SSPIF 
//#define stop_bit SSPSTATbits.I2C_STOP
//#define start_bit SSPSTATbits.I2C_START

// PIC16F690 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "i2c.h"
#include "../USART/usart.h"
unsigned char dummy_data[4]={0x12,0xC8,0x89,0x1E};
unsigned char slave_address=0x55;   // set slave address here to perform quick test
                                    //Note that this address must account the read/write bits in it
                                    // consult the data sheet of your slave device for addressing details
void main(void) {
    TRISC=0;
    I2C_Init();
    Usart_Init();
    printf("init complete\n\r");
    printf("Test I2C\n\r");
    while(1){
        int i;
        for(i=0;i<1000;i++){I2C_Delay();} // arbitrary delay
    printf("Sending single byte 0x34\n\r\n\r");
    I2C_Transmit_Byte(0x34);
    printf("Sending data 0xA5 to slave address 0x55\n\r\n\r");
    if(I2C_Single_Write(slave_address,0xA5)){
        printf("slave responded with ack, data sent\n\r\n\r");
    }
    else{
        printf("slave responded with Nack, data was no sent\n\r\n\r");
    }
    printf("Sending 4 bytes of dummy data to slave address 0x55\n\r\n\r");
    unsigned int bytes_sent=I2C_Multi_Write(slave_address,dummy_data,4);
    
    printf("Slave successfully received %d bytes of data\n\r\n\r",bytes_sent);
    }
    return;
}