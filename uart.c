#include "uart.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <xc.h>
#include <string.h>
#include "leds_rgb.h"


#define DELAY_105uS asm volatile ("REPEAT, #4201"); Nop(); // 105uS delay
void UARTInit(const uint32_t baud_rate, const uint8_t BRGH) {
    // Calculate BRG

   
            //LED_RGB_Enable(LED_RGB_LD3);
   // RPOR3bits.RP7R =3;
     ANSBbits.ANSB2 = 0;
    DELAY_105uS
    TRISBbits.TRISB2 = 0;
         __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
   
    //OSCCONbits.IOLOCK =1;

         //RPOR3bits.RP6R = 3;
         //RPOR0 = 0x0303;
         RPOR1= 0x0003;
         int i =0;
         for (i=0; i<100; i++ ){
             i++;
         }
         //RPOR10= 0x0303;
        // RPOR11= 0x0303;
        // RPOR5= 0x0303;
           //RPOR1bits.RP2R = 3;
    //RPINR18bits.U1RXR = 0x0005;   //RB5->UART1:U1RX;
   // OSCCONbits.IOLOCK =0;

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS

    
    // TXSTA register
    U1MODEbits.UARTEN = 0;

    //U1MODEbits.USIDL = 0;
    //U1MODEbits.IREN = 0;
    //U1MODEbits.RTSMD = 1;
    //U1MODEbits.WAKE = 0;
    //U1MODEbits.LPBACK = 0;
    U1MODEbits.ABAUD= 0;
    //U1MODEbits.URXINV =0;
    U1MODEbits.PDSEL = 0x00;
    U1MODEbits.STSEL=0;
    U1MODEbits.BRGH = 0;
    U1BRG=50; //0x01A0; //25

    U1STAbits.UTXISEL0 = 0;
    U1STAbits.UTXISEL1 = 0;
   // U1STAbits.UTXINV = 0;
    //U1STAbits.UTXBRK = 0;

    //U1STAbits.URXISEL =0x00;
    //U1STAbits.ADDEN = 0;
    
    //U1BRG = 25;//_XTAL_FREQ/(64*baud_rate) - 1;
   // IFS0bits.U1TXIF = 0; // Clear TX Interrupt flag
   // IEC0bits.U1TXIE = 1;

    //U1MODEbits.UEN= 0x00; //QUESTION ABOUT THIS ONE
    //U1STAbits.URXEN = 1;

    U1MODEbits.UARTEN = 1;

    U1STAbits.UTXEN = 1;

    //TXSTAbits.TXEN = 1;     // Enable transmission
    //TXSTAbits.SYNC = 0;     // Asynchronous mode
    
    // RCSTA register
//    RCSTAbits.SPEN = 1;     // Enable serial port
//    RCSTAbits.RX9 = 0;      // 8-bit reception
//    RCSTAbits.CREN = 1;     // Enable continuous reception
//    RCSTAbits.FERR = 0;     // Disable framing error //read only
//    RCSTAbits.OERR = 0;     // Disable overrun error //read only
    
    // Set up direction of RX/TX pins
//    UART_TRIS_RX = 1; //overwritten by the UART
//    UART_TRIS_TX = 0;
    //LED_RGB_Set(LED_RGB_LD3, 1023, 0, 0);
    

    //LED_RGB_Set(LED_RGB_LD3, 0, 0, 1023);
}

/**
 * Send a character
 * @param c character to send
 */
//read char would use urxda
void UARTSendChar(const char c) {
    
    while (U1STAbits.UTXBF == 1);    // Wait for buffer to be empty
    //transmit buffer ? waiting for it to be empty
    //can loop around it or cause an interrupt
    DELAY_105uS
    U1TXREG = c;
    //LED_RGB_Set(LED_RGB_LD3, 0, 1023, 0);

}

/**
 * Send a string, until '\0' is read, up to max_length characters
 * @param str
 * @param length
 */
void UARTSendString(const char* str, const uint8_t max_length) {
    int i = 0;
    for (i=0 ; i<max_length && str[i]!='\0' ; i++) {
        UARTSendChar(str[i]);
    }

}


//void __attribute__((__interrupt__)) _U1TXInterrupt(void)
//{
//U1TXREG = 'a'; // Transmit one character
//IFS0bits.U1TXIF = 0; // Clear TX Interrupt flag
//
//}