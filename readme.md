PIC16F690 I2C Support :
This project was created to facilitate anyone looking for open source I2C library for
pic16f690. This device does have a SSP peripheral but it only supports I2C slave 
functions via hardware. The I2C master support can only be provided in firmware with
interrupts on start/stop/transmit complete. 
The code uploaded here has been only tested in proteus simulation software. If you 
test this code in hardware and identify any issues, please report it in the
comments/bug/pull request etc.