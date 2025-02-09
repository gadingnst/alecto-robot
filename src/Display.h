#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>

/**
 * VDD/VCC -> 5V -> orange wire
 * GND -> GND -> yellow wire
 */
#define OLED_SDA 8 // blue wire
#define OLED_SCL 9 // green wire

class Display {
public:
  Display();
  void setup();
  void idle();
  void drawFaceOpen(int offsetEyeX);
  void drawFaceClosed(int offsetEyeX);
  void drawFaceSleeping();
  void sendBuffer();
  void clearBuffer();
  void drawMouthOpen();
  void drawMouthClosed();
  
private:
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
};

#endif // DISPLAY_H
