`         ; * = $c000
*=  $c000
;https://dustlayer.com/c64-coding-tutorials/2013/5/24/episode-3-6-custom-character-sets-hello-charpad

; set character set pointer to our custom set, turn off 
; multicolor for characters
           jsr $e544
customchar lda $d018
           ora #$0e       ; set chars location to $3800 for displaying the custom font
           sta $d018      ; Bits 1-3 ($400+512bytes * low nibble value) of $d018 sets char location
                          ; $400 + $200*$0E = $3800
           lda $d016      ; turn off multicolor for characters
           and #$ef       ; by cleaing Bit#4 of $D016
           sta $d016

;;
;;
;

           lda #$00      ; Put the value 0 in accumulator         
           tax           ; Put value of acc in x reg
           
           ldy #$00
makeboard  
           sta $0400,x   ; Put value of acc in $0400 + value in x reg
       
           sta $0400
           ldy $0400
           iny
           sty $0400
           lda $0400
           inx            ; Decrement value in x reg
            
           bne makeboard  

;http://unusedino.de/ec64/technical/aay/c64/romf6dd.htm

                ; jmp  $FFDE
            ;     SEI
             ;    LDA $A2       ; Real-time jiffy Clock
              ;   LDX $A1       ; Real-time jiffy Clock
               ;  LDY $A0 
                ; sta $04F0
                 ;stx $04F1
              ;   iny
               ;  sty $04F2
                ; cli



  ;;;        lda #$00
     ;;;     sta $cc ;activate cursor
;https://www.reddit.com/r/c64/comments/noikzz/help_with_cursor_in_assembly/
;;;loop234
   ;;;     jsr $ffe4 ;get character from keyboard buffer
      ;;;  beq loop234 ;loop if there is none
;;;wait
;;;  ldx $cf  ;check cursor phase ("fase")
 ;;; bne wait ; wait for cursor to blink off
 ;;; jsr $ffd2 ;output the character from keyboard


 ; sta ($d1),y
;https://libredd.it/r/c64/comments/noikzz/help_with_cursor_in_assembly/
;But that slows down the response to typing noticeably. The way to get 
;deterministic results without slowing down input is to either roll your 
;own cursor-blink routine or very carefully use the cursor state zero-page 
;locations to save and restore the character under the cursor before printing 
;the just-read character. You can find the screen code for the non-inverted 
;character under the cursor in location $CE, a pointer to the screen line in $D1-$D2, 
;and the column on that line in $D3. So something like this will uninvert the character 
;under the cursor:
;;;  lda $ce
 ;;; ldy $d3

;;;  sta $04F5
 ;;; bne loop234



start  LDX #$0
cycle  LDA hworld,X
       CMP #0
       BEQ donetxt
       STA $05E0,X
       INX
       JMP cycle


hworld text 'INPUT:'
       byte 0
donetxt

             ldx #$20
inputyellow  lda #$07 ;yellow
             sta $d9df,x
            ; sta $da2a,x
              sta $d800,x
            ;  sta $da08,x
             dex
             bne inputyellow
             sta $d92a


;;start2  LDX #$0





             ldx #$FF
aplyellow  lda #$01 ;yellow        
              sta $d800,x
             dex
             bne aplyellow
             sta $d800

;https://www.lemon64.com/forum/viewtopic.php?t=3296
loop
 jsr $E566; move cursor home
 ; Input a string (max. 256 chars)
       ;;   LDY #$F0     ; Y = char counter = 0
            ldy #$EA
LOOPline      
        JSR $FFCF    ; Jump to Input routine
           ;; jsr $ffe4
;could ffe4 refactor as getch
          CMP #$0D     ; Return (ASCII 13) pressed?
          ;;   cmp #$20;
          BNE LOOPline     ;  
       ;   STA BUFFER,Y ; Else, store char at buffer+Y
    jsr subpaint
       

          lda $ce  ;  $ce screen code of character under cursor
            
;POKE 211,C (moves cursor to specified Column, 0-79)
;POKE 214,R (moves cursor to specified Row, 0-24)

   
          sta $04fc,y
          sta $cf00,y  ;save to ram

          INY          ; Inc. char counter

          BNE LOOPline     ; If Y != 0, get another char.


refresh   



           lda #$00      ; Put the value 0 in accumulator         
           tax           ; Put value of acc in x reg
           
           ldy #$00
makeboard2  
           sta $0400,x   ; Put value of acc in $0400 + value in x reg
       
           sta $0400
           ldy $0400
           iny
           sty $0400
           lda $0400
           inx            ; Decrement value in x reg
            
           bne makeboard2  


cycle2  LDA badmove,X
       CMP #0
       BEQ donetxt2
       STA $0608,X
       INX
       JMP cycle2
badmove text 'SENDING TO PARSER:'
       byte 0
donetxt2

          ;was f0
           ldy #$ea
showinput
           lda $cf00,y
;add 5 052a 04f6
           sta $0530,y
           sta $04fc,y
           iny 
           bne showinput

;0400 d800   52a

             ldx #$28
parsergreen  lda #$05 ;green
            
          ;    sta $d800,x
              sta $da07,x
             dex
             bne parsergreen
         ;    sta $d92a

             ldx #$20
inputyellow2  lda #$07 ;yellow
             sta $d9df,x
            ; sta $da2a,x
         ;     sta $d800,x
            ;  sta $da08,x
             dex
             bne inputyellow2
       ;      sta $d92a


        
;test  jmp test        

        jmp loop

;;
subpaint
           sta $ce00
           sty $ce01
           stx $ce02
           lda #$00      ; Put the value 0 in accumulator         
           tax           ; Put value of acc in x reg
           
           ldy #$00
makeboard3  
           sta $0400,x   ; Put value of acc in $0400 + value in x reg
       
           sta $0400
           ldy $0400
           iny
           sty $0400
           lda $0400
           inx            ; Decrement value in x reg
            
           bne makeboard3  

         


             ldx #$FF
aplwhite  lda #$01 ;yellow        
              sta $d800,x
             dex
             bne aplwhite
             sta $d800



cycle3  LDA hworld3,X
       CMP #0
       BEQ donetxt3
       STA $05E0,X
       INX
       JMP cycle3


hworld3 text 'INPUT:'
       byte 0
donetxt3

             ldx #$20
inputyellow3  lda #$07 ;yellow
             sta $d9df,x
           
             dex
             bne inputyellow3
             sta $d92a

  lda $ce00
           ldy $ce01
           ldx $ce02
     sta $ce00
          rts
*=  $3800
INCBIN "aplcharsetnov2.bin"
