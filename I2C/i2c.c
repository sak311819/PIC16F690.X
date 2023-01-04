/*
 * File:   i2c.c
 * Author: Shahzad Anwar Khan
 * github.com/sak311819
 * Created on January 2, 2023, 11:26 AM
 
    *******************  Copyright Note ***************************************************
    Anyone having this code can use it for deveoplment purposes only. Redistribution
    of this code under antoher name and without permission will be an illegal and immoral
    action. If you want to improve this code, you are welcome to make forks, contribute and
    make pull requests or report bugs on github. All types of feedback(non-abusive of course)
    is welcomed and will help make this project more useful for everyone out there. Thanks!
    *****************************************************************************************
*/

#include "i2c.h"
bool I2C_Init(){
    PORTB=0;
    SSPSTAT=0;
    INTCON=0;
    PIR1=0;
    SSPBUF=0;
    SSPCON=0;
    ANSEL=0;
    ANSELH=0;
    SDA=1;
    SCL=1;
    PIE1=0;
    SSPCON=0x0B;
    SSPCONbits.CKP=0;
    SSPCONbits.SSPEN=1;
    unsigned char dummy=SSPBUF;
    start_bit=0;
    stop_bit=0;
//    BRG=35;
    return 1;
}
bool I2C_Start(){
//    if(I2C_busy()){return 0;}
    SCL=1;
    I2C_Delay();
    SDA=0;
    I2C_Delay();
//    SCL=0;
    return 1;
}
void I2C_Stop(){
    SCL=1;
    NOP();
    SDA=0;
    I2C_Delay();
    SDA=1;
    I2C_Delay();
}
bool I2C_busy(){
    bool flag=false;
    if(start_bit|stop_bit){
        if(start_bit==0 && stop_bit==1){flag=false;}
        else{flag=true;}
    }
    else{bool flag=false;}
    return flag;
}
void I2C_Delay(){
    unsigned int i,j;
    for(i=0;i<2;i++);
}
unsigned int I2C_Multi_Write(unsigned char add,unsigned char* ptr,unsigned int len){
    unsigned int count=0;
    while(!I2C_Start());
//    add=add&0x7F;
    if(NACK==I2C_Transmit_Byte(add)){
        printf("Multi Write NACK\n\r");
        I2C_Stop();
        return 0;
    }
    int i;
    for(i=0;i<len;i++){
    if(I2C_Transmit_Byte(*ptr)){
        ptr++;
        count++;
        }
    else{
        printf("Multi Write NACK\n\r");
        break;
        }
    }
        I2C_Stop();
    return count;
}
bool I2C_Single_Write(unsigned char add,unsigned char data){
    while(!I2C_Start());
//    add=add&0x7F;
    if(NACK==I2C_Transmit_Byte(add)){
        printf("Single Write NACK\n\r");
        I2C_Stop();
        return NACK;
    }
//    I2C_Start();
    I2C_Transmit_Byte(data);
    I2C_Stop();
    return ACK;
}
unsigned char I2C_Single_Read(unsigned char add){
    while(!I2C_Start());
//    add=add&0xFF;
    if(NACK==I2C_Transmit_Byte(add)){
        printf("Single Read NACK\n\r");
        return 0;
    }
//    I2C_Start();
    unsigned char data=0;
    data=I2C_Receive_Byte();
    I2C_Send_ACK(NACK);
    I2C_Stop();
    return data;
}
unsigned char I2C_Receive_Byte(){
    unsigned char received_byte=0;
    unsigned char mask=0x80;
    int i;
        SCL=0;
        NOP();  //avoid false stop condition by letting SCL low
        SDA=1;  // release sda to be used by slave 
    for(i=0;i<8;i++){
        SCL=0;
        I2C_Delay();
        SCL=1;
        I2C_Delay();  //data hold delay
        if(SDA_PIN==1){
            printf("1_");
            received_byte=received_byte|1;
        }
        else{
//            received_byte=received_byte|0;
            printf("0_");
        }
        if(i<7){
        received_byte=received_byte<<1;}
    }
        printf("\n\r");
    return received_byte;
}
bool I2C_Transmit_Byte(unsigned char data){
    char check=0;
    unsigned char mask=0x80;
    int i;
    for(i=0;i<8;i++){
        check=mask&data;
        data=data<<1;
        if(check==mask){
            transmit_1();
        }
        else{transmit_0();}
    }
    return I2C_Check_ACK();
}

unsigned int I2C_Multi_Read(unsigned char add,unsigned char*ptr,unsigned int len){
    unsigned int count=0;
    while(!I2C_Start());
    add=add&0x7F;
    if(NACK==I2C_Transmit_Byte(add)){
        printf("Multi Read NACK\n\r");
        return 0;
    }
    while(len>0){
    unsigned char data=0;
    *ptr=I2C_Receive_Byte();
    if(len>1){
    I2C_Send_ACK(NACK);}
    ptr++;
    len--;
    count++;    // this count will be returned, in future, I2C collisions will be addressed
    }
    I2C_Send_ACK(NACK);
    I2C_Stop();
    return count;
}
bool I2C_Check_ACK(){
    SCL=0;
    NOP();
    SDA=1;
    I2C_Delay();
    SCL=1;
    NOP();
    NOP();
    if(SDA_PIN==0){return ACK;}
    else{return NACK;}
}
void I2C_Send_ACK(bool ack){
    SCL=0;
    NOP();
    if(ack){SDA=0;} //send acknowledge
    else{SDA=1;}    // don't send acknowledge
    I2C_Delay();
    SCL=1;
    I2C_Delay();
//    NOP();
//    NOP();
}
void transmit_0(void){
    SCL=0;
    NOP();
    SDA=0;
//    NOP();
    I2C_Delay();
    I2C_Delay();
    SCL=1;
    I2C_Delay();
}
void transmit_1(void){
    SCL=0;
    NOP();
    SDA=1;
    I2C_Delay();
    I2C_Delay();
    SCL=1;
    I2C_Delay();
}