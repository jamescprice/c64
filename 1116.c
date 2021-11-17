#include <peekpoke.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <c64.h>
#include <cbm.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define	BSOUT(c)	kcall($FFD2,c,0,0)
#define CLRSCR \
__asm__("lda #$93"); \
__asm__("jsr $ffd2");
#define CURSORHOME \
__asm__("jsr $E566"); 
#define GETCH \
__asm__("JSR $FFCF");



//Remember, 53248 is V!

const unsigned char charsetData[] =  {    
  0x3C, 0x66, 0x6E, 0x6E, 0x60, 0x62, 0x3C, 0x00, 0x0C, 0x1E, 0x33, 0x7E, 0x66, 0xCC, 0xCC, 0x00, 0x3E, 0x33, 0x33, 0x7C, 0x66, 0xCC, 0xF8, 0x00, 0x1E, 0x33, 0x30, 0x60, 0x60, 0xCC, 0x78, 0x00, 0x3C, 0x36, 0x33, 0x66, 0x66, 0xD8, 0xF0, 0x00,
  0x3F, 0x30, 0x30, 0x78, 0x60, 0xC0, 0xFC, 0x00, 0x3F, 0x30, 0x30, 0x78, 0x60, 0xC0, 0xC0, 0x00, 0x1E, 0x33, 0x30, 0x6E, 0x66, 0xCC, 0x78, 0x00, 0x33, 0x33, 0x33, 0x7E, 0x66, 0xCC, 0xCC, 0x00, 0x1E, 0x0C, 0x0C, 0x18, 0x18, 0x30, 0x78, 0x00,
  0x0F, 0x06, 0x06, 0x0C, 0x0C, 0xD8, 0x70, 0x00, 0x33, 0x36, 0x3C, 0x70, 0x78, 0xD8, 0xCC, 0x00, 0x30, 0x30, 0x30, 0x60, 0x60, 0xC0, 0xFC, 0x00, 0x31, 0x3B, 0x3F, 0x6B, 0x63, 0xC6, 0xC6, 0x00, 0x33, 0x3B, 0x3F, 0x7E, 0x6E, 0xCC, 0xCC, 0x00,
  0x1E, 0x33, 0x33, 0x66, 0x66, 0xCC, 0x78, 0x00, 0x3E, 0x33, 0x33, 0x7C, 0x60, 0xC0, 0xC0, 0x00, 0x1E, 0x33, 0x33, 0x66, 0x66, 0x78, 0x1C, 0x00, 0x3E, 0x33, 0x33, 0x7C, 0x78, 0xD8, 0xCC, 0x00, 0x1E, 0x33, 0x30, 0x3C, 0x06, 0xCC, 0xF8, 0x00,
  0x3F, 0x0C, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x00, 0x33, 0x33, 0x33, 0x66, 0x66, 0xCC, 0x78, 0x00, 0x33, 0x33, 0x33, 0x66, 0x66, 0x78, 0x30, 0x00, 0x31, 0x31, 0x31, 0x6B, 0x7F, 0xEE, 0xC6, 0x00, 0x33, 0x33, 0x1E, 0x18, 0x3C, 0xCC, 0xCC, 0x00,
  0x33, 0x33, 0x33, 0x3C, 0x18, 0x30, 0x30, 0x00, 0x3F, 0x03, 0x06, 0x18, 0x30, 0xC0, 0xFC, 0x00, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00, 0x00, 0x10, 0x54, 0x54, 0x38, 0x10, 0x10, 0x00, 0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00,
  0x00, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x00, 0x10, 0x30, 0x7F, 0x7F, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF, 0xFF, 0x89, 0x81, 0xFF, 0x81, 0x89, 0x81, 0xFF, 0x7E, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x7E, 0x06, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0C, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00, 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30,
  0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00, 0x00, 0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C, 0x00, 0x18, 0x18, 0x38, 0x18, 0x18, 0x18, 0x7E, 0x00,
  0x3C, 0x66, 0x06, 0x0C, 0x30, 0x60, 0x7E, 0x00, 0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00, 0x06, 0x0E, 0x1E, 0x66, 0x7F, 0x06, 0x06, 0x00, 0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C, 0x00, 0x3C, 0x66, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00,
  0x7E, 0x66, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x00, 0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00, 0x3C, 0x66, 0x66, 0x3E, 0x06, 0x66, 0x3C, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30,
  0x0E, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0E, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x70, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x70, 0x00, 0x3C, 0x66, 0x06, 0x0C, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00, 0x3A, 0x66, 0x66, 0x66, 0x3B, 0x00,
  0x00, 0x00, 0x3C, 0x60, 0x78, 0x60, 0x3C, 0x00, 0x00, 0x30, 0x18, 0x18, 0x18, 0x1A, 0x0E, 0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x00, 0x00, 0x22, 0x6B, 0x6B, 0x7F, 0x36, 0x00, 0x00, 0x3C, 0x66, 0x66, 0x7E, 0x5A, 0x42, 0x42,
  0x10, 0x28, 0x28, 0x44, 0x44, 0x82, 0xFE, 0x00, 0x00, 0xFE, 0x82, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10, 0x38, 0x38, 0x54, 0x54, 0x92, 0xFE, 0x10, 0x10, 0xFE, 0x92, 0x54, 0x54, 0x38, 0x38, 0x10, 0x00, 0xFE, 0x82, 0x44, 0xFE, 0x28, 0x28, 0x10,
  0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x3C, 0x00, 0x18, 0x7E, 0xDB, 0xDB, 0xDB, 0x7E, 0x18, 0x00, 0x18, 0x7E, 0xC3, 0xFF, 0xC3, 0x7E, 0x18, 0x00, 0x98, 0x7E, 0xF3, 0xDB, 0xCF, 0x7E, 0x19, 0x00, 0x3C, 0x42, 0x99, 0xA5, 0xA5, 0x99, 0x42, 0x3C,
  0x3C, 0x62, 0x95, 0xBF, 0x9D, 0xB5, 0x42, 0x3C, 0x18, 0x7E, 0xDB, 0xDB, 0xDB, 0x7E, 0x18, 0x7E, 0x7E, 0x18, 0x7E, 0xDB, 0xDB, 0xDB, 0x7E, 0x18, 0x00, 0x00, 0x18, 0x24, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x3C, 0x00,
  0x00, 0x3C, 0x7E, 0x66, 0x66, 0x7E, 0x3C, 0x00, 0x3C, 0x7E, 0x66, 0x42, 0x66, 0x7E, 0x3C, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18, 0x00, 0x04, 0x06, 0x7F, 0x7F, 0x06, 0x04, 0x00, 0x01, 0x02, 0x7E, 0x08, 0x7E, 0x20, 0x40, 0x00,
  0x00, 0x66, 0x3C, 0x18, 0x18, 0x3C, 0x66, 0x00, 0x00, 0x08, 0x00, 0x7E, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x46, 0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x00, 0x00, 0x7C, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00,
  0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7C, 0x00, 0x18, 0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00, 0x3E, 0x7E, 0xC0, 0xC0, 0x7E, 0x3E, 0x00, 0x00, 0x7C, 0x7E, 0x03, 0x03, 0x7E, 0x7C, 0x00,
  0x00, 0xC0, 0x60, 0x30, 0x7E, 0x0C, 0x06, 0x00, 0x00, 0x03, 0x06, 0x0C, 0x7E, 0x30, 0x60, 0x00, 0xFF, 0x8D, 0x99, 0xB1, 0x81, 0x81, 0x81, 0xFF, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x0E, 0x18, 0x30, 0x60, 0x38, 0x0E, 0x00, 0x7E,
  0x70, 0x18, 0x0C, 0x06, 0x1C, 0x70, 0x00, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x7E, 0x7E, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0xC0, 0xC0, 0xC0, 0xF8, 0xF8, 0xC0, 0xC0, 0xC0,
  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x14, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x14, 0x08, 0x00, 0x39, 0x46, 0x00, 0x08, 0x14, 0x22, 0x22, 0x00, 0x39, 0x46, 0x00, 0x22, 0x22, 0x14, 0x08,
  0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x08, 0x10, 0x08, 0x08, 0x04, 0x00, 0x20, 0x10, 0x10, 0x08, 0x10, 0x10, 0x20, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 0x04, 0x3C, 0x08, 0x3C, 0x10, 0x3C, 0x20, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm

struct node { 
   int data;
   int key;
   int    *p_array;
   struct node *next;  
// declare a pointer variable to point to allocated heap space
   	
};

struct node *head = NULL;
struct node *current = NULL;
  char tmpstring[25];  //global
   char inputstring[25];

//display the list
void printList() {
int i;
   struct node *ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%d,%d) ",ptr->key,ptr->data);
      for(i=0; i < 5; i++) {
         printf(" %i ,", ptr->p_array[i]);	
	  }	 
	  printf("\n");
	  ptr = ptr->next;
   
   }
	
   printf(" ]");
   return;
}

//insert link at the first location
void insertFirst(int key, int data, char tmpstring[25]) {
   //create a link
   int i;
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->key = key;
   link->data = data;
   //
        // call malloc to allocate that appropriate number of bytes for the array

    link-> p_array = (int *)malloc(sizeof(int)*5);      // allocate 50 ints 
      /// if(p_array == NULL) {
     ///     printf("malloc of size %d failed!\n", 5);   // could also call perror here
   // use [] notation to access array buckets 
// (THIS IS THE PREFERED WAY TO DO IT)
   for(i=0; i < 5; i++) {
	   
    int j;
	j = rand();
      link->p_array[i] = j;
   }
   for(i=0; i < 5; i++) {
	 
      link->p_array[i] = tmpstring[i];
   }
   
   
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}



//delete first item
struct node* deleteFirst() {

   //save reference to first link
   struct node *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   return tempLink;
}




//is list empty
bool isEmpty() {
   return head == NULL;
}
int length() {
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

//find a link with given key
struct node* find(int key) {

   //start from the first link
   struct node* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if data found, return the current Link
   return current;
}


//delete a link with given key
struct node* delete(int key) {

   //start from the first link
   struct node* current = head;
   struct node* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
	
   return current;
}

void sort() {

   int i, j, k, tempKey, tempData;
   struct node *current;
   struct node *next;
	
   int size = length();
   k = size ;
	
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head;
      next = head->next;
		
      for ( j = 1 ; j < k ; j++ ) {   

         if ( current->data > next->data ) {
            tempData = current->data;
            current->data = next->data;
            next->data = tempData;

            tempKey = current->key;
            current->key = next->key;
            next->key = tempKey;
         }
			
         current = current->next;
         next = next->next;
      }
   }   
}

void reverse(struct node** head_ref) {
   struct node* prev   = NULL;
   struct node* current = *head_ref;
   struct node* next;
	
   while (current != NULL) {
      next  = current->next;
      current->next = prev;   
      prev = current;
      current = next;
   }
	
   *head_ref = prev;
}

void LoadCustomCharset(void)
{
 //  unsigned int i;
   // unsigned char *memDest;

    /*

POKE 56334, PEEK(56334) AND 254                      (Interrupts deactivate)
POKE 1, PEEK(1) AND 251                              (E/A aera deactivate, char set ROM online)
FOR A=53248 TO 57343:
    POKE A-40960, PEEK(A):
NEXT A  (copy routine)
POKE 1, PEEK(1) OR 4                                 (E/A aera activate)
POKE 56334, PEEK(56334) OR 1                         (Interrupts activate)

    */
 //Turn off KB and IO
    printf("turn off keyboard and IO\n");
//    POKE(56334, PEEK(56334) & 254);
  //  POKE(1u, PEEK(1u) & 251);


    //copy charset to ram
    printf("copying charset to ram at 12288\n");
//    memcpy(12288, charsetData, 8*128);
 ///////////
 //memcpy(57344, charsetData, 8*128);
 memcpy(49152, charsetData, 8*128);   //c000 this works 
 POKE (56576, PEEK(56576) & 252);
 POKE (53272, 32);  //vic register
 POKE (648,200);
 // font is at 49152 and       screen at 49152+2048   = 51200
 //https://www.lemon64.com/forum/viewtopic.php?t=23355
 //10 poke 56576,peek(56576)and252
 //20 poke53272,32
 //30 poke648,200

//Line 10 makes VIC-II access the last 16 KB, line 20 makes it 
//use font at 49152 and screen at 49152+2048, and finally 
//line 30 tells kernal output routines where the screen is. 
//After run-stop you 
//need to type "poke 648,4" blindly as that isn't restored by warm start routine.
 
 // to use 57344 youll need to have poke 648, something!
 
 //POKE(0xdd00, PEEK(0xdd00) & 0xfc);
 /////30 POKE56576,PEEK(56576AND252):POKE53272,32:POKE648,200

	
	//DD00 from hexadecimal to decimal is 56576
	//$D018  vic register  53272
//e000 = 57344
//c800  51200
//the bank is in 56573
//if you set the font to 0xe000 the memptr would be 8 for the font
//so POKE(0xd018, 0x28)
//and the 16k bank with POKE(0xdd00, peek(0xdd00) & 0xfc)
    //turn back IO and Keyboard
//    printf("turning back on keyboard and io\n");
 //   POKE(1, PEEK(1) |4);
   // POKE(56334, PEEK(56334) |1);

    printf("pointing VIC 2 to new charset location\n"); 
 ////////////////   POKE(53272, (PEEK(53272) & 240) |12); // bank 12, second to last
//  printf("Charset copied, all should be good"); 
	 
}
void corral(void)
{
	 char c;
     for (c=0;c<120; c++ )
		 { 
	 POKE(49152+2048+c,c);
//	 https://www.lemon64.com/forum/viewtopic.php?t=23355
	//         POKE(1024+c,c);
		//	 POKE(55296+c,1);
	     }
}

	
	
void iota()
{
	  int i,val;
	   
	   strncpy(tmpstring, & inputstring[1], 5); //  to \0
      printf("\n\n\n\n iota of %s\n", tmpstring);
     
	  
	  val = atoi(tmpstring);
	//  printf(" got value from atoi of %d \n", val);
	  for (i=0; i<=val; i++)
	  {printf(" %i",i);}
      printf("\n");
	 
}
	
void reversemonadic()
{
	int i, j, dummy;
	struct node * foundLink;
	if (inputstring[1] == 65) {  // is an A
	     foundLink = find(65);   }   
	if (inputstring[1] == 66) {  // is a B 
	     foundLink = find(66);   } 

    if(foundLink == NULL) {
      printf("foundlink was null, element not found \n ");
	  }
	if(foundLink != NULL) {
	   
	   printf("before reversing \n ");
	   for(i=0; i < 5; i++) {   
	//      printf("in rotate loop1");
         printf("%d ", foundLink->p_array[i]);
      }
	   
	  for(i=0; i < 2; i++) {    //only rotate the first half!!!!
	      dummy = foundLink->p_array[i];
	      foundLink->p_array[i] = foundLink->p_array[4-i];  //adjust later for general case
		  foundLink->p_array[4-i] = dummy;
      
	//	printf("in rotate loop0");
      }
	//  printf("after rotating  ");
	  foundLink->p_array[5] = dummy;
	  printf("\nafter reversing \n ");
	  for(i=0; i < 5; i++) {   
	//      printf("in rotate loop1");
         printf("%d ", foundLink->p_array[i]);
      }
    //  printf("in rotate loop2");
	}
	// printf("in rotate loop3");
}

void ibeam21()
{
	//  strncpy(tmpstring, & inputstring[1], 5); //  to \0
	  printf("size of clock_t %i\n", sizeof(clock_t));
	 
}
	 //  strncpy(tmpstring, & inputstring[1], 5); //  to \0
	   
	   
	   
void ibeam22()
{
	size_t size;
    size = _heapmemavail();
	   printf("heap size unsigned int %u\n", size);
	//   printf("sizeof size_t is %i\n", sizeof(size_t));
	  // printf("sizeof sizetest unsigned long is %i\n", sizeof(sizetest));
	  // printf("sizeof sizetest int is %i\n", sizeof(sizetestint));
}
void ibeam20()
{    long int timetotal;
	int a2, a1, a0, id3, i, j, k;
	 unsigned  int retTime;
	printf("\n\n\n\n\nin ibeam 20  system time\n");
	   __asm__("LDA $A2");      // ; Real-time jiffy Clock
       __asm__("LDX $A1");      // ; Real-time jiffy Clock
       __asm__("LDY $A0");
       printf("jiffy clock initialised\n");	
	   printf("zero page jiffy A 2 A 1 A 0 = \n");
	   a2 = PEEK(162);
	   printf("%i   ", a2);
	    a1 = PEEK(161);
	   printf("%i   ", a1);
	    a0 = PEEK(160);
	   printf("%i \n", a0);
	//   int id3 = byte0 + (byte1 << 8) + (byte2 << 16);
	 //  id3 = a2 + (a1 << 8) + (a0 << 16);   
	//   printf("%i  id3 = \n", id3);
	 //  time_t t;
	//   printf("%i time", time());
    
       retTime	  = time(0) + 1;
	   printf("%u retTime \n", retTime);
	   for (j=0;j<1000;j++){
		   for (k=0;k<100;k++)
		   {}
	   }
	   	   a2 = PEEK(162);
	   printf("%i   ", a2);
	    a1 = PEEK(161);
	   printf("%i   ", a1);
	    a0 = PEEK(160);
	   printf("%i \n", a0);
	//   int id3 = byte0 + (byte1 << 8) + (byte2 << 16);
	 //  id3 = a2 + (a1 << 8) + (a0 << 16);   
	//   printf("%i  id3 = \n", id3);
	 //  time_t t;
	//   printf("%i time", time());
    
       retTime	  = time(0) + 1;
	   printf("%u retTime \n", retTime);
	   
	  return;	   
}
	
	
	
	
void roll()
{
	int i;
	i = rand();
	printf("%i", i);
	return;
}

	
void main(void) {
	int notassignment = 0;
  struct node * foundLink;
  struct node * foundLink2;
  int i, xpos, ypos;
  size_t size;
   int val;
  char c;
   
//  char inputstring[25];
 // char tmpstring[25];
  int storeindex = 0;
  int linenotdone = 1;
  char storechar = 0;
  //	CLRSCR
  xpos = 0;
  ypos = 0;

  
  LoadCustomCharset();
  CLRSCR
  clrscr();
  while (1) {
    corral();
    
    CURSORHOME
    cursor(1);
    linenotdone = 1;
    c = 1; //dummy not 0 value
    while (linenotdone) {
      while (c != 13) { //exit chargetting loop if return key hit 
        c = cgetc();

        if (c == 17) { //cursor down
          ypos++;
          if (ypos > 2) {
            ypos = 0;
          }
        }
        if (c == 145) { //cursor up
          ypos--;
          if (ypos < 0) {
            ypos = 2;
          }
        }
        if (c == 29) { //right
          xpos++;
          if (xpos > 39) {
            xpos = 0;
          }
        }
        if (c == 157) { //left
          xpos--;
          if (xpos < 0) {
            xpos = 39;
          } 
        }
        if (c == 13) { //return
          xpos = 0;
          ypos = 0;
          //store char under cursor $ce into screen memory to show it being selected
          __asm__("lda $ce");
          __asm__("sta $04fc");
          storechar = PEEK(1276); //$04fc
          POKE(52992 + storeindex, storechar); //52992 = cf00
          POKE(1400 + storeindex, storechar);
          if ((storechar >= 1) && (storechar <= 31)) //char, add 64
          {
            storechar += 64;
          } else if ((storechar >= 64) && (storechar <= 94)) //char, add 64
          {
            storechar += 32;
          } else if ((storechar >= 95) && (storechar <= 119)) //char, add 64
          {
            storechar += 64;
          }

          inputstring[storeindex] = storechar;
          /*       if (storechar == 1) {
	            inputstring[storeindex] = 'a';
	          }
	          if (storechar == 2) {
	            inputstring[storeindex] = 'b';
	          }
	  */
          if (storechar == 0) {
            linenotdone = 0;
          }
          storeindex++;
        }
        gotox(xpos);
        gotoy(ypos);
      }

      //	printf("line done");  
      //printf("store char %c", storechar);

      c = 1; //reset from 13
    }
    inputstring[storeindex] = '\0';
    storeindex = 0;
    //CLRSCR
    printf("\n\n\n\ninput string is %s\n", inputstring);
	/* turn back on for input list down
    for (i = 0; i < 25; i++) {
      printf("integer %i char %c \n", inputstring[i], inputstring[i]);
      if (inputstring[i] == 0) {
        break;
      }
    }
	*/
    //input is read, now parse it

    switch (inputstring[1]) {

    case 95: { // 1F assignment  arrow
      printf(" assignment\n");
      strncpy(tmpstring, & inputstring[2], 5); //  to \0
      printf("\n\n\n\n\n\n\n\n creating assignment array for %s\n", tmpstring);
     // insertFirst(inputstring[0], 10, tmpstring);
	  
	//use later for now just treat as indiviual entries  val = atoi(tmpstring);
	//  printf(" got value from atoi of %d \n", val);
	  
	  
	  
	  
	  
	  insertFirst(inputstring[0], 10, tmpstring);  //was HARDWIRED FOR 1 = A revisit
	  printf(" tmpstring %s ",   tmpstring);
      printList();
      notassignment = 0;
      break;  
    }
	case 43: {
		printf("add \n");
		if ((inputstring[0] == 65) && (inputstring[2] == 66))
		  {
		   printf("add a plus b\n");
	       foundLink = find(65);      	 
	       foundLink2 = find(66); 
	  
	       for(i=0; i < 5; i++) {   
               printf("(%d) ", (foundLink->p_array[i])+(foundLink2->p_array[i] ));
                }
	      
	    }
		break;
     	}
    default:
	{notassignment = 1; //printf("didnt match first switch anything\n"); 
	}     

    }

    if (notassignment == 0) {printf("not assignment == 0 \n"); }  //skip it
    else {
    switch (inputstring[0]) {


   case 63  : { //#$3F is ? roll
      printf(" ? roll\n");
	  roll();
      break; /* optional */
   }
   
   
   case 98  : { //98 is iota
      printf(" iota\n");
	  iota();
      break; /* optional */
   }
   
     
   case 108  : { //reverse 
      printf(" reverse\n");
	  reversemonadic();
      break; /* optional */
   }
   
   
   case 38  :  {
      printf(" i-beam\n");
	 // if (inputstring[1] == "32") {printf("ok\n");
	  if ((inputstring[1] == 50) && (inputstring[2] == 48) ){ibeam20();}

	  if ((inputstring[1] == 50) && (inputstring[2] == 49) ){ibeam21();}
	  if ((inputstring[1] == 50) && (inputstring[2] == 50) ){ibeam22();}
	  if ((inputstring[1] == 50) && (inputstring[2] == 51) ){printf("0\n"); }//users }
      break; /* optional */
		}


    case 36: { //empty box is clear screen
      CLRSCR

      break; /* optional */
    }
    case 37: { //divided box, change to an ibeam

      size = _heapmemavail();
      printf("heap size unsigned int %u\n", size);
     // printf("sizeof size_t is %i\n", sizeof(size_t));
    //  printf("sizeof sizetest unsigned long is %i\n", sizeof(sizetest));
    //  printf("sizeof sizetest int is %i\n", sizeof(sizetestint));
      break;
    }
    default:
      /* Optional */
	  { //
	  //printf("didnt match anything second switch\n");
	  }

    }  //end case
  
  
	}  //notassignment 
   // printList(); 
	if (inputstring[0] == 65) {  // is an A
	     foundLink = find(65);   }   
	if (inputstring[0] == 66) {  // is a B 
	     foundLink = find(66);   } 
	if(foundLink == NULL) {
      printf("foundlink was null, element not found \n ");
	}
	if(foundLink != NULL) {
     // printf("Element found \n");
   //   printf("(%d,%d) ",foundLink->key,foundLink->data);
	//  printf("sizeof %d ", sizeof(foundLink->p_array));
	   
//	  printf(" %i ", foundLink->p_array[0]);
	//  printf("%i ", foundLink->p_array[1]);
//	  printf("%i ", foundLink->p_array[2]);
	//  printf("%i ", foundLink->p_array[3]);
	  
	 // seems to work foundLink->p_array[0] = 5;
	//  printf("%d", foundLink->p_array[0]);
	printf("\n");
	  for(i=0; i < 5; i++) {   
      //turned off for demo   printf("(%d) ", foundLink->p_array[i]);
      }
      
	}
	
//	printf("in do while");
	
     
  }  //end of do while 1

}  //end of main