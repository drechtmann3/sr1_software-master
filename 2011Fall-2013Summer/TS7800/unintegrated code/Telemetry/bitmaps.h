/* prevents multiple, redundant includes */
/* make sure to use a symbol that is fairly sure to be unique */
#ifndef BITMAPS_H
#define BITMAPS_H

static const char speedNum[450] =  //number | page offset
{0x00, 0x00,0xF8, 0xFC, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x00, 0x00, //0|1
0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, //0|2
0x00, 0x00, 0x1F, 0x3F, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x70, 0x3F, 0x1F, 0x00, 0x00, //0|3
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1C, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //1|1
0x00, 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //1|2
0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x60, 0x7F, 0x7F, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, //1|3
0x00, 0x00, 0x38, 0x3C, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x00, 0x00, //2|1
0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0x70, 0x38, 0x1C, 0x0E, 0x07, 0x03, 0x00, 0x00, //2|2
0x00, 0x00, 0x7E, 0x7F, 0x63, 0x61, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, //2|3
0x00, 0x00, 0x38, 0x3C, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x00, 0x00, //3|1
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x1E, 0x3F, 0xF3, 0xE1, 0x00, 0x00, //3|2
0x00, 0x00, 0x1C, 0x3C, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x70, 0x3F, 0x1F, 0x00, 0x00, //3|3
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x70, 0x1C, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, //4|1
0x00, 0x00, 0xC0, 0xF0, 0x9C, 0x87, 0x81, 0x80, 0x80, 0xFF, 0xFF, 0x80, 0x80, 0x00, 0x00, //4|2	 
0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7F, 0x7F, 0x01, 0x01, 0x00, 0x00, //4|3
0x00, 0x00, 0xFE, 0xFE, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, //5|1
0x00, 0x00, 0x0F, 0x0F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1C, 0xF8, 0xF0, 0x00, 0x00, //5|2
0x00, 0x00, 0x1C, 0x3C, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x70, 0x3F, 0x1F, 0x00, 0x00, //5|3
0x00, 0x00, 0xC0, 0xE0, 0x70, 0x38, 0x1C, 0x0E, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, //6|1
0x00, 0x00, 0xFF, 0xFF, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1C, 0xF8, 0xF0, 0x00, 0x00, //6|2
0x00, 0x00, 0x1F, 0x3F, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x70, 0x3F, 0x1F, 0x00, 0x00, //6|3
0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x86, 0xE6, 0xFE, 0x7E, 0x00, 0x00, //7|1
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF8, 0x7E, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, //7|2
0x00, 0x00, 0x60, 0x78, 0x7E, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //7|3
0x00, 0x00, 0xF8, 0xFC, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x00, 0x00, //8|1
0x00, 0x00, 0xE1, 0xF3, 0x3F, 0x1E, 0x0C, 0x0C, 0x0C, 0x1E, 0x3F, 0xF3, 0xE1, 0x00, 0x00, //8|2
0x00, 0x00, 0x1F, 0x3F, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x70, 0x3F, 0x1F, 0x00, 0x00, //8|3
0x00, 0x00, 0xF8, 0xFC, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x00, 0x00, //9|1
0x00, 0x00, 0x07, 0x0F, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0xFF, 0xFF, 0x00, 0x00, //9|2
0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x60, 0x70, 0x38, 0x1C, 0x0E, 0x07, 0x03, 0x00, 0x00  //9|3
};

static const char leftArrow[12] = {0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E};

static const char rightArrow[12] = {0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x7F, 0x3E, 0x1C, 0x08};

static const char num[50] =  //numbers
{0x3E, 0x41, 0x41, 0x41, 0x3E, //0
0x44, 0x42, 0x7F, 0x40, 0x40, //1
0x42, 0x61, 0x51, 0x49, 0x46, //2
0x22, 0x41, 0x49, 0x49, 0x36, //3
0x18, 0x14, 0x12, 0x7F, 0x10, //4
0x27, 0x45, 0x45, 0x45, 0x39, //5
0x3C, 0x4A, 0x49, 0x49, 0x30, //6
0x01, 0x61, 0x11, 0x09, 0x07, //7
0x36, 0x49, 0x49, 0x49, 0x36, //8
0x06, 0x49, 0x49, 0x29, 0x1E  //9
};

static const char alpha[130] = { //letters
0x7C,0x12,0x11,0x12,0x7C,//A
0x7F,0x49,0x49,0x4E,0x70,//B
0x1C,0x22,0x41,0x41,0x41,//C
0x7F,0x41,0x41,0x42,0x3C,//D
0x7F,0x49,0x49,0x49,0x41,//E
0x7F,0x09,0x09,0x09,0x01,//F
0x7F,0x41,0x49,0x49,0x78,//G
0x7F,0x08,0x08,0x08,0x7F,//H
0x41,0x41,0x7F,0x41,0x41,//I
0x60,0x40,0x40,0x40,0x3F,//J
0x7F,0x08,0x04,0x0A,0x71,//K
0x7F,0x40,0x40,0x40,0x40,//L
0x7F,0x01,0x0E,0x01,0x7F,//M
0x7F,0x06,0x08,0x30,0x7F,//N
0x7F,0x41,0x41,0x41,0x7F,//O
0x7F,0x09,0x09,0x09,0x0F,//P
0x7F,0x41,0x51,0x21,0x5F,//Q
0x7F,0x09,0x09,0x19,0x6F,//R
0x46,0x49,0x49,0x49,0x31,//S
0x01,0x01,0x7F,0x01,0x01,//T
0x3F,0x40,0x40,0x40,0x3F,//U
0x0F,0x30,0x40,0x30,0x0F,//V
0x7F,0x40,0x30,0x40,0x7F,//W
0x63,0x14,0x08,0x14,0x63,//X
0x07,0x08,0x70,0x08,0x07,//Y
0x61,0x51,0x49,0x45,0x43//Z
};

static const char colon[5] = {0x00, 0x36, 0x36, 0x00, 0x00};
					
static const char bullet[5] = {0x00, 0x3C, 0x3C, 0x3C, 0x00};	

static const char line = 0x7F;

static const char emptyBar = 0x41;

static const char fullBar = 0x7F;

static const char emptyLine = 0x00;

static const char underline = 0x80;

static const char pageLine = 0xFF;

static const char pageEmptyBar = 0x81;

#endif