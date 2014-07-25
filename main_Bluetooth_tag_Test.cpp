/*
 * Author: Edoardo De Marchi
 * Date: 02-07-13
 * Notes: HC05 Trasparent Mode
 * Modified by Clovis Fritzen in 07-25-2014 to be used on
 * the Freescale FRDM-K64F platform
*/
 
#include "mbed.h"
 
#define SERIAL_1
 
 
Serial pc(USBTX, USBRX);
#ifdef SERIAL_1
Serial blue(PTC15,PTC14);          // HC05
#endif
#ifdef SERIAL_2
Serial blue(PTC17,PTC16);         // TX = P14  RX = P13
#endif
 
DigitalOut BluetoothLed(LED1);
DigitalOut PCled(LED2);
 
 
int main() 
{
 
    blue.baud(9600);
    pc.baud(9600);
    pc.printf("Bluetooth Start\r\n");
    
    // echo back characters and toggle the LED
    while (1) 
    {
        if (blue.readable()) 
        {
            pc.putc(blue.getc());
            PCled = 1;
            BluetoothLed = 0;
        }
        if (pc.readable()) 
        {
            blue.putc(pc.getc());
            BluetoothLed = 1;
            PCled = 0;
        }
        
    }
}