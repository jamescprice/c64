10 print"{clear}" : a$ = "no"
20 print "world builder";
30 print "by stephen kimmel";
40 print "a program for designing worlds";
50 print "where no man has been before";
60 dim sc$(8), m(8), c$(8), s$(36), ls(36), ss$(36), sm(36), mp(15), r(15)
70 for i = 1 to 8: read sc$(i), m(i), c$(i): next i
71 data o,100, blue
72 data b,17,  pale blue
73 data a,3.2, white
74 data f,1.54,pale yellow
75 data g,1.02,yellow
76 data k,.75, orange
77 data m,.38, red
78 data d,0.,  red
80 for i = 1 to 17: read s$(i), ss$(i), sm(i): ls(i) = sm(i) ^ 3.5: next
81 data sol,              g2,1.0
82 data alpha centuri a,  g4,1.08
83 data alpha centuri b,  k1,.88
84 data epsilon eridani,  k2,.30
85 data tau ceti,         g8, .82
86 data 70 ophiuchi a,    k1,.9
87 data 70 ophiuchi b,    k5,.65
88 data eta cassiopeiae a,f9,.94
89 data eta cassiopeiae b,k6,.58
90 data sigma draconis,   g9,.82
91 data 36 ophiuchi a,    k2, .77
92 data 36 ophiuchi b,    k1,.76
93 data hr 7703,          k2, .76
94 data delta pavonis,    g7,.98
95 data 82 eridani,       g5,.91
96 data beta hydri,       g1,1.23
97 data hr 8832,          k3, .74
100 for i = 18 to 36: read s$(i), ss$(i), ls(i): sm(i) = ls(i) ^ .285714: next
200 data sirius,al,23,canopus,f0,130,vega,a0,52,arcturus,k2,100
210 data rigel,b8,52000,capella,g8,145,procyon,f5,7.6
220 data achernar,b5,1000,altair,a7,10,betelgeuse,m2,8300
230 data aldebaran,k5,160,spica,b1,760,antares,m1,830
240 data pollux,k0,33,fomalhaut,a3,13,beta crucis,b0,8300
250 data deneb,a2,52000,regulus,b7,160,barnard's star,m5,.00044
260 print"{clear}": print "world builder"
270 print "enter the number for the option you want"
280 print : print "1....use a known star"
290 print "2....use a star not on list"
300 print "3....list known stars"
310 print "4....quit"
320 input "your choice"; a
330 if a < l or a > 4 goto 260
340 on a goto 410, 550, 370, 350
350 input "are you sure you want to quit"; a$
360 if asc(a$) = 89 then end 
365   goto 260
370 print"{clear}": print "i know the following stars"
380 for i = 1 to 12
390 print s$(i); tab(20); s$(i + 12); tab(40); s$(i + 24)
400 next i
410 input "which star should i use"; s$
420 if s$ = "none" or s$ = "" then 260
430 for i = 1 to 36
440 if s$ = s$(i) then sk = i: goto 470
450 next i
460 print "i don't know that star": goto 270
470 sc = val(right$(ss$(sk), 1)) / 10
480 s1$ = left$(ss$(sk), 1)
490 for i = 1 to 7: if s1$ = sc$(i) then j = i: goto 510
500 next i
510 ms = sm(sk): l = ls(sk): ax = (ms ^ -2.5) * 10
520 p = (1.25 - ms / (l ^ .285714)) / .005
530 if p / 100 * ax > 10 then p = 1000 / ax
540 goto 740
550 input "what is the star's name"; s$
560 input "what is the star's spectral class"; s1$
570 if s1$ <> "" goto 640
580 input "what is the absolute magnitude (sun=4.85)"; m
590 l = exp(1.94 - .4 * m): ms = l ^ .285714
600 for i = 1 to 7: if m(i) < ms then j = i - l: goto 620
610 next i
620 s1$ = sc$(i - 1): sc = int((ms - m(j)) / (m(i) - m(j))) / 10
630 goto 680
640 sc = val(right$(s1$, 1)) / 10: s1$ = left$(s1$, 1)
650 for i = 1 to 7: if s1$ = sc$(i) then j = i: goto 670
660 next i: print "i don't know that class": goto 560
670 ms = m(j) - sc * (m(j) - m(j + l))
680 ax = (ms ^ -2.5) * 10
690 print s$; " has an expected life of "; ax; " billion years"
700 input "what percent (1-100) has already passed"; p
710 if p / 100 * ax > 12 then print "the big bang occured 12 billion years ago.":input "is this what you want"; a$: if asc(a$) <> 89 then goto 690
720 ms = ms * (1.25 - .005 * p)
730 l = ms ^ 3.5
740 ts = 6000 * ms ^ .35
750 ds = ms ^ .3333
760 print"{clear}" : print "stellar data"
770 print "the selected star, "; s$; " is a "; s1$; sc * 10; " star"
780 if sc > .75 then print "is "; c$(j + 1): goto 810
790 if sc < .25 then print "is "; cs(j): goto 810
800 print "is between "; cs(j); " and "; c$(j + l)
810 print "has a mass of "; ms; " times that of the sun"
820 print "it is "; l; " times as bright as the sun"
830 print "the star has an expected lifespan of"; ax; " billion years"
840 print "of which it has lived"; p; "% or about"; ax * p / 100; " billion years."
850 if p > 95 then print "  the star is in its death throes."
860 print "it has a surface temperature of "; ts; " degrees kelvin"
870 if j + sc < 2.5 or j + sc > 7 then print "and is believed to have no planets": goto 890
880 print "and may have planets"
890 print "this star will die as a ";
900 if ms < 1.5 then print "white dwarf": goto 940
910 if ms < 4.0 then print "neutron star": goto 940
920 if ms < 10. then print "neutron star after going nova": goto 940
930 print "black hole after going super nova"
940 input "another star"; a$
950 if asc(a$) = 89 then 260
960 p = p / 100
970 print"{clear}": print "the main planet of interest"
980 print "the earth has an average surface temperature of 60 degrees"
990 input "what surface temperature would you like"; tp: tp = tp + 460
1000 input "desired surface gravity (earth=1)"; g
1010 if g <= 0 then print "the planet must have some gravity": goto 1000
1020 rp = sqr(l / (tp / 520) ^ 4)
1030 if rp < ms / 5 then print "this planet is too close to be stable.": goto 980
1040 pp = sqr(rp ^ 3 / ms)
1050 ix = l / rp ^ 2
1060 rm = .00012 * ts
1070 rx = 6452 * exp(.0005 * ts)
1080 sa = ds / rp
1090 input "how big should the planet be relative to earth"; d
1100 m = g * d ^ 2
1110 if m < .055 then print "the planet won't retain an oxygen atmosphere"
1120 if m > 17.6 then print "the planet won't lose its hydrogen atmosphere"
1130 print "earth's orbit has an eccentrcity of .01672"
1140 input "what is the orbital eccentricity ( <1)"; ec
1150 if ec > l then 1140
1160 ca = (1 - ec) * rp: fa = (1 + ec) * rp
1170 input "how does the axis tilt (earth=23.5 degrees)"; axis
1180 if axis < 0 or axis > 90 then 1170
1190 input "how many moons does the planet have"; mn
1200 if mn > 10 then print "for convenience we'll limit this to 10": mn = 10
1210 mm = 1000: h = 0: r = 56 * g
1220 if mn <= 0 then 1320
1230 for i = 1 to mn
1240 print "mass of moon #"; i; " (our moon=1)"; : input mn(i)
1250 input "orbit (our moon=30)"; mr(i)
1260 if mr(i) < 3 * g then print "the moon is too close and will break up": goto 1250
1270 if mr(i) > 56 * g then print "the moon is too far and will drift away": goto 1250
1280 mp(i) = sqr(mr(i) ^ 3 / m) * 4
1290 if mr(i) < r then mm = mp(i): r = mr(i)
1300 h = mn(i) * .01235 / (mr(i) ^ 3) + h
1310 next i
1320 h2 = .85 * d ^ 4 / m * (ms * 333500 / (11759 * rp) ^ 3 + h)
1330 da = 1759260 * h2 * 14 + 10
1340 if da > mm then da = mm
1350 print"{clear}": print "this planet's day should be about"; da; " hours long."
1360 print "that makes its year"; 8766 / da * pp; "days long. with a tilt of"; axis
1370 hi = (1 + .025 * da / 24) * tp - 460: lo = (1 - .025 * da / 24) * tp - 460
1380 if lo < -460 then lo = -460
1390 print "today's high temperature should be"; hi; " degrees f."
1400 print "tonight's expected low is"; lo; " degrees f."
1410 sh = hi + 1.9 * axis * (1 + ec) ^ 2: ll = lo - 1.9 * axis / (1 + ec) ^ 2
1420 if ll < -460 then ll = -460
1430 print "this summer we expect it to get up to"; sh
1440 print "this winter it should drop down to"; ll
1450 if sh < 32 or ll > 175 then print "there are times when no liquid water exists."
1460 if mn <= 0 goto 1600
1470 if mn = 1 goto 1570
1480 for i = 1 to mn: f = 0: for k = 1 to mn - i
1490 if mr(k + 1) >= mr(k) then 1540
1500 t = mr(k): mr(k) = mr(k + 1): mr(k + 1) = t
1510 t = mn(k): mn(k) = mn(k + 1): mn(k + 1) = t
1520 t = mp(k): mp(k) = mp(k + 1): mp(k + 1) = t
1530 f = 1
1540 next k
1550 if f = 0 then 1570
1560 next i
1570 print : print "your selected system of moons"
1580 print "orbit", "mass", "period"
1590 for i = 1 to mn: print mr(i), mn(i), mp(i); "hours "; mp(i) / da; " days": next i
1600 input "want a different set of moons"; a$
1610 if asc(a$) = 89 then 1190
1620 print"{clear}" : print "planetary data"
1630 print "our principal planet of interest has an average surface"
1640 print "temperature of"; tp - 460; " degrees f. this requires an orbit"
1650 print "of"; rp; " astronomical units ("; rp * 93; " million miles)"
1660 print "closest approach ="; ca; " au: greatest distance ="; fa; " au"
1670 print "this also means it has a year that is"; pp; " years long"
1680 print "the star appears";
1690 if sa > 1.5 or sa < .75 then print " much"
1700 if sa > 1. then print " larger"; :  goto 1710
1705  print " smaller";
1710 print " than our sun."
1720 if g > .95 and g < 1.05 then print "gravity is essentially the same as earth's": goto 1780
1730 print "since our planet has a gravity"; : if g < 1 then 1760
1740 print " greater than earth's we expect"
1750 print "a thicker atmosphere. there is greater tectonic action and more greater resisting forces. thus we expect more continents and shorter mountains. earthquakes should be more frequent and more severe.": goto 1780
1760 print " less than earth's we expect"
1770 print "a thinner atmosphere. there is less tectonic action and less resistance. thus we expect fewer mountains but they may be much taller. earthquakes, if any, will be less severe."
1780 print "a gravity of "; g; " means that if you weigh 200 pounds"
1790 print "you would weigh"; g * 200; " on our planet"
1800 input "would you like a new gravity"; a$
1810 if asc(a$) = 89 then 1000
1820 print"{clear}" : print "life ???"
1830 if m < .055 or m > 17.6 then print "because of the bad atmosphere ": goto 2080
1840 if rp < rm or rp > rx then print "because of the level of radiation ": goto 2080
1850 if sh < 32 or ll > 175 then print "since liquid water never occurs ": goto 2080
1860 if ax * p < 1.5 then print "the planet is too young to have evolved life": goto 2080
1870 if p > .95 then print "since the star is in its death throes ": goto 2080
1880 print "there may be some ";
1890 if ax * p < 2 * g then print "bacteria and blue green algae": goto 2060
1900 if ax * p < 3 * g then print "single cell life with nucleus": goto 2060
1910 if ax * p < 4 * g then print "simple multicelled life": goto 2060
1920 if ax * p < 4.4 * g then print "water vertebrates and land plants": goto 2060
1930 print "major land animals and perhaps intelligence"
1940 if g < 95 then 1990
1950 if g < 1.05 then 2030
1960 print "higher gravity means a thick atmosphere which will support largebirds. it also means that short falls could be fatal so reaction times should be very short. all life forms will be shorter and stockier than on earth."
1970 if g > 1.2 then print "there are no two legged animals."
1980 print "the thick atmosphere improves sound transmission so the animals may will rely more on hearing.": goto 2030
1990 print "lower gravity means a thinner atmosphere. birds, if any, have larger wings. all life forms will should be taller and more slender than on earth."
2000 print "it there probably are many two legged animals."
2010 print "the thin atmosphere hurts sound transmission so animals will either have large ears or none. lungs will be much larger."
2020 if tp > 75 then print "some form of radiation protection will be necessary."
2030 if sa < .75 then print "because of the small sun, we expect animals to have large eyes or to rely on other senses."
2040 if sa > 1.5 then print "unless the atmosphere is obscured, we expect reliance on sight using relatively small eyes."
2050 if hi - lo > 50 then print "extreme temperature variations favor underground and underwater lifeforms."
2060 if (tp - 460) < 32 or (tp - 460) > 86 or g > 1.5 or g < .68 or m < .4 or m > 2.35 or da > 96 or sh > 120 or ll < -30 or hi > 110 or lo < -10 then hm = 0 : goto 2070
2065    hm = 1
2070 goto 2090
2080 print "there appears to be no life on this planet."
2090 print "this planet "; : if hm = 1 then print "might be"; :  goto 2100
2095   print "wouldn't be";
2100 print " considered habitable by man."
2110 input "want another planet"; a$
2120 if asc(a$) = 89 then 970
2130 print"{clear}" : print "other planets"
2140 input "how many planets would you like"; np
2150 if np > 15 then print "for convenience we'll limit this to 15": np = 15
2160 if np <= 1 then 2600
2170 am = 1180 / sqr(ms) - m * sqr(rp)
2180 r(1) = rp: mp(1) = m
2190 for i = 2 to np
2200 print"{clear}"
2210 print "our solar system is laid out like this:"
2220 print "planet      mass      distance from sun"
2230 print "mercury     .055       .387"
2240 print "venus       .815       .723"
2250 print "earth        1.0       1.0"
2260 print "mars        .108       1.524"
2270 print "jupiter     317.9      5.203"
2280 print "saturn      95.2       9.539"
2290 print "uranus      14.6       19.18"
2300 print "neptune     17.2       30.06"
2310 print "pluto       .100       39.44"
2320 print "mass for planet #"; i; : input mp(i)
2330 if mp(i) > 1000 then print "a body this large would become a star.": goto 2320
2340 input "distance from star"; r(i)
2350 if r(i) < ms / 5 then print "planet is too close to sun": goto 2340
2360 if r(i) > 56 * ms then print "planet is too far from the sun": goto 2340
2370 for k = 1 to i - 1: if r(k) > .9 * r(i) and r(k) < 1.1 * r(i) then 2430
2380 next k
2390 a1 = mp(i) * sqr(r(i))
2400 if a1 > am then print "the planet has too much mass for system": goto 2210
2410 am = am - a1
2420 next i: goto 2450
2430 print "this planet is too close to other planets to have a stable orbit"
2440 goto 2210
2450 for i = 1 to np: f = 0: for k = 1 to np - i
2460 if r(k + 1) >= r(k) then 2500
2470 t = r(k): r(k) = r(k + 1): r(k + 1) = t
2480 t = mp(k): mp(k) = mp(k + 1): mp(k + 1) = t
2490 f = 1
2500 next k
2510 if f = 0 then 2530
2520 next i
2530 print "planet #       mass          orbit"
2540 for i = 1 to np
2550 print i, mp(i), r(i);
2560 if r(i) > rm and r(i) < rx and mp(i) > .055 and mp(i) < 17.6 then print "life?" :goto2570
2565 print " "
2570 next i
2580 input "would you like to try another system"; a$
2590 if asc(a$) = 89 then 2130
2600 input "would you like to try another star"; a$
2610 if asc(a$) = 89 then 260
2620 end
