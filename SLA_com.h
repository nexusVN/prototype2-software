#ifndef SPICOM_H
#define SPICOM_H

#include <SLA_typedef.h>

#define SPI_PATH "/dev/spidev1.0"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

using namespace std;

class printerCom: public QObject
{
    Q_OBJECT

private:
    int fd_spi;
    uint8_t bits;
    uint8_t mode;
    uint32_t speed;

public slots:
    void updateDataPacket();

public:
   printerCom();  // Constructor
   int SpiConfig();
   int SpiTransfer(struct CoordData *transmitData,  uint8_t *receiveData, uint16_t dataLength);
   int SpiTransferDebug(uint8_t *transmitData, uint8_t *receiveData, uint16_t dataLength);

};

extern printerCom spiCom;

#ifdef SLA_DEBUG
    extern uint8_t tx[];
    extern uint8_t rx[];
#endif

#endif // SPICOM_H
