     
*=  $c000


;http://unusedino.de/ec64/technical/aay/c64/romf6dd.htm
  jsr $e544
               ;  jmp  $FFDE
             ;    SEI
loop
                 LDA $A2       ; Real-time jiffy Clock
                 LDX $A1       ; Real-time jiffy Clock
                 LDY $A0 
                sta $04F2
              stx $04F1
                 iny
                 sty $04F0
          ;       cli
      ;  jsr $BDCD

            ; jmp loop


;algo here 
;https://www.lemon64.com/forum/viewtopic.php?t=29680&start=15

    STY $FB
   STX $FC
    LDY #$04
tag06  JSR tag10
   STA $0400,Y
        DEY
     BPL tag06
       RTS
tag10     LDA $FC
       SEC
     SBC #$A0
     BCC tag19
      STA $FC
tag19     ROL $FD
      ROL $FE
      LDX #$0B
tag1f    LDA $FC
         SEC
      SBC #$50
     BCC tag28
     STA $FC
tag28     ROL $FD
     ROL $FE
        DEX
     BMI tag36
     ASL $FB
     ROL $FC
  JMP tag1f
tag36    LDA $FC
        LSR A
       LSR A
        LSR A
      ORA #$30
        TAX
      LDA $FD
     STA $FB
     LDA $FE
      AND #$1F
     STA $FC
       TXA
       RTS





end    jmp loop
;There's end a handy routine built into the BASIC ROM at $BDCD, 
;it's part of the LIST command that prints the line number, just load the
; Accumulator with the high byte and the .X register with the low byte 
;then jsr to the routine.
       ;   LDA #$00
      ;    LDX #$96
        ;  JSR $BDCD