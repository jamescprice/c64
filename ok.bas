1 poke53281,1:gosub190:gosub 1000
2 x=0:poke191,0:poke55,0:poke156,128
3 ifpeek(191)=255orpeek(191)=0thenpoke191,peek(191) 
4 a=peek(197):ifa=31thenpoke191,208: rem v-  video Chip (6566)
5 a=peek(197):ifa=17thenpoke191,224: rem r-    rom Operating System
6 a=peek(197):ifa=20thenpoke191,0: rem c-  clear to zero
7 a=peek(197):ifa=13thenpoke191,4:rem s - screen mem start
8 a=peek(197):ifa=28thenpoke191,8:rem b - basic  
9 a=peek(197):ifa=33thenpoke191,214:rem i - i/o 56320-56335 video Interface chip 6526 CIA DD00-DD0F 56576-56591
10 a=peek(197):ifa=23thenx=x+40:ifx+40>255thenx=x+40-256:b=peek(191):ifb<255thenpoke191,peek(191)+1:goto35 
11 a=peek(197):ifa=18thenx=x+1 :ifx+1>255 thenx=x+l-256 :goto35 
12 a=peek(197):ifa=10thenx=x-1 :ifx+1<0   thenx=x+l+256 :goto35 
13 a=peek(197):ifa=9 thenx=x-40:ifx-40<0  thenx=256+x-40:b=peek(191):ifb>0thenpoke191,peek(191)-1:goto35
14 a=peek(197):ifa=37thenforq=1524to1530: pokeq,55:next q: rem kaboom
24 a=peek(197):ifa=39thenforq=peek(191)*256+peek(2)+500topeek(191)*256+peek(2)+600: pokeq,55:next q: rem nuke  peek(191)*256+peek(2);peek(191)
25 a=peek(197):ifa=30thenpoke191,50: rem user sprite data nuke 53792  53872
35 ifx>255thenx=255 
36 ifx<0thenx=0 
39 poke2,x:sys49152 
40 print"{home}";peek(191)*256+peek(2);peek(191);"page ";" byte ";peek(2);"dir ";a;"  "
50 goto3
190 forr=49152to49152+65:readj:poker,j:next:return 
200 data 165, 2, 133, 251, 165, 191, 133, 252, 169, 0, 133 
210 data 253, 169, 4, 133, 254, 162, 4, 177, 251, 145 
220 data 253, 200, 208, 249, 230, 252, 230, 254, 202, 208 
230 data 242, 169, 0, 133, 251, 169, 216, 133, 252, 162 
240 data 4, 169, 4, 145, 251, 200, 208, 251, 230, 252 
250 data 202, 208, 246, 96, 0, 255, 255, 0, 0, 255 
260 data 255, 40, 10, 255, 255 
270 return
280 rem
1000 PRINT CHR$(147): V=53248: POKE V+33,0: REM clear screen
1002 FOR XX=12800 TO 12927: POKE XX,0: NEXT XX: REM Clear RAM for sprites

1010 FOR XX=12800 TO 12881: READ YY: POKE XX,YY: NEXT XX: REM sprite generation
1011 POKE 2040,200: POKE 2041,201: POKE 2042,201: POKE V+21,7
1012 POKE V+28,6: POKE V+37,15: POKE V+38,2: REM multicolor for sprite 1&2
1013 POKE V+39,7: POKE V+40,8: POKE V+41,6: REM sprite color sprite 0&1&2
1015 POKE V+23,7: POKE V+29,7: POKE V+16,1: REM sprite properties height, width, x position
1016 POKE V+1,133: POKE V+2,170: POKE V+5,115: REM x/y positions



1039 REM SPRITE C64-WIKI.DE (unicolor; sprite 0)
1040 DATA 239,81,85,139,81,20,137,81,28,137,81,89,137,213,89,142,85,93,138   
1041 DATA 95,85,138,91,85,238,91,85,0,0,0,0,0,0,0,0,0
1042 DATA 0,199,0,0,231,0,0,164,0,0,180,0,0,151,0,0,180,0,0,164,0,0,231,0,0,199,0

1044 REM multicolor sprite lines (sprite 1&2)
1045 DATA 0,255,255,255,170,85,170,170,85,170,85,170,85,85,170,85,255,255,255
1055 return