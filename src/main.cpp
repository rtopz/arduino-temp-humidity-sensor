#include <Wire.h>
#include <Arduino.h>
#include "LCD_SSD1306.h"
#include "TempHumid_Si7021.h"

//double measureHumidity(bool debug);
//double grabTempCelsius(bool debug);

long runCount;      // Track how many readings have been taken
int timeCount;      // Track how many seconds to next run
LCD_SSD1306 oled1;      // Object to write to SSD1306 OLED display
TempHumid_Si7021 sensorTH1;     // Object to request Si7021 sensor data
double tempC, tempF, humidPct;      // Store temp & humidty details

void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting Temp & Humidity Monitor"));

  runCount = 0L;          // Set test run amount to 1
  timeCount = 0;      // Set time to run new measurement to 0 to run one immediately
  tempC = -99.0;          // Set the tempC to something
  tempF = 0.0;          // Set the tempF to something
  humidPct = 0.0;       // Set the humidity to something

  Wire.begin();     // Begins I2C support

  oled1.initDisplay();      // Init the SSD1306 OLED display
}

void loop() {
  oled1.setTextSize(2);

  if(timeCount == 9) {
    runCount++;

    Serial.println((String)"" + F("----------Run #") + (String)runCount + F("----------"));
    // Run the humidity measurement with debug enabled or disabled
    humidPct = sensorTH1.measureHumidity(false);
  }

  Serial.println((String)"" + F("--Time Count: ") + (String)timeCount + F("--"));

  // Check humidty measurement did not fail
  if(humidPct != -99.0) {
    Serial.println("Humidity = " + (String)humidPct + F("%"));
    oled1.writeToDisplay((String)humidPct + "%");
  } else {
    Serial.println(F("ERROR: Couldn't get humidity reading"));
    oled1.writeToDisplay(F("H-ERROR"));
  }

  oled1.setTextSize(1);     // Set the text size to 1 to write separators
  oled1.writeToDisplay(F("--------------------"));
  oled1.setTextSize(3);     // Set the text size to 3 to write temperature

  // Note, the call to grab temp only woks if humidity was measured first.
  //  Temp is stored with the humidity measurement so you don't have to
  //  remeasure for temp.
  if(timeCount == 0 && humidPct != -99.0) {
    tempC = sensorTH1.grabTempCelsius(false);
  }

  // Check temperature grab did not fail
  if (tempC != -99.0) {
    tempF = (tempC * 1.8) + (double)32;      // Convert to farenheit
    Serial.println((String)"" + F("Temp = ") + (String)tempF + F("F | ") + (String)tempC + F("C"));
    oled1.writeToDisplay((String)tempF + "F");
  } else {
    Serial.println(F("ERROR: Couldn't get temp reading"));
    oled1.writeToDisplay(F("T-ERROR"));
  }

  oled1.setTextSize(1);
  oled1.writeToDisplay((String)"" + F("Run #: ") + (String)runCount);      // Write run #
  oled1.writeToDisplay((String)"" + F("Retest Time (s): ") + (String)timeCount);     // Write time count down
  oled1.updateDisplay();

  // Count down the time from 10 to 1 and then reset to 10 once it hits 1.  Based on delay, it will
  //  run as a multiple.  Ex: 10 counts x 1 sec delay (rough 1 sec) = 10-11 sec count down
  if(timeCount > 1) {
    timeCount--;
  } else {
    timeCount = 10;
  }

  oled1.clearDisplay(true);     // Clear display buffer and reset cursor position (true)

  delay(1000);
}