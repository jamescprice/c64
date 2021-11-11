;*= $c000   ;Workspace 

chrout      = $ffd2 ;Kernal Routin  
        LDA #$FF  ; maximum frequency value
        STA $D40E ; voice 3 frequency low byte
        STA $D40F ; voice 3 frequency high byte
        LDA #$80  ; noise waveform, gate bit off
        STA $D412 ; voice 3 control register  
		
     ldx #$0
copy_charset:
     lda charset,x
     sta $3800,x
     lda charset+256,x
     sta $3800+256,x
     lda charset+512,x
     sta $3800+512,x
     lda charset+768,x
     sta $3800+768,x
     lda charset+1024,x
     sta $3800+1024,x
     lda charset+1280,x
     sta $3800+1280,x
     lda charset+1536,x
     sta $3800+1536,x
     lda charset+1792,x
     sta $3800+1792,x
     dex
     bne copy_charset

; set character set pointer to our custom set, turn off 
; multicolor for characters
           jsr $e544
customchar: lda $d018
           ora #$0e       ; set chars location to $3800 for displaying the custom font
           sta $d018      ; Bits 1-3 ($400+512bytes * low nibble value) of $d018 sets char location
                          ; $400 + $200*$0E = $3800
           lda $d016      ; turn off multicolor for characters
           and #$ef       ; by cleaing Bit#4 of $D016
           sta $d016

;;
   
doagain:
          ; jsr domath
            jsr dofire
           jmp doagain

domath:    LDA $D41B  ;heres the random
                
output:      ;Print string to screen.
        LDX #0
        lda $D41B
        sta buf,x
        sta $0600
        sta $cf00
outloop: LDA buf,x
        BEQ done
        cmp $03 ; stop key
        beq skipit
        cmp $88
        beq skipit
        cmp $83
        beq skipit
        cmp $6b
        beq skipit
        JSR chrout
skipit:
        sta $0610
        INX
        BNE outloop
done:
        rts
   
dofire:    LDA $D41B
 cmp $03 ; stop key
        beq skipit2
 ; cmp $20 ;
  ; bmi skipit2
   cmp $7f
   ;bpl skipit
    bmi skipit2
        cmp $88
        beq skipit2
        cmp $83
        beq skipit2
        cmp $6b
        beq skipit2

    cmp $19
 beq skipit2
          jsr chrout
skipit2:
         rts
;index  byte 4       ;Reverse index into buffer
;str    null "     " ;String buffer of 5 spaces
   

 
  
        LDA #$FF  ; maximum frequency value
        STA $D40E ; voice 3 frequency low byte
        STA $D40F ; voice 3 frequency high byte
        LDA #$80  ; noise waveform, gate bit off
        STA $D412 ; voice 3 control register  




.data
index:    .byte 4
buf:    .asciiz "     "
;buf:      .null 
charset:    .incbin "aplcharset.bin"
