; https://retrocomputing.stackexchange.com/questions/12445/how-slow-was-the-6502-basic-compared-to-assembly
*=$C000
;;;addr      .equ 00fc
invscr    lda  #00      ; screen RAM start low byte
          sta  $00fc     ; unused zero-page location
          lda  #04      ; screen RAM start high byte
          sta  $00fc+1   
nextpage  ldy  #00      ; set 8-bit register Y to 0
nextchar  lda  ($00fc),Y ; load character from addr + Y
          ora  #$80      ; set bit 7 to make it inverse
          sta  ($00fc),y ; store modified character
          iny           ; increment Y
          bne  nextchar ; branch back if y != 0
          inc  $00fc+1   ; increment 16-bit screen address by 256
          lda  $00fc+1
          cmp  #08      ; reached end of screen?
          bne  nextpage 
exit          rts