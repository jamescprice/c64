`         ; * = $c000
*=  $c000
;https://dustlayer.com/c64-coding-tutorials/2013/5/24/episode-3-6-custom-character-sets-hello-charpad

write_text lda $d018
           ora #$0e       ; set chars location to $3800 for displaying the custom font
           sta $d018      ; Bits 1-3 ($400+512bytes * low nibble value) of $d018 sets char location
                          ; $400 + $200*$0E = $3800
           lda $d016      ; turn off multicolor for characters
           and #$ef       ; by cleaing Bit#4 of $D016
           sta $d016

loop_text  lda line1,x      ; read characters from line1 table of text...
           sta $0428,x      ; ...and store in screen ram near the center
           lda line2,x      ; read characters from line1 table of text...
           sta $0478,x      ; ...and put 2 rows below line1
           lda line3,x      ; read characters from line1 table of text...
           sta $0770,x      ; ...and put 2 rows below line1
           inx 
           cpx #$28         ; finished when all 40 cols of a line are processed
           bne loop_text
      ;     rts

           lda #$00      ; Put the value 0 in accumulator
         
           tax           ; Put value of acc in x reg
           ;lda #$58      ; Put the value $20 in acc
           lda #$00
makeboard  
           sta $0400,x   ; Put value of acc in $0400 + value in x reg
           
           sta $0500,x
           sta $0600,x
           sta $0700,x
           sta $0400
           ldy $0400
           iny
           sty $0400
           lda $0400
           inx            ; Decrement value in x reg
            
           bne makeboard  


loop       jmp loop
line1 text '64 PROGRAMMING TUTORIAL OF DIGITALERROR OF DARK CODEX'
       byte 0
line2 text '64 PROGRAMMING TUTORIAL OF DIGITALERROR OF DARK CODEX'
       byte 0
line3 text '64 PROGRAMMING TUTORIAL OF DIGITALERROR OF DARK CODEX'
       byte 0
;*= $2000
;*=   $1ffe
*=  $3800
INCBIN "bestsofar2345.bin"
