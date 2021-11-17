`         ; * = $c000
*=  $c000
           lda $d018
           ora #$0e       ; set chars location to $3800 for displaying the custom font
           sta $d018      ; Bits 1-3 ($400+512bytes * low nibble value) of $d018 sets char location
                          ; $400 + $200*$0E = $3800
           lda $d016      ; turn off multicolor for characters
           and #$ef       ; by cleaing Bit#4 of $D016
           sta $d016

;ok, input is handled, now replace IRQ at $c02c
         SEI         ; turn off interrupts while we do IRQ work
         LDA #$1c    ;  
         STA $0314   ; replace old IRQ with new at $c01c
         LDA #$C0    ;  
         STA $0315    
            rts
;loophere   jmp loophere
;show on top of screen - new irq here
         LDY #120        ;second argument from SYS, display up to 255 characters to screen
          
LOOP  
         DEY
     ;;;   LDA $3800,Y    ;walk through addresses passed from arg1, offset index arg2        
       ;;; rol a
          tya
         STA $0400,Y    ;store chars to screen 
         LDA #$01       ;set color to white
         STA $D800,Y    ;store to color RAM
         CPY #$00
         BNE LOOP
         JMP $EA31      ;$EA31/59953:   Main IRQ Entry Point

;loopy    jmp loopy

*=  $3800
INCBIN "bestsofar23456.bin"

