/*
 * File:   usart.h
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
#include <xc.h> // include processor files - each processor file is guarded.  
#include<stdio.h>
#include<stdbool.h>
void Usart_Init(void);
bool Usart_Send_Byte(unsigned char);


