#ifndef TempHumid_Si7021_H
#define TempHumid_Si7021_H
#include <Arduino.h>

#define I2C_NUM 64      // 0x40 hex address for Si7021 Sensor

class TempHumid_Si7021 {
  private:

  public:
    TempHumid_Si7021();
    double measureHumidity(bool debug);
    double grabTempCelsius (bool debug);
};

#endif
