#include "Display.h"
#include <Arduino.h> // Include for random function

#define OLED_SDA 8
#define OLED_SCL 9

Display::Display() : u8g2(U8G2_R0, OLED_SCL, OLED_SDA) {}

void Display::setup() {
  u8g2.setBusClock(100000);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  // randomSeed(esp_random());
  Serial.println("Display initialized");
}

void Display::clearBuffer() {
  u8g2.clearBuffer();
}

void Display::sendBuffer() {
  u8g2.sendBuffer();
}

void Display::idle() {
  int randomAction = random(0, 3);
  switch (randomAction) {
    case 0:
      drawFaceOpen(0); // Look center
      delay(2000);
      if (random(0, 2) == 0) { // 50% chance to blink
        drawFaceClosed(0);
        delay(300);
        drawFaceOpen(0);
        delay(1500);
        drawFaceClosed(0);
        delay(200);
        drawFaceOpen(0);
      }
      delay(2000);
      break;
    case 1:
      drawFaceOpen(-12); // Look left
      if (random(0, 2) == 0) { // 50% chance to blink
        delay(500);
        drawFaceClosed(-12);
        delay(300);
        drawFaceOpen(-12);
      }
      delay(500);
      break;
    case 2:
      drawFaceOpen(12); // Look right
      if (random(0, 2) == 0) { // 50% chance to blink
        delay(500);
        drawFaceClosed(12);
        delay(300);
        drawFaceOpen(12);
      }
      delay(500);
      break;
  }
}

void Display::drawFaceOpen(int offsetX) {
  clearBuffer();
  u8g2.drawRBox(25 + offsetX, 15, 30, 30, 5);
  u8g2.drawRBox(75 + offsetX, 15, 30, 30, 5);
  drawMouthClosed();
  sendBuffer();
}

void Display::drawFaceClosed(int offsetX) {
  clearBuffer();
  u8g2.drawLine(25 + offsetX, 30, 55 + offsetX, 30);
  u8g2.drawLine(75 + offsetX, 30, 105 + offsetX, 30);
  drawMouthClosed();
  sendBuffer();
}

void Display::drawFaceSleeping() {
  clearBuffer();
  drawFaceClosed(0);
  u8g2.setFont(u8g2_font_6x10_mr);
  u8g2.drawStr(95, 20, "Zzz");
  sendBuffer();
}

void Display::drawMouthClosed() {
  u8g2.drawLine(40, 60, 90, 60);
}

void Display::drawMouthOpen() {
  u8g2.drawRBox(50, 55, 20, 10, 2);
}
