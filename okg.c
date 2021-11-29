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
int  main(void){
xpos = 0; 
ypos = 0;
  memcpy((char * ) 0xe000, data, 1024); //APL charset loads into $e000
  *(char * ) 648 = 0xc8; // POKE 648,40;
  vic_setbank(3); // nice high-level way to move the sundry charset
  vic.memptr = 0x28; // settings into place in oscar64!
for (i = 0; i < 1024; i++) Screen[i] = 32;
for (i = 0; i < 120; i++) Screen[i] = i;
*(char * ) 0xd021 = 0x06;
for (i = 0 ; i < 120; i++) {
    (*(char * ) (0xd800 +i)) =  1;
    }

while (1) {
//cgetc
	__asm {
loc1ebd:     LDA $C6
loc1ebf:     BNE loc1ed8 
loc1ec1:     LDA $CC 
             PHA
             LDA $381C  
             JSR loc1ede  
loc1eca:     LDA $C6
loc1ecc:     BEQ loc1eca  
             LDX #$00
             PLA
             BNE loc1ed4
             INX
loc1ed4:     TXA
             JSR loc1ede 
loc1ed8:     JSR $e5b4
             sta $04f0
             LDX #$00
             RTS
loc1ede:     TAX
             BNE  loc1eff
             LDA $CC 
             BNE loc1efe 
             LDA #$01
             STA $CC  
             LDA $CF 
             BEQ loc1efa
             LDY $D3
             LDA ($D1),Y
             EOR #$80
             STA ($D1),Y
             LDA $0287 
             STA ($F3),Y
loc1efa:     LDA #$00
             STA $CF  
loc1efe:     RTS
loc1eff:     LDA #$00
             STA $CC
             RTS
done:
     }
c = *(char *) 0x04f0;
//printf("C IS %c %d ", c, c);
if (c==157)  {
                   xpos--;
                     xpos--;
          if (xpos < 0) {
            xpos = 39;
          }

                   gotoxy(xpos,ypos);
                 }

else if (c==29)  {
                   xpos++;
                   if (xpos > 39) {
                    xpos = 0;
                   }

                   gotoxy(xpos,ypos);
                 }

else if (c==17) {
                   ypos++;
                   if (ypos > 2) {
                           ypos = 0;
                   }
                   gotoxy(xpos,ypos);
                 }
else if (c==145)  {
                   ypos--;
                   if (ypos < 0) {
                      ypos = 2;
                   }
                   gotoxy(xpos,ypos);
                 }
}
}


