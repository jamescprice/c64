#include <c64/charwin.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stddef.h>
#include <c64/vic.h>
#define Screen  ((byte * ) 0xc800)
byte data[] = { 
#embed "apl.bin" 
}; 
int i, xpos, ypos;
char c;
int main(void) {

  int notassignment = 0;
  struct node * foundLink;
  struct node * foundLink2;
  size_t size;
  int val;

  char inputstring[25];
  char tmpstring[25];
  int storeindex = 0;
  int linenotdone = 1;
  char storechar = 0;
  xpos = 0;
  ypos = 0;
  memcpy((char * ) 0xe000, data, 1024); //APL charset loads into $e000
  *(char * ) 648 = 0xc8; // POKE 648,40;
  vic_setbank(3); // nice high-level way to move the sundry charset
  vic.memptr = 0x28; // settings into place in oscar64!
  for (i = 0; i < 1024; i++) Screen[i] = 32;
  for (i = 0; i < 120; i++) Screen[i] = i;
  *(char * ) 0xd021 = 0x06;
  for (i = 0; i < 120; i++) {
    ( * (char * )(0xd800 + i)) = 1;
  }

  while (1) {
    //corral
    for (i = 0; i < 120; i++) Screen[i] = i;
    linenotdone = 1;
    c = 1; //dummy not 0 value

    while (linenotdone) {
      while (c != 13) { ////exit chargetting loop if return key hit

        //cgetc
        __asm {
          loc1ebd: LDA $C6
          loc1ebf: BNE loc1ed8
          loc1ec1: LDA $CC
          PHA
          LDA $381C
          JSR loc1ede
          loc1eca: LDA $C6
          loc1ecc: BEQ loc1eca
          LDX #$00
          PLA
          BNE loc1ed4
          INX
          loc1ed4: TXA
          JSR loc1ede
          loc1ed8: JSR $e5b4
          sta $c8f0
          LDX #$00
          RTS
          loc1ede: TAX
          BNE loc1eff
          LDA $CC
          BNE loc1efe
          LDA #$01
          STA $CC
          LDA $CF
          BEQ loc1efa
          LDY $D3
          LDA($D1), Y
          EOR #$80
          STA($D1), Y
          LDA $0287
          STA($F3), Y
          loc1efa: LDA #$00
          STA $CF
          loc1efe: RTS
          loc1eff: LDA #$00
          STA $CC
          RTS
          done:
        }
        c = * (char * ) 0xc8f0;
        //printf("C IS %c %d ", c, c);
        if (c == 157) {
          xpos--;
          xpos--;
          if (xpos < 0) {
            xpos = 39;
          }

          gotoxy(xpos, ypos);
        } else if (c == 29) {
          xpos++;
          if (xpos > 39) {
            xpos = 0;
          }

          gotoxy(xpos, ypos);
        } else if (c == 17) {
          ypos++;
          if (ypos > 2) {
            ypos = 0;
          }
          gotoxy(xpos, ypos);
        } else if (c == 145) {
          ypos--;
          if (ypos < 0) {
            ypos = 2;
          }
          gotoxy(xpos, ypos);
        } else if (c == 13) {
          ypos = 0;
          xpos = 0;
          __asm {
            lda $ce
            sta $c8f3
          }
          storechar = * (char * ) 51443; //$c8f3
          if (storechar == 0) {
            linenotdone = 0;
            gotoxy(12, 12);
            printf("GOT NULL PARSE THIS %s \n", inputstring);
    break;
          }

          *(char * )(52992 + storeindex) = storechar; //52992 = cf00
          *(char * )(1400 + storeindex) = storechar;
          if ((storechar >= 1) && (storechar <= 31)) //char, add 64
          {
            storechar += 64;
          } else if ((storechar >= 64) && (storechar <= 94)) //char, add 64
          {
            storechar += 32;
          } else if ((storechar >= 95) && (storechar <= 119)) //char, add 64
          {
            storechar += 64;
          }

          inputstring[storeindex++] = storechar;
          //terminate it with null
          inputstring[storeindex + 1] = 0;
          gotoxy(10, 10);
          printf("%s", inputstring);
          gotoxy(xpos, ypos);
        }
        c = 1; //reset from 13
      } 
///      storeindex = 0;
    } 
    storeindex = 0;
 
    __asm {
      lda $ce
      sta $c8f1
    }
  }
}
