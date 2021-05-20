#ifndef IP5306_H
#define IP5306_H

#define IP5306_DEFAULT_SETUP    0x37  // set power boost keep on by default

#define IP5306_ADDR             0x75
#define IP5306_REG_SYS_CTL0     0x00  // initialize
#define IP5306_REG_READ0        0x70  // charge en
#define IP5306_REG_READ1        0x71  // charge full
#define IP5306_REG_UNKNOW       0x78  // bat level

class IP5306 {
    public:
        void begin(uint8_t sdaPin, uint8_t sclPin);
        uint8_t writeBytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t quantity);
        uint8_t readBytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t quantity);
        uint8_t setup(uint8_t initPrms = IP5306_DEFAULT_SETUP);
        uint8_t isChargerConnected();
        uint8_t isChargeFull();
        uint8_t getBatteryLevel();
};

#endif