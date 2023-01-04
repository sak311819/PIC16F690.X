/*
 * File:   usart.c
 * Author: Shahzad Anwar Khan
 *
 * Created on January 2, 2023, 6:05 PM
 */

#include "usart.h"

void Usart_Init(){
    TXSTA=0;
    RCSTA=0;
    SPBRG=25;
    SPBRGH=0;
    BAUDCTL=0x08;
    INTCON=0;
    TXSTA=0x24;
    RCSTA=0x90;
    
}
bool Usart_Send_Byte(unsigned char data){
    while(!TXSTAbits.TRMT);
    TXREG=data;
    return 1;
}
void putch(char ch){
    Usart_Send_Byte(ch);
}