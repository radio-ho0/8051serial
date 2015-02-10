#include "main.h"

#include <at89x52.h>
#include "lcd1602.h"
#include "serlib.h"

enum serial_cons{
    CMD_LENG = 16,

};

#define FOSC 12000000
#define  BAUD 2400
#define  SER_TH_VAL (256 - (FOSC / 12 / 32) / BAUD)

char cmd[CMD_LENG];
char c;
char ok;
char i;
int cmp_result;
char index = 0;



void UART_Init()
{
    SCON = 0x50;		/* configure serial */
    TMOD = 0x20;		/* configure timer */
    TH1 = SER_TH_VAL;		/* baud rate 2400*/
    TL1 = SER_TH_VAL;		/* baud rate 2400*/
//    TH1 = 0xf3;		/* baud rate 2400*/
//    TL1 = 0xf3;		/* baud rate 2400*/
    // TH1 = 0xE6; /* baud rate 1200 */
    // TL1 = 0xE6; /* baud rate 1200 */
    TR1 = 1;		/* enable timer */
    TI = 1;			/* enable transmitting */
    RI = 0;			/* waiting to receive */

}

void main()
{
//    LCDInit();
 //   DisplayListChar("51 os!!!");
    InitLcd1602();
    UART_Init();
    putstr("为者常成 行者常至");
    putstr("\r\n");
    
    LcdShowStr(3, 0, "51 os!!!");
    LcdShowStr(0, 1, "Go!!wait4login");


    for (;;) {
        c = getchar();
        if( (c != 0x0d) && (index < (CMD_LENG - 1) )){
            cmd[index++] = c;
            putchar(c);
        }else{
            cmd[index] = '\0';
            ok = 1;
        }

        if(ok){
            ok = 0;
            putstr("\r\n");
            putchar('>');

            putstr(cmd);
            if(!strcmp(cmd, "help") ){
                LcdShowStr( 3, 0, "ho0 serial os");
                newline("no help ha!");
                newline("cmds: ls apple abc ! :)");
                LcdShowStr(0, 1,"cmds: ls apple abc ! :)");

            }else if(!strcmp(cmd, "ls")){
                P3 = ~P3;
            }else if(!strcmp(cmd, "apple")){
                newline("I like apple!");
                LcdShowStr(0, 1,"I like apple!");
            }

            
          cmp_result =   strcmp(cmd, "abc");

          if(cmp_result == 0){
              newline("right");
              showStr("ILove2HateMyPC!");

          }
            index = 0;
            putstr("\r\n");
        }



    }
}

