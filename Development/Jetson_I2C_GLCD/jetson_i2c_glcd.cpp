#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <iostream>
#include <fstream>

#include <math.h>

#define BLACK 0
#define WHITE 1
#define INVERSE 2

#define SSD1306_128_64

// the memory buffer for the LCD
#define SSD1306_LCDHEIGHT 64
#define SSD1306_LCDWIDTH  128

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

void ssd1306_command(uint8_t c, int FileDescriptor);

static uint8_t buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0x80, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0xFF,
#if (SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH > 96*16)
0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
0x80, 0xFF, 0xFF, 0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x8C, 0x8E, 0x84, 0x00, 0x00, 0x80, 0xF8,
0xF8, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80,
0x00, 0xE0, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xC7, 0x01, 0x01,
0x01, 0x01, 0x83, 0xFF, 0xFF, 0x00, 0x00, 0x7C, 0xFE, 0xC7, 0x01, 0x01, 0x01, 0x01, 0x83, 0xFF,
0xFF, 0xFF, 0x00, 0x38, 0xFE, 0xC7, 0x83, 0x01, 0x01, 0x01, 0x83, 0xC7, 0xFF, 0xFF, 0x00, 0x00,
0x01, 0xFF, 0xFF, 0x01, 0x01, 0x00, 0xFF, 0xFF, 0x07, 0x01, 0x01, 0x01, 0x00, 0x00, 0x7F, 0xFF,
0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0xFF,
0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x03, 0x0F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC7, 0xC7, 0x8F,
0x8F, 0x9F, 0xBF, 0xFF, 0xFF, 0xC3, 0xC0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC,
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x01, 0x03, 0x03, 0x03,
0x03, 0x03, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01,
0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00,
0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x03,
0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
#if (SSD1306_LCDHEIGHT == 64)
0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x0F,
0x87, 0xC7, 0xF7, 0xFF, 0xFF, 0x1F, 0x1F, 0x3D, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0x7C, 0x7D, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x00, 0x30, 0x30, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xC0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xC0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x1F,
0x0F, 0x07, 0x1F, 0x7F, 0xFF, 0xFF, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8, 0xE0,
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00,
0x00, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x00, 0x00, 0xF0, 0xF8, 0x1C, 0x0E,
0x06, 0x06, 0x06, 0x0C, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFC,
0xFE, 0xFC, 0x00, 0x18, 0x3C, 0x7E, 0x66, 0xE6, 0xCE, 0x84, 0x00, 0x00, 0x06, 0xFF, 0xFF, 0x06,
0x06, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x06, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0xC0, 0xF8,
0xFC, 0x4E, 0x46, 0x46, 0x46, 0x4E, 0x7C, 0x78, 0x40, 0x18, 0x3C, 0x76, 0xE6, 0xCE, 0xCC, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00,
0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x03, 0x07, 0x0E, 0x0C,
0x18, 0x18, 0x0C, 0x06, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x01, 0x0F, 0x0E, 0x0C, 0x18, 0x0C, 0x0F,
0x07, 0x01, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00,
0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x07,
0x07, 0x0C, 0x0C, 0x18, 0x1C, 0x0C, 0x06, 0x06, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#endif
#endif
};



#define ssd1306_swap(a, b) { int16_t t = a; a = b; b = t; }
//----------------
#define _width 128
#define _height 64
#define _cp437 false
#define gfxFont NULL
#define wrap true
#define rotation 0

#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }

#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define PROGMEM

static const unsigned char font[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
	0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
	0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
	0x18, 0x3C, 0x7E, 0x3C, 0x18,
	0x1C, 0x57, 0x7D, 0x57, 0x1C,
	0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
	0x00, 0x18, 0x3C, 0x18, 0x00,
	0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
	0x00, 0x18, 0x24, 0x18, 0x00,
	0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
	0x30, 0x48, 0x3A, 0x06, 0x0E,
	0x26, 0x29, 0x79, 0x29, 0x26,
	0x40, 0x7F, 0x05, 0x05, 0x07,
	0x40, 0x7F, 0x05, 0x25, 0x3F,
	0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
	0x7F, 0x3E, 0x1C, 0x1C, 0x08,
	0x08, 0x1C, 0x1C, 0x3E, 0x7F,
	0x14, 0x22, 0x7F, 0x22, 0x14,
	0x5F, 0x5F, 0x00, 0x5F, 0x5F,
	0x06, 0x09, 0x7F, 0x01, 0x7F,
	0x00, 0x66, 0x89, 0x95, 0x6A,
	0x60, 0x60, 0x60, 0x60, 0x60,
	0x94, 0xA2, 0xFF, 0xA2, 0x94,
	0x08, 0x04, 0x7E, 0x04, 0x08,
	0x10, 0x20, 0x7E, 0x20, 0x10,
	0x08, 0x08, 0x2A, 0x1C, 0x08,
	0x08, 0x1C, 0x2A, 0x08, 0x08,
	0x1E, 0x10, 0x10, 0x10, 0x10,
	0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
	0x30, 0x38, 0x3E, 0x38, 0x30,
	0x06, 0x0E, 0x3E, 0x0E, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x5F, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x07, 0x00,
	0x14, 0x7F, 0x14, 0x7F, 0x14,
	0x24, 0x2A, 0x7F, 0x2A, 0x12,
	0x23, 0x13, 0x08, 0x64, 0x62,
	0x36, 0x49, 0x56, 0x20, 0x50,
	0x00, 0x08, 0x07, 0x03, 0x00,
	0x00, 0x1C, 0x22, 0x41, 0x00,
	0x00, 0x41, 0x22, 0x1C, 0x00,
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
	0x08, 0x08, 0x3E, 0x08, 0x08,
	0x00, 0x80, 0x70, 0x30, 0x00,
	0x08, 0x08, 0x08, 0x08, 0x08,
	0x00, 0x00, 0x60, 0x60, 0x00,
	0x20, 0x10, 0x08, 0x04, 0x02,
	0x3E, 0x51, 0x49, 0x45, 0x3E,
	0x00, 0x42, 0x7F, 0x40, 0x00,
	0x72, 0x49, 0x49, 0x49, 0x46,
	0x21, 0x41, 0x49, 0x4D, 0x33,
	0x18, 0x14, 0x12, 0x7F, 0x10,
	0x27, 0x45, 0x45, 0x45, 0x39,
	0x3C, 0x4A, 0x49, 0x49, 0x31,
	0x41, 0x21, 0x11, 0x09, 0x07,
	0x36, 0x49, 0x49, 0x49, 0x36,
	0x46, 0x49, 0x49, 0x29, 0x1E,
	0x00, 0x00, 0x14, 0x00, 0x00,
	0x00, 0x40, 0x34, 0x00, 0x00,
	0x00, 0x08, 0x14, 0x22, 0x41,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x00, 0x41, 0x22, 0x14, 0x08,
	0x02, 0x01, 0x59, 0x09, 0x06,
	0x3E, 0x41, 0x5D, 0x59, 0x4E,
	0x7C, 0x12, 0x11, 0x12, 0x7C,
	0x7F, 0x49, 0x49, 0x49, 0x36,
	0x3E, 0x41, 0x41, 0x41, 0x22,
	0x7F, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x49, 0x49, 0x49, 0x41,
	0x7F, 0x09, 0x09, 0x09, 0x01,
	0x3E, 0x41, 0x41, 0x51, 0x73,
	0x7F, 0x08, 0x08, 0x08, 0x7F,
	0x00, 0x41, 0x7F, 0x41, 0x00,
	0x20, 0x40, 0x41, 0x3F, 0x01,
	0x7F, 0x08, 0x14, 0x22, 0x41,
	0x7F, 0x40, 0x40, 0x40, 0x40,
	0x7F, 0x02, 0x1C, 0x02, 0x7F,
	0x7F, 0x04, 0x08, 0x10, 0x7F,
	0x3E, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x09, 0x09, 0x09, 0x06,
	0x3E, 0x41, 0x51, 0x21, 0x5E,
	0x7F, 0x09, 0x19, 0x29, 0x46,
	0x26, 0x49, 0x49, 0x49, 0x32,
	0x03, 0x01, 0x7F, 0x01, 0x03,
	0x3F, 0x40, 0x40, 0x40, 0x3F,
	0x1F, 0x20, 0x40, 0x20, 0x1F,
	0x3F, 0x40, 0x38, 0x40, 0x3F,
	0x63, 0x14, 0x08, 0x14, 0x63,
	0x03, 0x04, 0x78, 0x04, 0x03,
	0x61, 0x59, 0x49, 0x4D, 0x43,
	0x00, 0x7F, 0x41, 0x41, 0x41,
	0x02, 0x04, 0x08, 0x10, 0x20,
	0x00, 0x41, 0x41, 0x41, 0x7F,
	0x04, 0x02, 0x01, 0x02, 0x04,
	0x40, 0x40, 0x40, 0x40, 0x40,
	0x00, 0x03, 0x07, 0x08, 0x00,
	0x20, 0x54, 0x54, 0x78, 0x40,
	0x7F, 0x28, 0x44, 0x44, 0x38,
	0x38, 0x44, 0x44, 0x44, 0x28,
	0x38, 0x44, 0x44, 0x28, 0x7F,
	0x38, 0x54, 0x54, 0x54, 0x18,
	0x00, 0x08, 0x7E, 0x09, 0x02,
	0x18, 0xA4, 0xA4, 0x9C, 0x78,
	0x7F, 0x08, 0x04, 0x04, 0x78,
	0x00, 0x44, 0x7D, 0x40, 0x00,
	0x20, 0x40, 0x40, 0x3D, 0x00,
	0x7F, 0x10, 0x28, 0x44, 0x00,
	0x00, 0x41, 0x7F, 0x40, 0x00,
	0x7C, 0x04, 0x78, 0x04, 0x78,
	0x7C, 0x08, 0x04, 0x04, 0x78,
	0x38, 0x44, 0x44, 0x44, 0x38,
	0xFC, 0x18, 0x24, 0x24, 0x18,
	0x18, 0x24, 0x24, 0x18, 0xFC,
	0x7C, 0x08, 0x04, 0x04, 0x08,
	0x48, 0x54, 0x54, 0x54, 0x24,
	0x04, 0x04, 0x3F, 0x44, 0x24,
	0x3C, 0x40, 0x40, 0x20, 0x7C,
	0x1C, 0x20, 0x40, 0x20, 0x1C,
	0x3C, 0x40, 0x30, 0x40, 0x3C,
	0x44, 0x28, 0x10, 0x28, 0x44,
	0x4C, 0x90, 0x90, 0x90, 0x7C,
	0x44, 0x64, 0x54, 0x4C, 0x44,
	0x00, 0x08, 0x36, 0x41, 0x00,
	0x00, 0x00, 0x77, 0x00, 0x00,
	0x00, 0x41, 0x36, 0x08, 0x00,
	0x02, 0x01, 0x02, 0x04, 0x02,
	0x3C, 0x26, 0x23, 0x26, 0x3C,
	0x1E, 0xA1, 0xA1, 0x61, 0x12,
	0x3A, 0x40, 0x40, 0x20, 0x7A,
	0x38, 0x54, 0x54, 0x55, 0x59,
	0x21, 0x55, 0x55, 0x79, 0x41,
	0x22, 0x54, 0x54, 0x78, 0x42, // a-umlaut
	0x21, 0x55, 0x54, 0x78, 0x40,
	0x20, 0x54, 0x55, 0x79, 0x40,
	0x0C, 0x1E, 0x52, 0x72, 0x12,
	0x39, 0x55, 0x55, 0x55, 0x59,
	0x39, 0x54, 0x54, 0x54, 0x59,
	0x39, 0x55, 0x54, 0x54, 0x58,
	0x00, 0x00, 0x45, 0x7C, 0x41,
	0x00, 0x02, 0x45, 0x7D, 0x42,
	0x00, 0x01, 0x45, 0x7C, 0x40,
	0x7D, 0x12, 0x11, 0x12, 0x7D, // A-umlaut
	0xF0, 0x28, 0x25, 0x28, 0xF0,
	0x7C, 0x54, 0x55, 0x45, 0x00,
	0x20, 0x54, 0x54, 0x7C, 0x54,
	0x7C, 0x0A, 0x09, 0x7F, 0x49,
	0x32, 0x49, 0x49, 0x49, 0x32,
	0x3A, 0x44, 0x44, 0x44, 0x3A, // o-umlaut
	0x32, 0x4A, 0x48, 0x48, 0x30,
	0x3A, 0x41, 0x41, 0x21, 0x7A,
	0x3A, 0x42, 0x40, 0x20, 0x78,
	0x00, 0x9D, 0xA0, 0xA0, 0x7D,
	0x3D, 0x42, 0x42, 0x42, 0x3D, // O-umlaut
	0x3D, 0x40, 0x40, 0x40, 0x3D,
	0x3C, 0x24, 0xFF, 0x24, 0x24,
	0x48, 0x7E, 0x49, 0x43, 0x66,
	0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
	0xFF, 0x09, 0x29, 0xF6, 0x20,
	0xC0, 0x88, 0x7E, 0x09, 0x03,
	0x20, 0x54, 0x54, 0x79, 0x41,
	0x00, 0x00, 0x44, 0x7D, 0x41,
	0x30, 0x48, 0x48, 0x4A, 0x32,
	0x38, 0x40, 0x40, 0x22, 0x7A,
	0x00, 0x7A, 0x0A, 0x0A, 0x72,
	0x7D, 0x0D, 0x19, 0x31, 0x7D,
	0x26, 0x29, 0x29, 0x2F, 0x28,
	0x26, 0x29, 0x29, 0x29, 0x26,
	0x30, 0x48, 0x4D, 0x40, 0x20,
	0x38, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x38,
	0x2F, 0x10, 0xC8, 0xAC, 0xBA,
	0x2F, 0x10, 0x28, 0x34, 0xFA,
	0x00, 0x00, 0x7B, 0x00, 0x00,
	0x08, 0x14, 0x2A, 0x14, 0x22,
	0x22, 0x14, 0x2A, 0x14, 0x08,
	0x55, 0x00, 0x55, 0x00, 0x55, // #176 (25% block) missing in old code
	0xAA, 0x55, 0xAA, 0x55, 0xAA, // 50% block
	0xFF, 0x55, 0xFF, 0x55, 0xFF, // 75% block
	0x00, 0x00, 0x00, 0xFF, 0x00,
	0x10, 0x10, 0x10, 0xFF, 0x00,
	0x14, 0x14, 0x14, 0xFF, 0x00,
	0x10, 0x10, 0xFF, 0x00, 0xFF,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x14, 0x14, 0x14, 0xFC, 0x00,
	0x14, 0x14, 0xF7, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x14, 0x14, 0xF4, 0x04, 0xFC,
	0x14, 0x14, 0x17, 0x10, 0x1F,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0x1F, 0x00,
	0x10, 0x10, 0x10, 0xF0, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0xF0, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0xFF, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x14,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x1F, 0x10, 0x17,
	0x00, 0x00, 0xFC, 0x04, 0xF4,
	0x14, 0x14, 0x17, 0x10, 0x17,
	0x14, 0x14, 0xF4, 0x04, 0xF4,
	0x00, 0x00, 0xFF, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0xF7, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x17, 0x14,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0xF4, 0x14,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x00, 0x00, 0x1F, 0x10, 0x1F,
	0x00, 0x00, 0x00, 0x1F, 0x14,
	0x00, 0x00, 0x00, 0xFC, 0x14,
	0x00, 0x00, 0xF0, 0x10, 0xF0,
	0x10, 0x10, 0xFF, 0x10, 0xFF,
	0x14, 0x14, 0x14, 0xFF, 0x14,
	0x10, 0x10, 0x10, 0x1F, 0x00,
	0x00, 0x00, 0x00, 0xF0, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x38, 0x44, 0x44, 0x38, 0x44,
	0xFC, 0x4A, 0x4A, 0x4A, 0x34, // sharp-s or beta
	0x7E, 0x02, 0x02, 0x06, 0x06,
	0x02, 0x7E, 0x02, 0x7E, 0x02,
	0x63, 0x55, 0x49, 0x41, 0x63,
	0x38, 0x44, 0x44, 0x3C, 0x04,
	0x40, 0x7E, 0x20, 0x1E, 0x20,
	0x06, 0x02, 0x7E, 0x02, 0x02,
	0x99, 0xA5, 0xE7, 0xA5, 0x99,
	0x1C, 0x2A, 0x49, 0x2A, 0x1C,
	0x4C, 0x72, 0x01, 0x72, 0x4C,
	0x30, 0x4A, 0x4D, 0x4D, 0x30,
	0x30, 0x48, 0x78, 0x48, 0x30,
	0xBC, 0x62, 0x5A, 0x46, 0x3D,
	0x3E, 0x49, 0x49, 0x49, 0x00,
	0x7E, 0x01, 0x01, 0x01, 0x7E,
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
	0x44, 0x44, 0x5F, 0x44, 0x44,
	0x40, 0x51, 0x4A, 0x44, 0x40,
	0x40, 0x44, 0x4A, 0x51, 0x40,
	0x00, 0x00, 0xFF, 0x01, 0x03,
	0xE0, 0x80, 0xFF, 0x00, 0x00,
	0x08, 0x08, 0x6B, 0x6B, 0x08,
	0x36, 0x12, 0x36, 0x24, 0x36,
	0x06, 0x0F, 0x09, 0x0F, 0x06,
	0x00, 0x00, 0x18, 0x18, 0x00,
	0x00, 0x00, 0x10, 0x10, 0x00,
	0x30, 0x40, 0xFF, 0x01, 0x01,
	0x00, 0x1F, 0x01, 0x01, 0x1E,
	0x00, 0x19, 0x1D, 0x17, 0x12,
	0x00, 0x3C, 0x3C, 0x3C, 0x3C,
	0x00, 0x00, 0x00, 0x00, 0x00  // #255 NBSP
};



int cursor_y = 0;
int cursor_x = 0;

int textsize = 0;
uint16_t textcolor = 0xFFFF;
uint16_t textbgcolor = 0xFFFF;
char ip[14] = "138.51.120.89";


void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void writePixel(int16_t x, int16_t y, uint16_t color);
void write(uint8_t c);
void setCursor(int16_t x, int16_t y);
void setTextColor(uint16_t c);
void setTextSize(uint8_t s);

void startWrite();
void endWrite();

void print_ip_address(char ip[]);


void drawPixel(int16_t x, int16_t y, uint16_t color){
	if ((x<0) ||(x>=128)|| (y<0) || (y>=64)){
		return;	
	}
	switch(color){
		case WHITE: buffer[x+(y/8) * SSD1306_LCDWIDTH] |= (1<<(y&7));break;
		case BLACK: buffer[x+(y/8) * SSD1306_LCDWIDTH] &= ~(1<<(y&7));break;
		case INVERSE: buffer[x+(y/8) * SSD1306_LCDWIDTH] ^= (1<<(y&7));break;
	}
}


int open(){
	printf("enter get_filedescriptor function");
	char fileNameBuffer[32];
	sprintf(fileNameBuffer, "/dev/i2c-0");
	int FileDescriptor = open(fileNameBuffer, O_RDWR);   //value:2
	printf("FileDesctriptor: %d\n", FileDescriptor);
	if (FileDescriptor <0){
		return -1;
	}
	int opened = ioctl(FileDescriptor,I2C_SLAVE, 0x3c);
	if (opened <0){
		return -1;
	}
	printf("opened FileDescripriptor: %d\n", opened);
	return FileDescriptor;
}

int i2cwrite(int writeValue, int FileDescriptor){
	int toReturn = i2c_smbus_write_byte(FileDescriptor,writeValue);
	if (toReturn<0){
		return -1;
	}
	return toReturn;
}

//EDIT
int i2cwrite_data(int FileDescriptor, uint8_t command, uint8_t value){
	int toReturn = i2c_smbus_write_byte_data(FileDescriptor, command, value);
	if (toReturn<0){
		return -1;
	}
	return toReturn;
}

int i2cwrite_block_data(int FileDescriptor, uint8_t command, uint8_t length, uint8_t *values){
	int toReturn = i2c_smbus_write_block_data(FileDescriptor, command, length, values);
	if (toReturn<0){
		return -1;	
	}
	return toReturn;
}

int writeDisplay(int FileDescriptor){
	ssd1306_command(SSD1306_COLUMNADDR,FileDescriptor);
	ssd1306_command(0, FileDescriptor); //column start address
	ssd1306_command(SSD1306_LCDWIDTH-1, FileDescriptor); //column end address
	
	ssd1306_command(SSD1306_PAGEADDR,FileDescriptor);
	ssd1306_command(0,FileDescriptor);
	ssd1306_command(7,FileDescriptor); //lcdheight == 32
	
	
	
	//printf("enter write Display function\n");
	for (uint16_t i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++) {
		uint8_t command = 0x40;
		//i2cwrite(0x40, FileDescriptor);//WIRE_WRITE(0x40);
		for (uint8_t x=0; x<16; x++) {
        		i2cwrite_data(FileDescriptor, command, buffer[i]); //WIRE_WRITE(buffer[i]);
        		i++;
      		}
      		i--;	
	}
	
	/*
	printf("enter write display function");
	for (uint16_t i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++) {
		uint8_t command = 0x40;
		uint8_t value[16] = {};
		for (int x=0; x<16; x++){
			value[x] = buffer[i];
			i++;		
		}
		i--;	
		i2cwrite_block_data(FileDescriptor, command, 15, value);
	}
	*/	
	printf("done writing display");
	return 1;

}

void clear(void){
	memset(buffer, 0, (SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8));

	//for (uint8_t i=0; i< sizeof(buffer); i++) {
    //	buffer[i] = 0;
  	//}
}

void ssd1306_command(uint8_t c, int FileDescriptor){
	uint8_t control = 0x00;
	//i2cwrite(control, FileDescriptor);
	//i2cwrite(c, FileDescriptor);
	i2cwrite_data(FileDescriptor, control, c);
}



void begin(int FileDescriptor){
  ssd1306_command(SSD1306_DISPLAYOFF,FileDescriptor);                    // 0xAE
  ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV, FileDescriptor);            // 0xD5
  ssd1306_command(0x80, FileDescriptor);                                  // the suggested ratio 0x80

  ssd1306_command(SSD1306_SETMULTIPLEX, FileDescriptor);                  // 0xA8
  ssd1306_command(SSD1306_LCDHEIGHT - 1, FileDescriptor);

  ssd1306_command(SSD1306_SETDISPLAYOFFSET, FileDescriptor);              // 0xD3
  ssd1306_command(0x0, FileDescriptor);                                   // no offset
  ssd1306_command(SSD1306_SETSTARTLINE | 0x0, FileDescriptor);            // line #0
  ssd1306_command(SSD1306_CHARGEPUMP, FileDescriptor);                    // 0x8D

  ssd1306_command(0x14, FileDescriptor); //not external vcc
  ssd1306_command(SSD1306_MEMORYMODE, FileDescriptor);                    // 0x20
  ssd1306_command(0x00, FileDescriptor);                                  // 0x0 act like ks0108
  ssd1306_command(SSD1306_SEGREMAP | 0x1, FileDescriptor);
  ssd1306_command(SSD1306_COMSCANDEC, FileDescriptor);
  
  
  
//ssd1306_128_32
//  ssd1306_command(SSD1306_SETCOMPINS,FileDescriptor);                    // 0xDA
//  ssd1306_command(0x02,FileDescriptor);
//  ssd1306_command(SSD1306_SETCONTRAST, FileDescriptor);                   // 0x81
//  ssd1306_command(0x8F, FileDescriptor);
/////

//ssd1306_128_64
  ssd1306_command(SSD1306_SETCOMPINS,FileDescriptor);                    // 0xDA
  ssd1306_command(0x12,FileDescriptor);
  ssd1306_command(SSD1306_SETCONTRAST, FileDescriptor);                   // 0x81
  ssd1306_command(0x9F, FileDescriptor);
//
  ssd1306_command(SSD1306_SETPRECHARGE, FileDescriptor);                  // 0xd9

  ssd1306_command(0xF1, FileDescriptor);
  ssd1306_command(SSD1306_SETVCOMDETECT, FileDescriptor);                 // 0xDB
  ssd1306_command(0x40, FileDescriptor);
  ssd1306_command(SSD1306_DISPLAYALLON_RESUME, FileDescriptor);           // 0xA4
  ssd1306_command(SSD1306_NORMALDISPLAY, FileDescriptor);                 // 0xA6

  ssd1306_command(SSD1306_DEACTIVATE_SCROLL, FileDescriptor);

  ssd1306_command(SSD1306_DISPLAYON, FileDescriptor);//--turn on oled panel
  printf("done begin sequence");
}


 void close_device(int FileDescriptor){
	close(FileDescriptor);
 }

 //-----------------------------------------
 void setTextSize(uint8_t s){
 	textsize = (s>0) ? s:1;
 }
 void setTextColor(uint16_t c){
 	textcolor = textbgcolor = c;
 }
 void setCursor(int16_t x, int16_t y){
 	cursor_x = x;
 	cursor_y = y;
 }


void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size){
	if(!gfxFont) { // 'Classic' built-in font
        if((x >= _width)            || // Clip right
           (y >= _height)           || // Clip bottom
           ((x + 6 * size - 1) < 0) || // Clip left
           ((y + 8 * size - 1) < 0))   // Clip top
            return;
        if(!_cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior
        startWrite();
        for(int8_t i=0; i<5; i++ ) { // Char bitmap = 5 columns
            uint8_t line = pgm_read_byte(&font[c * 5 + i]);
            for(int8_t j=0; j<8; j++, line >>= 1) {
                if(line & 1) {
                    if(size == 1)
                        writePixel(x+i, y+j, color);
                    else
                        writeFillRect(x+i*size, y+j*size, size, size, color);
                } else if(bg != color) {
                    if(size == 1)
                        writePixel(x+i, y+j, bg);
                    else
                        writeFillRect(x+i*size, y+j*size, size, size, bg);
                }
            }
        }
        if(bg != color) { // If opaque, draw vertical line for last column
            if(size == 1) writeFastVLine(x+5, y, 8, bg);
            else          writeFillRect(x+5*size, y, size, 8*size, bg);
        }
        endWrite();
    } 
}

 void write(uint8_t c){
	if (!gfxFont){
		if (c == '\n'){
			cursor_x = 0;
			cursor_y += textsize * 8;
		}
		else if (c!= '\r'){
			if (wrap && ((cursor_x + textsize * 6) > _width)){ //off right?
				cursor_x = 0;
				cursor_y += textsize*8;
			}
			drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
			cursor_x += textsize * 6; 
		}
	}
	return;
}


void writePixel(int16_t x, int16_t y, uint16_t color){
	if (buffer){
		if((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return;
	}
	switch(color){
		case WHITE: buffer[x + (y/8)*SSD1306_LCDWIDTH] |= (1<<(y&7)); break;
		case BLACK: buffer[x + (y/8)*SSD1306_LCDWIDTH] &= ~(1<<(y&7)); break;
		case INVERSE: buffer[x + (y/8)*SSD1306_LCDWIDTH] ^= (1<<(y&7)); break;
	}
	//uint8_t *ptr = &buffer[x/8 + y*(_width/8)];	
	//uint8_t   *ptr  = &buffer[(x / 8) + y * ((_width + 7) / 8)];
   	// if(color) *ptr |=   0x80 >> (x & 7);
    	//else      *ptr &= ~(0x80 >> (x & 7));
}


void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
	startWrite();
    for (int16_t i=x; i<x+w; i++) {
        writeFastVLine(i, y, h, color);
    }
    endWrite();
}

void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color){
	startWrite();
    writeLine(x, y, x, y+h-1, color);
    endWrite();
}

void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color){
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t(x0, x1);
        _swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            writePixel(y0, x0, color);
        } else {
            writePixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}


void startWrite(){
}

void endWrite(){
}

void print_ip_address(char ip_address[]){
	for (int i= 0; i<14; i++){
		write(ip_address[i]);
	}
}
 

int main(){
	int FileDescriptor = open();
	begin(FileDescriptor);

	clear();
	setTextSize(2);
	setTextColor(WHITE);
	setCursor(0,0);

	print_ip_address(ip);
	writeDisplay(FileDescriptor);
	close(FileDescriptor);
	
	return 0;
}