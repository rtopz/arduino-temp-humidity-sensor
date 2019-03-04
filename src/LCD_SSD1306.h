#ifndef LCD_SSD1306_H
#define LCD_SSD1306_H
#include <Arduino.h>
#include <Adafruit_SSD1306_RT.h>

#define BLACK 0
#define WHITE 1
#define INVERSE 2

class LCD_SSD1306 {
  private:
    int textColor;
    int textSize;

  public:
    LCD_SSD1306();
    void initDisplay();
    void setTextSize(int size);
    int getTextSize();
    void setTextColor(int color);
    int getTextColor();
    void writeToDisplay(String text);
    void updateDisplay();
    void clearDisplay(bool reset);
};

#endif
