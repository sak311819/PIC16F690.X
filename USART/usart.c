/*
 * File:   usart.c
 * Author: Shahzad Anwar Khan
 * github.com/sak311819
 
 * Created on January 2, 2023, 6:05 PM
 
    *******************  Copyright Note ***************************************************
    Anyone having this code can use it for deveoplment purposes only. Redistribution
    of this code under antoher name and without permission will be an illegal and immoral
    action. If you want to improve this code, you are welcome to make forks, contribute and
    make pull requests or report bugs on github. All types of feedback(non-abusive of course)
    is welcomed and will help make this project more useful for everyone out there. Thanks!
    *****************************************************************************************
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