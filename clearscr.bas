10 loc=49152 : rem store the routine at $c000
20 read v: if v = -1 then end
30 poke loc,v : loc = loc + 1 : goto 20
50 data 169,0,133,252,169,4,133,253
60 data 160,0,177,252,9,128,145,252,200,208,247
70 data 230,253,165,253,201,8,208,237,96
90 data -1