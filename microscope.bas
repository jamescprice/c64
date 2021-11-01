4 data 32,115,0,240,27,32,138,173,32,247 
5 data 183,132,252,133,253,32,155,183,134  
6 data 254,120,169,44,141,20,3,169,192,141  
7 data 21,3,96,120,169,49,141,20,3,169,234  
8 data 141,21,3,96,164,254,136,177,252,153 
9 data 0,4,169,1,153,0,216,192,0,208,241,76,49,234 

10 for j = 49152 to 49215: read x : poke j,x : next  
20 print "{clear}{yellow}{down*6}sys 49152, start, number of locations "
40 print "{down} sys 49152,512,80 is input buffer, 
50 print "sys 49152,217,24=screen link table, 
60 print "sys 49152,255,18=number output buffer, 
70 print "sys 49152,41110,255=some rom keywords. 
100 print "{black}{down}sys 49152, turns routine off 

;https://www.c64-wiki.com/wiki/SYS#
;Before calling the specified address, SYS “loads” the accumulator, the X and the Y index ;register, and the status register with the bytes stored at addresses 780–783/$030C–030F: From ;BASIC, one can set up parameters and data here, to be processed by the machine language routine.

;two inputs come from SYS call from BASIC, the address and count of bytes to show
.C:c000  20 73 00    JSR $0073   ; handles two args from SYS stored at addresses 780–783/$030C–030F
.C:c003  F0 1B       BEQ $C020   ; ?if no argument, "SYS 49152," turn it off (restore normal IRQ)
;handle the address to display in first argument
.C:c005  20 8A AD    JSR $AD8A   ; $AD8A/44426:   Confirm Result
.C:c008  20 F7 B7    JSR $B7F7   ; $B7F7/47095:   Convert FAC#1 to Integer in LINNUM
.C:c00b  84 FC       STY $FC     ; FC-FD stores address to start displaying characters from
.C:c00d  85 FD       STA $FD     ; decimal values allowed are 0 to 65535
;handle second argument, count of bytes to show
.C:c00f  20 9B B7    JSR $B79B   ; $B79B:Evaluate Text to 1 Byte in XR
.C:c012  86 FE       STX $FE     ; how many characters in second field, up to 255

;ok, input is handled, now replace IRQ at $c02c
.C:c014  78          SEI         ; turn off interrupts while we do IRQ work
.C:c015  A9 2C       LDA #$2C    ;  
.C:c017  8D 14 03    STA $0314   ; replace old IRQ with new at $c02c
.C:c01a  A9 C0       LDA #$C0    ;  
.C:c01c  8D 15 03    STA $0315    
.C:c01f  60          RTS

;jump here if we want to shut this all off and restore IRQ to normal
.C:c020  78          SEI           ;turn off interrupts
.C:c021  A9 31       LDA #$31      ; 
.C:c023  8D 14 03    STA $0314     ;IRQ restore low byte     $31
.C:c026  A9 EA       LDA #$EA      ;put old IRQ high byte   #$EA 
.C:c028  8D 15 03    STA $0315     ; $EA31
.C:c02b  60          RTS

;show on top of screen - new irq here
.C:c02c  A4 FE       LDY $FE        ;second argument from SYS, display up to 255 characters to screen
LOOP from c03b
.C:c02e  88          DEY
.C:c02f  B1 FC       LDA ($FC),Y    ;walk through addresses passed from arg1, offset index arg2
.C:c031  99 00 04    STA $0400,Y    ;store chars to screen 
.C:c034  A9 01       LDA #$01       ;set color to white
.C:c036  99 00 D8    STA $D800,Y    ;store to color RAM
.C:c039  C0 00       CPY #$00
.C:c03b  D0 F1       BNE $C02E      ;go to LOOP
.C:c03d  4C 31 EA    JMP $EA31      ;$EA31/59953:   Main IRQ Entry Point
