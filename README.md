# Small Class which provides interface to control IP5306 using I2C bus (ESP32, ESP8266, Arduino)

Example
```c
#include "IP5306.h"

ip5306.begin(PIN_I2C_SDA, PIN_I2C_SCL);
ip5306.setup();
//
ip5306.getBatteryLevel();
```
