1 poke53281,1:gosub190:gosub300 
2 x=0 : poke191 , 0: poke55 ,0 : poke56 , 128 : r=33024 
3 ifpeek(191)=255orpeek(191)=0thenpoke19 1,peek(191) 
5 gosub1000 
10 a=peek( 197 ) : ifa=4thenx=x+40 : ifx+40>255thenx=x+40-256 : fl=l : goto20 
11 a=peek(197):ifa=3thenx=x+1:ifx+1>255thenx=x+l-256 : fl=l : goto20 
12 a=peek ( 197 ) : ifa=6 thenx=x-1 : ifx+1 < 0thenx=x+l+256 : fl=l : goto20 
13 a=peek( 197 ) : ifa=5thenx=x-40 : ifx-40<0thenx=256+x-40 : bl=l : got025 
20 ifpeek(191) <>255thenifa=4andf1=1thenz=l:poke191,peek(191)+z:fl=0:goto28 
21 ifpeek(191)=255thenifa=4andf1=1thenz= 1 : poke191 , peek( 191 ) -256+z : f1=0 : got028 
22 ifpeek(191)=0thenifa=5andb1=1thenz=-1 :poke191, peek ( 191)+256+z:bl=0:goto28 
25 ifpeek(191)<>0thenifa=5andb1=1thenz=- l:poke191, peek ( 191 )+z:bl=0 
28 ifpeek(191)=255andpeek(2)=255thenpoke 191,0:poke2,0 
35 ifx>255thenx=255 
36 ifx<0thenx=0 

39 poke2,x:sys49152 

40 print"{home}";peek(191)*256+peek(2); : got03 
190 forr=49152t049152+65:readj:poker,j:next : return 
200 data 165, 2, 133, 251, 165, 191, 133, 252, 169, 0, 133 
210 data 253, 169, 4, 133, 254, 162, 4, 177, 251, 145 
220 data 253, 200, 208, 249, 230, 252, 230, 254, 202, 208 
230 data 242, 169, 0, 133, 251, 169, 216, 133, 252, 162 
240 data 4, 169, 0, 145, 251, 200, 208, 251, 230, 252 
250 data 202, 208, 246, 96, 0, 255, 255, 0, 0, 255 
260 data 255, 40, 10, 255, 255 
300 dima(3) 

310 a(0)=2:a(1)=-80:a(2)=-2:a(3)=80 
320 wl=160:hl=32:sc=49658:a=sc+81 

330 print" {clear}{black}loading maze (c. bond)" 
340 forz=sctosc+40:pokez,160:next 
350 form=sctosc+3072:pokem, 160: next 
360 form=sctosc+3072step40:pokem,32:next 
370 form=sc+39tosc+3072step40:pokem,32:next 
410 pokea,4 

420 j=int(rnd(1)*4):x=j 

430 b=a+a ( j ) : ifpeek ( b ) =wlthenpokeb , j : pokea+a(j)/2,hl:a=b:goto420 
440 j=(j+1)*-(j<3):ifj<>xthen430 
450 j=peek(a) :pokea,hl:ifj<4thena=a-a(j) :goto420 
500 j=2 
510 return 
1000 rem 

1010 getd$:ifd$=""then1040 

1011 ifd$=chr$ ( 20 )thenpoker, 32 : poker+1 , 32:r=r-1:goto1040 

1012 if d$=chr$(157)then:r=r-1:goto1040 

1013 jf d$=chr$(29)thenr=r+1:goto1040 

1014 if d$=chr$(145)thenr=r-41:goto1040 

1015 if d$=chr$(17)thenr=r+39:goto1040 

1016 if d$=chr$(133)ord$=chr$(134)then1040 

1017 if d$="{clear}"thenfort=rtor+1024:poket, 32 :next:goto1040 

1020 e=asc(d$):ife>64thene=e-64 

1030 r=r+1 : ifr<40959andr>32768thenpoker,e 
1040 return