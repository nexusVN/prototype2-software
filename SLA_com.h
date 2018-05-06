#ifndef SPICOM_H
#define SPICOM_H

#include <QDataStream>

#define SPI_PATH "/dev/spidev1.0"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

using namespace std;

class printerCom {

private:
    int fd_spi;
    uint8_t bits;
    uint8_t mode;
    uint32_t speed;
public:
   printerCom();  // Constructor
   int SpiConfig();
   int SpiTransfer(struct CoordData *transmitData,  uint8_t *receiveData, uint16_t dataLength);
};

extern printerCom spiCom;
extern uint8_t tx[];
extern uint8_t rx[];

#endif // SPICOM_H
