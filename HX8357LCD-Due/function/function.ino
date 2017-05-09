#include <TFT_HX8357_Due.h> 
#include "Free_Fonts.h"
TFT_HX8357_Due tft = TFT_HX8357_Due(); 

//function
#if 0
//会用的
drawPixel(x, y, color)
init(void)
begin(void) 跟init一样，但是我更喜欢begin，与LiquidCrystal保持函数复用
fillScreen(uint16_t color)
    drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
垂直 drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
水平 drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
    drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),
    fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),
    drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color),
    fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color),
setRotation(uint8_t r),
invertDisplay(boolean i) 反色
 drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
drawEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint16_t color),
fillEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint16_t color),
drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color),
fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color),

//不会的
drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t font)
setWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
    pushColor(uint16_t color),
    pushColor(uint16_t color, uint16_t len),
    
    pushColors(uint16_t *data, uint8_t  len),
    pushColors(uint8_t  *data, uint16_t len),
    pushColor16(uint16_t *data, uint16_t len),
drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color),
fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color),  
drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color)
#endif

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
