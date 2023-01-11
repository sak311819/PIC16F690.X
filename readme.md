# PIC16F690 I2C Support :
This project was created to facilitate anyone looking for open source I2C library for
pic16f690. This device does have a SSP peripheral but it only supports I2C slave 
functions via hardware. The I2C master support can only be provided in firmware with
interrupts on start/stop/transmit complete. 
The code uploaded here has been only tested in proteus simulation software. If you 
test this code in hardware and identify any issues, please report it in the
comments/bug/pull request etc.
# Usage Example:
Clone the repository. Ideally, you should be able to open this cloned repo folder as MPLAB X's project by using the 'open project' options. Otherwise, you can create your own blank project on the ide of your choice and import these files and directly copy paste the code. You can use the I2C_test_main.c file as an example to start.

The main driving functions in the library are: I2C_Start,I2C_Stop, I2C_Transmit_Byte and I2C_Receive_Byte. All other functions are built around these basic functions. To write a single byte to a specific slave, you can use this function:
``` 
I2C_Single_Write(0x55,35);  // writes decimal 35 to slave device 0x55 
```

To write multiple bytes to a slave in single burst, use this function:
```
I2C_Multi_Write(0x55,& buffer_to_be_sent,10);    // transmit 10 bytes to slave device 0x55
```

# Note:
This code is under development and cannot be used in safety critical applications
where it can cause damage to equipment, personnel at work or medical applications etc.