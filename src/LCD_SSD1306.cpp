#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306_RT.h>
#include "LCD_SSD1306.h"

const int oled_D0 = 8;        // SCL, CLK, SCK
const int oled_D1 = 9;        // SDA, MOSI
const int oled_DC = 11;       // A0
const int oled_CS = 12;
const int oled_RESET = 10;

// Setup Adafruit library with the configured pins
Adafruit_SSD1306 display(oled_D1, oled_D0, oled_DC, oled_RESET, oled_CS);

LCD_SSD1306::LCD_SSD1306() {
  textSize = 1;
  textColor = WHITE;
}

void LCD_SSD1306::initDisplay() {
  //Initialize display & clear the pre-programmed buffer (adafruit logo)
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();

  // Configure the text size & color
  display.setTextSize(textSize);
  display.setTextColor(textColor);
}

void LCD_SSD1306::setTextSize(int size) {
  textSize = size;
  display.setTextSize(textSize);
}

int LCD_SSD1306::getTextSize() {
  return textSize;
}

void LCD_SSD1306::setTextColor(int color) {
  display.setTextColor(textColor);
}

int LCD_SSD1306::getTextColor() {
  return textColor;
}

void LCD_SSD1306::writeToDisplay(String text) {
  display.println(text);
}

void LCD_SSD1306::updateDisplay() {
  display.display();
}

void LCD_SSD1306::clearDisplay(bool reset) {
  // Clear the display buffer and reset the position to first character in first line
  display.clearDisplay();
  if(reset) {
    display.setCursor(0,0);
  }
}
