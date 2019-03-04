#include <Arduino.h>
#include <Wire.h>
#include "TempHumid_Si7021.h"

TempHumid_Si7021::TempHumid_Si7021() {
  Serial.begin(9600);
}

double TempHumid_Si7021::measureHumidity(bool bDebug) {
  Wire.beginTransmission(I2C_NUM);      // Open access to sensor
  Wire.write(byte(0xF5));     // Write code to ask for humidit measure (F5)
  uint16_t retVal = Wire.endTransmission();
  if(bDebug) Serial.println((String)"" + F("DEBUG--Humidity Transmit Return Val: ") + (String)retVal);

  delay(125);     // Pause a bit

  Wire.requestFrom(I2C_NUM, 2);     // Request 2 bytes from

  if(Wire.available() >= 2) {
    uint16_t MSB = Wire.read();
    uint16_t LSB = Wire.read();
    uint16_t hVal = (MSB << 8) | LSB;

    double hPct = (((double)125 * (double)hVal) / (double)65536) - (double)6;

    if(bDebug) Serial.println((String)"" + F("DEBUG--Humid Sensor MSB: ") + (String)MSB);
    if(bDebug) Serial.println((String)"" + F("DEBUG--Humid Sensor LSB: ") + (String)LSB);
    if(bDebug) Serial.println((String)"" + F("DEBUG--Humid Sensor Val: ") + (String)hVal);
    if(bDebug) Serial.println((String)"" + F("DEBUG--Relative Humidity: ") + (String)hPct + "%");

    return hPct;
  }
  else {
    if(bDebug) Serial.println(F("DEBUG--Less than 2 bytes available"));

    return -99.0;
  }
}

double TempHumid_Si7021::grabTempCelsius (bool bDebug) {
  Wire.beginTransmission(I2C_NUM);
  Wire.write(byte(0xE0));
  uint16_t retVal = Wire.endTransmission();
  if(bDebug) Serial.println((String)"" + F("DEBUG--Temp Transmit Return Val: ") + (String)retVal);

  delay(125);

  Wire.requestFrom(I2C_NUM, 2);

  if(Wire.available() >= 2) {
    uint16_t MSB = Wire.read();
    uint16_t LSB = Wire.read();
    uint16_t tempVal = (MSB << 8) + LSB;
    if(bDebug) Serial.println((String)"" + F("DEBUG--Temp Sensor Val: ") + (String)tempVal);

    double tCelsius = ((175.72 * (double)tempVal) / (double)65536) - 46.86;

    if(bDebug) Serial.println((String)"" + F("DEBUG--Temp (C): ") + (String)tCelsius);

    return tCelsius;
  }
  else {
    if(bDebug) Serial.println(F("DEBUG--Error: Less than 2 bytes available"));

    return -99.0;
  }
}
