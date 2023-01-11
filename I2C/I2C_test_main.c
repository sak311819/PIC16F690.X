/*
 * File:   main.c
 * Author: Shahzad Anwar Khan*/
//*** github.com/sak311819
//*** https://sak-engineering-lab.blogspot.com/ 
//*** fiver.com/SAK_engineering
 /* Created on January 2, 2023, 11:26 AM
 
    *******************  Copyright Note ***************************************************
    Anyone having this code can use it for deveoplment purposes only. Redistribution
    of this code under antoher name and without permission will be an illegal and immoral
    action. If you want to improve this code, you are welcome to make forks, contribute and
    make pull requests or report bugs on github. All types of feedback(non-abusive of course)
    is welcomed and will help make this project more useful for everyone out there. Thanks!
    *****************************************************************************************
*/
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
        unsigned int i;
        for(i=0;i<5000;i++){I2C_Delay();} // arbitrary delay
    printf("Sending single byte 0x34\n\r\n\r");
    I2C_Start();
    I2C_Transmit_Byte(0x34);
    I2C_Stop();
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
    unsigned char data_received=I2C_Single_Read(slave_address);
    printf("single data received=%d \n\r\n\r",data_received);
    unsigned char multi_receive_data[4]={0,0,0,0};
    unsigned receive_count=I2C_Multi_Read(slave_address,multi_receive_data,4);
    printf("received %d bytes in multi receive: %d, ",receive_count,multi_receive_data[0]);
    printf("%d, %d, %d \n\r\n\r",multi_receive_data[1],multi_receive_data[2],multi_receive_data[3]);
    }
    return;
}